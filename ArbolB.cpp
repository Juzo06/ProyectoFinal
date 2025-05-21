#include "ArbolB.h"

ArbolB::ArbolB(int orden) {
        raiz = NULL;
        this->orden = orden;
    }

void ArbolB::setraiz(Pagina *raiz) {
    this->raiz = raiz;
}

Pagina* ArbolB::getraiz() {
    return raiz;
}

int ArbolB::getNodosminimo() {
     int nodosMinimos = (orden - 1) / 2;
     return nodosMinimos;
}

int ArbolB::insertar(int dato) {
     Pagina *nodo, *padre;
     int i;
     // Asegurarse de que la llave no está en el árbol
     padre = nodo = this->getraiz();
     while (nodo) {
        padre = nodo;
        i = 0;
        while (i < nodo->getClavesUsadas() && nodo->getClave(i) < dato) {
          i++;
        }
        if (nodo->getClave(i) == dato && i < nodo->getClavesUsadas()) {
            return 0;
        } else {
           nodo = nodo->getEnlace(i);
        }
     }
     nodo = padre;
     inserta(dato, nodo, nullptr, nullptr);
     return 1;
}

void ArbolB::inserta(int dato, Pagina *nodo, Pagina *hijo1, Pagina *hijo2) {
    int i, j, lista[i];
    Pagina *padre, *nuevo, *listapunt[i];
    bool salir = false;
   // Insertar nueva llave en nodo:
    do {
      if (!nodo) {
        nodo = new Pagina(orden, dato);
        raiz = nodo;
      }
      padre = nodo->getPadre();
      if (nodo->getClavesUsadas() == (orden - 1)) {
     // Nodo derecho
         nuevo = new Pagina(orden, dato);
        // Construye lista ordenada:
         i = 0;
         while (nodo->getClave(i) < dato && i < (orden - 1)) {
            lista[i] = nodo->getClave(i);
            listapunt[i] = nodo->getEnlace(i);
            i++;
         }
         lista[i] = dato;
         listapunt[i] = hijo1;
         listapunt[i + 1] = hijo2;
         while (i < (orden - 1)) {
            lista[i + 1] = nodo->getClave(i);
            listapunt[i + 2] = nodo->getEnlace(i + 1);
            i++;
         }
        // Dividir nodos:
       // Nodo izquierdo:
         nodo->setClavesUsadas((orden - 1) / 2);
         for (j = 0; j < nodo->getClavesUsadas(); j++) {
            nodo->setClave(j, lista[j]);
            nodo->setEnlace(j, listapunt[j]);
         }
         nodo->setEnlace(nodo->getClavesUsadas(), listapunt[nodo->getClavesUsadas()]);
      // Nodo derecho:
         nuevo->setClavesUsadas((orden - 1) - nodo->getClavesUsadas());
         for (j = 0; j < nuevo->getClavesUsadas(); j++) {
            nuevo->setClave(j, lista[j + ((orden - 1) / 2) + 1]);
            nuevo->setEnlace(j, listapunt[j + ((orden - 1) / 2) + 1]);
         }
         nuevo->setEnlace(nuevo->getClavesUsadas(), listapunt[(orden - 1) + 1]);
         for (j = 0; j <= nodo->getClavesUsadas(); j++) {
            if (nodo->getEnlace(j)) {
              (nodo->getEnlace(j))->setPadre(nodo);
            }
         }
         for (j = 0; j <= nuevo->getClavesUsadas(); j++) {
            if (nuevo->getEnlace(j) != nullptr) {
                (nuevo->getEnlace(j))->setPadre(nuevo);
            }
         }
         dato = lista[(orden - 1) / 2];
         hijo1 = nodo;
         hijo2 = nuevo;
         nodo = padre;
      } else {
        // Inserta nueva llave en su lugar:
          i = 0;
          if (nodo->getClavesUsadas() > 0) {
             while (nodo->getClave(i) < dato && i < nodo->getClavesUsadas()) {
                i++;
             }
             for (j = nodo->getClavesUsadas(); j > i; j--) {
                nodo->setClave(j, nodo->getClave(j - 1));
             }
             for (j = nodo->getClavesUsadas() + 1; j > i; j--) {
                nodo->setEnlace(j, nodo->getEnlace(j - 1));
             }
          }
         nodo->setClavesUsadas(nodo->getClavesUsadas() + 1);
         nodo->setClave(i, dato);
         nodo->setEnlace(i, hijo1);
         nodo->setEnlace(i + 1, hijo2);
         if (hijo1) hijo1->setPadre(nodo);
           if (hijo2) hijo2->setPadre(nodo);
            salir = true;
      }
    } while (!salir);
}

