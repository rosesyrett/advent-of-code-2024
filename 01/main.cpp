#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <string>
#include <algorithm>
using namespace std;

/* Simply reads a text file with two columns of integers. Takes two vectors as input which this modifies. */
void readInput(string fileName, string delimiter, vector<int>& firstColumn, vector<int>& secondColumn) {
    ifstream file(fileName);

    //first, read the file to get the number of lines
    string line;

    while(getline(file, line)) {
        size_t found = line.find(delimiter); // The delimiter for this file is 3 spaces.

        // if we find the delimiter in the line, split by it and try to convert each half to int
        if(found != string::npos) {
            int firstItem;
            int secondItem;

            try {
                firstItem = stoi(line.substr(0, found));
                secondItem = stoi(line.substr(found + delimiter.length()));

            } catch (invalid_argument) {
                cerr << "Failed to parse";
                break;
            };
            firstColumn.push_back(firstItem);
            secondColumn.push_back(secondItem);
        };
    };
    
}

/* Solves part 1 of the puzzle. Finds the sum of the difference between the input columns. */
int differenceFinder() {
    vector<int> firstColumn;
    vector<int> secondColumn;
    readInput("input.txt", "   ", firstColumn, secondColumn);

    sort(firstColumn.begin(), firstColumn.end());
    sort(secondColumn.begin(), secondColumn.end());

    int totalDifference = 0;
    for (size_t i = 0 ; i< firstColumn.size(); i++) {
        totalDifference += abs(firstColumn.at(i) - secondColumn.at(i));
    }

    return totalDifference;
}


/*Solves part 2 of the puzzle. For each number in the 1st col, multiplies by number of occurences in the 2nd.*/
int main() {
    vector<int> firstColumn;
    vector<int> secondColumn;
    readInput("input.txt", "   ", firstColumn, secondColumn);

    // first, find the unique numbers in the firstColumn. Also store a count of how often it's appeared.

    vector<int> uniqueFirstColumn;
    vector<int> uniqueCountFirstColumn;

    for (int i = 0; i < firstColumn.size(); i++) {
        int item = firstColumn.at(i);

        // is it in the uniqueFirstColumn?
        int indexInUniqueFirstColumn =find(uniqueFirstColumn.begin(), uniqueFirstColumn.end(), item) - uniqueFirstColumn.begin();

        if (indexInUniqueFirstColumn > (int(uniqueFirstColumn.size()) - 1)) {
            // the index is greater than is possible. So, the item is not in uniqueFirstColumn. Add it.
            uniqueFirstColumn.push_back(item);
            uniqueCountFirstColumn.push_back(1);
        } else {
            // the index is possible, so the item is in uniqueFirstColumn.
            uniqueCountFirstColumn[indexInUniqueFirstColumn]++;
        }
    }

    // For each unique number of the firstColumn, find how many times it occurs in the secondColumn.
    // multiply this by the number of times it appears in the firstColumn, by the value of the item,
    // for each unique item.

    // store a total
    int total = 0;

    for (int i=0; i< uniqueFirstColumn.size(); i++) {
        int numberOfOccurences = count(secondColumn.begin(), secondColumn.end(), uniqueFirstColumn.at(i));
        total += uniqueFirstColumn.at(i) * uniqueCountFirstColumn.at(i) * numberOfOccurences;
    }

    cout << "total is: " << total << "\n";

    return 0;
}
