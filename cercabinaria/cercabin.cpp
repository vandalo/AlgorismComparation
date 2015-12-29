#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int binary_search(const vector<int>& v, int x, int esq, int dre){

	if(esq > dre) return -1;

	int mid = (esq+dre) / 2;

	if(v[mid] == x) return mid;
	else if(v[mid] < x) return binary_search(v,x,mid+1, dre);
	else return binary_search(v,x,esq,dre-1);
}



int main(){

	int n,x,count = 0;
	

	//leer num. palabras diccionario
	cin >> n;

	vector<int> v(n);
	//leer diccionario
	for(int i =0; i < n; ++i) cin >> v[i];


	//ordenar diccionario
	sort(v.begin(), v.end());

	//leer num palabras texto
	cin >> n;

	//leer texto
	for(int i =0; i < n; ++i){
		cin >> x;
		if(binary_search(v,x,0,v.size()-1) > -1) count++;
	}

	cout << "nombre de paraules trobades en el diccionari " << count  << endl;
	


}