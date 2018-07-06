/*
ID: bourahl1
PROG: subset
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>

using namespace std;


int main11()
{
    ifstream fin;
    ofstream fout;
    fin.open("subset.in");
    fout.open("subset.out");
    if(fin.is_open())
    {
        int N;
        fin >> N;
        int S = (N*(N+1))/2;
        if(S%2==1)
        {
            cout << 0 << endl;
            fout << 0 << endl;
            return 0;
        }
        long long sums[S/2+1] = { };
        for (int i = 1; i <= N; ++i) {
            for (int j = S/2+1-i; j > 0; --j)
                sums[j+i] += sums[j];
            sums[i]++;
        }
        cout << sums[S/2]/2 << endl;
        fout << sums[S/2]/2 << endl;
    }
    return 0;
}