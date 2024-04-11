#include "the5.h"


typedef enum {WHITE, GRAY, BLACK } colorFlag;


typedef struct{
    int ID;
    colorFlag color;
    
    int d;
    int f;
    
} vertex;


struct GRAPH{
    
    int vertexCount;
    
    std::vector<vertex*> vertices;
    std::vector<std::vector<int>> adj;
    
    
    GRAPH(const std::vector<std::vector<int>>& matrix)
    {
        vertexCount = matrix.size();
        adj.resize(vertexCount);
        for(int i=0; i<vertexCount; ++i)
        {
            vertex* v = new vertex;
            v->ID = i;
            v->color = WHITE;
            vertices.push_back(v);
            
            for(int j=0; j<vertexCount; ++j)
            {
                if( (matrix[j][i] == 1) && (i!=j) ) //Avoiding self loops
                    adj[i].push_back(j);
            }
        }
    }
    
    
    ~GRAPH()
    {
        for(int i=0 ; i<vertexCount; ++i)
            delete vertices[i];
    }
};





void DFS_Visit( GRAPH& G, 
                int id,
                bool& isCompilable,
                std::vector<int>& stack,
                std::vector<std::vector<int>>& cyclicDep,
                std::vector<int>& compileOrder,
                int& t
                )
{
    
    ++t;
    G.vertices[id] -> color = GRAY;
    G.vertices[id] -> d = t;
    
    stack.push_back(id);    //(1)
    
    for(auto& i : G.adj[id]) 
    {
        if(G.vertices[i]->color == WHITE)
            DFS_Visit(G, i, isCompilable, stack, cyclicDep,compileOrder, t);
        
        else if(G.vertices[i]->color == GRAY)
        {
            std::vector<int> circle;

            for (int k = stack.size() - 1; k > -1 ;--k) 
            {
                
                circle.push_back(stack[k]);
                if (stack[k] == i)
                        break;  
            }
            
            cyclicDep.push_back(circle);
            isCompilable = false;
            
        }
    }
    
    stack.pop_back();   //(2)

    ++t;
    G.vertices[id] ->  color = BLACK;
    G.vertices[id] -> f = t;
    
    compileOrder.push_back(id);
}
    

void DFS(   GRAPH& G, 
            bool& isCompilable,
            std::vector<std::vector<int>>& cyclicDep,
            std::vector<int>& compileOrder
            )
{
    int t=0;
    
    for(int i=0; i < G.vertexCount ; i++)
    {
        std::vector<int> stack;
        if(G.vertices[i] -> color == WHITE)
            DFS_Visit(G, i, isCompilable,stack,cyclicDep,compileOrder,t);
    }
    
}


void run(const std::vector<std::vector<int>>& dependencyMatrix, 
         bool& isCompilable,
         std::vector<int>& compileOrder, 
         std::vector<std::vector<int>>& cyclicDependencies)
{
    
    GRAPH G(dependencyMatrix);
    
    isCompilable = true;
    

    DFS(G, isCompilable,cyclicDependencies, compileOrder);
    
}
         







         
    