#include <iostream>
using namespace std;

struct Element {
    int row, col, val;
};

class SparseMatrix {
private:
    int rows, cols, numElements;
    Element *elements;

public:
    SparseMatrix(int r, int c, int n) {
        rows = r;
        cols = c;
        numElements = n;
        elements = new Element[n];
    }

    ~SparseMatrix() {
        delete[] elements;
    }

    void read() {
        cout << "Enter row, column, and value for each non-zero element:\n";
        for (int i = 0; i < numElements; i++) {
            cin >> elements[i].row >> elements[i].col >> elements[i].val;
        }
    }

    void displayFull() {
        int k = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (k < numElements && elements[k].row == i && elements[k].col == j) {
                    cout << elements[k++].val << " ";
                } else {
                    cout << "0 ";
                }
            }
            cout << endl;
        }
    }

    void displaySparse() {
        cout << "Row Col Value\n";
        for (int i = 0; i < numElements; i++) {
            cout << elements[i].row << " " << elements[i].col << " " << elements[i].val << endl;
        }
    }
};

int main() {
    int rows, cols, n;
    cout << "Enter number of rows, cols, and non-zero elements: ";
    cin >> rows >> cols >> n;

    SparseMatrix sm(rows, cols, n);
    sm.read();

    cout << "\nSparse Representation:\n";
    sm.displaySparse();

    cout << "\nFull Matrix Representation:\n";
    sm.displayFull();

    return 0;
}
