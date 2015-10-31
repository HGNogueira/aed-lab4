#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"graphL.h"
#include"LinkedList.h"
#include"defs.h"

int main(int argc, char* argv[]) {
    FILE *fp;
    char *fileOut;
    int i = 0;
    int n, r;
    int v, w, value;
    LinkedList *edges, *edgesAux;
    Edge *e;
    GraphL *g;

    if (argc < 2) {
        fprintf(stderr,"Usage:\n\t%s <nome_ficheiro_lista_adjacencias>.ram\n", argv[1]);
        return 1;
    }

    fp = fopen( argv[1], "r" );

    if(fp == NULL) {
        fprintf(stderr, "Can't open file %s\n", argv[1]);
        return 2;
    }

    fscanf(fp, "%d", &n);

    if(n <= 0) {
        fprintf(stderr, "Invalid number of n: %d", n);
        return 3;
    }

    fscanf(fp, "%d", &r);

    g = graphInit(n);
    for(i = 0; i < n; i++) {
        fscanf(fp, "%d %d %d", &v, &w, &value);
        insertEdge(g, v, w, value); 
    }

    fclose(fp);

    fileOut = (char*) malloc(sizeof(char) * (strlen(argv[1]) + 2));
    strncpy(fileOut, argv[1], strlen(argv[1]) - strlen(".adj"));
    fileOut[strlen(argv[1]) - strlen(".adj")] = '\0';
    strcat(fileOut, ".ladj");

    fp = fopen( fileOut, "w");

    fprintf(fp, "%d\n", n);

    for(i = 0; i < n; i++) {
        edges = getEdgesOfNode(g, i);
        edgesAux = edges;
        while(edgesAux != NULL) {
            e = (Edge *) getItemLinkedList(edgesAux);
            w = getDestNode(e);
            value = getValueEdge(e);
            fprintf(fp, "%d:%d ", w, value);
            edgesAux = getNextNodeLinkedList(edgesAux);
        }
        fprintf(fp, "-1 \n");
        freeLinkedList(edges, freeEdge);
    }

    fclose(fp);

    free(fileOut);
    destroyGraph(g);

    return 0;
}
