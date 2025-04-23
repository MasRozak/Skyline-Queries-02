#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <vector>
#include <string>
#include <chrono>

struct Product {
    int id;
    std::string label;
    int harga;
    int rating;
};

bool dominates(const Product& a, const Product& b) {
    return (a.harga <= b.harga && a.rating >= b.rating) &&
           (a.harga < b.harga || a.rating > b.rating);
}

std::vector<Product> readCSV(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    std::vector<Product> products;

    if (!file.is_open()) {
        std::cerr << "Gagal membuka file.\n";
        return products;
    }

    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, labelStr, hargaStr, ratingStr;

        if (!std::getline(ss, idStr, ',') ||
            !std::getline(ss, labelStr, ',') ||
            !std::getline(ss, hargaStr, ',') ||
            !std::getline(ss, ratingStr, ',')) {
            continue;
        }

        try {
            Product p;
            p.id = std::stoi(idStr);
            p.label = labelStr;
            p.harga = std::stoi(hargaStr);
            p.rating = std::stoi(ratingStr);
            products.push_back(p);
        } catch (...) {
            std::cerr << "Baris tidak valid: " << line << "\n";
        }
    }

    return products;
}

std::vector<Product> skylineQueryWithStack(const std::vector<Product>& products) {
    std::stack<Product> skylineStack;

    for (const auto& p : products) {
        std::stack<Product> tempStack;
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

    std::vector<Product> result;
    while (!skylineStack.empty()) {
        result.push_back(skylineStack.top());
        skylineStack.pop();
    }
    return result;
}

int main() {
    std::string filename = "ind_1000_2_product.csv";
    std::vector<Product> products = readCSV(filename);

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<Product> skyline = skylineQueryWithStack(products);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Skyline Result (via Stack):\n";
    for (const auto& p : skyline) {
        std::cout << "ID: " << p.id << ", Label: " << p.label
                  << ", Harga: " << p.harga << ", Rating: " << p.rating << "\n";
    }

    std::cout << "\nWaktu Komputasi: " << duration.count() << " detik\n";

    return 0;
}
