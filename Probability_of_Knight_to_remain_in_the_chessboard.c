/*
Let's have an N X N chess board and a knight is at the position (x,y). It is provided that the knight can take 'k' steps only, for each step it can choose any one out of the 8 directions at random.
We need to find the probability that after taking K steps and still the knight is on the chess board, but keeping one thing in mind that once the knight leaves the chess board it can't enter again.

Example:

We have an 8x8 chessboard, current position of the knight is at (x, y) = (0, 0).
For each step, the knight can choose 1 out of 8 directions. 

So, from (0, 0) there are only 2 out of 8 directions possible to keep the knight inside the board and for all other directions the knight will go outside,
therefor the probability = 2/8 = 0.25

Now after taking k steps the knight is at position (x, y). There are 8 possible ways by which the Knight can reach to (x, y) in one step, and those ways are 
(x-1, y+2), (x+1, y-2), (x+2, y+1), (x-2, y-1), (x+1, y+2), (x-1, y-2), (x+1, y-2), (x-2, y+1).

What if we already knew the probabilities of reaching these 8 positions after K-1 steps? 
Then, the final probability after K steps will simply be equal to the (Σ probability of reaching each of these 8 positions after K-1 steps)/8;
Divison by 8 is because each position on board have total of eight choices and (x, y) is one of them.
Probability for the positions outside the chess board will be equal to 0 or we can simply neglect it.


We are required to keep track for the probabiities of each position for every number of steps and that's why it becomes a dynamic programming problem.
For that we will take an array dp[x][y][steps] to store the probability for reaching (x, y) after [steps].
We can take base case as..if the no. of steps is 0, then the knight will be inside the board with probability = 1.

Implementation :
*/

#include <bits/stdc++.h> 
using namespace std; 
#define N 8 
int xx[] = { 1, 2, 2, 1, -1, -2, -2, -1 }; 
int xy[] = { 2, 1, -1, -2, -2, -1, 1, 2 }; 
  

bool in(int a, int b) 
{ 
    return (a >= 0 and a < N and b >= 0 and b < N); 
} 
  
double fProb(int x, int y, int ss) 
{ 
   
    double d1[N][N][N]; 
  
    for (int e = 0; e < N; ++e) 
        for (int f = 0; f < N; ++f) 
            d1[e][f][0] = 1; 
  
    
    for (int s = 1; s <= ss; ++s) 
    { 
        
        for (int x = 0; x < N; ++x) 
        { 
            for (int y = 0; y < N; ++y) 
            { 
                double prob = 0.0; 
  
                
                for (int i = 0; i < 8; ++i) 
                { 
                    int nx = x + xx[i]; 
                    int ny = y + xy[i]; 
  
                    
                    if (in(nx, ny)) 
                        prob += d1[nx][ny][s-1] / 8.0; 
                } 
  
                
                d1[x][y][s] = prob; 
            } 
        } 
    } 
  
    
    return d1[x][y][ss]; 
} 
  

int main() 
{ 
    
    int K = 3; 
  
    cout << fProb(0, 0, K) << endl; 
  
    return 0; 
} 


Output:

0.125

Time Complexity: O(NxNxKx8) which is O(NxNxK), where N is the size of the board and K is the number of steps.
Space Complexity: O(NxNxK)



