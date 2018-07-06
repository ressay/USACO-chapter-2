/*
ID: bourahl1
PROG: money
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>

using namespace std;


int maincc()
{
    ifstream fin;
    ofstream fout;
    fin.open("money.in");
    fout.open("money.out");
    if(fin.is_open())
    {
        int V,N;
        fin >> V >> N;
        int coins[V];
        long long** poss = new long long*[N+1];
        for (int i = 0; i <= N; ++i) {
            poss[i] = new long long[V];
            for (int j = 0; j < V; ++j) {
                poss[i][j] = 0;
            }
        }
        for (int i = 0; i < V; ++i) {
            fin >> coins[i];
            if(coins[i] <= N)
                poss[coins[i]][i] += 1;
        }
        for (int i = 1; i <= N; ++i) {
            for (int j = 0; j < V; ++j) {
                if (i - coins[j] >= 0) {
                    for (int l = 0; l < V; ++l) {
                        poss[i][j] += poss[i - coins[j]][l];
                    }
                }
                for (int k = 0; k < j; ++k)
                    if (i - coins[j] - coins[k] >= 0) {
                        poss[i][j] -= poss[i - coins[j]][k];
                    }
            }
        }

        long long res = 0;
        for (int j = 0; j < V; ++j) {
            res += poss[N][j];
        }
        cout << res << endl;
        fout << res << endl;
    }
    return 0;
}