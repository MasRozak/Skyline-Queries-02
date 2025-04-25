#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <cstdlib>
#include "../materials/timer.hpp"

using namespace std;
using namespace chrono;

const int MAX_PRODUCTS = 1000; // batas maksimal produk

struct Product {
    int id;
    string label;
    int attr1; // harga
    int attr2; // nilai ulasan
};

bool dominates(const Product &a, const Product &b) {
    return (a.attr1 <= b.attr1 && a.attr2 >= b.attr2) &&
           (a.attr1 < b.attr1 || a.attr2 > b.attr2);
}


int readCSV(const string &filename, Product products[]) {
    ifstream file(filename);
    string line;
    int count = 0;

    if (!file.is_open()) {
        cerr << "File tidak dapat dibuka!" << endl;
        exit(1);
    }

    getline(file, line); // skip header

    while (getline(file, line) && count < MAX_PRODUCTS) {
        stringstream ss(line);
        string item;

        getline(ss, item, ',');
        products[count].id = stoi(item);

        getline(ss, item, ',');
        products[count].label = item;

        getline(ss, item, ',');
        products[count].attr1 = stoi(item);

        getline(ss, item, ',');
        products[count].attr2 = stoi(item);

        count++;
    }

    return count;
}

int skylineQuery(Product products[], int productCount, Product skyline[]) {
    int skylineCount = 0;

    auto start = high_resolution_clock::now();

    for (int i = 0; i < productCount; ++i) {
        bool isDominated = false;
        for (int j = 0; j < productCount; ++j) {
            if (i != j && dominates(products[j], products[i])) {
                isDominated = true;
                break;
            }
        }
        if (!isDominated) {
            skyline[skylineCount++] = products[i];
        }
    }
    return skylineCount;
}

int main() {
    string filename = "../materials/ind_1000_2_product.csv";
    Product products[MAX_PRODUCTS];
    Product skyline[MAX_PRODUCTS];
    

    int productCount = readCSV(filename, products);
    auto start = high_resolution_clock::now();
    int skylineCount = skylineQuery(products, productCount, skyline);
    auto end = high_resolution_clock::now();

    cout << "Skyline Products (Baju Terbaik):\n";
    for (int i = 0; i < skylineCount; ++i) {
        cout << "ID: " << skyline[i].id
             << ", Label: " << skyline[i].label
             << ", Harga: " << skyline[i].attr1
             << ", Nilai Ulasan: " << skyline[i].attr2 << "\n";
    }

    cout << "\nWaktu komputasi: " <<  duration_cast<microseconds>(end - start).count() << " ms\n";

    return 0;
}
