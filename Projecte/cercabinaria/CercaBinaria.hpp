#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;



class CercaBinaria {

	private:
		vector<int> diccionari;
		ifstream arxiu_diccionari;

		int binary_search(const vector<int>& v, int x, int esq, int dre);

	public:

		CercaBinaria(const char* path);

		bool existeix(int num);

};