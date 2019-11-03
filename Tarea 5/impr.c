#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#include "impr.h"


 /* indique aca los campos que necesita en una orden de trabajo */
struct orden {
  Doc *doc;
  int listo; //1 si es true 
};

/* defina aca las variables globales que necesite y programe las funciones
 * pedidas.
 */
pthread_mutex_t m=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;
ColaFifo *cola;
pthread_t *t;
int cant;
int apagado=1; //apagado=0 prendido=1

void * impr_thread(void * ptr){
  Impr *imprs=ptr;

  while(apagado==1){
    pthread_mutex_lock(&m);

    while (vacia(cola) && apagado==1){
      pthread_cond_wait(&cond,&m);
    }
    pthread_cond_broadcast(&cond);

    if(apagado==0){
      pthread_mutex_unlock(&m);
      break;
    } 
  
    Orden *order= extraer(cola);
    pthread_mutex_unlock(&m);

    imprimir(order->doc, imprs);
    order->listo= 1;
    pthread_cond_broadcast(&cond);
  }

  return NULL;
}

void init_impr(Impr **imprs, int n_impr) {
  cant=n_impr;
  cola=nuevaColaFifo();
  t = (pthread_t*) malloc(sizeof(pthread_t)*n_impr);
  //arg=nuevoArg(t,n_impr);
  for (int i=0;i<n_impr;i++) {
    Impr *impresora= *(imprs+i);
    pthread_create(&t[i],NULL,impr_thread,impresora);
    //arg=nuevoArg(t,n_impr);
  }
}

void terminar_impr() {
  //printf("kk \n");
  apagado=0;
   /*no olvide invocar pthread_join para enterrar los threads */
  //int l=arg->cant_impr;
  //pthread_t *a=arg->arrt;
  for(int i=0;i<cant;i++){
    //printf("entre \n");
    pthread_mutex_unlock(&m);
    pthread_cond_broadcast(&cond);
    pthread_join(t[i],NULL);
    //printf("murio \n");
  }
  return ;
}

Orden *imprimir_asinc(Doc *doc) {
  pthread_mutex_lock(&m);
  Orden *order=malloc(sizeof(Orden));  
  order->doc= doc;  
  order->listo= 0;  
  agregar(cola, order);
  pthread_cond_broadcast(&cond);
  pthread_mutex_unlock(&m);
  return order;
}

void confirmar(Orden *order) {
  while (!order->listo){
    pthread_cond_wait(&cond,&m);
  }  
  free(order);
}

/* no olvide programar ademas la funcion que ejecutara cada thread */
