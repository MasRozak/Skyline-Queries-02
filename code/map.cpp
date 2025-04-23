#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "../materials/timer.hpp"


using namespace std;

typedef vector<int> Point;
typedef pair<string, Point> LabeledPoint;

// Cek apakah p1 didominasi oleh p2
bool isDominated(const Point& p1, const Point& p2) {
        // A mendominasi B jika:
        // A.harga <= B.harga AND A.rating >= B.rating AND (A.harga < B.harga OR A.rating > B.rating)

    bool harga_better_or_equal = p2[0] <= p1[0]; // harga lebih murah
    bool rating_better_or_equal = p2[1] >= p1[1]; // rating lebih tinggi
    bool strictly_better = (p2[0] < p1[0]) || (p2[1] > p1[1]);

    return harga_better_or_equal && rating_better_or_equal && strictly_better;
}


// Hitung skyline lokal dari subset
vector<LabeledPoint> computeLocalSkyline(const vector<LabeledPoint>& points) {
    vector<LabeledPoint> skyline;
    for (const auto& p : points) {
        bool dominated = false;
        for (const auto& q : points) {
            if (p != q && isDominated(p.second, q.second)) {
                dominated = true;
                break;
            }
        }
        if (!dominated) skyline.push_back(p);
    }
    return skyline;
}

// Gabungkan semua local skyline, dan hitung skyline global
vector<LabeledPoint> computeGlobalSkyline(const vector<vector<LabeledPoint>>& localSkylines) {
    vector<LabeledPoint> merged;
    for (const auto& skyline : localSkylines) {
        merged.insert(merged.end(), skyline.begin(), skyline.end());
    }
    return computeLocalSkyline(merged);
}

// Membaca CSV, mengambil kolom label, attr_1, attr_2
vector<LabeledPoint> readCSV(const string& filename) {
    vector<LabeledPoint> points;
    ifstream file(filename);
    string line;
    bool firstLine = true;

    while (getline(file, line)) {
        if (firstLine) { firstLine = false; continue; } // skip header

        stringstream ss(line);
        string id, label, val1, val2;

        getline(ss, id, ',');
        getline(ss, label, ',');
        getline(ss, val1, ',');
        getline(ss, val2, ',');

        Point attrs = {stoi(val1), stoi(val2)};
        points.push_back({label, attrs});
    }

    file.close();
    return points;
}

int main() {
    string filename = "../materials/ind_1000_2_product.csv";
    vector<LabeledPoint> data = readCSV(filename);

    // Simulasi Map Phase: bagi 2 blok
    size_t half = data.size() / 2;
    Timer Timer;
    vector<LabeledPoint> block1(data.begin(), data.begin() + half);
    vector<LabeledPoint> block2(data.begin() + half, data.end());

    vector<LabeledPoint> skyline1 = computeLocalSkyline(block1);
    vector<LabeledPoint> skyline2 = computeLocalSkyline(block2);

    vector<vector<LabeledPoint>> localSkylines = {skyline1, skyline2};
    vector<LabeledPoint> result = computeGlobalSkyline(localSkylines);
    
    
    double durasi = Timer.stop();
    cout << "Skyline Points (label, attr_1, attr_2):" << endl;
    for (const auto& item : result) {
        string label = item.first;
        Point attrs = item.second;
        cout << label << ": " << attrs[0] << ", " << attrs[1] << endl;
    }
    cout << "Waktu eksekusi: " << durasi << " detik" << endl;
    return 0;
}
