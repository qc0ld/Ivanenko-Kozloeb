#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

vector<vector<int>> linear_convolution(vector<vector<int>> x, vector<vector<int>> h, bool coordinate_system);

vector<vector<int>> circular_convolution(vector<vector<int>> x, vector<vector<int>> h, bool coordinate_system);

void print_2d_array(const vector<vector<int>> &array);

enum
{
    PHYSICAL,
    ALGEBRAIC
};

int main()
{
    vector<vector<int>> x = {
        {1},
        {2},
        {3}
        };

    vector<vector<int>> h = {
        {3,0,2,1},
        {-1,2,4,5}
        };

    try {
        print_2d_array(linear_convolution(x, h, PHYSICAL));
    }
    catch (const runtime_error &e) {
        cout << "Error: " << e.what() << endl;
    }
    return 0;
}

vector<vector<int>> linear_convolution(vector<vector<int>> x, vector<vector<int>> h, bool coordinate_system)
{
    int x_rows = x.size();
    int x_cols = x[0].size();
    int hRows = h.size();
    int hCols = h[0].size();
    int offset = hCols + hRows;

    vector<vector<int>> result(x_rows + hRows - 1, vector<int>(x_cols + hCols - 1, 0));
    vector<vector<int>> array(offset * 2, vector<int>(offset * 3, 0));

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

    if (coordinate_system == PHYSICAL)
    {
        reverse(result.begin(), result.end());
    }
    return result;
}

vector<vector<int>> circular_convolution(vector<vector<int>> x, vector<vector<int>> h, bool coordinate_system)
{
    int rows = x.size();
    int cols = x[0].size();
    int h_rows = h.size();
    int h_cols = h[0].size();

    if (rows != h_rows || cols != h_cols) {
        throw runtime_error("Matrices must be same size");
    }

    int offset = cols + rows;

    vector<vector<int>> result(rows, vector<int>(cols, 0));
    vector<vector<int>> array(offset * 2, vector<int>(offset * 3, 0));

    for (auto &row : h) { reverse(row.begin(), row.end()); }
    reverse(x.begin(), x.end());
    for (int i = offset; i < rows + offset; i++) {
        for (int j = offset; j < cols + offset; j++) {
            array[i][j] = h[i - offset][j - offset];
        }
    }

    for (int i = 0; i < offset; ++i) {
        for (int j = 0; j < 2 * offset; ++j) {
            array[i + offset][j + offset] = h[i % rows][j % cols];
            array[-i + offset][j + offset] = h[i % rows][j % cols];
        }
    }

    for (int i = 0; i < offset; ++i) {
        for (int j = 0; j < 2 * offset; ++j) {
            if (offset - j >= 0) {
                array[i + offset][offset - j] = array[i + offset][offset + cols - j];
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

    if (coordinate_system == PHYSICAL) {
        reverse(result.begin(), result.end());
    }
    return result;
}

void print_2d_array(const vector<vector<int>> &array)
{
    for (size_t i = 0; i < array.size(); ++i) {
        for (size_t j = 0; j < array[i].size(); ++j) {
            cout << array[i][j] << ' ';
        }
        cout << endl;
    }
}
