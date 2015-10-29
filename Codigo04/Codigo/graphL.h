#ifndef __graphL__h
#define __graphL__h 1
typedef struct _edge Edge;
typedef struct _graphL GraphL;

GraphL *graphInit(int nodes);
void insertEdge(GraphL *g, int v, int w, int value);
void deleteEdge(GraphL *g, int v, int w);
void destroyGraph(GraphL *g);

#endif
