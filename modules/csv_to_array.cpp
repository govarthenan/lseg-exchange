#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
    ifstream data_file(".\\orders.csv");  // Orders source file

    string row[5];  // To store each row
    string word;

    if (!data_file) {
        cout << "Error reading file!" << endl;
        return 0;
    } else {
        cout << "File read successfully!" << endl;
    }

    while (data_file.good()) {
        for (int i = 0; i < 4; i++) {
            getline(data_file, row[i], ',');
        }
        getline(data_file, row[4], '\n');
    }
}
