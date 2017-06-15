#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"


int main() {
    Graph g=GRAPHinit(5);
    Graph pontes=GRAPHinit(5);
    GRAPHinsertA(g,2,1);                            //so aceita valores validos!!!!
    GRAPHinsertA(g,1,2);
    GRAPHinsertA(g,2,3);
    GRAPHinsertA(g,3,2);
    GRAPHinsertA(g,2,4);
    GRAPHinsertA(g,4,2);
    GRAPHinsertA(g,3,4);
    GRAPHinsertA(g,4,3);
    GRAPHinsertA(g,4,5);
    GRAPHinsertA(g,5,4);


    printf("arestas do grafo:\n");
    GRAPHshow(g);

    if (GRAPHreach(g,2,1)){
        printf("existe caminho entre %d e %d\n",2,1);
    }else printf("caminho nao encontrado");

    UGRAPHbridges(g ,pontes);                                   //printa as pontes no grafo
    printf("pontes do grafo:\n");
    GRAPHshow(pontes);

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
