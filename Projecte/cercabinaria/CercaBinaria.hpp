#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;



class CercaBinaria {

	private:
		vector<int> diccionari;
		ifstream arxiu_diccionari;
        int num_comprovacions;
		int binary_search(const vector<int>& v, int x, int esq, int dre);

	public:

		CercaBinaria(const char* path);
        int getComprovacions();
		bool existeix(int num);

};