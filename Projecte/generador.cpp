//
//  main.cpp
//  PracticaAlgorismiaGeneradorArxius
//
//  Created by Ferran coma rosell on 5/12/15.
//  Copyright © 2015 Ferran coma rosell. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <fstream>
using namespace std;
int M = 34234;


int abs(int x){
    int res = x;
    if (x < 0)res = x*-1;
    return res;
}

int main() {
    
    //Recopilacio de dades
    int semilla, n, n2;
    cout<< "Introdueix una llabor: ";
    cin >> semilla;
    cout << "Introdueix el numero de Keys que vols tenir"<<endl<< "(Num. de Valors per el fitxer 1): ";
    cin >> n;
    cout << "Introdueix quants valors vols per cada Key, 'N'"<<endl<< "(Num. de Valors per el fitxer 1 * N:)"<<endl;
    cin >> n2;
    int numero = 0;
    
    //Generador de dades
    ofstream arxiu;
    arxiu.open("arxiu2.txt");
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n2; ++j){
            time_t var_time = time(0);
            numero *= var_time;
            numero += M % semilla;
            arxiu << abs(numero) << endl;
        }
    }
    arxiu.close();
    arxiu.open("arxiu1.txt");
    for(int i = 0; i < n; ++i){
        time_t var_time = time(0);
        numero *= var_time;
        numero += M % semilla;
        arxiu << abs(numero) << endl;
    }
    arxiu.close();
}
