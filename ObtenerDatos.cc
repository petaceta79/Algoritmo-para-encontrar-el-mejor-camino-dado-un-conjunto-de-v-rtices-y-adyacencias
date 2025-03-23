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
void CrearHashMapAToB(map<A, B> &AToB, string name) {
    ofstream FOut(name);
    if (!FOut) {
        cerr << "Error al crear el archivo: " << name << endl;
        return;
    }

    for (auto &x : AToB) {
        FOut << x.first << ' ' << x.second << endl;
    }
    FOut.close();
}

// Crea la matriz de adyacencias que utilizara el main
// fIn = el canal de entrada que utilizara 
// StringToInt = un mapa que relaciona cada nombre del vertice con su respectivo valor
// carpeta = subcarpeta donde se pondran todos los archivos
void CrearMatrizDeAdyacencias(ifstream &fIn, map<string, int> &StringToInt, string carpeta) {
    vector<vector<int>> M(StringToInt.size(), vector<int>(StringToInt.size(), 0));
    if (!fIn) {
        cerr << "Error al leer el archivo de entrada" << endl;
        return;
    }

    string line;
    while (getline(fIn, line)) {
        istringstream ss(line);
        string word;
        ss >> word;

        string AdyacentWord;
        while (ss >> AdyacentWord) {
            if (StringToInt.count(word) && StringToInt.count(AdyacentWord)) {
                M[StringToInt.at(word)][StringToInt.at(AdyacentWord)] = 1;
            }
        }
    }

    ofstream fOut(carpeta + "/matriz_de_adyacencia.txt");
    if (!fOut) {
        cerr << "Error al crear el archivo de matriz" << endl;
        return;
    }

    for (int i = 0; i < M.size(); ++i) {
        for (int j = 0; j < M[i].size(); ++j) {
            fOut << M[i][j] << ' ' ;
        }
        fOut << endl;
    }

    fOut.close();
}

// Crea dentro de la carpeta indicada, todos los archivos necesarios para el main
// link = nombre del archivo con formato (vertice) (adyacencias)
// carpeta = subcarpeta donde se pondran todos los archivos
void crearData(string link, string carpeta) {
    map<string, int> StringToInt;
    map<int, string> IntToString;

    ifstream fIn(link);
    if (!fIn) {
        cerr << "Error al abrir el archivo: " << link << endl;
        return;
    }

    string line;
    int n = 0;
    while (getline(fIn, line)) {
        istringstream ss(line);
        string word;
        ss >> word;

        if (StringToInt.count(word) == 0) {
            StringToInt[word] = n;
            IntToString[n] = word;
            ++n;
        }
    }
    fIn.close();

    CrearHashMapAToB(StringToInt, carpeta + "/hashMapStringToInt.txt");
    CrearHashMapAToB(IntToString, carpeta + "/hashMapIntToString.txt");

    fIn.open(link);
    if (!fIn) {
        cerr << "Error al reabrir el archivo: " << link << endl;
        return;
    }
    CrearMatrizDeAdyacencias(fIn, StringToInt, carpeta);
    fIn.close();
}

// Pasa todo un archivo a minusculas
void convertirMinusculas(const string& nombreArchivo) {
    ifstream entrada(nombreArchivo); // Abrir archivo en modo lectura
    string contenido;
    char c;
    while (entrada.get(c)) {
        contenido += tolower(c);
    }
    entrada.close();

    ofstream salida(nombreArchivo);
    salida << contenido;
    salida.close();
}

int main() {
    cout << "Nombre del archivo (con el .txt): " << endl;
    string link; cin >> link;
    
    //convertirMinusculas(link);
    crearData(link, "info");
}
