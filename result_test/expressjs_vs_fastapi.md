# Hasil Pengujian Performa API: Express.js vs FastAPI

## 1. Pengujian POST

### Hasil Express.js
- **Durasi Penyelesaian**: 5,4 detik
- **Rata-rata Waktu Respons**: 5,28 ms
- **p95**: 12,99 ms (95% requests lebih cepat dari ini)
- **p99**: 21,59 ms (99% requests lebih cepat dari ini)
- **Permintaan Berhasil**: 100.000 (100%)
- **Error**: 0%

### Hasil FastAPI
- **Durasi Penyelesaian**: 17,1 detik
- **Rata-rata Waktu Respons**: 17,02 ms
- **p95**: 56,89 ms (95% requests lebih cepat dari ini)
- **p99**: 75,26 ms (99% requests lebih cepat dari ini)
- **Permintaan Berhasil**: 100.000 (100%)
- **Error**: 0%

### Analisis POST
- **Kecepatan Penyelesaian**: Express.js lebih cepat menyelesaikan seluruh iterasi (5,4 detik) dibandingkan FastAPI (17,1 detik).
- **Waktu Respons**: Express.js memiliki waktu respons rata-rata lebih baik (5,28 ms) dibandingkan FastAPI (17,02 ms). Nilai p95 dan p99 juga menunjukkan stabilitas Express.js lebih unggul.
- **Keandalan**: Keduanya tidak memiliki error, sehingga sama-sama andal.

**Pemenang Pengujian POST**: Express.js

---

## 2. Pengujian GET

### Hasil Express.js
- **Throughput (permintaan per detik)**: 1.672 req/s
- **Rata-rata Waktu Respons**: 31,72 ms
- **p95**: 76,73 ms (95% requests lebih cepat dari ini)
- **p99**: 109,04 ms (99% requests lebih cepat dari ini)
- **Permintaan Berhasil**: 301.080
- **Error**: 0%

### Hasil FastAPI
- **Throughput (permintaan per detik)**: 400 req/s
- **Rata-rata Waktu Respons**: 133,06 ms
- **p95**: 320,65 ms (95% requests lebih cepat dari ini)
- **p99**: 389,14 ms (99% requests lebih cepat dari ini)
- **Permintaan Berhasil**: 72.123
- **Error**: 0%

### Analisis GET
- **Throughput**: Express.js memproses lebih banyak permintaan per detik (1.672 req/s) dibandingkan FastAPI (400 req/s).
- **Waktu Respons**: Express.js memiliki waktu respons rata-rata lebih baik (31,72 ms) dibandingkan FastAPI (133,06 ms). Nilai p95 dan p99 menunjukkan Express.js lebih stabil di bawah beban.
- **Keandalan**: Tidak ada error pada kedua framework, sehingga keduanya andal.

**Pemenang Pengujian GET**: Express.js

---

## 3. Visualisasi Data

| Metode | Framework  | Durasi Penyelesaian | Rata-rata Waktu Respons | p95        | p99        | Throughput  | Error Rate |
|--------|------------|---------------------|-------------------------|------------|------------|-------------|------------|
| POST   | Express.js | 5,4 detik           | 5,28 ms                 | 12,99 ms   | 21,59 ms   | N/A         | 0%         |
| POST   | FastAPI    | 17,1 detik          | 17,02 ms                | 56,89 ms   | 75,26 ms   | N/A         | 0%         |
| GET    | Express.js | 3 menit             | 31,72 ms                | 76,73 ms   | 109,04 ms  | 1.672 req/s | 0%         |
| GET    | FastAPI    | 3 menit             | 133,06 ms               | 320,65 ms  | 389,14 ms  | 400 req/s   | 0%         |

---

## 4. Kesimpulan

- **Pemenang Pengujian POST**: Express.js
- **Pemenang Pengujian GET**: Express.js

### Alasan Utama Kemenangan Express.js
- **Kinerja**: Lebih cepat menyelesaikan permintaan POST dan GET.
- **Waktu Respons**: Memiliki waktu respons rata-rata yang lebih rendah, baik untuk POST maupun GET.
- **Throughput (GET)**: Memproses lebih banyak permintaan per detik dibandingkan FastAPI.
