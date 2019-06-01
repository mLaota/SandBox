#ifndef STABLE_MARRIAGE_H
#define STABLE_MARRIAGE_H

#include <vector>
#include <queue>

// Gale-Shapely's Stable Marriage Algorithm

// initialize the std::queue of men to propose
// O(N)
void init_queue(int n, std::queue<int>& q)
{
    for (int i = 1; i <= n; ++i)
    {
        q.push(i);
    }
}

// for each man, record how he is ranked (j) by each woman (i)
// O(N^2)
void init_ranks(int n, std::vector<std::vector<int>>& rank, std::vector<std::vector<int>>& women_prefs)
{
    int temp;
    for(int i =0; i < n; ++i)
    {
        for(int j =0; j < n; ++j)
        {
            temp = women_prefs[i][j]; // represents the man ranked j for woman i
            rank[temp-1][i] = j;
        }
    }
}

// returns a matching represented as a std::vector of women such that pos i={0...N-1} in the std::vector
// holds woman (i+1)'s match
std::vector<int> stable_marriage(int n, std::vector<std::vector<int>> men_prefs, std::vector<std::vector<int>> women_prefs) 
{
    // empty matching (to be returned)
    std::vector<int> matching(n,-1);
    
    // represents rank of m in w's preferences
    // solves the problem of comparing ranks each iteration
    // by preprocessing ranks in O(N^2) and accessing in O(1)
    std::vector<std::vector<int>> rank(n, std::vector<int>(n));
    init_ranks(n,rank,women_prefs);
    
    // list of unmatched men and who they will propose to next
    std::queue<int> unmatched_men;
    init_queue(n,unmatched_men);
    
    // keeps track of what idx to propose to next for each man
    std::vector<int> next_proposal(n, 0);
    
    while (!unmatched_men.empty()) // = O(N^2) ... if all men propose to all women
    {
        // take m from the list of unmatched men
        int m = unmatched_men.front();
        unmatched_men.pop();

        // get the index of next woman to propose to in pref list
        int idx = next_proposal[m-1];     
        
        // if he's proposed to everyone, exit, because the algorithm failed
        if(idx >= n)
        { 
            exit(EXIT_FAILURE);
        }
        ++next_proposal[m-1];

        // w is the woman being proposed to in this iteration
        int w = men_prefs[m-1][idx];
        
        // current matching of w
        int m_old = matching[w-1];

        // if w unmatched, match m and w
        if (m_old == -1)
        {
            matching[w-1] = m;
        }
        else
        {
            // if she prefers the man proposing, match with him, unmatch old
            if(rank[m-1][w-1] < rank[m_old-1][w-1]) // = O(1) [optimal]
            {   
                matching[w-1] = m;
                unmatched_men.push(m_old);
            }
            else // reject m
            {
                unmatched_men.push(m);
            }
        }
    }
    return matching;
}
#endif
