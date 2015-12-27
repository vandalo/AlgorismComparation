#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iterator>
#include <string>
#include <vector>
#include <iostream>
#include "bloom_parameters.hpp"
using namespace std;

class bloom_filter{
public:
	 bloom_filter(const bloom_parameters& p);
	 
	 virtual ~bloom_filter();
	 
	inline void clear() {
		fill_n(bit_table_,raw_table_size_,0x00);//resetear tabla
		inserted_elements = 0;//reset num de elementos inseridos
	}
	
	
	inline void insert(const unsigned char* key_begin, const size_t& length) {
		size_t bit_index = 0;
		size_t bit = 0;
		for (size_t i = 0; i < salt_.size(); ++i) {
			compute_indices(hash_ap(key_begin,length,salt_[i]),bit_index,bit);
			bit_table_[bit_index / bits_per_char] |= bit_mask[bit];
		}
		++inserted_elements;
	}

	template<typename T>
	inline void insert(const T& t) {
		insert(reinterpret_cast<const unsigned char*>(&t),sizeof(T));
	}
	
	
	inline bool operator == (const bloom_filter& f) const {
      if (this != &f) {
         return
            (salt_count_                         == f.salt_count_)                         &&
            (table_size_                         == f.table_size_)                         &&
            (raw_table_size_                     == f.raw_table_size_)                     &&
            (expected_elements            == f.expected_elements)            &&
            (inserted_elements             == f.inserted_elements)             &&
            (random_seed_                        == f.random_seed_)                        &&
            (desired_false_positive_probability_ == f.desired_false_positive_probability_) &&
            (salt_                               == f.salt_)                               &&
            equal(f.bit_table_,f.bit_table_ + raw_table_size_,bit_table_);
      }
      else
         return true;
   }

   
   inline bool operator != (const bloom_filter& f) const {
      return !operator==(f);
   }

   
   inline bloom_filter& operator = (const bloom_filter& f) {
      if (this != &f) {
         salt_count_ = f.salt_count_;
         table_size_ = f.table_size_;
         raw_table_size_ = f.raw_table_size_;
         expected_elements = f.expected_elements;
         inserted_elements = f.inserted_elements;
         random_seed_ = f.random_seed_;
         desired_false_positive_probability_ = f.desired_false_positive_probability_;
         delete[] bit_table_;
         bit_table_ = new cell_type[static_cast<size_t>(raw_table_size_)];
         copy(f.bit_table_,f.bit_table_ + raw_table_size_,bit_table_);
         salt_ = f.salt_;
      }
      return *this;
   }
   

   inline bool operator!() const {
      return (0 == table_size_);
   }
	
	
	inline virtual bool contains(const unsigned char* key_begin, const size_t length) const {
		size_t bit_index = 0;
		size_t bit = 0;
		cout << "pero esta mierda entra aki o k?" << endl;
		for (size_t i = 0; i < salt_.size(); ++i) {
			compute_indices(hash_ap(key_begin,length,salt_[i]),bit_index,bit);
			cout << "mm: " << bit_table_[bit_index / bits_per_char] << " . " << bit_mask[bit] << " -- " << endl;
			if ((bit_table_[bit_index / bits_per_char] & bit_mask[bit]) != bit_mask[bit]) {
				cout << "tu puta madre" << endl;
				return false;
			}
		}
		return true;
	}

	
   template<typename T>
   inline bool contains(const T& t) const {
		return contains(reinterpret_cast<const unsigned char*>(&t),static_cast<size_t>(sizeof(T)));
	}

	
protected:
	typedef unsigned int bloom_type;
	typedef unsigned char cell_type;
	vector<bloom_type> salt_;
	unsigned char*          bit_table_;
	unsigned int            salt_count_;
	unsigned long long int  table_size_;
	unsigned long long int  raw_table_size_;
	unsigned long long int  expected_elements;
	unsigned int            inserted_elements;
	unsigned long long int  random_seed_;
	double                  desired_false_positive_probability_;
	
	inline virtual void compute_indices(const bloom_type& hash, size_t& bit_index, size_t& bit) const
   {
      bit_index = hash % table_size_;
      bit = bit_index % bits_per_char;
   }

