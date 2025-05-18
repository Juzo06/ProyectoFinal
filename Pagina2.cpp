#include "Pagina.h"

Pagina::Pagina(int orden, int dato){
    dato = dato;
    this->ordenM = orden;
}

Pagina::Pagina(){
    this->clave = new int[ordenM];
    this->enlace = new Pagina*[ordenM + 1];
    this->padre = nullptr;
    this->clavesUsadas = 0;
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