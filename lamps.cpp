/*
ID: bourahl1
PROG: lamps
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>

using namespace std;
int mySize=0;
int cmp(const void* T1,const void* T2)
{
    int *t1=(int*)T1,*t2=(int*)T2;
    int N=mySize;
    for (int i = 1; i < N; ++i) {
        if(t1[i] != t2[i]) return t1[i] - t2[i];
    }
    return 0;
}

void runButton(int b,int* lamps,int N)
{
    int jump = 1 + (b==2||b==1) + 2*(b==3);
    int start = 1 + (b==2);
    for (int i = start; i < N; i+=jump) {
        lamps[i] = !lamps[i];
    }
}

void dfs(int depth,int* lamps,int N,int* result,int** poss,int* found,int C,int* Cfound)
{
    if(depth == 4)
    {
        int i = 1;
        for (; i < N; ++i)
            if(result[i] && result[i]-1 != lamps[i])
                return;
        if(i==N)
        {
            int s = *found;
//            cout << "found one for " << C << " switches" << endl;
            for (int j = 1; j < N; ++j) {
                poss[s][j] = lamps[j];
//                cout << lamps[j];
            }
//            cout << endl;
            Cfound[s] = C;
            *found = s+1;
        }
        return;
    }
//    cout << "no switch" << endl;
    dfs(depth+1,lamps,N,result,poss,found,C,Cfound);
    runButton(depth,lamps,N);
//    cout << "switch" << endl;
    dfs(depth+1,lamps,N,result,poss,found,C+1,Cfound);
    runButton(depth,lamps,N);

}

int main13()
{
    ifstream fin;
    ofstream fout;
    fin.open("lamps.in");
    fout.open("lamps.out");
    if(fin.is_open())
    {
        int N,C;
        fin >> N >> C;
        int result[N+1] = {};
        int** poss = new int*[16];
        for (int i = 0; i < 16; ++i) {
            poss[i] = new int[100];
        }

        int* Cfound = new int[16];
        int* lamps = new int[N+1];
        for (int i = 0; i < N+1; ++i) {
            lamps[i] = 1;
        }
        int read = 1;
        while(read != -1)
        {
            fin >> read;
            result[read] = 2; // on
        }
        read = 1;
        while(read != -1)
        {
            fin >> read;
            result[read] = 1; // off
        }
        int found=0;
        dfs(0,lamps,N+1,result,poss,&found,0,Cfound);
        mySize = N+1;
//        qsort(poss,found,sizeof(int*),cmp);
        for (int i = 0; i < found; ++i) {
            int* min = poss[i];
            int k = i;
            for (int j = i+1; j < found; ++j) {
                if(cmp(poss[j],min)<0)
                {
                    min = poss[j];
                    k=j;
                }
            }
            poss[k] = poss[i];
            poss[i] = min;
            int temp = Cfound[k];
            Cfound[k] = Cfound[i];
            Cfound[i] = temp;
        }
        bool switches[5] = {!(C%2),C%2,!(C%2) && (C>1),(C%2)&&(C>2),!(C%2)&&(C>2)};
        int* prev = NULL;
        for (int i = 0; i < found; ++i) {
            if(switches[Cfound[i]])
                if(prev==NULL || cmp(prev,poss[i])) {
                    prev = poss[i];
                    for (int j = 1; j < N + 1; ++j) {
                        cout << poss[i][j];
                        fout << poss[i][j];
                    }
                    cout << endl;
                    fout << endl;
                }

        }
        if(prev==NULL)
        {
            cout << "IMPOSSIBLE" << endl;
            fout << "IMPOSSIBLE" << endl;
        }

    }
    return 0;
}