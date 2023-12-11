#include "signal_processing.h"

using namespace std;

void Signal::print_2d_vector(const vector<vector<double>> &vector, char name, bool system);

vector<vector<double>> Signal::linear_convolution_2d(vector<vector<double>> &x, vector<vector<double>> &h, bool system) {
    int x_rows = x.size();
    int x_cols = x[0].size();
    int hRows = h.size();
    int hCols = h[0].size();
    int offset = hCols + hRows;

    vector<vector<double>> result(x_rows + hRows - 1, vector<double>(x_cols + hCols - 1, 0));
    vector<vector<double>> array(offset * 3, vector<double>(offset * 3, 0));

    for (auto &row : h) { reverse(row.begin(), row.end()); }
    reverse(x.begin(), x.end());

    for (int i = offset; i < hRows + offset; i++) {
        for (int j = offset; j < hCols + offset; j++) {
            array[i][j] = h[i - offset][j - offset];
        }
    }

    int x_offset = offset + hCols - 1;
    int y_offset = offset + hRows - 1;
    for (int i = 0; i < x_rows + hRows - 1; ++i) {
        for (int j = 0; j < x_cols + hCols - 1; ++j) {
            for (int k = 0; k < x_rows; ++k) {
                for (int l = 0; l < x_cols; ++l) {
                    result[i][j] += x[k][l] * array[y_offset + k - i][x_offset + l - j];
                }
            }
        }
    }

    if (system == PHYSICAL)
    {
        reverse(result.begin(), result.end());
    }

    return result;
}

vector<double> Signal::linear_convolution(vector<double> &x, vector<double> &h) {
    vector<vector<double>> x_vector(1, vector<double>(x.size(), 0));
    vector<vector<double>> h_vector(1, vector<double>(h.size(), 0));
    vector<vector<double>> result(1, vector<double>(h.size() + x.size() - 1, 0));

    for (size_t i = 0; i < x.size(); i++) {
        x_vector[0][i] = x[i];
        h_vector[0][i] = h[i];
    }
    result = Signal::linear_convolution_2d(x_vector, h_vector, ALGEBRAIC);

    return result[0];
}

vector<vector<double>> Signal::circular_convolution_2d(vector<vector<double>> &x, vector<vector<double>> &h, bool system) {
    int rows = x.size();
    int cols = x[0].size();
    int h_rows = h.size();
    int h_cols = h[0].size();
    int offset = cols + rows;

    if (rows != h_rows || cols != h_cols) {
        throw runtime_error("Signals must be the same size");
    }

    vector<vector<double>> result(rows, vector<double>(cols, 0));
    vector<vector<double>> array(offset * 3, vector<double>(offset * 3, 0));

    for (auto &row: h) { reverse(row.begin(), row.end()); }
    reverse(x.begin(), x.end());

    for (int i = offset; i < rows + offset; i++) {
        for (int j = offset; j < cols + offset; j++) {
            array[i][j] = h[i - offset][j - offset];
        }
    }

    for (int i = 0; i < 2 * offset; ++i) {
        for (int j = 0; j < 2 * offset; ++j) {
            if (j + offset < 3 * offset) {
                if (i + offset < 3 * offset) {
                    array[i + offset][j + offset] = h[i % rows][j % cols];
                }
                if (-i + offset >= 0) {
                    array[-i + offset][j + offset] = h[i % rows][j % cols];
                }
            }
        }
    }

    for (int i = 0; i < 2 * offset; ++i) {
        for (int j = 0; j < 2 * offset; ++j) {
            if (offset - j >= 0) {
                if (offset + i < 3 * offset) {
                    array[i + offset][offset - j] = array[i + offset][offset + cols - j];
                }
                if (offset - i >= 0) {
                    array[offset - i][offset - j] = array[i + offset][offset + cols - j];
                }
            }
        }
    }

    int x_offset = offset + cols - 1;
    int y_offset = offset + rows - 1;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            for (int k = 0; k < rows; ++k) {
                for (int l = 0; l < cols; ++l) {
                    result[i][j] += x[k][l] * array[y_offset + k - i][x_offset + l - j];
                }
            }
        }
    }

    if (system == PHYSICAL) {
        reverse(result.begin(), result.end());
    }
    return result;
}

vector<double> Signal::circular_convolution(vector<double> &x, vector<double> &h) {
    vector<vector<double>> x_vector(1, vector<double>(x.size(), 0));
    vector<vector<double>> h_vector(1, vector<double>(h.size(), 0));
    vector<vector<double>> result(1, vector<double>(h.size(), 0));

    for (size_t i = 0; i < x.size(); i++) {
        x_vector[0][i] = x[i];
        h_vector[0][i] = h[i];
    }
    result = Signal::circular_convolution_2d(x_vector, h_vector, ALGEBRAIC);

    return result[0];
}

vector<double> Signal::median_filtering(vector<double> &x, int A, int amount) {
    vector<double> temp;
    double value;
    for (size_t i = 0; i < x.size(); i++) {
        cout << setw(4) << " ";
    }
    cout << endl << "   i    ";
    for (size_t i = 0; i < x.size(); i++) {
        cout << setw(4) << i;
    }
    cout << endl;
    print_vector(x, 'U');
    for (int n = 0; n < amount; n++) {
        vector<double> vector;
        for (size_t i = 0; i < x.size(); i++) {
            temp.clear();
            for (size_t j = 0; static_cast<int>(j) < A; j++) {
                if (i + j - floor(A / 2) >= 0 && i + j <= x.size()) {
                    temp.push_back(x[i + j - floor(A / 2)]);
                }
            }
            sort(temp.begin(), temp.end());
            if (temp.size() % 2 == 0) {
                value = (temp[temp.size() / 2 - 1] + temp[temp.size() / 2]) / 2;
            } else {
                value = temp[int(temp.size() / 2)];
            }
            vector.push_back(value);
        }
        x = vector;
        print_vector(x, 'y');
    }
    return x;
}

void Signal::print_2d_vector(const vector<vector<double>> &vector, char name, bool system) {
    int middle = floor(vector.size() / 2);
    cout << endl;
    for (size_t i = 0; i < vector.size(); ++i) {
        if (static_cast<int>(i) != middle) {
            cout << setw(9) << " ";
        } else {
            cout << "{" << name << "(i)}  =";
        }
        for (size_t j = 0; j < vector[i].size(); ++j) {
            cout << setw(4) << vector[i][j];
        }
        cout << endl;
    }
    cout << endl << "The answer is given in ";
    if (system == PHYSICAL) {
        cout << "Physical";
    } else if (system == ALGEBRAIC){
        cout << "Algebraic";
    }
    cout << " coordinate system." << endl << endl;
}

void Signal::print_vector(const vector<double> &vector, char name) {
    cout << "{" << name << "(i)} = [ ";
    for (size_t i = 0; i < vector.size(); i++) {
        if (i == 0) {
            cout << vector[i];
        } else {
            cout << setw(4) << vector[i];
        }
    }
    cout << " ]" << endl;
}