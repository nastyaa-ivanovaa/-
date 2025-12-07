#include "L0804_287.h"

// Инициализация графа
void initialize_graph(graph* g, bool directed) {
    g->nvertices = 0;
    g->nedges = 0;
    g->directed = directed;
    
    for (int i = 1; i <= MAXV; i++) {
        g->edges[i] = nullptr;
    }
}

// Вставка ребра
void insert_edge(graph* g, int x, int y, int weight, bool directed) {
    edgenode* p = new edgenode;
    
    p->weight = weight;
    p->y = y;
    p->next = g->edges[x];
    g->edges[x] = p;
    
    if (!directed) {
        insert_edge(g, y, x, weight, true);
    } else {
        g->nedges++;
    }
}

// Алгоритм Прима
int prim(graph* g, int start) {
    int i;                       // Счетчик
    edgenode* p;                 // Временный указатель
    bool intree[MAXV+1];         // Находится ли вершина уже в дереве
    int distance[MAXV+1];        // Стоимость добавления в дерево
    int parent[MAXV+1];          // Родитель в дереве
    int v;                       // Текущая вершина для обработки
    int w;                       // Кандидат на следующую вершину
    int dist;                    // Наименьшая стоимость расширения дерева
    int weight = 0;              // Вес дерева

    for (i = 1; i <= g->nvertices; i++) {
        intree[i] = false;
        distance[i] = MAXINT;
        parent[i] = -1;
    }

    distance[start] = 0;
    v = start;

    while (!intree[v]) {
        intree[v] = true;
        
        if (v != start) {
            std::cout << "Ребро (" << parent[v] << "," << v << ") в дереве \n";
            weight = weight + distance[v];
        }
        
        p = g->edges[v];
        while (p != nullptr) {
            w = p->y;
            if ((distance[w] > p->weight) && (!intree[w])) {
                distance[w] = p->weight;
                parent[w] = v;
            }
            p = p->next;
        }

        dist = MAXINT;
        for (i = 1; i <= g->nvertices; i++) {
            if ((!intree[i]) && (dist > distance[i])) {
                dist = distance[i];
                v = i;
            }
        }
    }
    
    return weight;
}
