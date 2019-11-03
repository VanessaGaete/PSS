#include <string.h>
#include "t1.h"
#include <stdlib.h>

uint comprimir(uint *a, int nbits){
    
    
    int size=0;
    int aux=sizeof(uint)<<3;
    while(aux){
        size++;
        aux<<=nbits;
    }

    uint maskNbits = (~((~0)<<nbits));
    uint respMask = 0;
    int i=0;

    while(size){
        uint comp=a[i]&maskNbits;
        respMask=respMask<<nbits;
        respMask=respMask|comp;
        size--;
        i++;
    }
    return respMask;
}

char *insercion(char *d, char *s){
    int size= strlen(d)+strlen(s)+1;
    char *anothers=malloc(sizeof(char)*size);

    strcpy(anothers,s);
    strcat(anothers,d);

    *(anothers+size-1)=0;

    return anothers;

}



void insertar(char *d, char *s){
    char *dPointer=d+strlen(d)-1;
    char *newPointer=dPointer+strlen(s);
    char *sPointer=s+strlen(s)-1;

    while(dPointer>=d){
        *newPointer=*dPointer;
        newPointer--;
        dPointer--;
    }
    while (newPointer>=d){
        *newPointer=*sPointer;
        sPointer--;
        newPointer--;
    }
  
}
