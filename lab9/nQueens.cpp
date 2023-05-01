/*
 * Name:
 * Date Submitted:
 * Lab Section:
 * Assignment Name:
 */

#include <iostream>
#include <vector>

using namespace std;

//Uses recursion to count how many solutions there are for
//placing n queens on an nxn chess board



bool isValid(const vector<int>& cols, int row, int col)
{
    for (int i = 0; i < row; i++) {
        if (cols[i] == col) return false;          // same column
        if (row - i == abs(col - cols[i])) return false;  // same diagonal
    }
    return true;
}

void nQueensHelper(vector<int>& cols, int n, int row, int& count)
{
    if (row == n) {
        // Found a valid solution
        count++;
        return;
    }

    // Try to place a queen in the current row, in each column
    for (int col = 0; col < n; col++) {
        if (isValid(cols, row, col)) {
            cols[row] = col;
            nQueensHelper(cols, n, row + 1, count);
            cols[row] = -1;
        }
    }
}
int nQueens(int n)
{
    vector<int> cols(n, -1);  // cols[i] = j means a queen is placed in row i, column j
    int count = 0;
    nQueensHelper(cols, n, 0, count);
    return count;
}

/*int main()
{
    cout << "1: " << nQueens(1) << endl;
    cout << "2: " << nQueens(2) << endl;
    cout << "3: " << nQueens(3) << endl;
    cout << "4: " << nQueens(4) << endl;
    cout << "5: " << nQueens(5) << endl;
    cout << "6: " << nQueens(6) << endl;
    cout << "7: " << nQueens(7) << endl;
    cout << "8: " << nQueens(8) << endl;
    cout << "9: " << nQueens(9) << endl;
    cout << "10: " << nQueens(10) << endl;
    cout << "11: " << nQueens(11) << endl;
    cout << "12: " << nQueens(12) << endl;
    return 0;
}*/