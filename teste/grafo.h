//
// Created by cliente on 13/06/2017.
//

#ifndef TESTE_GRAFO_H
#define TESTE_GRAFO_H

#endif //TESTE_GRAFO_H
#define vertex int


typedef struct node *link;

typedef struct graph *Graph;

void UGRAPHbridges( UGraph G,Graph P);

static void bridgesR( UGraph G, vertex v,Graph P);

int GRAPHreach( Graph G, vertex s, vertex t);

static void reachR( Graph G, vertex v);

Graph GRAPHinit( int V);

static link NEWnode( vertex w, link next);

void GRAPHinsertA( Graph G, vertex v, vertex w);

vertex randV( Graph G);

Graph GRAPHrand( int V, int A);

void GRAPHshow( Graph G);

void removeVertice(Graph G ,vertex v, vertex w);

void libera(Graph G);



