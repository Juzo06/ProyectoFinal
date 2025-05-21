#include "Pagina.h"

Pagina::Pagina(int orden, int dato){
    this->clave = new int[orden-1];
    this->enlace = new Pagina*[orden];
    this->padre = nullptr;
    for (int i = 0; i < orden-1; i++)
        this->clave[i] = -1; // Valor que nunca será clave válida
    for (int i = 0; i < orden; i++)
        this->enlace[i] = nullptr;
    this->clave[0] = dato;
    this->clavesUsadas = 0;
    this->ordenM = orden;
}

Pagina::Pagina(){
}

Pagina::~Pagina(){
    delete[] clave;
    delete enlace;
    delete padre;
}

int Pagina::getClave(int i){
    return clave[i];
}

void Pagina::setClave(int i, int valor){
    clave[i] = valor;
}

Pagina* Pagina::getEnlace(int i){
    return enlace[i];
}

void Pagina::setEnlace(int i, Pagina* enlace){
    this->enlace[i] = enlace;
}

Pagina* Pagina::getPadre(){
    return padre;
}

void Pagina::setPadre(Pagina* padre){
    this->padre = padre;
}

int Pagina::getClavesUsadas(){
    return clavesUsadas;
}

void Pagina::setClavesUsadas(int clavesUsadas){
    this->clavesUsadas = clavesUsadas;
}

int Pagina::getOrdenM(){
    return ordenM;
}

void Pagina::setOrdenM(int ordenM){
    this->ordenM = ordenM;
}