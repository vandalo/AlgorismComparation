#include <iostream>
#include <string>

#include "bloom_filter.hpp"
using namespace std;


int main() {

   bloom_parameters parameters;

   // expected elements to insert
   parameters.expected_elements = 1000;

   // Maximum tolerable false positive probability (0,1)
   parameters.false_positive_p = 0.0001; // 1 in 10000

   // Simple randomizer (optional)
   parameters.random_seed = 0xA5A5A5A5;

   if (parameters.usage()) {
      cout << "Error - Parametros mal inicializados!" << endl;
      return 1;
   }

   parameters.compute_optimal_parameters();
   //Instantiate Bloom Filter
   bloom_filter filter(parameters);
   string str_list[] = { "AbC", "iJk", "XYZ" };
cout <<"pta mierda4" << endl;
   // Insert into Bloom Filter
	// Insert some strings
/*	for (size_t i = 0; i < (sizeof(str_list) / sizeof(string)); ++i){
		filter.insert(str_list[i]);
	}
*/
	// Insert some numbers
	for (size_t i = 0; i < 100; ++i){
		filter.insert(i);
	}
cout <<"pta mierda3" << endl;
	// Query Bloom Filter
	// Query the existence of strings
	for (size_t i = 0; i < (sizeof(str_list) / sizeof(string)); ++i){
		if (filter.contains(str_list[i])){
		cout << "BF contains: " << str_list[i] << endl;
		}
	}

	// Query the existence of numbers
	for (size_t i = 100; i < 120; ++i){
		if (filter.contains(i)){
		cout << "BF contains: " << i << endl;
		}
	}

   return 0;
}









