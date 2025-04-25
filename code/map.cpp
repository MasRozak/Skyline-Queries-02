#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <chrono>
#include <vector>
#include <string>

using namespace std;
using namespace chrono;

// Struct untuk menyimpan data produk
struct Product {
    string name;
    float price;   // attr1
    float rating;  // attr2
};

// Fungsi untuk mengecek apakah produk a mendominasi produk b
bool dominates(const Product& a, const Product& b) {
    return (a.price <= b.price && a.rating >= b.rating) &&
           (a.price < b.price || a.rating > b.rating);
}

// Fungsi untuk membaca CSV dan mengembalikan map produk
map<int, Product> readCSV(const string& filename) {
    map<int, Product> products;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Gagal membuka file CSV.\n";
        return products;
    }

    string line;
    getline(file, line); // Lewati header

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        int id;
        string name;
        float attr1, attr2;

        getline(ss, token, ','); id = stoi(token);
        getline(ss, name, ',');
        getline(ss, token, ','); attr1 = stof(token);
        getline(ss, token, ','); attr2 = stof(token);

        Product p;
        p.name = name;
        p.price = attr1;
        p.rating = attr2;

        products[id] = p;
    }

    file.close();
    return products;
}

// Fungsi untuk menghitung skyline query
map<int, Product> computeSkyline(const map<int, Product>& products) {
    map<int, Product> skyline;

    for (map<int, Product>::const_iterator it = products.begin(); it != products.end(); ++it) {
        int id = it->first;
        const Product& prod = it->second;

        bool isDominated = false;

        for (map<int, Product>::const_iterator sit = skyline.begin(); sit != skyline.end(); ++sit) {
            if (dominates(sit->second, prod)) {
                isDominated = true;
                break;
            }
        }

        if (!isDominated) {
            vector<int> toRemove;
            for (map<int, Product>::const_iterator sit = skyline.begin(); sit != skyline.end(); ++sit) {
                if (dominates(prod, sit->second)) {
                    toRemove.push_back(sit->first);
                }
            }

            for (size_t i = 0; i < toRemove.size(); ++i) {
                skyline.erase(toRemove[i]);
            }

            skyline[id] = prod;
        }
    }

    return skyline;
}

int main() {
    string filename = "../materials/ind_1000_2_product.csv";
    map<int, Product> products = readCSV(filename);
    auto start = std::chrono::high_resolution_clock::now();
    map<int, Product> skyline = computeSkyline(products);
    auto end = std::chrono::high_resolution_clock::now();


    // Tampilkan hasil
    cout << "Produk-produk hasil skyline query:\n";
    for (map<int, Product>::iterator it = skyline.begin(); it != skyline.end(); ++it) {
        cout << "ID: " << it->first
             << ", Nama: " << it->second.name
             << ", Harga: " << it->second.price
             << ", Rating: " << it->second.rating << endl;
    }

    std::cout << "\nWaktu komputasi Map: " <<  duration_cast<microseconds>(end - start).count() << " us\n";

    return 0;
}
