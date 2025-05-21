#include <iostream>
using namespace std;
#include "ArbolB.h"

int main() {
    ArbolB arbol(5);
    int i;
    int dato;
    int orden = 5;
    int arr[10] = {2,7,9,8,6,3,1,4,5,10};
    cout << "Arbol B de orden " << orden << endl;
    cout << "Insertando claves en el arbol B: " << endl;
    for (i = 0; i < 10; i++) {
        dato = arr[i];
        arbol.insertar(dato);
        cout << "Insertando " << dato << endl;
        arbol.mostrar();
        cout << endl;
    }
    
    cout << "\n\nArbol B al finalizar insertado: ";
    arbol.mostrar();
    
    return 0;
}