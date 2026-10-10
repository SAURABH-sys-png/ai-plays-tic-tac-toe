#include <bits/stdc++.h>
using namespace std;
#include "Print.hpp"
#include "coremaths.hpp"

int arr[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
enum XO
{
    D = 0, // ->0
    O = 1, // ->1
    X  =-1// 
};

void updatePos(int PC, int i, int j)
{
    if(PC == 1 || PC == -1){
    arr[i][j] = PC;}
}

int check()
{
    // horizontals rows first
    for (int row = 0; row < 3; row++)
    {
        if (arr[row][0] == arr[row][1] && arr[row][1] == arr[row][2])
            return arr[row][1];
    }
    for (int col = 0; col < 3; col++)
    {
        if (arr[0][col] == arr[1][col] && arr[1][col] == arr[2][col])
            return arr[0][col];
    }
    if (arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2])
        return arr[0][0];

    if (arr[2][0] == arr[1][1] && arr[1][1] == arr[0][2])
        return arr[1][1];
    return 1;

}

void resest_board(){
    for(auto&row:arr){
        for(auto&col : row){
            col = 0;
        }
    }
}


class Neuron {
  mat Matrix;
  Neuron(mat Matrix)
}

void loop(){
    while (1)
    {
        std::string s;
        std::cin >> s;
        if(s=="Start"){
            resest_board();
            printBoard(arr);
            continue;
        }
        else if(s=="Update"){
            int en,i,j;
            cin >> en >> i>>j;
            updatePos(en,i,j);
            printBoard(arr);
            int op = check();
            if(op==1){
                std::cout<< 1 << '\n';
                break;
            }
            else if(op ==2){
                std::cout << 2 << '\n';
                break;
            }

            continue;
        }
        else if(s=="End"){
            break;
        }
    }
    
}



// importing and making use of the functions

int main()
{

    loop();
    return 0;
}
