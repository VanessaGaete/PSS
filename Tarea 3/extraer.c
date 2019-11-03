#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void extraer(char *archivo){
    
    FILE *dic= fopen(archivo, "r+"); 
    if (dic==NULL) { // Opcional
        perror("fopen");
        exit(1);
    }
    
    //Se lee la primera linea para saber cuantos elementos hay en la cola
    char bufCant[6];        // Aqui se guarda la primera linea
    fread(bufCant, 5, 1, dic);
    char *number=bufCant;   //Number guarda la la cantidad de elementos de la cola
    if(*number=='0'){
        printf("error: cola.txt esta vacia\n");
        exit(2);
    }


    //No se de qué tamaño debe ser el arreglo
    char bufLine[18];   // Aqui se guardan las líneas que se van leyendo
    size_t rc;
    int leidos= 0;      // Cantidad de líneas que se han leído
    int min=1000000;          // Valor de la mayor prioridad
    int position=0;     // La posicion de la persona con mayor prioridad
    char *pName;         // El nombre de la persona con mejor prioridad
    char name[11];
    char *priority;     // El valor de la prioridad que se está leyendo
    
    while ((rc= fread(bufLine, 17, 1, dic))==1) { 
        
        priority=bufLine; //quizas deba poner 0 en alguna parte
        //Se pone un cero al final de bufLine para que sea un string
        
        //Se devuelve el puntero al lugar donde empieza el número
        priority+=10;
        int p=atoi(priority);
        if(p<min){
            min=p;
            position=leidos;
            memcpy(name,bufLine,10);
            pName=name;
            pName+=10;
            *pName='\0';
            pName-=10;
        }

        leidos++; // contabilizar leidos
        if(leidos==atoi(number)){
            break;
        }
    }

    //Se muestra en consola el nombre de la persona eliminada
    printf("%s\n",pName);
    
    //Se copia la última línea en la que fue eliminada
    int lastLine=4+1+(atoi(number)-1)*(16+1);
    int line=4+1+position*(16+1);
    fseek(dic,lastLine, SEEK_SET); 
    if(fread(bufLine, 17, 1, dic)==1){
        fseek(dic,line, SEEK_SET);
        priority=bufLine;
        priority+=18;
        *priority=' ';
        fwrite(bufLine, 17, 1, dic); 
    }

    //Copiado del enunciado
    char s[6];
    sprintf(s, "%-4d\n", atoi(number)-1);
    //Se disminuye la cantidad de elementos en la cola
    fseek(dic, 0, SEEK_SET);
    fwrite(s, 5, 1, dic); 


}

int main(int argc, char **argv) {
    if (argc!=2) {
        printf("%s","ingresar: <File name>\n");
        exit(1);
    }
  
    char *nameFile= argv[1];
    extraer(nameFile);
    return 0;
}
