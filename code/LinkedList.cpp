#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
#include <chrono>
#include <iomanip>

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
    double total_duration_ns = 0.0;
    double total_duration_ms = 0.0;

    for (int i = 0; i < ITERATIONS; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<Node*> skyline = skylineQuery(head);
        auto end = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        total_duration_ns += duration.count();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        total_duration_ms += duration.count();
    }

    // Hasil akhir satu kali komputasi untuk ditampilkan ke layar
    std::vector<Node*> finalSkyline = skylineQuery(head);

    std::cout << "Skyline Products (Baju Terbaik):\n";
    for (auto node : finalSkyline) {
        std::cout << "ID: " << node->id
                  << ", Label: " << node->label
                  << ", Harga: " << node->harga
                  << ", Nilai Ulasan: " << node->ulasan << "\n";
    }

    // Hitung rata-rata waktu
    double avg_duration_ns = total_duration_ns / ITERATIONS;
    double avg_duration_ms = avg_duration_ns / 1e6;
    double avg_duration_s  = avg_duration_ns / 1e9;

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "\nWaktu komputasi (rata-rata " << ITERATIONS << " iterasi): "
              << avg_duration_ms << " ms | "
              << avg_duration_s  << " s\n";
    // double duration_ms = avg_duration_ns / 1e6 * 1000;

    std::cout << "\nWaktu komputasi " << ITERATIONS << " iterasi): "
              << total_duration_ms  << " ms\n";

    freeList(head);
    return 0;
}