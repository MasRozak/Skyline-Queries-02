#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <string>
#include <bits/stdc++.h>
#include "../materials/timer.hpp"

using namespace std;
using namespace chrono;

struct Baju {
    int id;
    int harga;
    int rating;
};

bool mendominasi(const Baju &a, const Baju &b) {
    return (a.harga <= b.harga && a.rating >= b.rating) &&
           (a.harga < b.harga || a.rating > b.rating);
}

vector<Baju> skylineQueryHashTable(const vector<Baju>& data) {
    unordered_map<int, Baju> hashSkyline;

    for (const Baju& baju : data) {
        bool didominasi = false;
        vector<int> toRemove;

        for (const auto& pair : hashSkyline) {
            const Baju& kandidat = pair.second;

            if (mendominasi(kandidat, baju)) {
                didominasi = true;
                break;
            } else if (mendominasi(baju, kandidat)) {
                toRemove.push_back(kandidat.id);
            }
        }

        if (!didominasi) {
            for (int id : toRemove) {
                hashSkyline.erase(id);
            }
            hashSkyline[baju.id] = baju;
        }
    }

    vector<Baju> hasil;
    for (const auto& pair : hashSkyline) {
        hasil.push_back(pair.second);
    }
    return hasil;
}

int main() {
    vector<Baju> dataset;
    ifstream file("../materials/ind_1000_2_product.csv");
    string line;

    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string id_str, label, harga_str, rating_str;
    
        getline(ss, id_str, ',');
        getline(ss, label, ',');
        getline(ss, harga_str, ',');
        getline(ss, rating_str, ',');
    
        try {
            int id = stoi(id_str);
            int harga = stoi(harga_str);
            int rating = stoi(rating_str);
            dataset.push_back({id, harga, rating});
        } catch (const exception& e) {
            cerr << "Error parsing line: " << line << "\n";
        }
    }
    
    file.close();

    auto start = high_resolution_clock::now();
    vector<Baju> hasilSkyline = skylineQueryHashTable(dataset);
    auto end = high_resolution_clock::now();

    duration<double> durasi = end - start;

    cout << "Hasil Skyline (ID, Harga, Rating):\n";
    for (const auto& b : hasilSkyline) {
        cout << "ID: " << b.id << ", Harga: " << b.harga << ", Rating: " << b.rating << '\n';
    }
    
    cout << "Waktu eksekusi Hash Table: " << durasi.count() * 1000 << " ms\n";

    return 0;
}
