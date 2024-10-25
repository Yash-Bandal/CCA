#include <bits/stdc++.h>
using namespace std;
// A utility function to print solution
void printSolution(vector<vector<int>> &board)
{
    int n = board.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            if (board[i][j] == 1)
                cout << "Q ";
            else
                cout << ". ";
        cout << "\n";
    }
}

bool isSafe(vector<vector<int>> &board, int row, int col)
{
    int n=board.size();

    int i, j;
    for ( i = 0; i < col; i++)
        if (board[row][i] == 1)
            return false;

    for ( i = row,j=col; i >=0 && j>=0; i--,j--)
        if (board[i][j] == 1)
            return false;


    for ( i = row,j=col; i <n && j>=0; i++,j--)
        if (board[i][j] == 1)
            return false;

   return true;         
}

bool NQueen(vector<vector<int>> &board, int col)
{
    int n = board.size();
    if (col >= n)
    {
        return true;
    }

    for (int i = 0; i < n; i++)
    {
        if (isSafe(board, i, col))
        {
            board[i][col] = 1;

            if (NQueen(board, col + 1) == true)
            {
                return true;
            }
            board[i][col] = 0;
        }
    }
    return false;
}
int main()
{
    int n = 4;
    vector<vector<int>> board(n, vector<int>(n, 0));

    if (NQueen(board, 0) == false)
    {
        cout << "No sol" << endl;
        return false;
    }

    printSolution(board);
    return 0;
}
