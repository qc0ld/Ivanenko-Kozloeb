#include "dialog.h"

using namespace std;


void Dialog::linear_convolution_2d() {
    vector<vector<double>> x = read_matrix('x');
    vector<vector<double>> h = read_matrix('h');
    vector<vector<double>> result;

    bool system = read_system();

    result = Signal::linear_convolution_2d(x, h, system);

    Signal::print_2d_vector(result, 'y', system);
}

void Dialog::circular_convolution_2d() {
    vector<vector<double>> x = read_matrix('x');
    vector<vector<double>> h = read_matrix('h');
    vector<vector<double>> result;

    bool system = read_system();
    try {
        result = Signal::circular_convolution_2d(x, h, system);
    } catch (const runtime_error &e) {
        cout << "Error: " << e.what() << endl;
    }
    if (!result.empty()) {
        Signal::print_2d_vector(result, 'y', system);
    }
}

void Dialog::linear_convolution() {
    vector<double> x = read_vector('x');
    vector<double> h = read_vector('h');
    vector<double> result;

    result = Signal::linear_convolution(x, h);

    cout << endl;
    Signal::print_vector(result, 'y');
    cout << endl;
}

void Dialog::circular_convolution() {
    vector<double> x = read_vector('x');
    vector<double> h = read_vector('h');
    vector<double> result;

    try {
        result = Signal::circular_convolution(x, h);
    } catch (const runtime_error &e) {
        cout << "Error: " << e.what() << endl;
    }
    if (!result.empty()) {
        cout << endl;
        Signal::print_vector(result, 'y');
        cout << endl;
    }
}


void Dialog::median_filtering() {
    vector<double> x = read_vector('x');

    int A = read_int("Enter A: ");
    int amount = read_int("Enter number of repetitions: ");

    for (size_t i = 0; i < x.size(); i++) {
        cout << setw(4) << " ";
    }

    cout << endl << "   i    ";

    for (size_t i = 0; i < x.size(); i++) {
        cout << setw(4) << i;
    }

    cout << endl;

    Signal::print_vector(x, 'U');
    
    for (int i = 0; i < amount; i++) {
        x = Signal::median_filtering(x, A);
        Signal::print_vector(x, 'y');
    }
    
    cout << endl;
}