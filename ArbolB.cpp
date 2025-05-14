#include "ArbolB.h"

ArbolB(int orden) {
        raiz = NULL;
        this->orden = orden;
    }

int ArbolB::insertar(int dato) {
     Pagina *nodo, *padre;
     int i;
     // Asegurarse de que la llave no está en el árbol
     padre = nodo = this->setraiz();
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
     inserta(dato, nodo, null, null);
     return 1;
}

void ArbolB::inserta(int dato, Pagina *nodo, Pagina *hijo1, Pagina *hijo2) {
    Pagina *padre, *nuevo;
    int i, j;
    boolean salir = false;
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
            if (nuevo->getEnlace(j) != null) {
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
 
   for (i = 0; i < nodo->getClavesUsadas() - 1; i++) {
      cout<<" " + nodo->getClave(i) +  " - ";
   }
   if (nodo->getClavesUsadas() > 0) {
      cout<<"  " + nodo->getClave(i)+ " [ ";
   }
   if (nodo->getPadre()) {
      cout<<" padre" + (nodo->getPadre())->getClave(0));
   }else  cout<<" * ";
   cout<<" ]";
   for (i = 0; i <= nodo->getClavesUsadas(); i++) {
       ver(nodo->getEnlace(i));
   }
}

void ArbolB::BorrarNodo(Pagina *nodo) {
  int i;
  if(!nodo) return;
  
  for(i = 0; i <= nodo->clavesUsadas; i++)
	 BorrarNodo(nodo->puntero[i]);
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
      while(i < nodo->clavesUsadas && (nodo->llave[i] < dato))
          i++;
      if(nodo->llave[i] == dato && i < nodo->clavesUsadas)
         encontrado = 1 ;
      else nodo = nodo->puntero[i];
   }
   if(encontrado) Borrarllave(nodo, dato);
}

void ArbolB::Borrarllave(Pagina *nodo, int dato) {
   Pagina *actual, *derecha, *izquierda, *padre;
   int posllavePadre, pos, i;

   // Buscar posición dentro de lista de claves:
   pos = 0;
   while(nodo->llave[pos] < dato) pos++;
   // ¿Está la llave en un nodo hoja?
   if(nodo->puntero[0]) { // No, se trata de un nodo intermedio
      // Buscar actual del dato siguiente:
      actual = nodo->puntero[pos+1];
      while(actual->puntero[0])  actual = actual->puntero[0];
      // Intercambiar con el dato siguiente:
      nodo->llave[pos] = actual->llave[0];
      // La posición de la llave a borrar en ahora la 0:
      pos = 0;
   } else actual = nodo;

   // Borrar llave
   for(i = pos; i < actual->clavesUsadas; i++)
      actual->llave[i] = actual->llave[i+1];
   actual->clavesUsadas--;

   if(actual == Raiz && actual->clavesUsadas == 0) {
      delete actual;
      Raiz = NULL;
      return;
   }

   // ¿Es el número de claves mayor que el mínimo para el nodo?
   if(actual == Raiz || actual->clavesUsadas >= nodosMinimos)
   return;

   do {
      // El número de claves es menor que el mínimo:
      // Buscar nodos a derecha e izquierda:
      padre = actual->padre;
      for(posllavePadre = 0;padre->puntero[posllavePadre] != actual; posllavePadre++);
      if(posllavePadre > 0)
         izquierda = padre->puntero[posllavePadre-1];
      else izquierda = NULL;
      if(posllavePadre < padre->clavesUsadas)
         derecha = padre->puntero[posllavePadre+1];
      else derecha = NULL;

      // Intentar pasar una llave de un nodo cercano:
      if(derecha && derecha->clavesUsadas > nodosMinimos)
         PasarllaveDerecha(derecha, padre, actual, posllavePadre);
      else if(izquierda && izquierda->clavesUsadas > nodosMinimos)
         PasarllaveIzquierda(izquierda, padre, actual, posllavePadre-1);
      // Si no fue posible, unir con un nodo cercano y una llave de padre:
      else if(derecha) // Usar nodo derecho
         unirnodo(actual, padre, derecha, posllavePadre);
      else             // Usar el nodo izquierdo
        unirnodo(izquierda, padre, actual, posllavePadre-1);
      // Vuelta a empezar:
      actual = padre;
   } while(actual && actual != Raiz && actual->clavesUsadas < nodosMinimos);
}

void ArbolB::PasarllaveDerecha(Pagina * derecha, Pagina * padre, Pagina * nodo, int posllavePadre) {
   int i;

   nodo->llave[nodo->clavesUsadas] = padre->llave[posllavePadre];
   nodo->clavesUsadas++;
   padre->llave[posllavePadre] = derecha->llave[0];
   nodo->puntero[nodo->clavesUsadas] = derecha->puntero[0];
   if(derecha->puntero[0])
    derecha->puntero[0]->padre = nodo;
   for(i = 0; i < derecha->clavesUsadas; i++)
   derecha->llave[i] = derecha->llave[i+1];
   for(i = 0; i <= derecha->clavesUsadas; i++)
   derecha->puntero[i] = derecha->puntero[i+1];
   derecha->clavesUsadas--;
}

void ArbolB::PasarllaveIzquierda(Pagina * izquierda, Pagina * padre, Pagina * nodo, int posllavePadre) {
   int i;

   for(i = nodo->clavesUsadas; i > 0; i--)
   nodo->llave[i] = nodo->llave[i-1];
   for(i = nodo->clavesUsadas+1; i > 0; i--)
    nodo->puntero[i] = nodo->puntero[i-1];
   nodo->clavesUsadas++;
   nodo->llave[0] = padre->llave[posllavePadre];
   padre->llave[posllavePadre] = izquierda->llave[izquierda->clavesUsadas-1];
   nodo->puntero[0] = izquierda->puntero[izquierda->clavesUsadas];
   if(nodo->puntero[0])
   nodo->puntero[0]->padre = nodo;
   izquierda->clavesUsadas--;
}

void ArbolB::unirnodo(Pagina * izquierda, Pagina * &padre, Pagina * derecha, int posllavePadre) {
   int i;

   izquierda->llave[izquierda->clavesUsadas] = padre->llave[posllavePadre];
   padre->clavesUsadas--;
   for(i = posllavePadre; i < padre->clavesUsadas; i++) {
      padre->llave[i] = padre->llave[i+1];
      padre->puntero[i+1] = padre->puntero[i+2];
   }
   izquierda->clavesUsadas++;
   for(i = 0; i < derecha->clavesUsadas; i++)
      izquierda->llave[izquierda->clavesUsadas+i] = derecha->llave[i];
   for(i = 0; i <= derecha->clavesUsadas; i++)   {
      izquierda->puntero[izquierda->clavesUsadas+i] = derecha->puntero[i];
   if(derecha->puntero[i])
       derecha->puntero[i]->padre = izquierda;
   }

   izquierda->clavesUsadas += derecha->clavesUsadas;
   if(padre == Raiz && padre->clavesUsadas == 0) { // Cambio de Raiz
      Raiz = izquierda;
      Raiz->padre = NULL;
      delete padre;
      padre = NULL;
   }
   delete derecha;
}
