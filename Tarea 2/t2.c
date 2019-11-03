#include "t2.h"
#include <stdio.h>
#include <stdlib.h>

Nodo *fatherNode= NULL;
int izq=1; //Determina si estamos en arbol der o izq.

int calzar(Nodo *a, Nodo **ppat){
     
    //Lo que es null es el puntero, o el nodo?
    //Por ahora lo hago con puntero null.
    if (!*ppat && fatherNode==NULL){
        *ppat=a;
        //int valuep=(**ppat).x;
        return 1;
    }
    else if(!*ppat){
        //Nodo *p=*ppat;
        //Nodo nodeA=*a;
        //Nodo nodeP=*p;
        if(izq==1){
            (*fatherNode).izq=a;
            //int valuep=(**ppat).x;
            return 1;
        }
        else{
            (*fatherNode).der=a;
            //int valuep=(**ppat).x;
            return 1;
        }
    
    }
    else if(!a){
        return 0;
    }
    else if((*a).x!=(**ppat).x){
        return 0;
    }
    else{
        Nodo *p=*ppat;
        Nodo nodeA=*a;
        Nodo nodeP=*p;
        //int valuep=(nodeP).x;
        //int valuea=(nodeA).x;
        fatherNode= p;
        izq=1;
        int izqTree=calzar(nodeA.izq,&nodeP.izq);
        izq=0;
        fatherNode= *ppat;
        int derTree=calzar(nodeA.der,&nodeP.der);
        return izqTree & derTree;
    }
}

