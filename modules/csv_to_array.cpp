#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ifstream data_file(".\\orders.csv");  // Orders source file

    array<string, 5> row;             // To store each row
    vector<array<string, 5>> orders;  // Master vector to store transaction orders

    if (!data_file) {  // Check if file is read
        cout << "Error reading file!" << endl;
        return 0;
    } else {
        cout << "File read successfully!" << endl;
    }

    while (data_file.good()) {  // When filestream is being read, iterate each line
        for (int i = 0; i < 4; i++) {
            getline(data_file, row[i], ',');  // Read each value up to comma and store it inside array
        }
        getline(data_file, row[4], '\n');  // For the last value, read till newline

        orders.push_back(row);  // Append curren't row's array to the vector
    }

    // DEBUG: To print read values
    // for (auto row : orders) {
    //     for (auto data : row) {
    //         cout << data << " ";
    //     }
    //     cout << endl;
    // }
}
