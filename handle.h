#ifndef HANDLE_H
#define HANDLE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>

enum {
    PHYSICAL,
    ALGEBRAIC,
};

using namespace std;

vector<vector<double>> read_matrix(char name);

vector<double> read_vector(char name);

int read_int(string str);

bool read_system();

int read_menu();


#endif //HANDLE_H
