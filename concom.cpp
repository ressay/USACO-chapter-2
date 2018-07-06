/*
ID: bourahl1
PROG: concom
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>
#include "vector"

using namespace std;


int maink()
{
    ifstream fin;
    ofstream fout;
    fin.open("concom.in");
    fout.open("concom.out");
    if(fin.is_open())
    {
        int N;
        fin >> N;
        int mat[101][101] = {};
        bool own[101][101] = {};
        for (int i = 0; i < N; ++i) {
            int x,y,k;
            fin >> x >> y >> k;
            mat[x][y] = k;
            if(k >= 50)
                own[x][y] = true;
        }

        for (int i = 1; i < 101; ++i) {
            vector<int> stack;
            int vec[101];

            for (int j = 1; j < 101; ++j) {
                if(own[i][j])
                    stack.push_back(j);
                vec[j] = mat[i][j];
            }
            while(stack.size())
            {
                int element = stack[stack.size()-1];
                stack.pop_back();
                for (int j = 1; j < 101; ++j) {
                    vec[j] += mat[element][j];
                    if(vec[j] >= 50 && !own[i][j]) {
                        stack.push_back(j);
                        own[i][j] = true;
                    }
                }
            }
        }

        for (int i = 0; i < 101; ++i) {
            for (int j = 0; j < 101; ++j) {
                if(own[i][j] && i!= j)
                {
                    cout << i << " " << j << endl;
                    fout << i << " " << j << endl;
                }
            }
        }
    }
    return 0;
}