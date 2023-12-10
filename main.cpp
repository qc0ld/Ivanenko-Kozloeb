#include "dialog.h"

using namespace std;
using namespace Dialog;

void menu();

int main() {
    int number;

    while (1) {
        menu();

        number = read_menu();

        if (number == 0) {
            break;
        } else if (number == 1) {
            median_filtering();
        } else if (number == 2) {
            linear_convolution();
        } else if (number == 3) {
            circular_convolution();
        } else if (number == 4) {
            linear_convolution_2d();
        } else if (number == 5) {
            circular_convolution_2d();
        }
    }
    return 0;
}

void menu() {
    cout << "1. Median filtering" << endl;
    cout << "2. Linear convolution" << endl;
    cout << "3. Circular convolution" << endl;
    cout << "4. Linear convolution 2D" << endl;
    cout << "5. Circular convolution 2D" << endl;
    cout << "0. Exit" << endl;
}

