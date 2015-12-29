#include "bloom_parameters.hpp"
#include <iostream>
using namespace std;

class bloom_filter {

public:
	bloom_filter(const bloom_parameters& p);

		//FUNCIONES PARA INSERIR Y COMPROBAR EXISTENCIA DE LAS PALABRAS
	inline void insert(const unsigned int key_begin, const unsigned int& length) {
		//unsigned int bit_index = 0;
		//unsigned int bit = 0;
		cout << key_begin << length << endl;
		for (unsigned int i = 0; i < hash_values.size(); ++i) {
			
			//compute_indices(hash_ap(key_begin,length,hash_vec[i]),bit_index,bit);
			//bit_table_[bit_index / bits_per_char] |= bit_mask[bit];
		}
		++inserted_elements;
	}
	

	template<typename Iterator>
	inline void insert(const Iterator begin, const Iterator end) {
		Iterator itr = begin;
		while (end != itr) insert(*(itr++), 1);
	}
	

	inline virtual bool contains(const unsigned int key_begin, const unsigned int length) const {
		//unsigned int bit_index = 0;
		//unsigned int bit = 0;
		cout << key_begin << length << endl;
		for (unsigned int i = 0; i < hash_values.size(); ++i) {
			//compute_indices(hash_ap(key_begin,length,hash_vec[i]),bit_index,bit);
			//if ((bit_table_[bit_index / bits_per_char] & bit_mask[bit]) != bit_mask[bit]) 
				//return false;
		}
		return true;
	}
	
	template<typename InputIterator>
	inline unsigned int contains(const InputIterator begin, const InputIterator end) {
		unsigned int cont = 0;
		InputIterator itr = begin;
		while (end != itr) if(contains(*(itr++), 1)) cont++;
		return cont;
	}
	
	

	inline virtual unsigned long long int size() const {
		return table_size;
	}


protected:
	
	//FUNCIONES DEL ALGORITMO PARA DETERMINAR QUE BITS ESTAN
	//A 1 O A 0 Y PARA SETEAR LOS BITS EN CASO DE INSERT
	//O COMPROBARLOS EN CASO DE CONTAINS
	vector<unsigned int> hash_values;
	char *bit_table;
	unsigned int numHashes;
	unsigned long long int table_size;
	unsigned int inserted_elements;
	unsigned long long int random_seed;
	double falsepp;
};


//return pow(1.0 - exp(-1.0 * salt_.size() * inserted_elements / size()), 1.0 * salt_.size());
//reinterpret_cast<const unsigned int*>(itr)