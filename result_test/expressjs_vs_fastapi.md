![express vs fastapi](https://ik.imagekit.io/sarrahmanme/expressvsfastapi.png?updatedAt=1733816140808)
# Analisis Kinerja ExpressJS vs FastAPI

Berikut adalah analisis kinerja kedua framework berdasarkan pengujian `POST` dan `GET`.

## 1. Pengujian POST
**Parameter Analisis:**
- **Jumlah Permintaan Berhasil:** Kedua framework mencapai 100,000 permintaan dengan status 201 (100% sukses).
- **Rata-rata Waktu Respons (avg):**
  - Express.js: 29.27 ms
  - FastAPI: 198.69 ms
- **P99 Waktu Respons:**
  - Express.js: 53.48 ms
  - FastAPI: 450.7 ms
- **Throughput (request per detik):**
  - Express.js: 3409.36/s
  - FastAPI: 503.07/s
- **Durasi Total untuk 100,000 Iterasi:**
  - Express.js: 29.3 s
  - FastAPI: 3m18.8 s (198.8 s)

## 2. Pengujian GET
**Parameter Analisis:**
- **Jumlah Permintaan Berhasil:**
  - Express.js: 9465
  - FastAPI: 2126
- **Rata-rata Waktu Respons (avg):**
  - Express.js: 1.07 s
  - FastAPI: 4.72 s
- **P99 Waktu Respons:**
  - Express.js: 5.15 s
  - FastAPI: 11.62 s
- **Throughput (request per detik):**
  - Express.js: 52.52/s
  - FastAPI: 11.70/s
- **Data yang Diterima (GET):**
  - Express.js: 61 GB
  - FastAPI: 14 GB

---

## Kesimpulan Perbandingan

| Framework   | POST Waktu Respons (avg) | POST P99 Respons | GET Waktu Respons (avg) | GET P99 Respons | Throughput (POST) | Throughput (GET) | GET Data Diterima |
|-------------|--------------------------|------------------|-------------------------|-----------------|-------------------|------------------|-------------------|
| Express.js  | 29.27 ms                | 53.48 ms         | 1.07 s                 | 5.15 s          | 3409.36/s         | 52.52/s          | 61 GB             |
| FastAPI     | 198.69 ms               | 450.7 ms         | 4.72 s                 | 11.62 s         | 503.07/s          | 11.70/s          | 14 GB             |

### Faktor Penentu Pemenang
1. **Kecepatan Penyelesaian (POST dan GET):** 
   - Express.js lebih unggul secara signifikan dalam waktu respons rata-rata dan P99.
2. **Keandalan:** 
   - Kedua framework mencatat 0% kesalahan, sehingga keduanya setara dalam keandalan.
3. **Throughput:** 
   - Express.js unggul di POST (3409.36/s vs 503.07/s) dan GET (52.52/s vs 11.70/s).

**Pemenang:** Express.js

---

## Analisis Terperinci

### 1. Pengujian POST
| Framework   | Rata-rata Waktu Respons (ms) | P95 Waktu Respons (ms) | P99 Waktu Respons (ms) | Throughput (req/s) | Keandalan |
|-------------|------------------------------|-------------------------|-------------------------|--------------------|-----------|
| Express.js  | 29.27                       | 50.86                  | 53.48                  | 3409.36            | 100%      |
| FastAPI     | 198.69                      | 420.94                 | 450.7                  | 503.07             | 100%      |

### 2. Pengujian GET
| Beban      | Framework   | Throughput (req/s) | Rata-rata Waktu Respons (ms) | P95 Waktu Respons (ms) | P99 Waktu Respons (ms) |
|------------|-------------|--------------------|------------------------------|-------------------------|-------------------------|
| Light Load | Express.js  | 52.52             | 1070                         | 2760                   | 5150                   |
|            | FastAPI     | 11.7              | 4720                         | 9910                   | 11,620                 |
| High Load  | Express.js  | 52.52             | 1070                         | 2760                   | 5150                   |
|            | FastAPI     | 11.7              | 4720                         | 9910                   | 11,620                 |
| Spike Load | Express.js  | 52.52             | 1070                         | 2760                   | 5150                   |
|            | FastAPI     | 11.7              | 4720                         | 9910                   | 11,620                 |

---

## Visualisasi Grafik
- **Pengujian POST - Rata-rata Waktu Respons:**  
  Express.js memiliki performa waktu respons yang jauh lebih baik dibandingkan FastAPI.

- **Pengujian GET - Rata-rata Waktu Respons:**  
  Dalam kondisi Light, High, dan Spike Load, Express.js unggul secara signifikan dibandingkan FastAPI.

- **Throughput (Permintaan per Detik):**  
  Express.js menunjukkan kemampuan menangani throughput lebih tinggi dibandingkan FastAPI di semua pengujian.

---

## Kesimpulan
- **Pemenang untuk Pengujian POST:** Express.js karena waktu respons rata-rata lebih rendah (29.27 ms dibandingkan 198.69 ms) dan throughput lebih tinggi (3409 req/s dibandingkan 503 req/s).
- **Pemenang untuk Pengujian GET:** Express.js karena throughput yang lebih konsisten dan waktu respons rata-rata lebih rendah di semua skenario.
