/*
 * Name:
 * Date Submitted:
 * Lab Section:
 * Assignment Name:
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

struct point
{
    double x;
    double y;
};

/*Implement the following function
  Reads in a file specified by the parameter
  Format of file: #of points on first line
                  remaining (#of points) lines: x-value and y-value of point
                  one point per line
                  x-value and y-value are double-precision values and
                  bounded by the unit square 0.0 <= x,y < 1.0
  Should use "spatial hashing" where the #of cells scales with the #of points
  and find the distance between the closest pair of points which will be
  returned as a double type value
*/
double closestPair(string filename);

double closestPair(string filename) {
    ifstream file(filename);
    int n;

    if (!file.is_open()) {  //check if file exists
        cout << "FILE DOES NOT EXIST" << endl;
        return 0;
    }

    file >> n; //read the first number in the file, which sets the size of the list.

    vector<vector<vector<point>>> cells; //make a 3d array of points

    // Calculate the value of b based on the number of points
    int b = ceil(sqrt(n));
    //we find the ceil(sqrt(n)) because the vector defined by vector<vector<vector<point>>> cells
    //is "3 dimensional". So the best way to calculate b is by treating the number of elements as though
    //it's a square. That way, we can iterate through "planes" of the 3d vector all at once.


    // Initialize the cells
    cells.resize(b);
    for (int i = 0; i < b; i++) {
        cells[i].resize(b);
    }

    // Read the points and add them to the appropriate cell
    for (int i = 0; i < n; i++) {
        point p;
        file >> p.x >> p.y;

        int cell_x = floor(p.x * b);
        int cell_y = floor(p.y * b);
        cells[cell_x][cell_y].push_back(p);
    }

    // Find the closest pair of points
    double min_dist = INFINITY;
    for (int i = 0; i < b; i++) {
        for (int j = 0; j < b; j++) {
            for (auto &p1 : cells[i][j]) {
                for (int k = -1; k <= 1; k++) {
                    for (int l = -1; l <= 1; l++) {
                        int x = i + k;
                        int y = j + l;
                        if (x >= 0 && x < b && y >= 0 && y < b) {
                            for (auto &p2 : cells[x][y]) {
                                if (&p1 == &p2) {
                                    continue;
                                }
                                double dist = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
                                if (dist < min_dist) {
                                    min_dist = dist;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return min_dist;
}
/*int main()
{
    double min;
    string filename;
    cout << "File with list of points within unit square: ";
    cin >> filename;
    min = closestPair(filename);
    cout << setprecision(16);
    cout << "Distance between closest pair of points: " << min << endl;
    return 0;
}*/