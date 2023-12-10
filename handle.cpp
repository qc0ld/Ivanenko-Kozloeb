#include "handle.h"


using namespace std;

bool read_system() {
    cout << "Enter coordinate system (0 - Physical, 1 - Algebraic): ";
    bool system = read_int("");
    while (1) {
        if (system == 1 || system == 0) {
            break;
        } else {
            cout << "Enter correct number (1 - Physical, 2 - Algebraic): ";
        }
    }
    return system;
}

int read_menu() {
    int number = read_int(":>");
    while (1) {
        if (number <= 5 && number >= 0) {
            break;
        } else {
            cout << "Enter correct number: ";
        }
    }
    return number;
}

bool is_number(const string &s) {
    std::istringstream iss(s);
    double number;
    iss >> number;
    return !iss.fail() && iss.eof();
}

int read_int(string str) {
    string input;
    cout << str;
    while (true) {
        cin >> input;
        if (is_number(input)) {
            return stoi(input);
        } else {
            cout << "Enter correct number: " << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

vector<double> read_vector(char name) {
    cout << "Enter amount of elements in a row in vector " << name << ": ";
    int elements_amount = read_int("");
    vector<double> x(elements_amount);
    cout << "Enter elements: ";
    for (int i = 0; i < elements_amount; ++i) {
        x[i] = read_int("");
    }
    return x;
}

vector<vector<double>> read_matrix(char name) {
    cout << "Enter amount of rows in " << name << " matrix: ";
    int rows_amount = read_int("");
    cout << "Enter amount of elements in a row in matrix " << name << ": ";
    int elements_amount = read_int("");

    vector<vector<double>> x(rows_amount, vector<double>(elements_amount));

    for (int i = 0; i < rows_amount; ++i) {
        cout << "Enter elements for row #" << i + 1 << ": ";
        for (int j = 0; j < elements_amount; ++j) {
            x[i][j] = read_int("");
        }
    }
    return x;
}
