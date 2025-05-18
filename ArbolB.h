#ifndef ARBOLB_H
#define ARBOLB_H
#include "Pagina.h"

class ArbolB {
    private:
        Pagina* raiz;
        int orden;
    public:
        ArbolB(int);
        Pagina* getraiz();
        void setraiz(Pagina* raiz);
        int getOrden();
        int insertar(int);
        void inserta(int, Pagina*, Pagina*, Pagina*);
        void inserta(int, Pagina*, Pagina*, Pagina*);
        void mostrar();
        void ver(Pagina*);
        void BorrarNodo(Pagina*);
        void Borrar(int);
        void Borrarllave(Pagina*, int);
        void PasarllaveDerecha(Pagina*, Pagina*, Pagina*, int);
        void PasarllaveIzquierda(Pagina*, Pagina*, Pagina*, int);
        void unirnodo(Pagina*, Pagina*&, Pagina*, int);
};

#endif