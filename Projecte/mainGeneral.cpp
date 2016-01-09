//
//  mainGeneral.cpp
//  
//
//  Created by Ferran coma rosell on 29/12/15.
//
//

#include <iostream>
#include <fstream>
#include <cstdio>
#include <ctime>
#include "hash/Hash.hpp"
#include "cercabinaria/CercaBinaria.hpp"
#include "bloom/bloom_filter.hpp"

using namespace std;


inline void print_capcalera(){
    cout << " ;---------------------------------------;" <<endl;
    cout << " ;                                       ;" <<endl;
    cout << " ;           MAIN - ALGORISMIA           ;" <<endl;
    cout << " ;            Comprovacio de             ;" <<endl;
    cout << " ;           temps de procesat           ;" <<endl;
    cout << " ;                                       ;" <<endl;
    cout << " ;---------------------------------------;" <<endl;
}


int main(){
    print_capcalera();
    cout << endl;
    clock_t start;
    double duration;
	vector<unsigned int> keys_diccionario;
	vector<unsigned int> valores_texto;
    
	/////////////////////////////////////////////////////
	///////BUCLE PARA COMPROBAR LOS JUEGOS DE PRUEBAS
	/////////////////////////////////////////////////////
	unsigned int numTests;
	vector<string> diccionarios;
	vector<string> textos;
	cin >> numTests;
	unsigned int aux;
	string aux2;
	for (unsigned int i = 0; i < numTests; i++){
		cin >> aux;
		aux2 = aux + ".txt";
		diccionarios.push_back("dic" + aux2);
		textos.push_back("text" + aux2);
	}
	
	for (unsigned int i = 0; i < numTests; i++){
		aux2 = "jocdeprobes/" + diccionarios[i];
		unsigned int ii = i;
		//arxiu d'entrada
		ifstream arxiu(aux2.c_str());// jp1.txt);
		int temanyDadesArxiu1;
		arxiu >> temanyDadesArxiu1;
		unsigned int buffer;
		while (arxiu >>buffer) keys_diccionario.push_back(buffer);
		
		//////////////////////////////////
		//////////////TESTS//////////////
		/////////////////////////////////
		
		cout << endl;
		cout << "Test amb " << temanyDadesArxiu1 << " dades en el diccionari" << endl;
		cout << endl;
		
		cout << "Insercio de hash..." << endl;
		//omplir taula de hash
		taula_hash hash(2*temanyDadesArxiu1);
		
		
		start = clock();
		for (unsigned int i = 0; i < keys_diccionario.size(); i++) 
			hash.insertKey(keys_diccionario[i]);

		duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
		
		cout << "Insercio de hash completada" << endl;
		cout << "Temps d'insercio: " << duration <<endl;
		cout << endl;
		
		
		
		
		//omplir filtre de bloom
		//////////////
		cout << "Insercio de la taula de bits del filtre de bloom..." << endl;
		const double expected_fpp = 1.0 / keys_diccionario.size();
		unsigned int random_seed = 0;
		bloom_parameters parameters(keys_diccionario.size(), expected_fpp, ++random_seed); //iniciar parametros
		bloom_filter filter(parameters); //iniciar filtro con parametros optimos
		
		start = clock();
		
		filter.insert(keys_diccionario.begin(),keys_diccionario.end()); //insertar lista de palabras
		
		duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;

		cout << "Insercio completada" << endl;
		cout << "Temps d'insercio: " << duration <<endl;
		cout << endl;
		
		
		/////////////////////////////////////
		//omplim vetor cerca binaria
		cout << "Insercio del vector de cerca binaria..." << endl;
		start = clock();
		
		CercaBinaria cb(keys_diccionario);
		

		duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;

		cout << "Insercio al vector de cerca binaria completada" << endl;
		cout << "Temps d'insercio: " << duration <<endl;
		cout << endl;
		
		
		arxiu.close();
		
		
		
		
		
		
		
			cout << endl << endl <<
				" ;---------------------------------------;" <<endl;
		cout << " ;          Prueba de contains           ;" <<endl;
		cout << " ;---------------------------------------;" <<endl << endl;
		
		//arxiu d'entrada2
		aux2 = "jocdeprobes/" + textos[ii];
		ifstream arxiuTexto(aux2.c_str());//jp2.txt");
		while (arxiuTexto >>buffer) valores_texto.push_back(buffer);
		
		int trobats = 0, fallats = 0;
		
		
		
		//comprvar elements hash
		cout << "Comprovacio de hash..." << endl;
		start = clock();
		for (unsigned int i = 0; i < valores_texto.size(); i++) {
			if (hash.getKey(valores_texto[i])) trobats++;
			else fallats++;
		}
		duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
		
		cout << "Comprovacio de hash completada" << endl;
		cout << "-------------------------------------------" << endl;
		cout << "Temps d'acces: " << duration <<endl;
		cout << "Encerts: " << trobats << endl;
		cout << "Fallats: " << fallats << endl;
		cout << "Comprovacions relitzades totals: " << hash.getComprovacions() << endl;
		cout << "-------------------------------------------" << endl;
		cout << endl << endl;
		
		

		//BLOOOOOM
		trobats = 0, fallats = 0;
		
		//comprvar elements filtre bloom
		cout << "Comprovacio del filtre de bloom..." << endl;
		start = clock();
		trobats = filter.contains(valores_texto.begin(), valores_texto.end());
		fallats = valores_texto.size() - trobats;
		duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
		
		cout << "Comprovacio de bloom completada" << endl;
		cout << "-------------------------------------------" << endl;
		cout << "Temps d'acces: " << duration <<endl;
		cout << "Encerts: " << trobats << endl;
		cout << "Fallats: " << fallats << endl;
		cout << "Comprovacions relitzades totals: " << filter.comprobaciones(valores_texto.size()) << endl;
		///////////////////
		//HE DE COMPROBAR EL NUMERO DE COMPROBACIONES K HAGO
		/////////////////////////
		cout << "-------------------------------------------" << endl;
		cout << endl << endl;
		
		
		
		
		//reset arxiu entrada2
		arxiuTexto.close();
		
		trobats = 0, fallats = 0;
		
		//comprvar elements cerca binaria
		cout << "Comprovacio de cerca binaria..." << endl;
		start = clock();
		for (unsigned int i = 0; i < valores_texto.size(); i++) {
			if (cb.existeix(valores_texto[i])) trobats++;
			else fallats++;
		}

		duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
		
		cout << "Comprovacio de cerca binaria completada" << endl;
		cout << "-------------------------------------------" << endl;
		cout << "Temps d'acces: " << duration <<endl;
		cout << "Encerts: " << trobats << endl;
		cout << "Fallats: " << fallats << endl;
		cout << "Comprovacions relitzades totals: " << cb.getComprovacions() << endl;
		cout << "-------------------------------------------" << endl;
		cout << endl;

		cout << "-------------------------------------------" << endl;
		cout << endl;
		cout << "-------------------------------------------" << endl;
		cout << endl << endl;
	}
    
}


