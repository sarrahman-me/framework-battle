# Tabel Perbandingan Hasil Pengujian POST dan GET

## 1. Hasil Pengujian POST

| **Kriteria**              | **ActixWeb (Rust)**  | **Express (JavaScript)** | **Komentar** |
|---------------------------|----------------------|--------------------------|--------------|
| **Iterasi Target**         | 500,000              | 500,000                  | -            |
| **Iterasi Selesai**        | 500,000              | 305,494                  | ActixWeb menyelesaikan seluruh iterasi target. |
| **Persentase Selesai**     | 100%                 | 61.1%                    | -            |
| **Permintaan Berhasil (201)** | 499,024              | 304,023                  | ActixWeb unggul dalam permintaan berhasil. |
| **Error Rate**             | 0.19%                | 0.48%                    | ActixWeb lebih andal dengan tingkat kesalahan lebih rendah. |
| **Durasi Total Pengujian** | 1m 30s               | 5m 1.2s                  | ActixWeb jauh lebih cepat. |
| **Rata-rata Waktu Respons** | 56.55 ms             | 487.23 ms                | ActixWeb ~8x lebih cepat dibandingkan Express. |
| **P95 Waktu Respons**      | 67.41 ms             | 1.11 s                   | ActixWeb unggul dalam latensi tinggi. |
| **P99 Waktu Respons**      | 78.2 ms              | 1.18 s                   | ActixWeb lebih baik dalam skenario ekstrem. |
| **Throughput**             | 5,549 req/s          | 1,014 req/s              | Throughput ActixWeb ~5.5x lebih tinggi. |

**Catatan**: Express gagal menyelesaikan target iterasi karena **“dropped iterations”** sebanyak 194,506 iterasi, yang menunjukkan keterbatasan dalam menangani beban tinggi.

---

## 2. Hasil Pengujian GET

### Light Load (50 VUs)

| **Skenario**             | **ActixWeb (Rust)**  | **Express (JavaScript)** | **Komentar** |
|--------------------------|----------------------|--------------------------|--------------|
| **Permintaan Berhasil (200)** | 2,745                | 1,348                    | ActixWeb memproses lebih banyak permintaan. |
| **Error Rate**            | 0.14%                | 39.32%                   | ActixWeb jauh lebih andal. |
| **Rata-rata Waktu Respons** | 1.23 s              | 3.76 s                   | ActixWeb lebih cepat. |
| **Throughput**            | 91 req/s             | 22 req/s                 | Throughput ActixWeb ~4x lebih tinggi. |

---

### High Load (100 VUs)

| **Skenario**             | **ActixWeb (Rust)**  | **Express (JavaScript)** | **Komentar** |
|--------------------------|----------------------|--------------------------|--------------|
| **Permintaan Berhasil (200)** | 4,512                | 1,026                    | ActixWeb memproses permintaan jauh lebih banyak. |
| **Error Rate**            | 0.12%                | 39.32%                   | ActixWeb jauh lebih andal. |
| **Rata-rata Waktu Respons** | 4.53 s              | 4.65 s                   | Waktu respons ActixWeb lebih baik meskipun bebannya tinggi. |
| **Throughput**            | 52.9 req/s           | 22.6 req/s               | ActixWeb menunjukkan performa throughput lebih tinggi. |

---

### Spike Load (10-500 VUs)

| **Skenario**             | **ActixWeb (Rust)**  | **Express (JavaScript)** | **Komentar** |
|--------------------------|----------------------|--------------------------|--------------|
| **Permintaan Berhasil (200)** | 1,018                | 200                      | ActixWeb memproses lebih banyak permintaan. |
| **Error Rate**            | 13.48%               | 39.32%                   | ActixWeb lebih andal meskipun beban melonjak. |
| **Rata-rata Waktu Respons** | 16.82 s             | 36.26 s                  | ActixWeb hampir 2x lebih cepat. |
| **Throughput**            | 27 req/s             | 1.3 req/s                | ActixWeb jauh lebih efisien dalam throughput. |

**Catatan**: ActixWeb secara konsisten menunjukkan performa yang lebih baik dengan throughput lebih tinggi, waktu respons lebih cepat, dan tingkat kesalahan yang jauh lebih rendah dibandingkan Express.

---

## Analisis dan Pemenang Berdasarkan Aturan

### Pengujian POST
- **Kecepatan Penyelesaian**: **Pemenang: ActixWeb**. Dengan waktu penyelesaian 1m 30s dibandingkan 5m 1.2s dari Express.
- **Keandalan**: **Pemenang: ActixWeb**. Dengan tingkat error hanya 0.19% dibandingkan 0.48% Express.
- **Throughput**: **Pemenang: ActixWeb**. Dengan 5,549 req/s dibandingkan 1,014 req/s milik Express.

**Kesimpulan**: ActixWeb menang telak dalam pengujian POST.

### Pengujian GET
- **Throughput**: **Pemenang: ActixWeb**. Dalam semua skenario (Light, High, Spike Load), throughput ActixWeb jauh lebih tinggi daripada Express.
- **Latensi dan Waktu Respons**: **Pemenang: ActixWeb**. Waktu respons rata-rata dan P95/P99 lebih rendah dibandingkan Express.
- **Keandalan**: **Pemenang: ActixWeb**. Dengan tingkat error jauh lebih rendah dibandingkan Express dalam semua skenario.

**Kesimpulan**: ActixWeb menang dengan keunggulan signifikan dalam pengujian GET.

---

## Kesimpulan Akhir

**ActixWeb adalah pemenang jelas untuk kedua pengujian (POST dan GET).**

- **Alasan**: ActixWeb menunjukkan kecepatan, keandalan, dan performa yang jauh lebih baik dibandingkan Express, terutama dalam menghadapi beban tinggi dan skenario lonjakan beban.
