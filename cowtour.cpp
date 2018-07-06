/*
ID: bourahl1
PROG: cowtour
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>
#include "vector"
#include "math.h"

using namespace std;



double getdistance(double x, double y)
{

    return sqrt(x*x+y*y);
}

double distance(double x1, double y1, double x2, double y2)
{
    return getdistance(x1-x2,y1-y2);
}


int mainLALR()
{
    const double MAX = 4294967295;
    ifstream fin;
    ofstream fout;
    fin.open("cowtour.in");
    fout.open("cowtour.out");
    if(fin.is_open())
    {
        int N;
        fin >> N;
        double X[N];
        double Y[N];
        double adj[N][N];
        for (int i = 0; i < N; ++i) {
            fin >> X[i] >> Y[i];
        }

        for (int i = 0; i < N; ++i) {
            string k;
            fin >> k;
            for (int j = 0; j < N; ++j) {
                adj[i][j] = (k[j] == '1')?distance(X[i],Y[i],X[j],Y[j]):(MAX*(i!=j));
            }
        }


//        for (int i = 0; i < N; ++i) {
//            for (int j = 0; j < N; ++j) {
//                if(i!=j)
//                    for (int k = 0; k < N; ++k) {
//                        if(adj[i][k]+adj[k][j] < adj[i][j])
//                            adj[i][j] = adj[i][k]+adj[k][j];
//                    }
//            }
//        }

        for (int k = 0; k < N; ++k) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    if (adj[i][k] + adj[k][j] < adj[i][j] && i!=j)
                        adj[i][j] = adj[i][k] + adj[k][j];
                }
            }
        }


//        for (int i = 0; i < N; ++i) {
//            for (int j = 0; j < N; ++j) {
//                cout << adj[i][j] << "\t";
//            }
//            cout << endl;
//        }

        double max[N];
        for (int i = 0; i < N; ++i) {
            max[i] = 0;
            for (int j = 0; j < N; ++j) {
                if(max[i]<adj[i][j] && adj[i][j] != MAX)
                    max[i] = adj[i][j];
            }
//            cout << "max of " << i << " is " << max[i] << endl;
        }

        double min = MAX;
        for (int i = 0; i < N; ++i) {
            for (int j = i+1; j < N; ++j) {
                if(adj[i][j] == MAX)
                {
                    double dis = max[i] + max[j] + distance(X[i],Y[i],X[j],Y[j]);
//                        cout << "min between " << i << " and " << j << " is " << dis << "their max is " << max[i] << " " << max[j]  << endl;
                    if(min >= dis) {
                        min = dis;
//                        cout << "min between " << i << " and " << j << " is " << min << "their max is " << max[i] << " " << max[j]  << endl;
                    }
                }
            }
        }

        for (int i = 0; i < N; ++i) {
            for (int j = i+1; j < N; ++j) {
                if(adj[i][j] != MAX && adj[i][j] > min)
                    min = adj[i][j];
            }
        }
        char* s = new char[255];
        sprintf(s,"%.6f",min);
        cout << s << endl;
        fout << s << endl;
        //39796.392691


    }
    return 0;
}