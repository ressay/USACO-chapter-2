/*
ID: bourahl1
PROG: maze1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>
#include "vector"

using namespace std;

int mainb2123()
{
    ifstream fin;
    ofstream fout;
    fin.open("maze1.in");
    fout.open("maze1.out");
    if(fin.is_open())
    {
        int W,H;
        string s;
        int xS[2],yS[2];
        int iS=1;
        fin >> W >> H;
        vector<pair<int,int> > adj[H][W];
        std::getline(fin,s);
        for (int i = 0; i < 2*H+1; ++i) {
            std::getline(fin,s);
//            cout << s << endl;
            if(s.size() != 2*W+1)
            {
                for (int j = s.size(); j < 2*W+1; ++j) {
                    s += " ";
                }
            }
            for (int j = 0; j < 2*W+1; ++j) {
                if(!i || i==2*H || !j || j==2*W) {
                    if (s[j] == ' ') {
                        adj[i/2-1*(i==2*H)][j/2-1*(j==2*W)].push_back(pair<int,int>(-iS,-iS));
                        iS++;
                    }
                }
                else
                {
                    // horizontal walls
                    if(i%2 == 0)
                    {
                        if(s[j] == ' ')
                        {
                            adj[i/2-1][j/2].push_back(pair<int,int>(i/2,j/2));
                            adj[i/2][j/2].push_back(pair<int,int>(i/2-1,j/2));
                        }
                    }
                    else if(j%2 == 0)
                    {
                        if(s[j] == ' ')
                        {
                            adj[i/2][j/2-1].push_back(pair<int,int>(i/2,j/2));
                            adj[i/2][j/2].push_back(pair<int,int>(i/2,j/2-1));
                        }
                    }

                }

            }
        }

//        for (int i = 0; i < H; ++i) {
//            for (int j = 0; j < W; ++j) {
//                cout << i << "," << j << " has: ";
//                for (int k = 0; k < adj[i][j].size(); ++k) {
//                     cout << adj[i][j][k].first << "," << adj[i][j][k].second << " ";
//                }
//                cout << endl;
//            }
//        }
        int max = 0;
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                vector<pair<int,int> > queue;
                vector<int> depth;
                int done[H][W] = {};
                queue.push_back(pair<int,int>(i,j));
                depth.push_back(0);
                done[i][j] = true;
                bool found = false;
                while (!queue.empty())
                {
                    pair<int,int> p = queue[0];
                    queue.erase(queue.begin());
                    int d = depth[0];
                    depth.erase(depth.begin());
//                    cout << "visiting " << p.first << "," << p.second << endl;

                    for (int k = 0; k < adj[p.first][p.second].size(); ++k) {
                        pair<int,int> p2 = adj[p.first][p.second][k];
                        if(p2.first < 0)
                        {
                            found = true;
                            if(max < d+1) {
//                                cout << "from point " << i << "," << j <<" found " << d+1 << endl;
                                max = d+1;
                            }
                            break;
                        }

                        if(!done[p2.first][p2.second]) {
//                            cout << "pushing " << p2.first << "," << p2.second << endl;
                            queue.push_back(p2);
                            depth.push_back(d+1);
                            done[p2.first][p2.second] = true;
                        }
                    }
//                    cout <<"queue has: ";
//                    for (int k = 0; k < queue.size(); ++k) {
//                        cout << queue[k].first << "," << queue[k].second << " ";
//                    }
//                    cout << endl;
                    if(found)
                        break;
                }
            }
        }

        fout << max << endl;
        cout << max << endl;

    }
    return 0;
}