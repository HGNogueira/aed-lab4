#ifndef __graphM__
#define __graphM__ 1

typedef struct _graph Graph;

Graph *graphInit(int nodes);
int insertEdge(Graph *g, int v, int w, int value);
int deleteEdge(Graph *g, int v, int w);
float getDensity(Graph *g);
int getBranches(Graph *g);
int getMaxGrade(Graph *g);
int getBranch(Graph *g, int v, int w);
void destroyGraph(Graph *g);

#endif
