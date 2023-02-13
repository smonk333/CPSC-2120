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

Grouping::Grouping(std::string fileName) {
    ifstream inFile(fileName);//creating a filestream and pointing it at the file that was passed in from main()
    string tmp; //making a string to temporarily hold each line from the filestream
    vector<int> converted; //making a vector of ints to hold the output of the conversion to ints from a string
    vector<vector<int>> array; //making a 2d vector to hold the rows in 2d

    if (inFile.is_open()) {
        while (getline(inFile, tmp)) { //start grabbing lines from the file
            array.push_back(convert(tmp));
        }
    }
    else if (!inFile.is_open()) {
        cout << "FILE NOT OPENED";
    }
    //convert the 2d vector into a 2d int array, and push those values into this->grid[][]

    int rows = array.size();
    int cols = array[0].size();
    int **arr2d = new int*[rows];

    for (int i = 0; i < rows; i++) {
        arr2d[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            arr2d[i][j] = array[i][j];
        }
    }

    //fill the this->grid member variable with the contents of the arr2d variable

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = arr2d[i][j];
        }
    }
/*
    //freeing memory held by arrays and vectors and closing the filestream as they are no longer necessary
    in.close();

    for (int i = 0; i < rows; i++) {
        delete[] arr2d[i];
    }
    delete[] arr2d;

    for (int i = 0; i < rows; i++) {
        array[i].clear();
    }

    array.clear();

    converted.clear();*/
}

void Grouping::findGroup(int r, int c) {
    int groupIndex = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (grid[i][j] == 1) { // found a new single group
                groupIndex++;
                vector<GridSquare> group;
                findGroup(i, j);
                groups.push_back(group);
            }
        }
    }

    if (r < 0 || r >= 10 || c < 0 || c >= 10 || this->grid[r][c] == 0) { // base case, we hit the edge of the grid or a square that's not occupied.
        return;
    }

}




//Simple main function to test Grouping
//Be sure to comment out main() before submitting
int main()
{
    Grouping input1("input1.txt");
    input1.printGroups();
    
    return 0;
}

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