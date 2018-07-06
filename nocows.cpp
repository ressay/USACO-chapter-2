/*
ID: bourahl1
PROG: nocows
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>

using namespace std;

const int mod = 9901;

int main26()
{
    ifstream fin;
    ofstream fout;
    fin.open("nocows.in");
    fout.open("nocows.out");
    if(fin.is_open())
    {
        int N,K;
        fin >> N >> K;
        if(!(N%2))
        {
            cout << 0 << endl;
            fout << 0 << endl;
            return 0;
        }
        int* mat[K+1][N+1];
        for (int i = 0; i < K+1; ++i) {
            for (int j = 0; j < N+1; ++j) {
                mat[i][j] = new int[(N+1)/2+1];
                for (int k = 0; k < (N+1)/2+1; ++k) {
                    mat[i][j][k] = 0;
                }
            }
        }

        mat[1][3][2] = 1;
        mat[0][1][1] = 1;
        for (int i = 2; i < K; ++i) { // depth loop
            int start = i*2-1;
            int end = (i >= 8)? N : (1<<i < N)? 1<<i : N;
            int all = 0;
            for (int j = start; j < end; j+=2) // number of node of previous depth loop
            {
                for (int k = 2; k <= j && k<= (N+1)/2; k+=2) // number of nodes in last depth loop
                {
                    if(mat[i-1][j][k]) { // number of possibilities depth i-1 nodes j last depth nodes k
                        long long choose = k;
                        for (int l = 1; l <= k && j+l*2 <= N && l*2 <= (N+1)/2; ++l) { // loop over nodes of last depth
                            mat[i][j + l * 2][l * 2] += (mat[i - 1][j][k] * choose%mod) % mod;
                            mat[i][j + l * 2][l * 2] = mat[i][j + l * 2][l * 2] % mod;
                            choose*= k - l;
                            choose /= (l+1);
                        }
                    }

                }
            }
        }
        long long sum = 0;
        for (int i = 2; i < (N+1)/2+1; i+=2) {
            sum += mat[K-1][N][i];
            sum = sum%mod;
        }

        cout << sum << endl;
        fout << sum << endl;
    }
    return 0;
}