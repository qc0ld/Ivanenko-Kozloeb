#ifndef SIGNAL_PROCESSING_H
#define SIGNAL_PROCESSING_H

#include "handle.h"

namespace Signal {
    vector<vector<double>> linear_convolution_2d(vector<vector<double>> &x, vector<vector<double>> &h, bool system);

    vector<double> linear_convolution(vector<double> &x, vector<double> &h);

    vector<vector<double>> circular_convolution_2d(vector<vector<double>> &x, vector<vector<double>> &h, bool system);

    vector<double> circular_convolution(vector<double> &x, vector<double> &h);

    void print_2d_vector(const vector<vector<double>> &vector, char name, bool system);

    void print_vector(const vector<double> &vector, char name);

    vector<double> median_filtering(vector<double> &x, int A, int amount);
}



#endif //SIGNAL_PROCESSING_H
