#include <iostream>
using namespace std;

struct Node {
    int row, col, val;
    Node* next;
    Node(int r, int c, int v) : row(r), col(c), val(v), next(nullptr) {}
};

class SparseMatrix {
private:
    int rows, cols;
    Node* head;

public:
    SparseMatrix(int r, int c) {
        rows = r;
        cols = c;
        head = nullptr;
    }

    ~SparseMatrix() {
        Node* temp;
        while (head) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insert(int r, int c, int v) {
        Node* newNode = new Node(r, c, v);
        if (!head || (r < head->row || (r == head->row && c < head->col))) {
            newNode->next = head;
            head = newNode;
            return;
        }
        Node* curr = head;
        while (curr->next && (curr->next->row < r || (curr->next->row == r && curr->next->col < c))) {
            curr = curr->next;
        }
        newNode->next = curr->next;
        curr->next = newNode;
    }

    void displaySparse() {
        cout << "Row Col Value\n";
        Node* curr = head;
        while (curr) {
            cout << curr->row << " " << curr->col << " " << curr->val << endl;
            curr = curr->next;
        }
    }

    void displayFull() {
        Node* curr = head;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (curr && curr->row == i && curr->col == j) {
                    cout << curr->val << " ";
                    curr = curr->next;
                } else {
                    cout << "0 ";
                }
            }
            cout << endl;
        }
    }
};

int main() {
    int rows, cols, n;
    cout << "Enter number of rows, cols, and non-zero elements: ";
    cin >> rows >> cols >> n;

    SparseMatrix sm(rows, cols);
    cout << "Enter row, column, and value for each non-zero element:\n";
    for (int i = 0; i < n; i++) {
        int r, c, v;
        cin >> r >> c >> v;
        sm.insert(r, c, v);
    }

    cout << "\nSparse Representation:\n";
    sm.displaySparse();

    cout << "\nFull Matrix Representation:\n";
    sm.displayFull();

    return 0;
}
