#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <queue>
#include <chrono>
#include "../materials/timer.hpp"

using namespace std;
using namespace chrono;
struct product{
    int id;
    string label;
    int atr_1, atr_2;
};

vector<product> read_csv(const string csv_file){
    vector<product> data;
    string csv_line;
    ifstream file(csv_file);
    if(!file.is_open()){
        cerr << "Error: gagal buka file " << csv_file << "\n";
        return data;
    }

    getline(file, csv_line);

    while(getline(file, csv_line)){
        stringstream ss(csv_line);
        string field;
        product p;

        // kolom 1: id
        if (!getline(ss, field, ',')) continue;
        p.id = std::stoi(field);

        // kolom 2: label
        if (!getline(ss, field, ',')) continue;
        p.label = field;

        // kolom 3: attr_1
        if (!getline(ss, field, ',')) continue;
        p.atr_1 = std::stoi(field);

        // kolom 4: attr_2
        if (!getline(ss, field, ',')) continue;
        p.atr_2= std::stoi(field);

        data.push_back(p);
    }
    file.close();
    return data;
}

void print_table(const vector<product>& products) {
    // header
    cout << left
         << setw(4)  << "ID"
         << setw(15) << "Label"
         << setw(8)  << "Harga"
         << setw(8)  << "Ulasan"
         << "\n";
    // garis pemisah
    cout << string(4 + 15 + 8 + 8, '-') << "\n";

    // isi tabel
    for (const auto& p : products) {
        cout << left
             << setw(4)  << p.id
             << setw(15) << p.label
             << setw(8)  << p.atr_1   // pastikan pakai attr_1, bukan atr_1
             << setw(8)  << p.atr_2   // sama di sini, attr_2
             << "\n";
    }
}



bool dominates(const product& a, const product& b) {
    return (a.atr_1 <= b.atr_1 && a.atr_2 >= b.atr_2)
        && (a.atr_1 <  b.atr_1 || a.atr_2 >  b.atr_2);
}

vector<product> skyline_with_queue(const vector<product>& items) {
    queue<product> q;
    for (auto& s : items) {
        bool isDominated = false;
        int n = q.size();

        // pop–compare–push cycle
        for (int i = 0; i < n; ++i) {
            product cur = q.front(); q.pop();

            if (dominates(cur, s)) {
                // ada yang ngalahin s → skip s, keep cur
                isDominated = true;
                q.push(cur);
            }
            else if (dominates(s, cur)) {
                // s ngalahin cur → drop cur (tidak push)
                continue;
            }
            else {
                // keduanya ga saling ngalahin → keep cur
                q.push(cur);
            }
        }

        if (!isDominated) {
            // s belum terkalahkan → push
            q.push(s);
        }
    }

    // ambil hasil skyline dari queue
    vector<product> sky;
    while (!q.empty()) {
        sky.push_back(q.front());
        q.pop();
    }
    return sky;
}

int main() {
    auto products = read_csv("../materials/ind_1000_2_product.csv");
    cout << "Total baris: " << products.size() << "\n";

    auto t0 = chrono::high_resolution_clock::now();
    auto sky = skyline_with_queue(products);
    auto t1 = chrono::high_resolution_clock::now();

    cout << "=== Hasil Skyline ===\n";
    print_table(sky);
    cout << "\nWaktu komputasi: " <<  duration_cast<microseconds>(t1 - t0).count() << " ms\n";



    return 0;
}
