#ifndef OBTENERDATOS_HH
#define OBTENERDATOS_HH

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <list>
#include <map>
#include <vector>

using namespace std;

// Crea el hash map de tipos A B
// A = tipo de la key
// B = tipo del value
// AToB = mapa<A, B> del cual coje la informacion
// name = nombre del archivo que creara
template<typename A, typename B>
void CrearHashMapAToB(map<A, B> &AToB, string name);

// Crea la matriz de adyacencias que utilizara el main
// fIn = el canal de entrada que utilizara
// StringToInt = un mapa que relaciona cada nombre del vertice con su respectivo valor
// carpeta = subcarpeta donde se pondran todos los archivos
void CrearMatrizDeAdyacencias(ifstream &fIn, map<string, int> &StringToInt, string carpeta);

// Crea dentro de la carpeta indicada, todos los archivos necesarios para el main
// link = nombre del archivo con formato (vertice) (adyacencias)
// carpeta = subcarpeta donde se pondran todos los archivos
void crearData(string link, string carpeta);

// Pasa todo un archivo a minusculas
void convertirMinusculas(const string& nombreArchivo);

#endif // OBTENERDATOS_HH