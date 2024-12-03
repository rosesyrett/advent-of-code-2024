#include <string>
#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

/* Split a string by a delimiter

E.g. `split("1, 2, 3, 4", delimiter=", ")` yields a vector with `{"1", "2", "3", "4"}`*/
vector<string> split(const string& line, const string& delimiter) {
    size_t nextPos = 0;
    size_t lastPos = 0;
    vector<string> tokens;

    while((nextPos = line.find(delimiter, lastPos)) != string::npos) {
        string sub = line.substr(lastPos, nextPos - lastPos);
        tokens.push_back(sub);
        lastPos = nextPos + delimiter.length();
    }

    tokens.push_back(line.substr(lastPos, line.length() - lastPos));

    return tokens;
}

/* Evaluate if a report is safe or not.

A safe report is one where the levels are:
- all increasing or all decreasing
- delta varies between 1-3

E.g. a report with 4 levels like,

1 3 5 6

is safe, but

1 3 3 2

... is not.
*/
bool safeReport(vector<int>& report) {
    bool ascending; // will either be true or false


    for (int i=1; i<report.size(); i++) {
        int currentNumber = report.at(i);
        int previousNumber = report.at(i-1);
        
        if(i>1 && ((currentNumber > previousNumber) != ascending)) {
            return false;
        }
        if ((previousNumber - currentNumber) == 0 || abs(previousNumber - currentNumber) > 3 ) {
            return false;
        }
        ascending = currentNumber > previousNumber;
    }

    return true;
}



/*Calls safeReport on a report with a missing value? */
bool testSafeReportByRemovingOneItemIfUnsafe(vector<int>& report) {
    bool isSafe = safeReport(report);

    if (!isSafe) {
        for(int i=0; i< report.size(); i++) {
            vector<int> reportWithoutItem(report);
            reportWithoutItem.erase(reportWithoutItem.begin() + i);

            // if any of these are 'true', then it is true.
            if (safeReport(reportWithoutItem)) {
                isSafe = true;
                break;
            }
        }
    }
    return isSafe;
}


/* like safetyTest but dumber */
int safetyTest(string fileName, vector<bool>& safety) {
    ifstream file(fileName);

    //first, read the file to get the number of lines
    string line;
    int safeCounter = 0;

    while(getline(file, line)) {
        vector<string> delimitedLine = split(line, " ");
        vector<int> report;

        for(const string& item: delimitedLine) {
            report.push_back(stoi(item));
        }

        bool safe = testSafeReportByRemovingOneItemIfUnsafe(report);
        safety.push_back(safe);
        if (safe == true) {
            safeCounter++;
        }
    };

    return safeCounter;
}

int main() {
    vector<bool> safety;

    int numberOfSafeReports = safetyTest("input.txt", safety);

    cout << numberOfSafeReports << "\n";
    return 0;
}