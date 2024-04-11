#include "the4.h"

int divide_land(int X, int Y, bool** possible_plots){
    
    std::vector<std::vector<int>> W(X+1, std::vector<int>(Y+1));

    for(int i=0; i<=X; ++i)
        W[i][0] = 0;

    for(int i=0; i<=Y; ++i)
        W[0][i] = 0;
       
    
    for(int i=1; i<= X; ++i)   //max area for each X = i  
    {
        for(int j=1; j<= Y; ++j)   //for each Y = 1,2,...,Y
        {
            if(possible_plots[i][j])
                W[i][j] = i*j;
            
            else
            {
                for(int h=1; h<j; ++h)  //h<Y for current Y
                    W[i][j] = std::max( W[i][j]  , W[i][h] + W[i][j-h] );
                
               
                for(int v=1; v<i; ++v)  //v<X for current X
                    W[i][j] = std::max( W[i][j]  , W[i-v][j] + W[v][j] );
            }
            
        }
    }
    
    return  X*Y - W[X][Y];
}

