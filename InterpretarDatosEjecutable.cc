#include "LogicaPrincipal.hh"

int main() {
    map<int, string> hashMapIntToString = readHashMap_a_to_b<int, string>(hashMapIntToStringLink);
    map<string, int> hashMapStringToInt = readHashMap_a_to_b<string, int>(hashMapStringToIntLink);

    vector<vector<bool>> matrizAdyacencias = readMatriz<bool>(hashMapIntToString.size(), matrizAdyacenciasLink);


    //preguntarSiSeTocan2Nodos(matrizAdyacencias, hashMapStringToInt);

    //decirTodosLosNodosAdyacentes(matrizAdyacencias, hashMapStringToInt, hashMapIntToString);

    // Main
    cout << "Introduce primer nodo (en ingles)" << endl << "Mirar Hash para el nombre exacto" << endl;
    string as1 = ""; inputCorrecto(as1, hashMapStringToInt);
    cout << "Introduce segundo nodo (en ingles)" << endl << "Mirar Hash para el nombre exacto" << endl;
    string as2 = ""; inputCorrecto(as2, hashMapStringToInt);

    cout << "Introduce los nodos que no quieres que se visiten (cerrar entrada para parar, control + z o control + d)" << endl;
    list<int> noVisitados;
    string nodo = "";
    while (inputCorrecto(nodo, hashMapStringToInt)) {
        noVisitados.push_back(hashMapStringToInt.at(nodo));
        cout << "Annadido" << endl;
    }

    int a = hashMapStringToInt.at(as1);
    int b = hashMapStringToInt.at(as2);
    list<int> camino = CaminoMasRapido(a, b, matrizAdyacencias, noVisitados);

    cout << "Ruta mas optima: " << endl;
    for (auto x : camino) {
        cout << hashMapIntToString.at(x) << endl;
    }
}