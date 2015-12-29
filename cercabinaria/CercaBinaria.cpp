#include "CercaBinaria.hpp"


int CercaBinaria::binary_search(const vector<int>& v, int x, int esq, int dre){

	if(esq > dre) return -1;

	int mid = (esq+dre) / 2;

	if(v[mid] == x) return mid;
	else if(v[mid] < x) return binary_search(v,x,mid+1, dre);
	else return binary_search(v,x,esq,dre-1);
}

CercaBinaria::CercaBinaria(const char* path){
	arxiu_diccionari.open(path);
	int n;
	arxiu_diccionari >> n;
	diccionari = vector<int>(n);
	for(int i=0; i < n; ++i) arxiu_diccionari >> diccionari[i];
	sort(diccionari.begin(), diccionari.end());
	arxiu_diccionari.close();
}

bool CercaBinaria::existeix(int n){
	return binary_search(this->diccionari, n, 0, (this->diccionari).size()) != -1;

}

