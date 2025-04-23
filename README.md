# Skyline-Queries-02
Skyline Queries Problem Kelompok 2
---

## 📊 4. Penjelasan Penggunaan Hash Table dalam Algoritma Skyline Query

Pada kasus ini, setiap objek adalah sebuah entitas `Baju` dengan dua atribut utama:
- `harga` (semakin rendah semakin baik).
- `rating` (semakin tinggi semakin baik).

### 🎯 Aturan Dominasi:
Objek A dikatakan **mendominasi** objek B jika:
- `A.harga <= B.harga` **dan**
- `A.rating >= B.rating`, serta
- Setidaknya salah satu atribut **lebih baik secara ketat**

---

### 🔧 Fungsi Skyline Query dengan Hash Table

### Potongan Kode:
```cpp
unordered_map<int, Baju> hashSkyline;
```

`unordered_map` di sini bertindak sebagai **hash table** untuk menyimpan elemen yang menjadi **kandidat hasil skyline**.

### Proses Algoritma:
Untuk setiap objek `baju` dalam dataset:
1. **Periksa apakah `baju` didominasi** oleh objek lain dalam `hashSkyline`.
   - Jika ya, **abaikan** `baju`.
2. **Periksa apakah `baju` mendominasi** objek dalam `hashSkyline`.
   - Jika ya, **hapus** objek-objek yang didominasi.
3. Jika `baju` **tidak didominasi**, **tambahkan ke `hashSkyline`**.

Berikut merupakan sebuah diagram yang dapat menggambarkan proses algoritmanya:

![Diagram Hash Table Final](https://github.com/user-attachments/assets/ba2b85d0-4ec6-4caa-9e0d-a03b9044b89a)

Pada diagram tersebut, kita dapat melihat bahwa penggunaan hash table bekerja dengan cara mengiterasikan tiap data dan menyimpan data yang benar dalam sebuah hash table dan akan mengembalikan data dalam bentuk vector.

### Logika Kode Inti:
```cpp
if (!didominasi) {
    for (int id : toRemove) {
        hashSkyline.erase(id);
    }
    hashSkyline[baju.id] = baju;
}
```

Pada potongan kode inti tersebut, program akan mengecek apakah produk saat ini **tidak didominasi** oleh produk lain di hash table. Jika iya, maka produk ini akan dijadikan kandidat skyline dan akan 'mengusir' produk lain yang terdominasi oleh produk ini. Lalu program akan melakukan penambahan produk baru yang dianggap terbaik dan akan konstan selalu mengecek apakah hash table hanya berisi dengan produk-produk terbaik.

⏱️ Kompleksitas:
   - Pada kode ini, kompleksitas dalam notasi big O adalah O(N), dimana N adalah jumlah produk yang didominasi. Jadi, secara general, cukup efektif dan cepat.

Adapun output dari program tersebut setelah menganalisis dataset yang telah diberikan sebagai berikut: (menggunakan data 1000 baju)

![hash](https://github.com/user-attachments/assets/e1a9edd6-3481-4fa3-9ab1-8d61ceaf7432)

Output tersebut menunjukkan 9 produk baju yang tidak didominasi oleh produk lain dalam hal kombinasi harga dan rating. Artinya, produk-produk tersebut merupakan produk terbaik dalam dataset yang telah diberikan, berikut 2 contoh alasannya:
- Produk ID 964 (Harga 5, Rating 195) tidak didominasi oleh produk lain karena memiliki harga terendah.
- Produk ID 160 (Harga 104, Rating 283) tidak didominasi karena memiliki rating tertinggi.

### 📈 Pola yang Terlihat
Trade-off Harga vs Rating:

1. Semakin murah harga → rating cenderung lebih rendah.
   - Semakin mahal → rating cenderung lebih tinggi.

2. Pareto Frontier:
   - Hasil membentuk "frontier" optimal di grafik harga-rating.
   - Tidak mungkin menemukan produk di luar daftar ini yang lebih murah dengan rating lebih tinggi.

### 💡 Contoh Dominasi
Misal ada produk X (Harga 30, Rating 240):
   - Didominasi oleh ID 351 (Harga 23, Rating 240) karena lebih murah dengan rating sama.
   - Tidak mendominasi ID 947 (Harga 28, Rating 244) karena rating lebih rendah.

---

### ✅ Keuntungan Penggunaan Hash Table

| Fitur                              | Keuntungan Menggunakan `unordered_map` |
|-----------------------------------|----------------------------------------|
| 🔍 Akses Berdasarkan ID           | O(1) untuk pencarian dan penghapusan   |
| 🧹 Hapus Data yang Didominasi     | Cepat dan efisien                      |
| 🚫 Hindari Duplikasi              | ID sebagai key unik                   |
| ⚡ Kinerja Lebih Optimal           | Cocok untuk dataset besar             |

Keuntungan ini juga tercatat dalam Output ketika menggunakan set kode yang telah diberikan untuk mengukur seberapa lama jika sebuah program memakai hash table untuk mengeksekusi sebuah algoritma, berikut merupakan hasil dari pencatatan waktu menggunakan hash table:

![image](https://github.com/user-attachments/assets/6d0406aa-77a9-41ca-8c27-13f5a7d4318d)

Dari gambar output tersebut, dapat disimpulkan bahwa penggunaan hash table tergolong sangat cepat dan menggunakan waktu yang sangat minimum untuk menemukan data yang tida terdominasi.

---

### 📌 Kesimpulan

Penggunaan `unordered_map` sebagai hash table dalam algoritma Skyline Query:
- **Tepat** secara logika dan efisien.
- Meningkatkan performa pencarian, penambahan, dan penghapusan.
- Mempermudah manajemen hasil sementara skyline.

---
