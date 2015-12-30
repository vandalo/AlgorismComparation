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

using namespace std;


void print_capcalera(){
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

    
    //arxiu d'entrada
    ifstream arxiu("jocdeprobes/jp1.txt");
    int temanyDadesArxiu1;
    arxiu >> temanyDadesArxiu1;
    
    cout << endl;
    cout << "Test amb " << temanyDadesArxiu1 << " dades en el diccionari" << endl;
    cout << endl;
    
    cout << "Insercio de hash..." << endl;
    //omplir taula de hash
    taula_hash hash(temanyDadesArxiu1);
    start = clock();
    while(!arxiu.eof()){
        int aux;
        arxiu >> aux;
        hash.insertKey(aux);
    }
    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
    
    cout << "Insercio de hash completada" << endl;
    cout << "Temps d'insercio: " << duration <<endl;
    cout << endl;
    
    //omplir filtre de bloom
    
    //omplim vetor cerca binaria
    cout << "Insercio del vector de cerca binaria..." << endl;
    start = clock();
    
    CercaBinaria cb("jocdeprobes/jp1.txt");
    

    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;

    cout << "Insercio al vector de cerca binaria completada" << endl;
    cout << "Temps d'insercio: " << duration <<endl;
    cout << endl;
    
    
    arxiu.close();
    
    //arxiu d'entrada2
    ifstream arxiu2("jocdeprobes/jp2.txt");
    int trobats = 0, fallats = 0;
    
    //comprvar elements hash
    cout << "Comprovacio de hash..." << endl;
    start = clock();
    while(!arxiu2.eof()){
        int aux;
        arxiu2 >> aux;
        if(hash.getKey(aux))trobats++;
        else fallats ++;
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
    
    //reset arxiu entrada2
    arxiu2.close();
    ifstream arxiu3("jocdeprobes/jp2.txt");
    trobats = 0, fallats = 0;
    
    //comprvar elements cerca binaria
    cout << "Comprovacio de cerca binaria..." << endl;
    start = clock();
    while(!arxiu3.eof()){
        int aux;
        arxiu3 >> aux;
        if(cb.existeix(aux))trobats++;
        else fallats ++;
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
    
}


