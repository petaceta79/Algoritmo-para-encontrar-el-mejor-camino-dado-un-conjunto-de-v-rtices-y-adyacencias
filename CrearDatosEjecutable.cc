#include "ObtenerDatos.hh"


int main() {
    cout << "Nombre del archivo (con el .txt): " << endl;
    string link; cin >> link;
    
    //convertirMinusculas(link);
    crearData(link, "info");
}