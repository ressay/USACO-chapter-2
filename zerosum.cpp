/*
ID: bourahl1
PROG: zerosum
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>

using namespace std;



int operate(int op1, int op2, int op)
{
    if(op == 1)
        return op1 + op2;
    else
        return op1 - op2;
}

void DFS(int depth,string s,int index) {
    if (index == depth+1) {
//        cout << s << endl;
        int result = 1;
        int prevOp = 0;
        int current = 1;
        for (int i = 0; i < depth-1; i++) {

//            cout << result << " " << s[2 * i + 1] << " " << current << endl;
            if(s[2*i+1] == ' ')
            {
                current*=10;
                current+=i+2;
                if(!prevOp)
                    result = current;
            }
            else if(s[2*i+1] == '+')
            {
                if(prevOp)
                    result = operate(result, current, prevOp);

                prevOp = 1;
                current = i+2;
            }
            else
            {
                if(prevOp)
                    result = operate(result, current, prevOp);
                prevOp = 2;
                current = i+2;
            }
        }
//        cout << result << " " << " " << current << endl;
        if(prevOp)
            result =  operate(result,current,prevOp);

//        cout << "result: " << result << endl;
        if (!result) {
            cout << s << endl;
//            fout << s << endl;
        }
        return;
    }
    {
        string s2 = s + " ";
        s2 += ('0' + index);
        DFS(depth, s2,index + 1);
    }
    {
        string s2 = s + "+";
        s2 += ('0' + index);
        DFS(depth, s2,index + 1);
    }
    {
        string s2 = s + "-";
        s2 += ('0' + index);
        DFS(depth, s2,index + 1);
    }

}

int maina()
{
    ifstream fin;
    ofstream fout;
    fin.open("zerosum.in");
    fout.open("zerosum.out");
    if(fin.is_open())
    {
        int N;
        fin >> N;
        DFS(N,"1",2);
    }
    return 0;
}