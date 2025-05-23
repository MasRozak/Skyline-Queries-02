#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
#include <chrono>
#include <iomanip>
#include "../materials/timer.hpp"


using namespace std;
using namespace chrono;
struct Node {
    int id;
    std::string label;
    int harga;
    int ulasan;
    Node* next;
};

Node* insert(Node* head, int id, const std::string& label, int harga, int ulasan) {
    Node* newNode = new Node{id, label, harga, ulasan, nullptr};
    if (!head) return newNode;

    Node* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = newNode;
    return head;
}

bool dominates(Node* a, Node* b) {
    return (a->harga <= b->harga && a->ulasan >= b->ulasan) &&
           (a->harga < b->harga || a->ulasan > b->ulasan);
}

std::vector<Node*> skylineQuery(Node* head) {
    std::vector<Node*> skyline;
    for (Node* current = head; current != nullptr; current = current->next) {
        bool dominated = false;
        for (auto& s : skyline) {
            if (dominates(s, current)) {
                dominated = true;
                break;
            }
        }
        if (!dominated) {
            skyline.erase(
                std::remove_if(skyline.begin(), skyline.end(),
                               [&](Node* s) { return dominates(current, s); }),
                skyline.end());
            skyline.push_back(current);
        }
    }
    return skyline;
}

Node* readCSV(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    Node* head = nullptr;
    bool skipHeader = true;

    while (std::getline(file, line)) {
        if (skipHeader) {
            skipHeader = false;
            continue;
        }

        std::stringstream ss(line);
        std::string idStr, labelStr, hargaStr, ulasanStr;

        if (!std::getline(ss, idStr, ',') ||
            !std::getline(ss, labelStr, ',') ||
            !std::getline(ss, hargaStr, ',') ||
            !std::getline(ss, ulasanStr, ',')) {
            std::cerr << "Baris tidak lengkap, dilewati: " << line << "\n";
            continue;
        }

        try {
            int id = std::stoi(idStr);
            int harga = std::stoi(hargaStr);
            int ulasan = std::stoi(ulasanStr);
            head = insert(head, id, labelStr, harga, ulasan);
        } catch (const std::exception& e) {
            std::cerr << "Gagal parse baris: " << line << " - " << e.what() << "\n";
        }
    }
    return head;
}

void freeList(Node* head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Node* head = readCSV("../materials/ind_1000_2_product.csv");

    const int ITERATIONS = 1000;
    double total_duration_ms = 0.0;

        auto start = std::chrono::high_resolution_clock::now();
        std::vector<Node*> skyline = skylineQuery(head);
        auto end = std::chrono::high_resolution_clock::now();
    // Hasil akhir satu kali komputasi untuk ditampilkan ke layar
    std::vector<Node*> finalSkyline = skylineQuery(head);

    std::cout << "Skyline Products (Baju Terbaik):\n";
    for (auto node : finalSkyline) {
        std::cout << "ID: " << node->id
                  << ", Label: " << node->label
                  << ", Harga: " << node->harga
                  << ", Nilai Ulasan: " << node->ulasan << "\n";
    }

    std::cout << "\nWaktu komputasi Linked List: " <<  duration_cast<microseconds>(end - start).count() << " us\n";

    freeList(head);
    return 0;
}
