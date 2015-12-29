//
//  mainGeneral.cpp
//  
//
//  Created by Ferran coma rosell on 29/12/15.
//
//

#include <iostream>
#include <fstream>
#include "hash/Hash.hpp"
#include "cercabinaria/CercaBinaria.hpp"

using namespace std;

int main(){
    //arxiu d'entrada
    ifstream arxiu("jocdeprobes/jp1.txt");
    int temanyDadesArxiu1;
    arxiu >> temanyDadesArxiu1;
    cout << temanyDadesArxiu1 << endl;
    
    //omplir taula de hash
    taula_hash hash(temanyDadesArxiu1);
    while(!arxiu.eof()){
        int aux;
        arxiu >> aux;
        hash.insertKey(aux);
    }
    cout << "taula de hash completa" << endl;
    
    //omplir filtre de bloom
    
    //omplim vetor cerca binaria
    
    //comprvar elements hash
    

    
}
