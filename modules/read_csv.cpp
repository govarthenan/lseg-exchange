#include <array>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

struct Order {
    string order_id;
    string instrument;
    int side;
    double price;
    int quantity;
};

vector<Order> readCSVFile(const string& filename) {
    ifstream data_file(filename);  // Orders source file

    string possible_instruments[] = {"Rose", "Lavender", "Lotus", "Tulip", "Orchid"};  // For validation
    int valid_instrument;                                                              // Indicator variable for validating instrument value

    string temp;           // For temporarily storage during reading values
    Order row;             // To store each row
    vector<Order> orders;  // Master vector to store transaction orders

    int n = 0;  // DEBUG: line counter

    if (!data_file) {  // Check if file is read
        cout << "Error reading file!" << endl;
        return orders;  // Return empty vector
    } else {
        cout << "File read successfully!" << endl;
    }

    // Read the file as long as the file pointer is good
    // Read each data point. Try to validate it.
    // On fail, move file pointer to next line and skip iteration.
    // If valid, assign to struct and push struct to master vector.
    while (data_file.good()) {  // When filestream is being read, iterate each line
        n++;                    // DEBUG: line counter

        row = {};  // Reset all members of the struct

        // Column 1 - User Order ID
        getline(data_file, row.order_id, ',');

        if ((row.order_id.length() < 1) || (row.order_id.length() > 7)) {
            cout << "Line " << n << " skipped!. (Column 1)" << endl;  // DEBUG
            data_file.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        // Column 2 - Instrument
        getline(data_file, row.instrument, ',');

        valid_instrument = 0;  // For each new row, set the indicator as 0, since it's unchecked
        for (string instrument : possible_instruments) {
            if (instrument == row.instrument) {
                valid_instrument = 1;  // If value is in possible values
            }
        }

        if (!valid_instrument) {
            cout << "Line " << n << " skipped!. (Column 2)" << endl;  // DEBUG
            data_file.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        // Column 3 - Side
        getline(data_file, temp, ',');

        if ((temp != "1") && (temp != "2")) {
            cout << "Line " << n << " skipped!. (Column 3)" << endl;  // DEBUG
            data_file.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        row.side = stoi(temp);  // Assign converted valid value to struct

        // Column 4 - Quantity
        getline(data_file, temp, ',');
        row.quantity = stoi(temp);  // Convert and store

        if (((row.quantity % 10) != 0) || (row.quantity < 10) || (row.quantity > 1000)) {
            cout << "Line " << n << " skipped!. (Column 4)" << endl;  // DEBUG
            data_file.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        // Column 5 - Price
        getline(data_file, temp, '\n');
        row.price = stod(temp);  // Convert and store

        if (row.price <= 0.0) {
            cout << "Line " << n << " skipped!. (Column 5)" << endl;  // DEBUG
            // data_file.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        orders.push_back(row);  // Append each row to master vector
    }

    return orders;  // Return the master vector
}

int main() {
    vector<Order> orders = readCSVFile("../orders.csv");

    // DEBUG: To print read values
    cout << endl;
    for (auto line : orders) {
        cout << line.order_id << " " << line.instrument << " " << line.side << " " << line.quantity << " " << line.price << endl;
    }
}