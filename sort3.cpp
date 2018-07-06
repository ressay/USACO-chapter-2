/*
ID: bourahl1
PROG: sort3
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>

using namespace std;

int getPos(int i,int* count)
{
    if(i < count[1]) return 1;
    if(i < count[2]) return 2;
    return 3;
}

int main6()
{
    ifstream fin;
    ofstream fout;
    fin.open("sort3.in");
    fout.open("sort3.out");
    if(fin.is_open())
    {
        int N;
        fin >> N;
        int number=0;
        int tab[N];
        int count[4];
        for (int i = 0; i < 4; ++i) {
            count[i]=0;
        }
        for (int i = 0; i < N; ++i) {
            fin >> tab[i];
            count[tab[i]]++;
        }
        int acc[4];
        acc[0] = 0;
        for (int k = 1; k < 4; ++k) {
//            cout << "count " << count[k] << endl;
            acc[k] = acc[k-1] + count[k];
        }
        for (int i = 0; i < N; ++i) {
            if(tab[i] != getPos(i,acc))
            {
//                cout << "pos " << i << " in " << getPos(i,acc) << endl;
                for (int j = acc[tab[i]-1]; j < acc[tab[i]]; ++j) {
//                    cout << j << " ";
                    if(getPos(i,acc) == tab[j])
                    {
                        //cout << "changing " << tab[i] << " with " << tab[j] << endl;
                        int m = tab[j];
                        tab[j] = tab[i];
                        tab[i] = m;
                        number ++;
                        break;
                    }
                }
//                cout << endl;
            }
        }
        while(true) {
            int pos[3] = {-1,-1,-1};
            for (int i = 0; i < 3; ++i) {

                for (int j = acc[i]; j < acc[i + 1]; ++j) {
                    {
                        if (tab[j] != getPos(j, acc)) {
                                    pos[i] = j;
                        }
                    }
                }
            }
            if(pos[0]==-1)
                break;
            tab[pos[0]] = 1;
            tab[pos[1]] = 2;
            tab[pos[2]] = 3;
            number+=2;
        }
//        cout << number << endl;
        fout << number << endl;

    }
    return 0;
}