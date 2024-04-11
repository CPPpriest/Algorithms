#include "the6.h"


struct vertex {
    int id;
    int key;
    bool inMST;
    vertex* parent;
    int d;
};



struct greater{
    bool operator()(vertex* a, vertex* b)
    {
        return a->key > b->key;
    }
};



int find_structure( std::vector< std::vector<std::pair<int,int> > >& bond_energies, 
                    std::vector< std::vector<std::pair<int,int> > >& lowest_energy_structure) 
{
    int lowest_total_energy = 0;
    
    std::priority_queue < vertex*, std::vector<vertex*>, greater > minPQ;
    
    int V = bond_energies.size();
    
    
    std::vector<vertex*> vertices;
    
    //initialize vertices and minPQ and source vertex
    
    
    for(int i=0; i<V; ++i)
    {
        vertex* v = new vertex;
        v->id = i;
        v->key = INT_MAX;
        v->inMST = false;
        v->parent = nullptr;
        v->d = 0;
        
        vertices.push_back(v);
        
        minPQ.push(v);
    }
    
    vertices[0]->key = 0;
    
    
    while( ! minPQ.empty())
    {
        vertex* sVertex = minPQ.top();
        minPQ.pop();
        
        
        if (sVertex->inMST)
            continue;
            
            
        sVertex->inMST = true;
        lowest_total_energy += sVertex->key;
        
        
        if (sVertex->parent != nullptr) 
        {
            std::pair<int, int> edge(sVertex->parent->id, sVertex->key);
            lowest_energy_structure[sVertex->id].push_back(edge);
            
            std::pair<int, int> edge2(sVertex->id, sVertex->key);
            lowest_energy_structure[sVertex->parent->id].push_back(edge2);
        }
        

        
        for(int i=0; i<bond_energies[sVertex->id].size() ; ++i)
        {
            //if v not in mst AND w(s,v) is smaller than v's key
            int vId = bond_energies[sVertex->id][i].first;
            int s_v_energy = bond_energies[sVertex->id][i].second;
            
            if( (vertices[vId]->key > s_v_energy) && (vertices[vId]->inMST == false) ) 
            {
                vertices[vId]->key = s_v_energy;
                vertices[vId]->parent = sVertex;
                
                 minPQ.push(vertices[vId]);
                 
                 
            
            }
        }
    }
    
    for(int i=0; i<V; ++i)
        delete vertices[i];
    
    return lowest_total_energy;
}



void dfs_visit(std::vector<vertex*>& vertices, std::vector< std::vector<std::pair<int,int> > >& graph, vertex* parent, int v ) 
{
    //inMST used as VISITED flag
    
    vertices[v]->inMST = true;
    vertices[v]->parent = parent;
    
    for(int i=0; i < graph[v].size() ; ++i)
    {
        
        int u = graph[v][i].first ;
    
        if(!vertices[u]->inMST)
        {
            vertices[u]->d = vertices[v]->d + 1;
            dfs_visit(vertices,graph,vertices[v],u);
        }
        
    }
    
}


int find_longest_chain(std::vector< std::vector<std::pair<int,int> > >& molecule_structure, std::vector<int>& chain){
    
    int longest_chain_size = 0;
    
    int V = molecule_structure.size();
    std::vector<vertex*> vertices;
    
    for(int i=0; i<V; ++i)
    {
        vertex* v = new vertex{i,-1,false,nullptr,0};
        vertices.push_back(v);
    }

    dfs_visit(vertices, molecule_structure,nullptr, 0);
    
    int maxD = 0;
    for(int i=0; i<V; ++i)
    {
        if(vertices[i]->d > vertices[maxD]->d)
        {
            maxD = i;   
        }
        vertices[i] -> d =0;
        vertices[i] -> inMST = false;
    }
    
    
    dfs_visit(vertices, molecule_structure, nullptr, maxD);
    
    
    
    
    
    for(int i=0; i<V; ++i)
    {
        if(vertices[i]->d > vertices[maxD] -> d)
        {
            maxD = i;   
        }
        
    }

    int curr = maxD;
    chain.push_back(curr);
    while (vertices[curr]->d > 0) 
    {
        for (int i=0; i<molecule_structure[curr].size(); ++i) 
        {
            int u = molecule_structure[curr][i].first;
            if (vertices[u]->d == vertices[curr]->d - 1) 
            {
                chain.push_back(u);
                curr = u;
                break;
            }
        }
    }
    
    longest_chain_size = vertices[maxD]->d;
    
    
    
    for(int i=0; i<V; ++i)
        delete vertices[i];
    
    return longest_chain_size;
}















