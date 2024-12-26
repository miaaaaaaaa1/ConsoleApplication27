#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
    string carNumber;            
    vector<string> violations;  
    Node* left;             
    Node* right;                  

    Node(string carNum, string violation) {
        carNumber = carNum;
        violations.push_back(violation);
        left = nullptr;
        right = nullptr;
    }
};

class TrafficDatabase {
private:
    Node* root; 

    Node* insert(Node* node, const string& carNumber, const string& violation) {
        if (node == nullptr) {
            return new Node(carNumber, violation);
        }

        if (carNumber < node->carNumber) {
            node->left = insert(node->left, carNumber, violation);
        }
        else if (carNumber > node->carNumber) {
            node->right = insert(node->right, carNumber, violation);
        }
        else {
            node->violations.push_back(violation);
        }
        return node;
    }

    void printAll(Node* node) {
        if (node == nullptr) return;

        printAll(node->left);
        cout << "Car Number: " << node->carNumber << "\nViolations: ";
        for (const string& violation : node->violations) {
            cout << violation << "; ";
        }
        cout << "\n";
        printAll(node->right);
    }

    Node* search(Node* node, const string& carNumber) {
        if (node == nullptr || node->carNumber == carNumber) {
            return node;
        }

        if (carNumber < node->carNumber) {
            return search(node->left, carNumber);
        }
        else {
            return search(node->right, carNumber);
        }
    }

    void printRange(Node* node, const string& low, const string& high) {
        if (node == nullptr) return;

        if (node->carNumber > low) {
            printRange(node->left, low, high);
        }

        if (node->carNumber >= low && node->carNumber <= high) {
            cout << "Car Number: " << node->carNumber << "\nViolations: ";
            for (const string& violation : node->violations) {
                cout << violation << "; ";
            }
            cout << "\n";
        }

        if (node->carNumber < high) {
            printRange(node->right, low, high);
        }
    }

public:
    TrafficDatabase() : root(nullptr) {}

    void addViolation(const string& carNumber, const string& violation) {
        root = insert(root, carNumber, violation);
    }

    void printAll() {
        printAll(root);
    }

    void printByCarNumber(const string& carNumber) {
        Node* node = search(root, carNumber);
        if (node == nullptr) {
            cout << "Car number " << carNumber << " not found.\n";
        }
        else {
            cout << "Car Number: " << node->carNumber << "\nViolations: ";
            for (const string& violation : node->violations) {
                cout << violation << "; ";
            }
            cout << "\n";
        }
    }

    void printByRange(const string& low, const string& high) {
        printRange(root, low, high);
    }
};

int main() {
    TrafficDatabase db;

    db.addViolation("AA1234BB", "Speeding");
    db.addViolation("AA1234BB", "Parking Violation");
    db.addViolation("CC5678DD", "Red Light Violation");
    db.addViolation("BB4321CC", "Speeding");

    cout << "Full Database:\n";
    db.printAll();

    cout << "\nData for car number AA1234BB:\n";
    db.printByCarNumber("AA1234BB");

    cout << "\nData for cars in range BB0000AA - CC9999ZZ:\n";
    db.printByRange("BB0000AA", "CC9999ZZ");
}
