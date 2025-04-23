# Skyline-Queries-02
Skyline Queries Problem Kelompok 2
---
## 📘 1. Penggunaan Array dalam Algoritma Skyline Query

Pada kasus ini kita ditugaskan untuk menemukan produk-produk terbaik (baju) dari dataset CSV berdasarkan:
- Harga (lebih murah lebih baik)
- Nilai Ulasan (semakin tinggi semakin baik)
Produk termasuk Skyline jika tidak ada produk lain yang lebih murah DAN memiliki ulasan lebih tinggi.

### Aturan Dominasi dalam Skyline Query
Sebuah produk A mendominasi produk B jika dan hanya jika:
Harga A lebih murah atau sama dengan harga B, dan
Nilai ulasan A lebih tinggi atau sama dengan nilai ulasan B, dan
Ada minimal satu atribut di mana A lebih baik dari B

### Apa Itu Array?
Array adalah struktur data yang digunakan untuk menyimpan sekumpulan elemen dengan tipe data yang sama dalam satu blok memori, dan diakses menggunakan indeks.





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

### 📑 Apa itu Hash Table ❓

**Hash table** merupakan struktur data yang secara asosiatif menyimpan data. Dalam hal ini, data disimpan dalam format array, di mana setiap nilai data memiliki nilai indeks uniknya sendiri. Akses data akan menjadi sangat cepat jika Anda mengetahui indeks dari data yang diinginkan. 

Dengan demikian, hash table menjadi struktur data di mana operasi penyisipan dan pencarian data terjadi sangat cepat terlepas dari ukuran data tersebut. Hash table menggunakan array sebagai media penyimpanan dan tekniknya untuk menghasilkan indeks suatu elemen yang dimasukkan atau ditempatkan.

Untuk membuat hash table, sepotong memori perlu diblokir dengan cara yang sama seperti saat membuat array. Anda perlu membuat indeks yang didasarkan pada kunci dengan menggunakan fungsi hash karena indeks yang dihasilkan harus sesuai dengan potongan memori. 

Ada dua pemeriksaan yang dibutuhkan saat menempatkan data baru pada hash table, yaitu nilai hash dari kunci dan bagaimana nilainya dibandingkan dengan objek lain. Pemeriksaan ini diperlukan saat membuatnya karena saat data dimasukkan, kunci akan di-hash dan di-mask agar diubah menjadi larik atau indeks yang efisien. 

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

Dari gambar output tersebut, dapat disimpulkan bahwa penggunaan hash table tergolong sangat cepat dan menggunakan waktu yang sangat minimum untuk menemukan data yang tidak terdominasi.

---

### 📌 Kesimpulan

Jadi, penggunaan hash table dalam algoritma Skyline Query dapat disimpulkan keuntungannya menjadi berikut:
- Tepat secara logika dan efisien.
- Meningkatkan performa pencarian, penambahan, dan penghapusan.
- Mempermudah manajemen hasil sementara skyline.

---

# Analisis Performa Struktur Data untuk Skyline Query

Dalam implementasi algoritma Skyline Query, enam struktur data yang digunakan untuk menyimpan dan memproses data adalah:

- `Array`
- `Stack`
- `Queue`
- `Linked List`
- `Map` (`std::map`)
- `Hash Table` (`std::unordered_map`)

Setelah melakukan pengujian, ditemukan bahwa **Hash Table (unordered_map)** adalah yang tercepat, sedangkan **Map (std::map)** adalah yang paling lambat.

---

## 🔍 Penjelasan Performa

### 1. Hash Table (`std::unordered_map`) ✅
- **Kompleksitas rata-rata:** O(1) untuk pencarian, penyisipan, dan penghapusan.
- **Mengapa cepat?**
  - Menggunakan **hashing** yang mengakses elemen langsung melalui indeks hash.
  - Cocok untuk pemeriksaan dan penghapusan elemen yang didominasi tanpa traversal sekuensial.
- **Kelemahan:** Tidak menjaga urutan elemen.

### 2. Map (`std::map`) ❌
- **Kompleksitas:** O(log n) karena berbasis **binary search tree** (biasanya Red-Black Tree).
- **Mengapa lambat?**
  - Untuk setiap operasi pencarian dan penyisipan, perlu traversal tree.
  - Meskipun elemen terurut, performa tidak cocok untuk kasus-kasus yang mengandalkan pencarian cepat.

### 3. Array
- **Kompleksitas:** O(n²) untuk skyline query karena perlu perbandingan berpasangan.
- **Mengapa lumayan?**
  - Akses langsung cepat (O(1)), tetapi tidak efisien untuk operasi manipulasi (penyisipan atau penghapusan di tengah).

### 4. Stack / Queue
- **Kompleksitas:** O(n²) juga saat membandingkan antar elemen.
- **Karakteristik:**
  - Stack: LIFO – tidak cocok untuk pemeriksaan dominasi acak.
  - Queue: FIFO – sama, tidak efisien untuk pencarian acak.

### 5. Linked List
- **Kompleksitas:** O(n²) karena traversal pointer.
- **Mengapa kalah cepat?**
  - Tidak mendukung akses langsung.
  - Semua perbandingan dan penghapusan perlu traversal manual.

---

## 🚀 Kesimpulan

| Struktur Data     | Kecepatan  | Kompleksitas | Catatan                                      |
|-------------------|------------|--------------|----------------------------------------------|
| Hash Table        | ⭐⭐⭐⭐⭐     | O(1)         | Tercepat, ideal untuk lookup & update cepat  |
| Array             | ⭐⭐⭐       | O(n²)        | Sederhana, tapi boros saat data besar        |
| Stack / Queue     | ⭐⭐        | O(n²)        | Tidak efisien untuk skyline                  |
| Linked List       | ⭐⭐        | O(n²)        | Sulit untuk penghapusan & traversal acak     |
| Map               | ⭐         | O(log n)     | Terlambat karena traversal tree              |

Gunakan `Hash Table` untuk performa maksimal dalam kasus seperti Skyline Query yang melibatkan banyak pemeriksaan dominasi antar elemen.
