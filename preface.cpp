/*
ID: bourahl1
PROG: preface
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>

using namespace std;

const int MAX_N = 3501;

int* counts = new int[26];

void countChars(string s)
{
    int size = s.size();
    for (int i = 0; i < size; ++i) {
        counts[s[i]-'A']++;
    }
}

int main10()
{
    ifstream fin;
    ofstream fout;
    fin.open("preface.in");
    fout.open("preface.out");
    if(fin.is_open())
    {
        int N;
        fin >> N;
        string nums[MAX_N];
        string toTen[11] = {"I","II","III","IV","V","VI","VII","VIII","IX","X"};
        for (int i = 0; i < 10; ++i) {
            nums[i+1] = toTen[i];
        }
        nums[50] = "L";
        nums[100] = "C";
        nums[500] = "D";
        nums[1000] = "M";
        char poss[7] = {'I','V','X','L','C','D','M'};
        for (int i = 0; i < 26; ++i) {
            counts[i] = 0;
        }
        for (int i = 10; i < MAX_N; i*=10) {
            for (int j = i*2; j <= i*10; j+=i) {
                if(j>=MAX_N){
                    for (int k = j-i+1; k < j; ++k) {
                        if(k>=MAX_N)break;
                        nums[k] = nums[j-i]+nums[k-j+i];
                    }
                    break;
                }
                if(j <= i*3) nums[j] = nums[j-i]+nums[i];
                else if(j == i*4) nums[j] = nums[i]+nums[i*5];
                else if(j <= i*8 && j!=i*5) nums[j] = nums[j-i] + nums[i];
                else if(j == i*9) nums[j] = nums[i]+nums[i*10];
//                cout << "j is " << j << " nums " << nums[j] << endl;
                for (int k = j-i+1; k < j; ++k) {
                    if(k>=MAX_N)break;
                    nums[k] = nums[j-i]+nums[k-j+i];
                }
            }
        }

        for (int i = 1; i <= N; ++i) {
            countChars(nums[i]);
//            cout << nums[i] << endl;
        }
//        for (int i = 0; i < 7; ++i) {
//            cout << poss[i] << " " << counts[poss[i]-'A'] << endl;
//        }
//        cout << endl;
        for (int i = 0; i < 7; ++i) {
            if(counts[poss[i]-'A']>0)
            {
                cout << poss[i] << " " << counts[poss[i]-'A'] << endl;
                fout << poss[i] << " " << counts[poss[i]-'A'] << endl;
            }
        }

    }
    return 0;
}