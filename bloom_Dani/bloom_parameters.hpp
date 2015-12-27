#define maxSize 10000000
#include <cmath>
#include <cstddef>

static const size_t bits_per_char = 0x20; 
static const unsigned int bit_mask[bits_per_char] = {
	0x01,  //00000001
	0x02,  //00000010
	0x04,  //00000100
	0x08,  //00001000
	0x10,  //00010000
	0x20,  //00100000
	0x40,  //01000000
	0x80,   //10000000
	
	0x100, 
	0x200,  
	0x400,  
	0x800,   
	0x1000, 
	0x2000,  
	0x4000,  
	0x8000, 
	
	0x10000, 
	0x20000,  
	0x40000,  
	0x80000, 
	0x100000, 
	0x200000,  
	0x400000,  
	0x800000, 
	
	0x1000000, 
	0x2000000,  
	0x4000000,  
	0x8000000,
	0x10000000, 
	0x20000000,  
	0x40000000,  
	0x80000000
	};

class bloom_parameters{
	public:

	bloom_parameters();
	
	virtual ~bloom_parameters(){}
	
	inline bool usage(){
		return (min_size > max_size)  ||
		(min_hashes > max_hashes) ||
		(min_hashes < 1)     	  ||
		(0 == max_hashes)    	  ||
		(0 == expected_elements)  ||
		(false_positive_p < 0.0)  ||
		(0 == random_seed);
	}
	
	//Allowed min/max size of the bloom filter in bits
	unsigned long long int min_size;
	unsigned long long int max_size;

	//Allowed min/max number of hash functions
	unsigned int min_hashes;
	unsigned int max_hashes;
	
	//The approximate number of elements to be inserted
	unsigned long long int expected_elements;

	//The approximate false positive probability expected.
	//default is the reciprocal of the expected_elements.
	double false_positive_p;

	unsigned long long int random_seed;
	
	
	struct optimal_parameters_t {
      optimal_parameters_t()
      : number_of_hashes(0),
        table_size(0)
      {}

      unsigned int number_of_hashes;
      unsigned long long int table_size;
   };

   optimal_parameters_t optimal_parameters;

   virtual bool compute_optimal_parameters() {
      if (!(*this).usage())
         return false;

      double min_m = maxSize;
      double min_k = 0.0;
      double curr_m = 0.0;
      double k = 1.0;

      while (k < 1000.0) {
         double numerator   = (- k * expected_elements);
         double denominator = log(1.0 - pow(false_positive_p, 1.0 / k));
         curr_m = numerator / denominator;
         if (curr_m < min_m)
         {
            min_m = curr_m;
            min_k = k;
         }
         k += 1.0;
      }

      optimal_parameters_t& optp = optimal_parameters;

      optp.number_of_hashes = static_cast<unsigned int>(min_k);
      optp.table_size = static_cast<unsigned long long int>(min_m);
      optp.table_size += (((optp.table_size % bits_per_char) != 0) ? (bits_per_char - (optp.table_size % bits_per_char)) : 0);

      if (optp.number_of_hashes < min_hashes)
         optp.number_of_hashes = min_hashes;
      else if (optp.number_of_hashes > max_hashes)
         optp.number_of_hashes = max_hashes;

      if (optp.table_size < min_size)
         optp.table_size = min_size;
      else if (optp.table_size > max_size)
         optp.table_size = max_size;

      return true;
   }
	
};
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	