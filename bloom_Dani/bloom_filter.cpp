#include <iostream>
#include <string>

#include "bloom_filter.hpp"
using namespace std;


bloom_filter::bloom_filter(const bloom_parameters& p):bit_table_(0),
	expected_elements(p.expected_elements),
	inserted_elements(0),
	random_seed_((p.random_seed * 0xA5A5A5A5) + 1),
	desired_false_positive_probability_(p.false_positive_p) {
		salt_count_ = p.optimal_parameters.number_of_hashes;
		table_size_ = p.optimal_parameters.table_size;
		cout <<"pta mierda" << endl;
		generate_unique_salt();
		cout <<"pta mierda2" << endl;
		raw_table_size_ = table_size_ / bits_per_char;
		bit_table_ = new cell_type[static_cast<size_t>(raw_table_size_)];
		fill_n(bit_table_,raw_table_size_,0x00);
	}
	
	bloom_filter::~bloom_filter(){
      delete[] bit_table_;
   }





