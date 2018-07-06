/*
ID: bourahl1
PROG: ttwo
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>
#include "vector"

using namespace std;
int countsF[10][10][4] = { };
int countsC[10][10][4] = { };
int moveY[4] = {0,1,0,-1};
int moveX[4] = {-1,0,1,0};

bool inRange(int x)
{
    return x >=0 && x<10;
}

bool inRange2(int x,int y)
{
    return inRange(x) && inRange(y);
}

int hcf(int n1,int n2)
{
    int hcf = 1;
    if ( n2 > n1) {
        int temp = n2;
        n2 = n1;
        n1 = temp;
    }

    while(n1%n2)
    {
        int temp = n2;
        n2 = n1%n2;
        n1 = temp;
    }

    return n2;
}

int lcm(int n1,int n2)
{
    return (n1*n2)/hcf(n1,n2);
}

int max(int x, int y)
{
    return (x>y)?x:y;
}

int getIntersection(int f1,int f2,int p1,int p2)
{
    int min = 2147483647;
    if(p1 == p2) return min;
    int diff = (f1<f2)?(f2-f1)%p1:(f1-f2)%p2;
    int maxp = max(p1,p2);
    int minp = (maxp==p1)?p2:p1;
    int maxf = max(f1,f2);
    if((p1-p2)*(f1-f2)<0)
    {
//        cout << "entered" << endl;
        maxf = ((maxf==f1)?f1:f2) + maxp-diff;
        diff = (maxp-diff)%minp;

    }
    int cpt = 0;
    int svdiff = diff;
//    cout << "maxp " << maxp << " diff " << diff << endl;
    for (; diff && (!cpt || diff != svdiff) ; ++cpt) {
//        cout << " diff is " << diff << endl;
        diff += maxp;
        diff %= minp;
    }
//    cout << "cpt " << cpt << " maxf " << maxf<< endl;
    if(diff)
    return min;
    return cpt*maxp + maxf;
}
int maink55()
{
    ifstream fin;
    ofstream fout;
    fin.open("ttwo.in");
    fout.open("ttwo.out");
    if(fin.is_open())
    {
        string map[10];
        int fx=0,fy=0,cx=0,cy=0,fdir=0,cdir=0;
        for (int i = 0; i < 10; ++i) {
            fin >> map[i];
            for (int j = 0; j < 10; ++j) {
                if(map[i][j] == 'F')
                {
                    fx = i; fy = j;
                    countsF[i][j][0] = 1;
                }
                else if(map[i][j] == 'C')
                {
                    cx = i; cy = j;
                    countsC[i][j][0] = 1;
                }
            }
        }

        int countF = 1,countC = 1;
        int floop = 0, cloop = 0;
        while(fx != cx || fy != cy)
        {
            // move F
            int tx = fx+moveX[fdir],ty = fy + moveY[fdir];
//            cout << "moving farmer from " << fx << "," << fy << " to " << tx << "," << ty << endl;
            if(inRange2(tx,ty) && map[tx][ty] != '*')
            {
                fx = tx; fy = ty;
            }
            else
            {
                fdir = (fdir+1)%4;
            }
            if(countsF[fx][fy][fdir]) {
                if(!floop)
                floop = countsF[fx][fy][fdir];
//                cout << "trying to break f at " << cloop << endl;
                if(cloop) break;
            }
            else
            countsF[fx][fy][fdir] = ++countF;
            // move C
            tx = cx+moveX[cdir],ty = cy + moveY[cdir];
//            cout << "moving cow from " << cx << "," << cy << " to " << tx << "," << ty << endl;
            if(inRange2(tx,ty) && map[tx][ty] != '*')
            {
                cx = tx; cy = ty;
            }
            else
            {
                cdir = (cdir+1)%4;
            }
            if(countsC[cx][cy][cdir]) {
                if(!cloop)
                cloop = countsC[cx][cy][cdir];
//                cout << "trying to break c at " << floop << endl;
                if(floop) break;
            }
            else
            countsC[cx][cy][cdir] = ++countC;
//            if(fx == cx && fy==cy)
//                cout << fx << "," << fy << endl;
        }

        if(floop && cloop)
        {
            int min = 2147483647;
            bool found = false;
            int p1=0,p2=0;
            for (int i = 0; i < 10; ++i) {
                for (int j = 0; j < 10; ++j) {
                    for (int k = 0; k < 4; ++k) {
//                        if(countsF[i][j][k])
//                            cout << "found " << i << "," << j << " as " << countsF[i][j][k] << " and floop " << floop << endl;
                        if(countsC[i][j][k] >= cloop)
                        {
                            p2++;
                        }

                        if(countsF[i][j][k] >= floop)
                        {
                            p1++;
                        }
                    }
                }
            }
            for (int i = 0; i < 10; ++i) {
                for (int j = 0; j < 10; ++j) {
                    for (int k = 0; k < 4; ++k) {
                        for (int l = 0; l < 4; ++l) {
                            if(countsC[i][j][k]>0 || countsF[i][j][l])
//                            cout << "not yet::: intersection of " << countsC[i][j][k] << " and " << countsF[i][j][l] << " with loop of " << p2 << " and " << p1  << " calculating... " <<  endl;
                            if(countsC[i][j][k] >= cloop && countsF[i][j][l] >= floop)
                            {
//                                cout << "intersection of " << countsC[i][j][k] << " and " << countsF[i][j][l] << " with loop of " << p2 << " and " << p1  << " calculating... " <<  endl;
                                int inters = getIntersection(countsC[i][j][k],countsF[i][j][l],p2,p1);
//                                cout << "intersection of " << countsC[i][j][k] << " and " << countsF[i][j][l] << " with loop of " << p2 << " and " << p1  << " is " << inters << " in position " << i << "," << j << endl;
//                                cout  << "min is " <<min << endl;
                                if(min > inters) {
                                    min = inters;
                                    found = true;
                                }
                            }
                        }
                    }
                }
            }
            if(found)
            {
                cout << min - 1 << endl;
                fout << min - 1 << endl;
            } else
            {
                cout << 0 << endl;
                fout << 0 << endl;
            }
        }
        else {
            cout << countC - 1 << endl;
            fout << countC - 1 << endl;
        }

    }
    return 0;
}