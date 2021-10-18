#ifndef ARBOL_AVL_DEFINED
#define ARBOL_AVL_DEFINED
#include <iostream>
#include "Nodo.cpp"

using namespace std;

template <class T>

class ArbolAVL{
    private:
        Nodo<T> *raiz;
    
    public:
        ArbolAVL(){
            raiz=NULL;
        }

        int alturaMaxima(Nodo<T> *izquierdo,Nodo<T> *derecho){
            int alturaMaximaIzquierda=0;
            int alturaMaximaDerecha=0;
            if(izquierdo!=NULL){
                alturaMaximaIzquierda=izquierdo->getAltura();
            }
            if(derecho!=NULL){
                alturaMaximaDerecha=derecho->getAltura();
            }
            return (alturaMaximaDerecha>alturaMaximaIzquierda) ? alturaMaximaDerecha : alturaMaximaIzquierda;
        }

        int calcularFb(Nodo<T> *nodo){
            if(nodo==NULL){
                return 0;
            }
            int fbIzquierdo=0;
            int fbDerecho=0;
            if(nodo->getIzquierda()!=NULL){
                fbIzquierdo=nodo->getIzquierda()->getAltura();
                cout<<"Nodo izquierdo de "<< nodo->getDato()<<" "<< fbIzquierdo<<endl;
               
            }
            if(nodo->getDerecha()!=NULL){
                fbDerecho=nodo->getDerecha()->getAltura();
                cout<<"Nodo derecho de "<< nodo->getDato()<<" "<< fbDerecho<<endl;

            }
            return fbIzquierdo-fbDerecho;
        }

        Nodo<T>* rotarALaDerecha(Nodo<T> *pivote){
            cout<<"Entra rotacion a la derecha "<<endl;
            Nodo<T> *derechaPivote= pivote->getDerecha();
            Nodo<T> *izquierdaPivote= pivote->getIzquierda();
            izquierdaPivote->setDerecha(pivote);
            pivote->setIzquierda(derechaPivote);
            if(izquierdaPivote!=NULL){
                izquierdaPivote->setAltura(1+ alturaMaxima(izquierdaPivote->getDerecha(),izquierdaPivote->getIzquierda()));
            }
            if(pivote!=NULL){
                pivote->setAltura(1+ alturaMaxima(pivote->getDerecha(),pivote->getIzquierda()));
            }
            return izquierdaPivote;
        }
        Nodo<T>* rotarALaIzquierda(Nodo<T> *pivote){
            cout<<"Entra rotacion a la izquierda "<<endl;
            Nodo<T> *derechaPivote= pivote->getDerecha();
            Nodo<T> *izquierdaPivote= pivote->getIzquierda();
            derechaPivote->setIzquierda(pivote);
            pivote->setDerecha(izquierdaPivote);
            if(derechaPivote!=NULL){
                derechaPivote->setAltura(1+ alturaMaxima(derechaPivote->getDerecha(),derechaPivote->getIzquierda()));
            }
            if(pivote!=NULL){
                pivote->setAltura(1+ alturaMaxima(pivote->getDerecha(),pivote->getIzquierda()));
            }
            return derechaPivote;
        }
        Nodo<T>* insertarRec(Nodo<T> *nodo,T dato){
            cout<<"Insertando nodo "<<dato<<endl;
            if(nodo==NULL){
                return new Nodo<T>(dato);
            }
            cout<<"Insertando nodo "<<dato<<" con nodo entrada "<<nodo->getDato()<<endl; 

            if(dato<nodo->getDato()){
                nodo->setIzquierda(insertarRec(nodo->getIzquierda(),dato));
            }
            if(dato>nodo->getDato()){
                nodo->setDerecha(insertarRec(nodo->getDerecha(),dato));
            } 
                 
            nodo->setAltura(1+alturaMaxima(nodo->getIzquierda(),nodo->getDerecha()));
            cout<<"Actualizando altura de nodo "<<nodo->getDato()<<" altura: "<<nodo->getAltura()<<endl; 
            int fb=calcularFb(nodo);
            cout<<"El factor de balance de tu nodo "<<nodo->getDato()<<" es "<<fb<<endl;
            if (fb>1 && dato<nodo->getIzquierda()->getDato()){
                return rotarALaDerecha(nodo);
            }
            if (fb<-1 && dato>nodo->getDerecha()->getDato()){
                return rotarALaIzquierda(nodo);
            }    
            if (fb>1 && dato>nodo->getIzquierda()->getDato()){
                nodo->setIzquierda(rotarALaIzquierda(nodo->getIzquierda()));
                return rotarALaDerecha(nodo);
            }  
            if (fb<-1 && dato<nodo->getDerecha()->getDato()){
                nodo->setDerecha(rotarALaDerecha(nodo->getDerecha()));
                return rotarALaIzquierda(nodo);
            }                    
            return nodo;
        }
        void insertar(T dato){
            raiz=insertarRec(raiz, dato);
        }

        void imprimirRec(Nodo<T> *nodo){
            if(nodo!=NULL){
                if(nodo->getDerecha()==NULL && nodo->getIzquierda()==NULL){
                    cout<<"HOJA: "<<nodo->getDato()<<" ";
                }else{
                    cout<<"DATO: "<<nodo->getDato()<<endl;
                    cout<<"SUBARBOL DERECHO DE " <<nodo->getDato()<<": ";
                    imprimirRec(nodo->getDerecha());
                    cout<<endl;
                    cout<<"SUBARBOL IZQUIERDO DE " <<nodo->getDato()<<": ";
                    imprimirRec(nodo->getIzquierda());
                    cout<<endl;
                }
            }else{
                cout<<"VACIO";
            }
        }  

        void imprimir(){
            imprimirRec(raiz);
        }          
};


#endif
