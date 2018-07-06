/*
ID: bourahl1
PROG: hamming
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>

using namespace std;

int hammingDistance(int a,int b)
{
    int k = a^b;
    int count = 0;
//    cout << "k is " << k << endl;
    while(k)
    {
        k -= (-k&k); // take off first bit set to 1 from right to left
        count ++;
    }
//    cout << "distance between " << a << " and " << b << " is " << count << endl;
    return count;
}

int main9()
{
    ifstream fin;
    ofstream fout;
    fin.open("hamming.in");
    fout.open("hamming.out");
    if(fin.is_open())
    {
        int N,B,D;
        fin >> N >> B >> D;
        int size = 1;
        for (int i = 0; i < B; ++i) {
            size *= 2;
        }
        int generated[N];
        generated[0] = 0;
        int gen=1;
        cout << 0;
        fout << 0;
        for (int i = 1; i < size && gen < N; ++i) {
            int j = 0;
            for (; j < gen; ++j) {
                if(hammingDistance(i,generated[j]) < D) {
                    break;
                }
            }
            if(j==gen)
            {

                if(gen%10 == 0)
                {
                    cout << endl << i;
                    fout << endl << i;
                }
                else
                {
                    cout << " " << i;
                    fout << " " << i;
                }
                generated[gen++] = i;
            }
        }
            cout << endl;
            fout << endl;
    }
    return 0;
}