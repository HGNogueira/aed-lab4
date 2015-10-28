#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _graph{
    int nodes;
    int branch;
    int **adjM;
    int *grade;
    float density;
} Graph;

int main(int argc, char *argv[]) 
{
    FILE *fp;
    char *fileOut;
    Graph *graph;
    int n;
    int i = 0;
    int j = 0;
    int maxGrade = 0;


    if(argc < 2){
        fprintf(stderr, "USAGE:\n\t %s <input file name>\n", argv[0]);
        return 1;
    }

    fp = fopen( argv[1], "r");
    if(fp == NULL) {
        fprintf(stderr, "ERROR: couldn't open file %s\n", argv[1]);
        return 2;
    }

    graph = (Graph*) malloc(sizeof(Graph));

    if(graph ==  NULL) {
        fprintf(stderr, "ERROR: memory error\n");
        return 3;
    }

    /* reading adjacency matrix from file */

    fscanf(fp, "%d", &graph->nodes);

    if(graph->nodes <= 0) {
        fprintf(stderr, "ERROR: invalid n (node number): %d\n", graph->nodes);
        fclose(fp);
        return 4;
    }

    n = graph->nodes;
    graph->density = 0;

    graph->adjM = (int**) malloc(n * sizeof(int*));
    for(i = 0; i < n; i++)
        graph->adjM[i] = (int*) malloc(n * sizeof(int));
    
    if(graph->adjM == NULL) {
        fprintf(stderr, "ERROR: memory error\n");
        return 3;
    }

    graph->grade = (int*) malloc(sizeof(int) * n);
    for(i = 0; i < n; i++)
        graph->grade[i] = 0;

    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++)
            fscanf(fp, "%d", &graph->adjM[i][j]);
    }
    fclose(fp);

    /* calculating graph density, max node grade
     * and total number of branches */

    graph->branch = 0;
    for(i = 0; i < n; i++) {
        for(j = 0; j <= i; j++) {
            if(graph->adjM[i][j] >= 1){
                graph->density += 1.;
                graph->branch++;
                graph->grade[i]++;
                graph->grade[j]++;
            }
        }
    }
    graph->density = graph->density * 2 / ((float) graph->nodes);

    maxGrade = 0;
    for(i = 0; i < n; i++) {
        if(graph->grade[i] > maxGrade)
            maxGrade = graph->grade[i];
    }

    fprintf(stdout, "Graph density: %f\n", graph->density);
    fprintf(stdout, "Max grade: %d\n", maxGrade);

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

    fprintf(fp, "%d\n%d\n", graph->nodes, graph->branch);

    for(i = 0; i < n; i++){
        for(j = 0; j <= i; j++){
            if(graph->adjM[i][j] >= 1)
                fprintf(fp, "%d %d %d\n", j, i, graph->adjM[i][j]);
        }
    }


    fclose(fp);
    
    /* freeing memory */
    
    for(i = 0; i < n; i++)
        free(graph->adjM[i]);
    free(graph->adjM);
    free(graph->grade);
    free(graph);
    free(fileOut);




    return 0;
}