   void generate_unique_salt()
   {
      /*
        Note:
        A distinct hash function need not be implementation-wise
        distinct. In the current implementation "seeding" a common
        hash function with different values seems to be adequate.
      */
      const unsigned int predef_salt_count = 128;
      static const bloom_type predef_salt[predef_salt_count] =
                                 {
                                    0xAAAAAAAA, 0x55555555, 0x33333333, 0xCCCCCCCC,
                                    0x66666666, 0x99999999, 0xB5B5B5B5, 0x4B4B4B4B,
                                    0xAA55AA55, 0x55335533, 0x33CC33CC, 0xCC66CC66,
                                    0x66996699, 0x99B599B5, 0xB54BB54B, 0x4BAA4BAA,
                                    0xAA33AA33, 0x55CC55CC, 0x33663366, 0xCC99CC99,
                                    0x66B566B5, 0x994B994B, 0xB5AAB5AA, 0xAAAAAA33,
                                    0x555555CC, 0x33333366, 0xCCCCCC99, 0x666666B5,
                                    0x9999994B, 0xB5B5B5AA, 0xFFFFFFFF, 0xFFFF0000,
                                    0xB823D5EB, 0xC1191CDF, 0xF623AEB3, 0xDB58499F,
                                    0xC8D42E70, 0xB173F616, 0xA91A5967, 0xDA427D63,
                                    0xB1E8A2EA, 0xF6C0D155, 0x4909FEA3, 0xA68CC6A7,
                                    0xC395E782, 0xA26057EB, 0x0CD5DA28, 0x467C5492,
                                    0xF15E6982, 0x61C6FAD3, 0x9615E352, 0x6E9E355A,
                                    0x689B563E, 0x0C9831A8, 0x6753C18B, 0xA622689B,
                                    0x8CA63C47, 0x42CC2884, 0x8E89919B, 0x6EDBD7D3,
                                    0x15B6796C, 0x1D6FDFE4, 0x63FF9092, 0xE7401432,
                                    0xEFFE9412, 0xAEAEDF79, 0x9F245A31, 0x83C136FC,
                                    0xC3DA4A8C, 0xA5112C8C, 0x5271F491, 0x9A948DAB,
                                    0xCEE59A8D, 0xB5F525AB, 0x59D13217, 0x24E7C331,
                                    0x697C2103, 0x84B0A460, 0x86156DA9, 0xAEF2AC68,
                                    0x23243DA5, 0x3F649643, 0x5FA495A8, 0x67710DF8,
                                    0x9A6C499E, 0xDCFB0227, 0x46A43433, 0x1832B07A,
                                    0xC46AFF3C, 0xB9C8FFF0, 0xC9500467, 0x34431BDF,
                                    0xB652432B, 0xE367F12B, 0x427F4C1B, 0x224C006E,
                                    0x2E7E5A89, 0x96F99AA5, 0x0BEB452A, 0x2FD87C39,
                                    0x74B2E1FB, 0x222EFD24, 0xF357F60C, 0x440FCB1E,
                                    0x8BBE030F, 0x6704DC29, 0x1144D12F, 0x948B1355,
                                    0x6D8FD7E9, 0x1C11A014, 0xADD1592F, 0xFB3C712E,
                                    0xFC77642F, 0xF9C4CE8C, 0x31312FB9, 0x08B0DD79,
                                    0x318FA6E7, 0xC040D23D, 0xC0589AA7, 0x0CA5C075,
                                    0xF874B172, 0x0CF914D5, 0x784D3280, 0x4E8CFEBC,
                                    0xC569F575, 0xCDB2A091, 0x2CC016B4, 0x5C5F4421
                                 };

      if (salt_count_ <= predef_salt_count)
      {
         copy(predef_salt,
                   predef_salt + salt_count_,
                   back_inserter(salt_));
          for (unsigned int i = 0; i < salt_.size(); ++i)
          {
            /*
              Note:
              This is done to integrate the user defined random seed,
              so as to allow for the generation of unique bloom filter
              instances.
            */
            salt_[i] = salt_[i] * salt_[(i + 3) % salt_.size()] + static_cast<bloom_type>(random_seed_);
          }
      }
      else
      {
         copy(predef_salt,predef_salt + predef_salt_count,back_inserter(salt_));
         srand(static_cast<unsigned int>(random_seed_));
         while (salt_.size() < salt_count_)
         {
            bloom_type current_salt = static_cast<bloom_type>(rand()) * static_cast<bloom_type>(rand());
            if (0 == current_salt) continue;
            if (salt_.end() == find(salt_.begin(), salt_.end(), current_salt))
            {
               salt_.push_back(current_salt);
            }
         }
      }
   }

   inline bloom_type hash_ap(const unsigned char* begin, size_t remaining_length, bloom_type hash) const
   {
      const unsigned char* itr = begin;
      unsigned int loop = 0;
      while (remaining_length >= 8)
      {
         const unsigned int& i1 = *(reinterpret_cast<const unsigned int*>(itr)); itr += sizeof(unsigned int);
         const unsigned int& i2 = *(reinterpret_cast<const unsigned int*>(itr)); itr += sizeof(unsigned int);
         hash ^= (hash <<  7) ^  i1 * (hash >> 3) ^
              (~((hash << 11) + (i2 ^ (hash >> 5))));
         remaining_length -= 8;
      }
      if (remaining_length)
      {
         if (remaining_length >= 4)
         {
            const unsigned int& i = *(reinterpret_cast<const unsigned int*>(itr));
            if (loop & 0x01)
               hash ^=    (hash <<  7) ^  i * (hash >> 3);
            else
               hash ^= (~((hash << 11) + (i ^ (hash >> 5))));
            ++loop;
            remaining_length -= 4;
            itr += sizeof(unsigned int);
         }
         if (remaining_length >= 2)
         {
            const unsigned short& i = *(reinterpret_cast<const unsigned short*>(itr));
            if (loop & 0x01)
               hash ^=    (hash <<  7) ^  i * (hash >> 3);
            else
               hash ^= (~((hash << 11) + (i ^ (hash >> 5))));
            ++loop;
            remaining_length -= 2;
            itr += sizeof(unsigned short);
         }
         if (remaining_length)
         {
            hash += ((*itr) ^ (hash * 0xA5A5A5A5)) + loop;
         }
      }
      return hash;
   }
	 
};
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	