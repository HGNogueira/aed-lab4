#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"graphM.h"

int main(int argc, char *argv[]) 
{
    FILE *fp;
    char *fileOut;
    Graph *g;
    int n;
    int i = 0;
    int j = 0;
    int aux = 0;

    if(argc < 2){
        fprintf(stderr, "USAGE:\n\t %s <input file name>\n", argv[0]);
        return 1;
    }

    fp = fopen( argv[1], "r");
    if(fp == NULL) {
        fprintf(stderr, "ERROR: couldn't open file %s\n", argv[1]);
        return 2;
    }


    /* reading adjacency matrix from file */

    fscanf(fp, "%d", &n);

    if(n <= 0) {
        fprintf(stderr, "ERROR: invalid n (node number): %d\n", n);
        fclose(fp);
        return 4;
    }

    g = graphInit(n);

    for(i = 0; i < n; i++) {
        for(j = 0; j < n ; j++) {
            fscanf(fp, "%d", &aux);
            insertEdge(g, i, j, aux);
        }
    }
    fclose(fp);

    fprintf(stdout, "Graph density: %f\n", getDensity(g));
    fprintf(stdout, "Max grade: %d\n", getMaxGrade(g));

    /* Writing to output file 
     * [number of nodes]
     * [number of branches]
     * [node a] [node b] [branch value]
     * ...
     */

    fileOut = (char*) malloc(sizeof(char) * (strlen(argv[1]) + 1));
    strncpy(fileOut, argv[1], strlen(argv[1]) - strlen(".adj"));
    fileOut[strlen(argv[1]) - strlen(".adj")] = '\0';
    strcat(fileOut, ".ram");

    fp = fopen(fileOut, "w");

    fprintf(fp, "%d\n%d\n", n, getBranches(g));

    for(i = 0; i < n; i++){
        for(j = 0; j <= i; j++){
            if(getBranch(g, i, j) >= 1)
                fprintf(fp, "%d %d %d\n", j, i, getBranch(g, i, j));
        }
    }


    fclose(fp);
    
    /* freeing memory */
    
    destroyGraph(g);
    free(fileOut);

    return 0;
}

