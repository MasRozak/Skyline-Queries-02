#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <vector>
#include <string>
#include <chrono>
#include "../materials/timer.hpp"

using namespace std;
using namespace chrono;

struct Product {
    int id;
    string label;
    int harga;
    int rating;
};

bool dominates(const Product& a, const Product& b) {
    return (a.harga <= b.harga && a.rating >= b.rating) &&
           (a.harga < b.harga || a.rating > b.rating);
}

vector<Product> readCSV(const string& filename) {
    ifstream file(filename);
    string line;
    vector<Product> products;

    if (!file.is_open()) {
        cerr << "Gagal membuka file.\n";
        return products;
    }

    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, labelStr, hargaStr, ratingStr;

        if (!getline(ss, idStr, ',') ||
            !getline(ss, labelStr, ',') ||
            !getline(ss, hargaStr, ',') ||
            !getline(ss, ratingStr, ',')) {
            continue;
        }

        try {
            Product p;
            p.id = stoi(idStr);
            p.label = labelStr;
            p.harga = stoi(hargaStr);
            p.rating = stoi(ratingStr);
            products.push_back(p);
        } catch (...) {
            cerr << "Baris tidak valid: " << line << "\n";
        }
    }

    return products;
}

vector<Product> skylineQueryWithStack(const vector<Product>& products) {
    stack<Product> skylineStack;

    for (const auto& p : products) {
        stack<Product> tempStack;
        bool isDominated = false;

        while (!skylineStack.empty()) {
            Product top = skylineStack.top();
            skylineStack.pop();

            if (dominates(top, p)) {
                isDominated = true;
                tempStack.push(top);
                break;
            } else if (!dominates(p, top)) {
                tempStack.push(top);
            }
        }

        if (!isDominated) {
            tempStack.push(p);
        }

        while (!tempStack.empty()) {
            skylineStack.push(tempStack.top());
            tempStack.pop();
        }
    }

    vector<Product> result;
    while (!skylineStack.empty()) {
        result.push_back(skylineStack.top());
        skylineStack.pop();
    }
    return result;
}

int main() {
    string filename = "../materials/ind_1000_2_product.csv";
    vector<Product> products = readCSV(filename);

    auto start = chrono::high_resolution_clock::now();

    vector<Product> skyline = skylineQueryWithStack(products);

    auto end = chrono::high_resolution_clock::now();

    cout << "Skyline Result (via Stack):\n";
    for (const auto& p : skyline) {
        cout << "ID: " << p.id << ", Label: " << p.label
                  << ", Harga: " << p.harga << ", Rating: " << p.rating << "\n";
    }

    cout << "\nWaktu komputasi: " <<  duration_cast<microseconds>(end - start).count() << " ms\n";

    return 0;
}
