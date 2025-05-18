#ifndef PAGINA_H
#define PAGINA_H
#include <iostream>
using namespace std;

class Pagina {
    private:
        int* clave;
        Pagina** enlace;
        Pagina* padre;
        int clavesUsadas;
        int ordenM;
    public:
        Pagina();
        Pagina(int, int);
        ~Pagina();
        int getClave(int);
        void setClave(int, int);
        Pagina* getEnlace(int);
        void setEnlace(int, Pagina*);
        Pagina* getPadre();
        void setPadre(Pagina*);
        int getClavesUsadas();
        void setClavesUsadas(int);
        int getOrdenM();
        void setOrdenM(int);
};
#endif