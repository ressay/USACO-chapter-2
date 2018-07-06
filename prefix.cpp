/*
ID: bourahl1
PROG: prefix
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>

using namespace std;

int main5()
{
    ifstream fin;
    ofstream fout;
    fin.open("prefix.in");
    fout.open("prefix.out");
    if(fin.is_open())
    {
        string prims[200];
        int sPr = 0;
        string seq = "";
        string read = "";
        bool bef = true;
        while (!fin.eof())
        {
            fin >> read;
            if(bef && !fin.eof())
            {
                if(read != ".")
                prims[sPr++] = read;
                else
                bef = false;
            }
            else if(!fin.eof())
                seq += read;
        }
        bool found[seq.size()+1] = {};
        found[0] = true;
        int max = 0;
        for (int i = 1; i < seq.size()+1; ++i) {
            for (int j = 0; j < sPr; ++j) {
                if(i-prims[j].size() >= 0 && i-prims[j].size() < seq.size() &&found[i-prims[j].size()]) {
                    if (seq.substr(i - prims[j].size(), prims[j].size()) == prims[j]) {
                        found[i] = true;
                        max = i;
                        break;
                    }
                }
            }
        }
        fout << max << endl;
        cout << max << endl;
    }
    return 0;
}