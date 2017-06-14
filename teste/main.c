#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"


int main() {
    Graph g=GRAPHinit(5);
    GRAPHinsertA(g,2,1);                            //so aceita valores validos!!!!
    GRAPHinsertA(g,1,2);
    GRAPHinsertA(g,2,5);
    GRAPHinsertA(g,1,4);
    GRAPHinsertA(g,2,4);
    GRAPHinsertA(g,3,4);
    GRAPHinsertA(g,4,2);
    GRAPHinsertA(g,1,4);
    GRAPHinsertA(g,5,3);
    GRAPHshow(g);

    if (GRAPHreach(g,1,3)){
        printf("existe caminho entre %d e %d",1,3);
    }else printf("caminho nao encontrado");

/*
    removeVertice(g,1,2);
    removeVertice(g,1,3);
    removeVertice(g,4,2);
    removeVertice(g,4,2);


    GRAPHshow(g);
    */
    libera(g);
    g=NULL;


    return 0;
}
