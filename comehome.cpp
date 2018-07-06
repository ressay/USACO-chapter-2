/*
ID: bourahl1
PROG: comehome
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>
#include "vector"
#include "math.h"

using namespace std;


int mainLR()
{
    const int MAX = 10000000;
    ifstream fin;
    ofstream fout;
    fin.open("comehome.in");
    fout.open("comehome.out");
    if(fin.is_open())
    {
        int N;
        fin >> N;
        int adj[52][52];
        for (int i = 0; i < 52; ++i) {
            for (int j = 0; j < 52; ++j) {
                adj[i][j] = MAX;
            }
        }
        for (int i = 0; i < N; ++i) {
            char a,b;
            int dis,i1,i2;
            fin >> a >> b >> dis;
            i1 = (a >= 'A' && a <= 'Z')?(a-'A'+26):(a-'a');
            i2 = (b >= 'A' && b <= 'Z')?(b-'A'+26):(b-'a');

            if(adj[i1][i2] > dis) {
                adj[i1][i2] = dis;
                adj[i2][i1] = dis;
            }
        }



        for (int k = 0; k < 52; ++k) {
            for (int i = 0; i < 52; ++i) {
                for (int j = 0; j < 52; ++j) {
                    if (adj[i][k] + adj[k][j] < adj[i][j])
                        adj[i][j] = adj[i][k] + adj[k][j];
                }
            }
        }

//        for (int i = 0; i < 52; ++i) {
//            cout << i+1 << "- ";
//            for (int j = 0; j < 52; ++j) {
//                cout << adj[i][j] << "\t";
//            }
//            cout << endl;
//        }

        int min = adj[26][51];
        int index = 0;
        for (int i = 27; i < 51; ++i) {
            if(adj[i][51] < min) {
                min = adj[i][51];
                index = i - 26;
            }
        }

        cout << (char)('A' + index) << " " << min << endl;
        fout << (char)('A' + index) << " " << min << endl;

    }
    return 0;
}