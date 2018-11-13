/*
Probability of Knight to remain in the chessboard

Given an NxN chessboard and a Knight at position (x,y). The Knight has to take exactly K steps, where at each step it chooses any of the 8 directions uniformly at random. What is the probability that the Knight remains in the chessboard after taking K steps, with the condition that it can’t enter the board again once it leaves it.

Examples:

Let's take:
8x8 chessboard,
initial position of the knight : (0, 0),
number of steps : 1
At each step, the Knight has 8 different positions to choose from. 

If it starts from (0, 0), after taking one step it will lie inside the
board only at 2 out of 8 positions, and will lie outside at other positions.
So, the probability is 2/8 = 0.25

One thing that we can observe is that at every step the Knight has 8 choices to choose from. Suppose, the Knight has to take k steps and after taking the Kth step the knight reaches (x,y). There are 8 different positions from where the Knight can reach to (x,y) in one step, and they are: (x+1,y+2), (x+2,y+1), (x+2,y-1), (x+1,y-2), (x-1,y-2), (x-2,y-1), (x-2,y+1), (x-1,y+2).
What if we already knew the probabilities of reaching these 8 positions after K-1 steps? Then, the final probability after K steps will simply be equal to the (Σ probability of reaching each of these 8 positions after K-1 steps)/8;
Here we are dividing by 8 because each of these 8 positions have 8 choices and position (x,y) is one of the choice.
For the positions that lie outside the board, we will either take their probabilities as 0 or simply neglect it.

Since, we need to keep track of the probabilities at each position for every number of steps, we need Dynamic Programming to solve this problem.
We are going to take an array dp[x][y][steps] which will store the probability of reaching (x,y) after (steps) number of moves.
Base case : if number of steps is 0, then the probability that the Knight will remain inside the board is 1.

Here is the implementation :
*/

// C++ program to find the probability of the 
// Knight to remain inside the chessboard after 
// taking exactly K number of steps 
#include <bits/stdc++.h> 
using namespace std; 
  
// size of the chessboard 
#define N 8 
  
// direction vector for the Knight 
int dx[] = { 1, 2, 2, 1, -1, -2, -2, -1 }; 
int dy[] = { 2, 1, -1, -2, -2, -1, 1, 2 }; 
  
// returns true if the knight is inside the chessboard 
bool inside(int x, int y) 
{ 
    return (x >= 0 and x < N and y >= 0 and y < N); 
} 
  
// Bottom up approach for finding the probability to 
// go out of chessboard. 
double findProb(int start_x, int start_y, int steps) 
{ 
    // dp array 
    double dp1[N][N][N]; 
  
    // for 0 number of steps, each position 
    // will have probability 1 
    for (int i = 0; i < N; ++i) 
        for (int j = 0; j < N; ++j) 
            dp1[i][j][0] = 1; 
  
    // for every number of steps s 
    for (int s = 1; s <= steps; ++s) 
    { 
        // for every position (x,y) after 
        // s number of steps 
        for (int x = 0; x < N; ++x) 
        { 
            for (int y = 0; y < N; ++y) 
            { 
                double prob = 0.0; 
  
                // for every position reachable from (x,y) 
                for (int i = 0; i < 8; ++i) 
                { 
                    int nx = x + dx[i]; 
                    int ny = y + dy[i]; 
  
                    // if this position lie inside the board 
                    if (inside(nx, ny)) 
                        prob += dp1[nx][ny][s-1] / 8.0; 
                } 
  
                // store the result 
                dp1[x][y][s] = prob; 
            } 
        } 
    } 
  
    // return the result 
    return dp1[start_x][start_y][steps]; 
} 
  
// Driver program 
int main() 
{ 
    // number of steps 
    int K = 3; 
  
    cout << findProb(0, 0, K) << endl; 
  
    return 0; 
} 


Output:

0.125

Time Complexity: O(NxNxKx8) which is O(NxNxK), where N is the size of the board and K is the number of steps.
Space Complexity: O(NxNxK)



