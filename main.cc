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

// n = 177
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

// Devuelve si dos paises se estan tocando (si no encuentra los paises devuelve false)
// s1 = nombre del pais uno
// s2 = nombre del pais dos
// matrizAdyacencias = una matriz con las adyacencias respectivamente 
// hashMapStringToInt = un mapa que relaciona los numeros con los que trabajan la matriz y el nombre de los paises
bool dosPaisesSeTocan(string s1, string s2, vector<vector<bool>> &matrizAdyacencias, map<string, int> &hashMapStringToInt) {
    if (hashMapStringToInt.count(s1) && hashMapStringToInt.count(s2)) return matrizAdyacencias[hashMapStringToInt.at(s1)][hashMapStringToInt.at(s2)];
    return false;
}

// Escribe todas las adyacencias de un pais
// s = nombre del pais 
// matrizAdyacencias = una matriz con las adyacencias respectivamente 
// hashMapStringToInt = un mapa que relaciona los numeros con los que trabajan la matriz y el nombre de los paises
// hashMapIntToString = un mapa que relaciona los paises y los numeros con los que trabajan la matriz
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

// Pregunta por dos paises y te dicen si se tocan
// matrizAdyacencias = una matriz con las adyacencias respectivamente 
// hashMapStringToInt = un mapa que relaciona los numeros con los que trabajan la matriz y el nombre de los paises
void preguntarSiSeTocan2Paises(vector<vector<bool>> &matrizAdyacencias, map<string, int> &hashMapStringToInt) {
    string s1, s2;
    cout << "introduce dos paises:" << endl;
    while (cin >> s1 >> s2) {
        if (hashMapStringToInt.count(s1) && hashMapStringToInt.count(s2)) {
            if (dosPaisesSeTocan(s1, s2, matrizAdyacencias, hashMapStringToInt)) cout << "Si se chocan" << endl;
            else cout << "No se chocan" << endl;
        }
        else cout << "Error" << endl;
        
    }
}

// Dado un pais dice todos sus adyacentes
// matrizAdyacencias = una matriz con las adyacencias respectivamente 
// hashMapStringToInt = un mapa que relaciona los numeros con los que trabajan la matriz y el nombre de los paises
// hashMapIntToString = un mapa que relaciona los paises y los numeros con los que trabajan la matriz
void decirTodosLosPaisesAdyacentes(vector<vector<bool>> &matrizAdyacencias, map<string, int> &hashMapStringToInt, map<int, string> &hashMapIntToString) {
    string s1;
    cout << "Introduce un pais:" << endl;
    while (cin >> s1 ) {
        printAdyacencias(s1, matrizAdyacencias, hashMapStringToInt, hashMapIntToString);
    }
}


// Devuelve una lista con el camino mas rapido entre estos dos vertices
// a = valor numerico del pais 1
// a = valor numerico del pais 2
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
    while (cin >> val && !hashMapStringToInt.count(val)) {
        cout << "- puede que quisieses decir:";
        for (auto it = hashMapStringToInt.begin(); it != hashMapStringToInt.end(); ++it) {
            if (comienza_con(val, (it -> first))) cout << ' ' << (it -> first);
        } cout << endl;
    }

    if (val == "") return false;
    return true;

}


int main() {
    map<int, string> hashMapIntToString = readHashMap_a_to_b<int, string>(hashMapIntToStringLink);
    map<string, int> hashMapStringToInt = readHashMap_a_to_b<string, int>(hashMapStringToIntLink);

    vector<vector<bool>> matrizAdyacencias = readMatriz<bool>(hashMapIntToString.size(), matrizAdyacenciasLink);


    //preguntarSiSeTocan2Paises(matrizAdyacencias, hashMapStringToInt);

    //decirTodosLosPaisesAdyacentes(matrizAdyacencias, hashMapStringToInt, hashMapIntToString);

    // Main
    cout << "Introduce primer pais (en ingles)" << endl << "Mirar Hash para el nombre exacto" << endl;
    string as1; inputCorrecto(as1, hashMapStringToInt);
    cout << "Introduce primer pais (en ingles)" << endl << "Mirar Hash para el nombre exacto" << endl;
    string as2; inputCorrecto(as2, hashMapStringToInt);

    cout << "Introduce los paises que no quieres que se visiten (cerrar entrada para parar, control + z o control + d)" << endl;
    list<int> noVisitados;
    string pais;
    while (inputCorrecto(pais, hashMapStringToInt)) {
        noVisitados.push_back(hashMapStringToInt.at(pais));
    }

    int a = hashMapStringToInt.at(as1);
    int b = hashMapStringToInt.at(as2);
    list<int> camino = CaminoMasRapido(a, b, matrizAdyacencias, noVisitados);

    cout << "Ruta mas optima: " << endl;
    for (auto x : camino) {
        cout << hashMapIntToString.at(x) << endl;
    }
}