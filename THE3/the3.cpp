#include "the3.h"

// do not add extra libraries, but you can define helper functions below.

int LCS(    std::string A, std::string B, int a, int b, int& count, int call_count, std::string &possible_alignment )
{
    ++count;
    if(count > call_count)
        return -1;
    
    if(a == 0 || b == 0)
        return 0;
    
    if(A[a-1] == B[b-1])
    {
        possible_alignment += A[a-1];
        int sc = LCS(A, B, a-1, b-1, count, call_count, possible_alignment);
        
        
        if(sc == -1)
            return -1;
        
        return sc+1;
    }
    
    else
    {
        std::string s1 = '.' + possible_alignment;
        std::string s2 = '_' + possible_alignment;
        
        int c1 = LCS(A, B, a-1, b, count, call_count, s1);
        int c2 = LCS(A, B, a, b-1, count, call_count, s2);


        if(c1 > c2)
        {
            possible_alignment = s1;
            return c1;
        }
        
        else
        {
            possible_alignment = s2;
            return c2;
        }
    }
    
}


/* 
PART 1
you are expected to call recursive_alignment (as the name suggests) recursively to find an alignment. 
initial call_count value given to you will be 0.
you should check if call_count >= 1000000, if so, set possible_alignment string to "STACK LIMIT REACHED", return INT_MIN (or anything - it will not be checked).
*/
int recursive_alignment(std::string sequence_A, std::string sequence_B, int gap, int mismatch, int match, std::string &possible_alignment, int call_count){
    int highest_alignment_score;
    
    int a = sequence_A.length();
    int b = sequence_B.length();
   
    int count = 0;
    int lcs= LCS(sequence_A, sequence_B, a, b, count, call_count, possible_alignment);
    
    if(lcs == -1)
    {
        possible_alignment = "STACK LIMIT REACHED";
        return -5;
    }
    
    reverse(possible_alignment.begin(), possible_alignment.end());
    int gp = b-a;    
    
    int mss = b-lcs-gp;
    
    highest_alignment_score = (lcs * match) - (mss * mismatch) - (gp * gap);
    
    return highest_alignment_score;    
}

/* 
PART 2
you are expected to create a dynamic programming table to find the highest alignment score. 
then you will need to reconstruct a possible alignment string from the table.
*/




void STR(int **s, std::string sequence_A, int i, int j, std::string &possible_alignment )
{
    if(j == 0 && j == 0)
        return; 
    
    if(i==0 && j != 0)
    {
        STR(s,sequence_A, i, j-1, possible_alignment);
        possible_alignment += "_";
        return;
    }
    
    
    if(s[i][j] == 1)
    {
        STR(s,sequence_A, i-1, j-1, possible_alignment);
        possible_alignment += sequence_A[i-1];
        return; 
    }
    if(s[i][j] == 2)
    {
        
        STR(s,sequence_A, i-1, j, possible_alignment);
        possible_alignment += ".";
        
        return; 
    }
    if(s[i][j] == 3)
    {
        
        STR(s,sequence_A, i, j-1, possible_alignment);
        possible_alignment += "_";
        return; 
    }
    
}




int dp_table_alignment(std::string sequence_A, std::string sequence_B, int gap, int mismatch, int match, std::string &possible_alignment){
    int highest_alignment_score;
    
    int gp=0;
    int mss=0;
    
    int n=sequence_A.length();
    int m=sequence_B.length();
    //First string guaranteed to be smaller equal to second string
    gp = m-n;
    mss = n;
    
    
    int** r = new int* [n+1] ; // length of the LCS for S1[0..i] and S1[0..j]
    int** s = new int* [n+1] ;
    
    for(int i=0; i<=n; ++i)
    {
        r[i] = new int[m+1];
        r[i][0] = 0;
        
        s[i] = new int[m+1];
        s[i][0] = 0;
    }
        
    for(int i=0; i<=m; ++i)
    {    
        r[0][i] = 0;
        s[0][i] = 0;
    }
    
    
        
    
    
    //at the end, returns r[n-1][m-1]
    for(int i=1; i <= n; ++i)
    {
        for(int j=1; j <= m; ++j)
        {
            if( sequence_A[i-1] == sequence_B[j-1] )
            {
                r[i][j] = r[i-1][j-1] + 1;
                s[i][j] = 1;    //match
            }        
            else 
            {
                if( r[i-1][j] >= r[i][j-1] )
                {
                    r[i][j] = r[i-1][j] ;
                    s[i][j] = 2;    //gap at B
                }
                else
                {
                    r[i][j] = r[i][j-1] ;
                    s[i][j] = 3;    //gap at A
                }
            
            }    
        }

    }
    
    STR(s, sequence_A, n, m, possible_alignment );
    
    
    highest_alignment_score = (r[n][m] * match) - ( ( mss - r[n][m] ) * mismatch) - (gp * gap); 
    
    
    
    
    for(int i=0; i<=n; ++i)
    {
        delete[] s[i];
    }
    delete[] s;
    
    
    return highest_alignment_score;    
}
