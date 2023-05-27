#include <array>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

int main() {
    ifstream data_file(".\\orders.csv");  // Orders source file

    string possible_instruments[] = {"Rose", "Lavender", "Lotus", "Tulip", "Orchid"};  // For validation
    int valid_instrument;  // Indicator variable for validating instrument value

    array<string, 5> row;             // To store each row
    vector<array<string, 5>> orders;  // Master vector to store transaction orders

    int n = 0;             // DEBUG: line counter

    if (!data_file) {  // Check if file is read
        cout << "Error reading file!" << endl;
        return 0;
    } else {
        cout << "File read successfully!" << endl;
    }

    // Read the file as long as the file pointer is good
    // Read each data point. Try to validate it.
    // On fail, move file pointer to next line and skip iteration.
    while (data_file.good()) {  // When filestream is being read, iterate each line
        n++;                    // DEBUG: line counter
        // Column 1
        getline(data_file, row[0], ',');

        if ((row[0].length() < 1) || (row[0].length() > 7)) {
            cout << "Line " << n << " skipped!. (Column 1)" << endl;  // DEBUG
            data_file.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        // Column 2
        getline(data_file, row[1], ',');

        valid_instrument = 0;  // For each new row, set the indicator as 0, since it's unchecked
        for (string instrument : possible_instruments) {
            if (instrument == row[1]) {
                valid_instrument = 1;  // If value is in possible values
            }
        }

        if (!valid_instrument) {
            cout << "Line " << n << " skipped!. (Column 2)" << endl;  // DEBUG
            data_file.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        // Column 3
        getline(data_file, row[2], ',');

        if ((row[2] != "1") && (row[2] != "2")) {
            cout << "Line " << n << " skipped!. (Column 3)" << endl;  // DEBUG
            data_file.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        // Column 4
        getline(data_file, row[3], ',');

        int read_quantity = stoi(row[3]);
        if ((read_quantity < 10) || (read_quantity > 1000) || (read_quantity % 10 != 0)) {
            cout << "Line " << n << " skipped!. (Column 4)" << endl;  // DEBUG
            data_file.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        // Column 5
        getline(data_file, row[4], '\n');

        double read_price = stod(row[4]);
        if (read_price <= 0.0) {
            cout << "Line " << n << " skipped!. (Column 5)" << endl;  // DEBUG
            data_file.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        // DEBUG
        // cout << "Line " << n << " read!" << endl;

        orders.push_back(row);  // Append each row to master vector
    }

    // DEBUG: To print read values
    // for (auto row : orders) {
    //     for (auto data : row) {
    //         cout << data << " ";
    //     }
    //     cout << endl;
    // }
}