void ArbolB::mostrar() {
    cout<<"** Arbol **";
    ver(raiz);
    cout<<" Fin ";
}

void ArbolB::ver(Pagina *nodo) {
   int i;
   if (!nodo) return;
   cout << "------------------" << endl;
   for (i = 0; i < nodo->getClavesUsadas() - 1; i++) {
      cout << " " << nodo->getClave(i) << " - ";
   }
   cout << "------------------" << endl;
   if (nodo->getClavesUsadas() > 0) {
      cout << "  " << nodo->getClave(i) << " [ ";
   }
   if (nodo->getPadre()) {
      cout << " padre" << nodo->getPadre()->getClave(0);
   } else {
      cout << " * ";
   }
   cout << " ]";
   for (i = 0; i <= nodo->getClavesUsadas(); i++) {
       ver(nodo->getEnlace(i));
   }
}

void ArbolB::BorrarNodo(Pagina *nodo) {
  int i;
  if(!nodo) return;
  
  for(i = 0; i <= nodo->getClavesUsadas(); i++)
	 BorrarNodo(nodo->getEnlace(i));
  delete nodo;
}

void ArbolB::Borrar(int dato) {
   Pagina *nodo;
   int encontrado = 0;
   int i;

   // Busca el nodo que contiene la llave, si existe
   nodo = raiz;
   while(nodo && !encontrado) {
      i = 0;
      while(i < nodo->getClavesUsadas() && (nodo->getClave(i) < dato))
          i++;
      if(nodo->getClave(i) == dato && i < nodo->getClavesUsadas())
         encontrado = 1 ;
      else nodo = nodo->getEnlace(i);
   }
   if(encontrado) Borrarllave(nodo, dato);
}

void ArbolB::Borrarllave(Pagina *nodo, int dato) {
   Pagina *actual, *derecha, *izquierda, *padre;
   int posllavePadre, pos, i;

   // Buscar posición dentro de lista de claves:
   pos = 0;
   while(nodo->getClave(pos) < dato) pos++;
   // ¿Está la llave en un nodo hoja?
   if(nodo->getEnlace(0)) { // No, se trata de un nodo intermedio
      // Buscar actual del dato siguiente:
      actual = nodo->getEnlace(pos + 1);
      while(actual->getEnlace(0))  actual = actual->getEnlace(0);
      // Intercambiar con el dato siguiente:
      nodo->setClave(pos, actual->getClave(0));
      // La posición de la llave a borrar en ahora la 0:
      pos = 0;
   } else actual = nodo;

   // Borrar llave
   for(i = pos; i < actual->getClavesUsadas(); i++)
      actual->setClave(i, actual->getClave(i + 1));
   actual->setClavesUsadas(actual->getClavesUsadas()-1);//posible solucion (actual->setClavesUsadas(actual->getClavesUsadas()-1);)

   if(actual == this->getraiz() && actual->getClavesUsadas() == 0) {
      delete actual;
      this->raiz = nullptr;
      return;
   }

   // ¿Es el número de claves mayor que el mínimo para el nodo?
   if(actual == this->getraiz() || actual->getClavesUsadas() >= this->getNodosminimo())
      return;
   return;

   do {
      // El número de claves es menor que el mínimo:
      // Buscar nodos a derecha e izquierda:
      padre = actual->getPadre();
      for(posllavePadre = 0;padre->getEnlace(posllavePadre) != actual; posllavePadre++);
      if(posllavePadre > 0)
         izquierda = padre->getEnlace(posllavePadre-1);
      else izquierda = NULL;
      if(posllavePadre < padre->getClavesUsadas())
         derecha = padre->getEnlace(posllavePadre+1);
      else derecha = NULL;

      // Intentar pasar una llave de un nodo cercano:
      if(derecha && derecha->getClavesUsadas() > this->getNodosminimo())
         PasarllaveDerecha(derecha, padre, actual, posllavePadre);
      else if(izquierda && izquierda->getClavesUsadas() > this->getNodosminimo())
         PasarllaveIzquierda(izquierda, padre, actual, posllavePadre-1);
      // Si no fue posible, unir con un nodo cercano y una llave de padre:
      else if(derecha) // Usar nodo derecho
         unirnodo(actual, padre, derecha, posllavePadre);
      else             // Usar el nodo izquierdo
        unirnodo(izquierda, padre, actual, posllavePadre-1);
      // Vuelta a empezar:
      actual = padre;
   } while(actual && actual != this->getraiz() && actual->getClavesUsadas() < this->getNodosminimo());
}

