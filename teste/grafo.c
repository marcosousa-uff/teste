//
// Created by cliente on 13/06/2017.
//
#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"

static int low[1000];
static int cnt, pre[1000];
static vertex parent[1000];

static int visit[1000];// cria um vetor de visitados se a caminho de um vertice ate 4 o numero visit[4] vai conter o valor 1

struct graph {
    int V;
    int A;
    link *adj;
};

struct node {
    vertex w;
    link next;
};


Graph GRAPHinit( int V){//inicia o grafo com o numero de vertices ja determinado a função so aceita valores validos
    vertex v;
    Graph G = (Graph) malloc(sizeof *G);            //aloca memoria do grafo
    G->V = V;                                       //diz o numero maximo de vertices
    G->A = 0;                                       //inicia com 0 arestas
    G->adj = (link *) malloc(V * sizeof (link));    //aloca memoria do link de adjacencias
    for (v = 1; v <= V; ++v)                         //inicia tudo como null
        G->adj[v] = NULL;
    return G;
}

static link NEWnode( vertex w, link next) {         //função adiciona uma adjacencia ao link de adjacencias
    link a = (link) malloc(sizeof (struct node));   //aloca na memoria uma nova adjacencia
    a->w = w;                                       //atribui o valor do vertice dessa nova adjacencia
    a->next = next;                                 //faz a nova adjacencia apontar para o link de adjacencias
    return a;
}

void GRAPHinsertA( Graph G, vertex v, vertex w) {   /*insere Digrafo para inserir grafo tem que chamar duas vezes
                                                      ou colocar uma chamada recursiva invertendo v e w
                                                      a funçao so aceita valores validos!!!*/
    link a;
    for (a = G->adj[v]; a != NULL; a = a->next)     //confere se ja existe uma adjacencia igual a que voce esta inserindo
        if (a->w == w) return;                      //se ja existir sai da função

    G->adj[v] = NEWnode( w, G->adj[v]);             //adiciona uma nova adjacencia
    G->A++;                                         //incrementa contador de adjacencias
}
vertex randV( Graph G) {                            //cria valores random
    double r;
    r = rand( ) / (RAND_MAX + 1.0);
    return r * G->V;
}
Graph GRAPHrand( int V, int A) {                    //insere adjacencias com valores random
    Graph G = GRAPHinit( V);
    while (G->A < A) {
        vertex v = randV( G);
        vertex w = randV( G);
        if (v != w)
            GRAPHinsertA( G, v, w);
    }
    return G;
}
void GRAPHshow( Graph G) {                          //metodo mostra
    vertex v;                                       //so mostra grafos do tipo lista
    link a,b;

    for (v = 1; v <= G->V; ++v) {
        if(G->adj[v]!=NULL) {                    //se existe adjacencia percorre o link de adjacencia ate o final
            for (a = G->adj[v]; a != NULL; a = a->next) {
                printf("(%d , %d)", v, a->w);      //printa todas as adjacencias
            }
        }
        printf("\n");
    }
}

void removeVertice(Graph G ,vertex v, vertex w){    //remove um digrafo
    link a,p;
    a =G->adj[v];
    if(a==NULL){                                    //se nao exite retorna
        printf("nao exite esse vertice\n");
        return;
    }
    if(a->w==w){                                    //se o primeiro da lista for o vertice W
        G->adj[v]=a->next;
        free(a);
        printf("removido (%d , %d)\n",v,w);
        return;
    }else {                                         //busca o vertice w a partir do primeiro da lista
        for (a = G->adj[v]; a->next != NULL; a = a->next) {
            if(a->next->w==w){
                p=a->next;
                a->next=a->next->next;
                free(p);
                printf("removido (%d , %d)\n",v,w);
                return;
            }

        }
    }
    printf("nao existe adjacencia (%d , %d)\n",v,w);

}
void libera(Graph G){           //libera memoria alocada
    if(G==NULL)return;
    vertex v;
    link a,p;
    for (v = 1;  v<=G->V ; v++) {
        if(G->adj[v]!=NULL){
            a = G->adj[v];
            while (a != NULL) {
                p = a;
                a = a->next;
                free(p);
            }
            free(G->adj[v]);
        }
    }
    free(G);
    printf("\nremovido");
}
int GRAPHreach( Graph G, vertex s, vertex t)    //popula o vetor visit[] com zeros e chama reachR que dis se a caminho
{
    for (vertex v = 0; v < G->V; ++v)
        visit[v] = 0;
    reachR( G, s);                              //chamada do metodo reachR que vai marcando com 1 oque ele ja visitou
    if (visit[t] == 0) return 0;                //retorna verdadeiro se o valor de t foi visitado por reachR
    else return 1;                              //poderia ser simplesmente return visit[t]
}
static void reachR( Graph G, vertex v){         //visita todos os vertices a partir do vertice v
    visit[v] = 1;
    for (link a = G->adj[v]; a != NULL; a = a->next)
        if (visit[a->w] == 0)                   //se um vertice não foi visitado visita todos a partir dele
            reachR( G, a->w);
}
void UGRAPHbridges( UGraph G,Graph P)
{
    vertex v;
    for (v = 1; v <= G->V; ++v)
        pre[v] = parent[v] = -1;
    cnt = 0;
    for (v = 1; v <= G->V; ++v)
        if (pre[v] == -1) {
            parent[v] = v;
            bridgesR( G, v,P);
        }
}
static void bridgesR( UGraph G, vertex v,Graph P)
{
    link a; int min;
    pre[v] = cnt++;

    min = pre[v];
    for (a = G->adj[v]; a != NULL; a = a->next) {
        vertex w = a->w;
        if (pre[w] == -1) {
            parent[w] = v;
            bridgesR( G, w ,P);
            if (low[w] < min) /*A*/
                min = low[w];
        }
        else {
            if (pre[w] < min && w != parent[v]) /*B*/
                min = pre[w];
        }
    }
    low[v]= min;
        for (v = 1; v <= G->V; ++v)
            if (low[v] == pre[v] && parent[v] != v) {
                /* arco parent[v]-v faz parte de ponte */
                //printf("%d-%d\n", parent[v], v);                  //estava printando mais de uma vez o mesmo grafo
                GRAPHinsertA(P,parent[v],v);                        //resolvi colocar o resultado em outro grafo
            }
}

