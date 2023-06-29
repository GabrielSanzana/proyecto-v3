#ifndef Heap_h
#define Heap_h

typedef struct Heap Heap;

Heap* createHeap();
void* heap_top(Heap* pq);
void heap_popMax(Heap* pq);
void heap_pushMin(Heap* pq, void* data, int priority);
void heap_pushMax(Heap* pq, void* data, int priority);
void heap_pop(Heap* pq);


#endif 