void ArbolB::PasarllaveDerecha(Pagina * derecha, Pagina * padre, Pagina * nodo, int posllavePadre) {
   int i;

   nodo->setClave(nodo->getClavesUsadas(), padre->getClave(posllavePadre));
   nodo->setClavesUsadas(nodo->getClavesUsadas()+1); //posible solucion (nodo->setClavesUsadas(nodo->getClavesUsadas()+1);)
   padre->setClave(posllavePadre, derecha->getClave(0));
   nodo->setEnlace(nodo->getClavesUsadas(), derecha->getEnlace(0));
   if(derecha->getEnlace(0))
      derecha->getEnlace(0)->setPadre(nodo);
   for(i = 0; i < derecha->getClavesUsadas(); i++)
      derecha->setClave(i, derecha->getClave(i+1));
   for(i = 0; i <= derecha->getClavesUsadas(); i++)
      derecha->setEnlace(i, derecha->getEnlace(i+1));
   derecha->setClavesUsadas(derecha->getClavesUsadas()-1); //posible solucion (derecha->setClavesUsadas(derecha->getClavesUsadas()-1);)
}

void ArbolB::PasarllaveIzquierda(Pagina * izquierda, Pagina * padre, Pagina * nodo, int posllavePadre) {
   int i;

   for(i = nodo->getClavesUsadas(); i > 0; i--)
      nodo->setClave(i, nodo->getClave(i-1));
   for(i = nodo->getClavesUsadas()+1; i > 0; i--)
      nodo->setEnlace(i, nodo->getEnlace(i-1));
   nodo->setClavesUsadas(nodo->getClavesUsadas()+1); //posible solucion (nodo->setClavesUsadas(nodo->getClavesUsadas()+1);)
   nodo->setClave(0, padre->getClave(posllavePadre));
   padre->setClave(posllavePadre, izquierda->getClave(izquierda->getClavesUsadas()-1));
   nodo->setEnlace(0, izquierda->getEnlace(izquierda->getClavesUsadas()));
   if(nodo->getEnlace(0))
      nodo->getEnlace(0)->setPadre(nodo);
   izquierda->setClavesUsadas(izquierda->getClavesUsadas()-1); //posible solucion (izquierda->setClavesUsadas(izquierda->getClavesUsadas()-1);)
}

void ArbolB::unirnodo(Pagina * izquierda, Pagina * &padre, Pagina * derecha, int posllavePadre) {
   int i;

   izquierda->setClave(izquierda->getClavesUsadas(), padre->getClave(posllavePadre));
   padre->setClavesUsadas(padre->getClavesUsadas()-1); //posible solucion (padre->setClavesUsadas(padre->getClavesUsadas()-1);)
   for(i = posllavePadre; i < padre->getClavesUsadas(); i++) {
      padre->setClave(i, padre->getClave(i+1));
      padre->setEnlace(i+1, padre->getEnlace(i+2));
   }
   izquierda->setClavesUsadas(izquierda->getClavesUsadas() + 1);
   for(i = 0; i < derecha->getClavesUsadas(); i++)
      izquierda->setClave(izquierda->getClavesUsadas() + i, derecha->getClave(i));
   for(i = 0; i <= derecha->getClavesUsadas(); i++)   {
      izquierda->setEnlace(izquierda->getClavesUsadas()+i, derecha->getEnlace(i));
      if(derecha->getEnlace(i))
          derecha->getEnlace(i)->setPadre(izquierda);
   }

   izquierda->setClavesUsadas(izquierda->getClavesUsadas() + derecha->getClavesUsadas()); //posible solucion (izquierda->setClavesUsadas(izquierda->getClavesUsadas()+derecha->getClavesUsadas());)
   if(padre == this->getraiz() && padre->getClavesUsadas() == 0) { // Cambio de Raiz
      this->setraiz(izquierda); //posible solucion (this->setraiz(izquierda);)
      izquierda->setPadre(nullptr);
      delete padre;
      padre = nullptr;
   }
   delete derecha;
}
