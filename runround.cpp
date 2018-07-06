/*
ID: bourahl1
PROG: runround
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>

using namespace std;

int size(long long  val)
{
    int s = 0;
    for (; val ; s++,val/=10);
    return s;
}

int getPosition(long long val,int pos)
{
    int p = 1;
    for (int i = 0; i < pos; ++i,p*=10);
    val/=p;
    return val%10;
}
bool verify(long long val)
{
    int si = size(val);
    if(si == 1)
        return true;
    bool b[si] = {};
    int next = si-1;
    for (int i = 0; i < si; ++i) {
        int k = getPosition(val,next);
        int newPos = (next-k)%si + si*((next-k)%si<0);
        if(b[newPos] || newPos == next)
            return false;
        else
            b[newPos] = true;
        next = newPos;
    }
    return true;
}
bool rec(long long val,int depth,int* left,int start,long long* sol,int min)
{
    if(!depth)
    {
//        cout << "found value " << val << endl;
        if(verify(val) && val > min)
        {
            *sol = val;
            return true;
        }
        else return false;
    }

    for (int i = start; i < 9; ++i) {
        int temp = left[i];
        left[i] = left[start];
        left[start] = temp;
        int next = left[start];
        val*=10;
        val+=next;
        if(rec(val,depth-1,left,start+1,sol,min)) return true;
        val/=10;
    }
    for (int i = 8; i > start; --i) {
        int temp = left[i];
        left[i] = left[start];
        left[start] = temp;
    }
    return false;
}

int main12()
{
    ifstream fin;
    ofstream fout;
    fin.open("runround.in");
    fout.open("runround.out");
    if(fin.is_open())
    {
        int N;
        fin >> N;
        int v = 81362;
//        if(verify(v)) cout << "done" << endl;
//        else cout << "not done" << endl;
        int left[] = {1,2,3,4,5,6,7,8,9};
        long long sol=0;
        int s = size(N);
        for (int i = s; i < 9; ++i)
            if(rec(0,i,left,0,&sol,N))
            {
                cout << sol << endl;
                fout << sol << endl;
                return 0;
            }

    }
    return 0;
}