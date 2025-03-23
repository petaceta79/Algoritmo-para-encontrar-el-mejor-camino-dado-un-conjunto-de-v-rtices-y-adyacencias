#ifndef LOGICAPRINCIPAL_HH
#define LOGICAPRINCIPAL_HH

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <type_traits>
#include <map>
#include <vector>
#include <list>
#include <queue>
#include <set>

using namespace std;

// Constantes para las rutas de los archivos
const string hashMapIntToStringLink = "info/hashMapIntToString.txt";
const string hashMapStringToIntLink = "info/hashMapStringToInt.txt";
const string matrizAdyacenciasLink = "info/matriz_de_adyacencia.txt";

// Lee un fichero (link) y obtiene de este un map
// keyType = el tipo de la key
// valueType = el tipo del value
// link = la direccion del archivo
template<typename keyType, typename valueType>
map<keyType, valueType> readHashMap_a_to_b(string link) {
    ifstream fIn(link);

    map<keyType, valueType> M;

    keyType key;
    valueType value;
    while (fIn >> key >> value) {
        M.insert({key, value});
    }
    
    fIn.close();
    return M;
}

// Lee una matriz cuadrada del fichero (link)
// T = tipo de la matriz
// n = tamanno de la matriz
// link = direccion del archivo
template<typename T>
vector<vector<T>> readMatriz(int n, string link) {
    ifstream fIn(link);
    vector<vector<T>> matriz(n, vector<T>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int val; fIn >> val;

            if (is_same<T, bool>::value) matriz[i][j] = (val == 1);
            else {
                matriz[i][j] = val;
            }
        }
    }

    fIn.close();
    return matriz;
}

// Devuelve si dos nodos se estan tocando (si no encuentra los nodos devuelve false)
// s1 = nombre del nodo uno
// s2 = nombre del nodo dos
// matrizAdyacencias = una matriz con las adyacencias respectivamente 
// hashMapStringToInt = un mapa que relaciona los numeros con los que trabajan la matriz y el nombre de los nodos
bool dosNodosSeTocan(string s1, string s2, vector<vector<bool>> &matrizAdyacencias, map<string, int> &hashMapStringToInt);

// Escribe todas las adyacencias de un nodo
// s = nombre del nodo 
// matrizAdyacencias = una matriz con las adyacencias respectivamente 
// hashMapStringToInt = un mapa que relaciona los numeros con los que trabajan la matriz y el nombre de los nodos
// hashMapIntToString = un mapa que relaciona los nodos y los numeros con los que trabajan la matriz
void printAdyacencias(string s, vector<vector<bool>> &matrizAdyacencias, map<string, int> &hashMapStringToInt, map<int, string> &hashMapIntToString);

// Pregunta por dos nodos y te dicen si se tocan
// matrizAdyacencias = una matriz con las adyacencias respectivamente 
// hashMapStringToInt = un mapa que relaciona los numeros con los que trabajan la matriz y el nombre de los nodos
void preguntarSiSeTocan2Nodos(vector<vector<bool>> &matrizAdyacencias, map<string, int> &hashMapStringToInt);

// Dado un nodo dice todos sus adyacentes
// matrizAdyacencias = una matriz con las adyacencias respectivamente 
// hashMapStringToInt = un mapa que relaciona los numeros con los que trabajan la matriz y el nombre de los nodos
// hashMapIntToString = un mapa que relaciona los nodos y los numeros con los que trabajan la matriz
void decirTodosLosNodosAdyacentes(vector<vector<bool>> &matrizAdyacencias, map<string, int> &hashMapStringToInt, map<int, string> &hashMapIntToString);

// Devuelve una lista con el camino mas rapido entre estos dos vertices
// a = valor numerico del nodo 1
// b = valor numerico del nodo 2
// matrizAdyacencias = una matriz con las adyacencias respectivamente 
// VerticesNoVisitables = Numeros no visitables
list<int> CaminoMasRapido(int a, int b, vector<vector<bool>> &matrizAdyacencias, list<int> VerticesNoVisitables);

// Comprueba que b comienze como a, que a sea el primer subconjunto de b
bool comienza_con(const std::string& a, const std::string& b);

// Facilita ingresar el nombre
// val el valor de salida
// hashMapStringToInt = mapa que contiene todos los vertices
bool inputCorrecto(string &val, map<string, int> &hashMapStringToInt);

#endif // LOGICAPRINCIPAL_HH