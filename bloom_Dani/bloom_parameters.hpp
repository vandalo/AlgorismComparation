#define maxSize 10000000 //10.000.000
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iterator>
#include <limits>
#include <string>
#include <vector>
using namespace std;

static const size_t bits_per_char = 0x08;    // 8 bits in 1 char(unsigned)
static const unsigned char bit_mask[bits_per_char] = {
	0x01,  //00000001
	0x02,  //00000010
	0x04,  //00000100
	0x08,  //00001000
	0x10,  //00010000
	0x20,  //00100000
	0x40,  //01000000
	0x80   //10000000
	};

class bloom_parameters {
public:
	bloom_parameters(unsigned long long int expected_elements, double false_positive_p, unsigned long long int random_seed);

	//Struct para guardar los parametros optimos
	struct optimos {
		optimos() : number_of_hashes(0),
			table_size(0) {}
		unsigned int number_of_hashes;
		unsigned long long int table_size;
	} opt_par;
	
	unsigned long long int min_size;
	unsigned long long int max_size;
	unsigned int min_hashes;
	unsigned int max_hashes;
	unsigned long long int expected_elements;
	double false_positive_p;
	unsigned long long int random_seed;
	
protected:
	virtual bool calcular_optimos();
};
	
	
	
	
	

	