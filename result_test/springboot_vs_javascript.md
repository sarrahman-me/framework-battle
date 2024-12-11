# Hasil Pengujian Express.js vs Spring Boot

Berikut adalah hasil perbandingan kinerja antara **Express.js** dan **Spring Boot** dalam pengujian `POST` dan `GET`.

---

## Hasil Pengujian POST

### Ringkasan Hasil
| **Metrik**                | **Express.js**         | **Spring Boot**         | **Komentar**                                                                 |
|---------------------------|------------------------|-------------------------|-----------------------------------------------------------------------------|
| **Total Iterasi**          | 250,000                | 250,000                 | Kedua sistem berhasil menyelesaikan iterasi yang sama.                        |
| **Permintaan Berhasil (%)**| 99.93% (249,836/250,000) | 99.94% (249,853/250,000) | Keduanya hampir sempurna; Spring Boot unggul dengan selisih kecil.            |
| **Waktu Respons Rata-rata**| 185.97 ms              | 137.71 ms               | Spring Boot memiliki waktu respons lebih cepat.                               |
| **P95 (latensi 95%)**      | 419.2 ms               | 433.62 ms               | Express.js unggul sedikit dalam latensi tinggi.                               |
| **P99 (latensi 99%)**      | 437.63 ms              | 552.34 ms               | Express.js menang dalam latensi ekstrem.                                      |
| **Permintaan Gagal (%)**  | 0.06% (164/250,000)    | 0.05% (147/250,000)     | Tingkat kegagalan lebih rendah pada Spring Boot.                              |
| **Throughput**             | 1,341 permintaan/s     | 1,796 permintaan/s      | Spring Boot menunjukkan throughput lebih tinggi.                             |
| **Durasi Tes Total**       | 3 menit 6 detik        | 2 menit 19 detik        | Spring Boot selesai lebih cepat.                                             |

### Kesimpulan Pengujian POST
- **Spring Boot** unggul dalam waktu respons rata-rata, throughput, dan durasi tes total.
- **Express.js** lebih baik dalam latensi tinggi (P95 dan P99).
- **Pemenang untuk POST**: **Spring Boot**

---

## Hasil Pengujian GET

### Ringkasan Hasil
| **Metrik**                | **Express.js**         | **Spring Boot**         | **Komentar**                                                                 |
|---------------------------|------------------------|-------------------------|-----------------------------------------------------------------------------|
| **Total Permintaan GET**  | 3,723                  | 2,129                   | Express.js memproses lebih banyak permintaan.                                |
| **Permintaan Berhasil (%)**| 88.93% (3,311/3,723)   | 65.10% (1,386/2,129)     | Express.js jauh lebih andal dalam menangani GET.                             |
| **Waktu Respons Rata-rata**| 5.22 detik             | 11.6 detik              | Express.js memiliki waktu respons rata-rata lebih cepat.                     |
| **P95 (latensi 95%)**      | 11.78 detik            | 38.33 detik             | Express.js unggul dalam latensi tinggi.                                      |
| **P99 (latensi 99%)**      | 60 detik               | 53.73 detik             | Spring Boot sedikit lebih baik dalam kasus ekstrem.                          |
| **Throughput**             | 20 permintaan/s        | 11 permintaan/s         | Express.js memiliki throughput hampir dua kali lipat lebih tinggi.           |
| **Permintaan Gagal (%)**  | 11.06% (412/3,723)     | 34.89% (743/2,129)      | Express.js jauh lebih andal dengan tingkat kegagalan yang lebih rendah.      |
| **Durasi Tes Total**       | 3 menit 3 detik        | 3 menit 11 detik        | Durasi pengujian hampir sama.                                                |

### Kesimpulan Pengujian GET
- **Express.js** unggul dalam hampir semua metrik, termasuk jumlah permintaan, waktu respons, dan tingkat kegagalan.
- **Pemenang untuk GET**: **Express.js**

---

## Ringkasan Keseluruhan

| **Pengujian** | **Pemenang**    | **Alasan**                                                              |
|---------------|-----------------|-------------------------------------------------------------------------|
| **POST**      | **Spring Boot** | Lebih cepat dalam waktu rata-rata, throughput lebih tinggi, dan tingkat kegagalan lebih rendah. |
| **GET**       | **Express.js**  | Memproses lebih banyak permintaan, lebih cepat secara keseluruhan, dan lebih andal. |

---

## Tabel Visualisasi

| **Metrik**               | **POST Express.js** | **POST Spring Boot** | **GET Express.js** | **GET Spring Boot** |
|--------------------------|---------------------|----------------------|--------------------|---------------------|
| **Jumlah Iterasi**        | 250,000             | 250,000              | 3,723              | 2,129               |
| **Berhasil (%)**          | 99.93%              | 99.94%               | 88.93%             | 65.10%              |
| **Gagal (%)**             | 0.06%               | 0.05%                | 11.06%             | 34.89%              |
| **Waktu Respons (avg)**   | 185.97 ms           | 137.71 ms            | 5.22 detik         | 11.6 detik          |
| **Throughput**            | 1,341 req/s         | 1,796 req/s          | 20 req/s           | 11 req/s            |

---

## Kesimpulan Akhir
- **POST**: **Spring Boot** lebih baik untuk pengujian POST karena kecepatan dan throughput yang lebih tinggi.
- **GET**: **Express.js** unggul dalam pengujian GET, dengan performa yang lebih cepat dan stabil.

**Pemenang Utama**: Jika kinerja GET lebih penting dalam sistem Anda, **Express.js** adalah pilihan terbaik. Namun, jika penanganan POST lebih krusial, maka **Spring Boot** lebih disarankan.
