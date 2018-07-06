/*
ID: bourahl1
PROG: frac1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <bitset>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

class Z
{
public:
    double val;
    int a,b;
    Z(double val, int a, int b) : val(val), a(a), b(b) {}
    Z(){}
};

int compare(Z a, Z b)
{
    if(a.val-b.val < 0.00001 && a.val-b.val > -0.00001) return a.b<b.b;
    return a.val<b.val;
}

int main4()
{
    ifstream fin;
    ofstream fout;
    fin.open("frac1.in");
    fout.open("frac1.out");
    if(fin.is_open())
    {
        int N;
        fin >> N;
        fout << "0/1" << endl;
//        cout << "0/1" << endl;
//        double** fracts = new double*[N];
        Z fracts[N*(N+1)/2];
        int s=0;
        for (int i = 0; i < N; ++i) {
            for (int j = 1; j < i+1; ++j) {
                fracts[s++] = Z((double)(j)/(double)(i+1),j,i+1);
            }
        }
        sort(fracts,fracts+s,compare);
        double prev = 0;
        for (int k = 0; k < s; ++k) {
            if(fracts[k].val - prev < 0.00001) continue;
//            cout << fracts[k].a << "/" << fracts[k].b << endl;
            fout << fracts[k].a << "/" << fracts[k].b << endl;
            prev = fracts[k].val;
        }
//        cout << "1/1"<< endl;
        fout << "1/1"<< endl;
    }
    return 0;
}