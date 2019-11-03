#include <stdio.h>
#include <pthread.h>

#include "integral.h"

double holawa=0;

typedef struct 
{
    Funcion f;
    void * pointer;
    double start;
    double end;
    int cant;
    double result;
}Args;

void *integrate_thread(void * ptr){
    Args *arg=ptr;
    arg->result=integral(arg->f,arg->pointer,arg->start,arg->end,arg->cant);
    return NULL;
}


double integral_par(Funcion f, void *ptr, double xi, double xf, int n, int p) {
    pthread_t t[p];
    Args array[p];
    int k=n%p;
    double m=(xf-xi)/p;

    for(int s=0;s<p;s++){
        Args * arg=&array[s];
        arg->f=f;
        arg->pointer=ptr;
        arg->start=xi;
        xi+=m;
        arg->end=xi;
        int i =n/p;
        if(s<k){
            i++;
        }
        arg->cant=i;
        
        pthread_create(&t[s],NULL,integrate_thread,arg);
    }


    double sum=0;
    for(int s=0;s<p;s++){
        pthread_join(t[s], NULL);
        sum+=array[s].result;
    }

    return sum;
}
