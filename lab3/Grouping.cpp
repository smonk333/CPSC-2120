/*
 * Name:
 * Date Submitted:
 * Lab Section:
 * Assignment Name:
 */

#include "Grouping.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//Implement the (parameterized) constructor and findGroup functions below
vector<int> convert(string tmp) { //convert the tmp string from '.' and 'X' to '0' and '1'
    vector<int> a; //make a vector to temporarily hold the values before we convert them to an array;

    for (int i = 0; i < tmp.size(); i++) {
        if (tmp[i] == '.') {
            a.push_back(0);
        }
        else {
            a.push_back(1);
        }
    }

    return a; //return the vector of ints
}

Grouping::Grouping(std::string fileName) : grid{}, groups(){
    // Read the input file into the grid
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        std::cerr << "Unable to open file " << fileName << std::endl;
        return;
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            char c;
            inputFile >> c;
            if (c == '.') {
                grid[i][j] = 0;
            } else {
                grid[i][j] = 1;
            }
        }
    }
    inputFile.close();

    // Process the grid to populate groups
    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 10; col++) {
            if (grid[row][col] == 1) {
                std::vector<GridSquare> group;
                findGroup(row, col, group);
                groups.push_back(group);
            }
        }
    }
}

// Recursive function that finds the group of an occupied square
// r: the row of the current square
// c: the column of the current square

void Grouping::findGroup(int r, int c, vector<GridSquare> &group) {
    if (r < 0 || r >= 10 || c < 0 || c >= 10 || grid[r][c] == 0) {
        return;
    }
    grid[r][c] = 0;
    group.push_back(GridSquare(r, c));
    findGroup(r - 1, c, group);
    findGroup(r + 1, c, group);
    findGroup(r, c - 1, group);
    findGroup(r, c + 1, group);
}




//Simple main function to test Grouping
//Be sure to comment out main() before submitting
/*int main()
{
    Grouping input1("input4.txt");
    input1.printGroups();
    
    return 0;
}*/

//Do not modify anything below

GridSquare::GridSquare() : row(0), col(0) {} //Default constructor, (0,0) square

GridSquare::GridSquare(int r, int c) : row(r), col(c) {} //(r,c) square

//Compare with == operator, used in test cases
bool GridSquare::operator== (const GridSquare r) const
{
    if ((row == r.row) && (col == r.col))
    {
        return true;
    }
    return false;
}

int GridSquare::getRow() //return row value
{
    return row;
}

int GridSquare::getCol() //return column value
{
    return col;
}

//Output using << operator, used in Grouping::printGroups()
//Function definition for <ostream> << <GridSquare>
ostream& operator<< (ostream& os, const GridSquare obj)
{
    os << "(" << obj.row << "," << obj.col << ")";
    return os;
}

Grouping::Grouping() : grid{},groups() {} //Default constructor, no groups

void Grouping::printGroups() //Displays grid's groups of squares
{
    for(int g=0; g<groups.size(); g++)
    {
        cout << "Group " << g+1 << ": ";
        for(int s=0; s<groups[g].size(); s++)
        {
            cout << " " << groups[g][s];
        }
        cout << endl;
    }
}

vector<vector<GridSquare>> Grouping::getGroups() //Needed in unit tests
{
    return groups;
}