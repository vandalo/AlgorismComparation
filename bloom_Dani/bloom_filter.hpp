#include "bloom_parameters.hpp"
using namespace std;

class bloom_filter {
protected:

	typedef unsigned int bloom_type;
	typedef unsigned char cell_type;

public:

	bloom_filter(const bloom_parameters& p);


	virtual ~bloom_filter() {
		delete[] bit_table_;
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

	
	////////
	

	template<typename InputIterator>
	inline void insert(const InputIterator begin, const InputIterator end) {
		InputIterator itr = begin;
		while (end != itr) {
			insert(*(itr++));
		}
	}
   
   
   
	template<typename InputIterator>
	inline InputIterator contains_all(const InputIterator begin, const InputIterator end) const {
		InputIterator itr = begin;
		while (end != itr) {
			if (!contains(*itr)) {
				return itr;
			} ++itr;
		} return end;
	}
	
	///////////////
	
	

	inline virtual bool contains(const unsigned char* key_begin, const size_t length) const {
		size_t bit_index = 0;
		size_t bit = 0;
		for (size_t i = 0; i < salt_.size(); ++i) {
			compute_indices(hash_ap(key_begin,length,salt_[i]),bit_index,bit);
			if ((bit_table_[bit_index / bits_per_char] & bit_mask[bit]) != bit_mask[bit]) {
				return false;
			}
		}
		return true;
	}

	template<typename T>
	inline bool contains(const T& t) const {
		return contains(reinterpret_cast<const unsigned char*>(&t),static_cast<size_t>(sizeof(T)));
	}

	

	inline virtual unsigned long long int size() const {
		return table_size_;
	}


	inline double effective_fpp() const {
		return pow(1.0 - exp(-1.0 * salt_.size() * inserted_elements / size()), 1.0 * salt_.size());
	}



	protected:
	inline virtual void compute_indices(const bloom_type& hash, size_t& bit_index, size_t& bit) const {
		bit_index = hash % table_size_;
		bit = bit_index % bits_per_char;
	}

	void generate_unique_salt(); 
	

	inline bloom_type hash_ap(const unsigned char* begin, size_t remaining_length, bloom_type hash) const {
		const unsigned char* itr = begin;
		unsigned int loop = 0;
		while (remaining_length >= 8) {
			const unsigned int& i1 = *(reinterpret_cast<const unsigned int*>(itr)); itr += sizeof(unsigned int);
			const unsigned int& i2 = *(reinterpret_cast<const unsigned int*>(itr)); itr += sizeof(unsigned int);
			hash ^= (hash <<  7) ^  i1 * (hash >> 3) ^ (~((hash << 11) + (i2 ^ (hash >> 5))));
			remaining_length -= 8;
		}
		if (remaining_length) {
			if (remaining_length >= 4)  {
				const unsigned int& i = *(reinterpret_cast<const unsigned int*>(itr));
				if (loop & 0x01) hash ^=    (hash <<  7) ^  i * (hash >> 3);
				else hash ^= (~((hash << 11) + (i ^ (hash >> 5))));
				++loop;
				remaining_length -= 4;
				itr += sizeof(unsigned int);
			}
			if (remaining_length >= 2) {
				const unsigned short& i = *(reinterpret_cast<const unsigned short*>(itr));
				if (loop & 0x01)
				hash ^=    (hash <<  7) ^  i * (hash >> 3);
				else
				hash ^= (~((hash << 11) + (i ^ (hash >> 5))));
				++loop;
				remaining_length -= 2;
				itr += sizeof(unsigned short);
			}
			if (remaining_length) {
				hash += ((*itr) ^ (hash * 0xA5A5A5A5)) + loop;
			}
		}
		return hash;
	}

	vector<bloom_type> salt_;
	unsigned char*          bit_table_;
	unsigned int            salt_count_;
	unsigned long long int  table_size_;
	unsigned long long int  raw_table_size_;
	unsigned long long int  expected_elements_;
	unsigned int            inserted_elements;
	unsigned long long int  random_seed_;
	double                  desired_false_positive_p_;
};



