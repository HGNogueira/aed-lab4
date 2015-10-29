#include<stdio.h>
#include<stdlib.h>
#include"graphM.h"

struct _graph{
    int nodes;
    int branches;
    int **adjM;
    int *grade;
    float density;
};

Graph *graphInit(int nodes) {
    int i = 0, j = 0;
    Graph *g = (Graph*) malloc(sizeof(Graph));

    if(g == NULL) {
        fprintf(stderr, "Memory error\n");
        return NULL;
    }

    g->nodes = nodes;
    g->branches = 0;
    g->density = 0;

    g->adjM = (int**) malloc(sizeof(int*) * nodes);
    if(g->adjM == NULL){
        fprintf(stderr, "Memory error\n");
        free(g);
        return NULL;
    }

    for( i = 0; i < nodes; i++) {
        g->adjM[i] = (int*) malloc(sizeof(int) * nodes);
        for(j = 0; j < nodes; j++)
            g->adjM[i][j] = 0;
    }

    g->grade = (int*) malloc(sizeof(int) * nodes);
    for(i = 0; i < nodes; i++)
        g->grade[i] = 0;

    return g;
}

int insertEdge(Graph *g, int v, int w, int value) {
    if(g->adjM[v][w] == 0 && value != 0) {
        g->adjM[v][w] = value;
        g->adjM[w][v] = value;
        g->branches++;
        g->density = 2 * g->branches/((float) g->nodes);
        g->grade[w]++;
        g->grade[v]++;
        return 1;
    }
    return 0;
}

float getDensity(Graph *g) {
    return g->density;
}

int getBranches(Graph *g) {
    return g->branches;
}

int getMaxGrade(Graph *g) {
    int maxGrade = 0;
    int i = 0;

    for(i = 0; i < g->nodes; i++){
        if(g->grade[i] > maxGrade)
            maxGrade = g->grade[i];
    }
    return maxGrade;
}

int deleteEdge(Graph *g, int v, int w) {
    if(g->adjM[v][w] != 0){
        g->adjM[v][w] = 0;
        g->adjM[w][v] = 0;
        g->grade[v]--;
        g->grade[w]--;
        g->branches--;
        g->density = 2 * g->branches/((float) g->nodes);
        return 1;
    }
    return 0;
}

int getBranch(Graph *g, int v, int w) {
    return g->adjM[v][w];
}

void destroyGraph(Graph *g){
    int i = 0;
    
    for(i = 0; i < g->nodes; i++)
        free(g->adjM[i]);
    free(g->adjM);
    free(g->grade);
    free(g);
}
