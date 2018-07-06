/*
ID: bourahl1
PROG: holstein
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>

using namespace std;

bool getWorkingCombination(int depth,int size,int** feed,int* indexes,int i,int* required,int V)
{
    if(!depth)
    {
        int sum[V];
        for (int j = 0; j < V; ++j) {
            sum[j] = 0;
        }
        for (int j = 0; j < size; ++j) {
            cout << indexes[j] << " ";
            if(indexes[j])
                for (int k = 0; k < V; ++k) {
                    sum[k] += feed[j][k];
                }
        }
        cout << endl;
        for (int j = 0; j < V; ++j) {
            if(required[j] > sum[j])
                return false;
        }
        return true;
    }
    else
    {
        for (int j = i; j < size - depth+1; ++j) {
            indexes[j] = 1;
            if(getWorkingCombination(depth-1,size,feed,indexes,j+1,required,V))
                return true;
            indexes[j] = 0;
        }
    }
    return false;
}

int main7()
{
    ifstream fin;
    ofstream fout;
    fin.open("holstein.in");
    fout.open("holstein.out");
    if(fin.is_open())
    {
        int V,G;
        fin >> V;
        int* vitPerDay = new int[V];
        for (int i = 0; i < V; ++i) {
            fin >> vitPerDay[i];
        }
        fin >> G;
        int** feed = new int*[G];
        for (int i = 0; i < G; ++i) {
            feed[i] = new int[V];
            for (int j = 0; j < V; ++j) {
                fin >> feed[i][j];
            }
        }
        int* indexes = new int[G];
        for (int i = 0; i < G; ++i) {
            indexes[i] = 0;
        }
        for (int i = 1; i < G+1; ++i)
            if(getWorkingCombination(i,G,feed,indexes,0,vitPerDay,V))
            {
                cout << i;
                fout << i;
                for (int j = 0; j < G; ++j)
                    if(indexes[j]){

                        cout << " " << j+1;
                        fout << " " << j+1;
                    }
                cout << endl;
                fout << endl;
                break;
            }


    }
    return 0;
}