#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <string>

struct Node {
    int id;
    int attr1;
    int attr2;
    Node* next;
};

Node* insert(Node* head, int id, int attr1, int attr2) {
    Node* newNode = new Node{id, attr1, attr2, nullptr};
    if (!head) return newNode;

    Node* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = newNode;
    return head;
}

bool dominates(Node* a, Node* b) {
    return (a->attr1 <= b->attr1 && a->attr2 <= b->attr2) &&
           (a->attr1 < b->attr1 || a->attr2 < b->attr2);
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
        std::string idStr, labelStr, attr1Str, attr2Str;

        // Sesuai urutan: id, label, attr1, attr2
        if (!std::getline(ss, idStr, ',') ||
            !std::getline(ss, labelStr, ',') ||
            !std::getline(ss, attr1Str, ',') ||
            !std::getline(ss, attr2Str, ',')) {
            std::cerr << "Baris tidak lengkap, dilewati: " << line << "\n";
            continue;
        }

        try {
            int id = std::stoi(idStr);
            int attr1 = std::stoi(attr1Str);
            int attr2 = std::stoi(attr2Str);
            head = insert(head, id, attr1, attr2);
        } catch (const std::exception& e) {
            std::cerr << "Gagal parse baris: " << line << " - " << e.what() << "\n";
        }
    }
    return head;
}


int main() {
    Node* head = readCSV("ind_1000_2_product.csv");

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<Node*> skyline = skylineQuery(head);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Skyline Items:\n";
    for (auto node : skyline) {
        std::cout << "ID: " << node->id << ", Attr1: " << node->attr1
                  << ", Attr2: " << node->attr2 << "\n";
    }

    std::cout << "\nWaktu Komputasi: " << duration.count() << " detik\n";
    return 0;
}
