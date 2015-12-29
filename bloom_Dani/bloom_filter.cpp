#include "bloom_filter.hpp"
using namespace std;


bloom_filter::bloom_filter(const bloom_parameters& p): random_seed((p.random_seed * 0xA5A5A5A5) + 1),
		falsepp(p.false_positive_p) {
			numHashes = p.optimos.num_hashes;
			table_size = p.optimos.table_size;
			bit_table = new char[table_size];
			fill_n(bit_table,table_size,0);
		}



