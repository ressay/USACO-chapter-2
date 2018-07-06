/*
ID: bourahl1
PROG: fracdec
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>
#include "vector"
#include "math.h"

using namespace std;

int getDigit(int number,int position)
{
    int puiss = 1;
    int i=1;
    for(;i<position;i++)
        puiss *= 10;
    number = number/puiss;
    int u = number % 10;
    return u;
}

string to_string1(int val)
{
    string s = "";
    int count = 0;
    int t = val;
    for (; val ; ++count) {
        val/=10;
    }
    if(!count)
        return "0";

    for (int i = count; i > 0; --i) {
        s += '0' + getDigit(t,i);
    }
    return s;
}

int main()
{
    ifstream fin;
    ofstream fout;
    fin.open("fracdec.in");
    fout.open("fracdec.out");
    if(fin.is_open())
    {
        int N,D;
        fin >> N >> D;
        string s;
        int q = N/D;
        int r = N%D;
        int* rest = new int[D];
        for (int i = 0; i < D; ++i) {
            rest[i] = 0;
        }
        s = to_string1(q);
        if(!r)
        {
            cout << s << ".0" << endl;
            fout << s << ".0" << endl;
            return 0;
        }
        s += ".";
        int count = 2;
        rest[r] = 1;
        string ap = "";
        while(r)
        {
            r*=10;
            ap += to_string1(r/D);
            r%=D;
            if(!rest[r])
                rest[r] = count++;
            else
            {
                for (int i = 0; i < rest[r]-1; ++i) {
                    s += ap[i];
                }
                string temp = "(";
                for (int i = rest[r]-1; i <ap.size() ; ++i) {
                    temp+=ap[i];
                }
                temp += ")";
                s += temp;
                for (int i = 0; i < s.size(); ++i) {
                    fout << s[i];
                    cout << s[i];
                    if((i+1)%76 == 0 && i)
                    {
                        fout << endl;
                        cout << endl;
                    }
                    if((i+1)%76 && i == s.size()-1)
                    {
                        fout << endl;
                        cout << endl;
                    }
                }

                return 0;
            }
        }

        s+=ap;
        for (int i = 0; i < s.size(); ++i) {
            fout << s[i];
            cout << s[i];
            if(i%75 == 0 && i)
            {
                fout << endl;
                cout << endl;
            }
            if(i%75 && i == s.size()-1)
            {
                fout << endl;
                cout << endl;
            }
        }
    }
    return 0;
}