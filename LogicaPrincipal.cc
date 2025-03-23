#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <type_traits>

#include "LogicaPrincipal.hh"

#include <map>
#include <vector>
#include <list>
#include <queue>
#include <set>

using namespace std;

// Devuelve si dos nodos se estan tocando (si no encuentra los nodos devuelve false)
// s1 = nombre del nodo uno
// s2 = nombre del nodo dos
// matrizAdyacencias = una matriz con las adyacencias respectivamente 
// hashMapStringToInt = un mapa que relaciona los numeros con los que trabajan la matriz y el nombre de los nodos
bool dosNodosSeTocan(string s1, string s2, vector<vector<bool>> &matrizAdyacencias, map<string, int> &hashMapStringToInt) {
    if (hashMapStringToInt.count(s1) && hashMapStringToInt.count(s2)) return matrizAdyacencias[hashMapStringToInt.at(s1)][hashMapStringToInt.at(s2)];
    return false;
}

// Escribe todas las adyacencias de un nodo
// s = nombre del nodo 
// matrizAdyacencias = una matriz con las adyacencias respectivamente 
// hashMapStringToInt = un mapa que relaciona los numeros con los que trabajan la matriz y el nombre de los nodos
// hashMapIntToString = un mapa que relaciona los nodos y los numeros con los que trabajan la matriz
void printAdyacencias(string s, vector<vector<bool>> &matrizAdyacencias, map<string, int> &hashMapStringToInt, map<int, string> &hashMapIntToString) {
    if (hashMapStringToInt.count(s)) {
        int i = hashMapStringToInt.at(s);
        cout << s;
        for (int j = 0; j < matrizAdyacencias.size(); ++j) {
            if (matrizAdyacencias[i][j]) cout << ' ' << hashMapIntToString.at(j);
        }
        cout << endl;
    }
    else {
        cout << "Error" << endl;
    }
}

// Pregunta por dos nodos y te dicen si se tocan
// matrizAdyacencias = una matriz con las adyacencias respectivamente 
// hashMapStringToInt = un mapa que relaciona los numeros con los que trabajan la matriz y el nombre de los nodos
void preguntarSiSeTocan2Nodos(vector<vector<bool>> &matrizAdyacencias, map<string, int> &hashMapStringToInt) {
    string s1, s2;
    cout << "introduce dos nodos:" << endl;
    while (cin >> s1 >> s2) {
        if (hashMapStringToInt.count(s1) && hashMapStringToInt.count(s2)) {
            if (dosNodosSeTocan(s1, s2, matrizAdyacencias, hashMapStringToInt)) cout << "Si se chocan" << endl;
            else cout << "No se chocan" << endl;
        }
        else cout << "Error" << endl;
        
    }
}

// Dado un nodo dice todos sus adyacentes
// matrizAdyacencias = una matriz con las adyacencias respectivamente 
// hashMapStringToInt = un mapa que relaciona los numeros con los que trabajan la matriz y el nombre de los nodos
// hashMapIntToString = un mapa que relaciona los nodos y los numeros con los que trabajan la matriz
void decirTodosLosNodosAdyacentes(vector<vector<bool>> &matrizAdyacencias, map<string, int> &hashMapStringToInt, map<int, string> &hashMapIntToString) {
    string s1;
    cout << "Introduce un nodo:" << endl;
    while (cin >> s1 ) {
        printAdyacencias(s1, matrizAdyacencias, hashMapStringToInt, hashMapIntToString);
    }
}


// Devuelve una lista con el camino mas rapido entre estos dos vertices
// a = valor numerico del nodo 1
// a = valor numerico del nodo 2
// matrizAdyacencias = una matriz con las adyacencias respectivamente 
// VerticesNoVisitables = Numeros no visitables
list<int> CaminoMasRapido(int a, int b, vector<vector<bool>> &matrizAdyacencias, list<int> VerticesNoVisitables) {
    if (a == b) return {a};

    int n = matrizAdyacencias.size();
    queue<int> verticesAVisitar; 
    vector<bool> Visitados(n, false);
    vector<int> predecesor(n, -1); 

    verticesAVisitar.push(a);
    Visitados[a] = true;
    for (auto x : VerticesNoVisitables) Visitados[x] = true;

    bool finded = false;

    while (!verticesAVisitar.empty() && !finded) {
        int nodo = verticesAVisitar.front();
        verticesAVisitar.pop();

        for (int j = 0; j < n; ++j) {
            if (matrizAdyacencias[nodo][j] && !Visitados[j]) {
                verticesAVisitar.push(j);
                Visitados[j] = true;
                predecesor[j] = nodo;

                if (j == b) {
                    finded = true; 
                    break;
                }
            }
        }
    }

    list<int> result;
    if (!finded) return result;

    for (int at = b; at != -1; at = predecesor[at]) {
        result.push_front(at);
    }

    return result;
}

// Comprueba que b comienze como a, que a sea el primer subconjunto de b
bool comienza_con(const std::string& a, const std::string& b) {
    // Verifica si la longitud de a es menor o igual que b
    if (a.size() > b.size()) {
        return false;
    }
    // Compara los primeros caracteres de b con a
    return b.substr(0, a.size()) == a;
}

// Facilita ingresar el nombre
// val el valor de salida
// hashMapStringToInt = mapa que contiene todos los vertices
bool inputCorrecto(string &val, map<string, int> &hashMapStringToInt) {
    if (!(cin >> val)) return false;
    while (!hashMapStringToInt.count(val)) {
        cout << "- puede que quisieses decir:";
        for (auto it = hashMapStringToInt.begin(); it != hashMapStringToInt.end(); ++it) {
            if (comienza_con(val, (it -> first))) cout << ' ' << (it -> first);
        } cout << endl;

        if (!(cin >> val)) return false;
    }

    return true;
}