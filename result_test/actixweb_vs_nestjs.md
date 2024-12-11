# Analisis dan Perbandingan Hasil Pengujian Kinerja

Berikut adalah analisis rinci dari hasil pengujian untuk dua framework **NestJS** (TypeScript) dan **Actix Web** (Rust) pada skenario **POST** dan **GET**, berdasarkan data yang telah disediakan.

---

## Tabel Perbandingan Hasil Pengujian POST

| **Parameter**              | **NestJS**                  | **Actix Web**               | **Komentar**                                                           |
|----------------------------|-----------------------------|-----------------------------|-----------------------------------------------------------------------|
| **Jumlah Data Berhasil**    | 159,806 / 250,000 (63.92%)   | 249,943 / 250,000 (99.97%)   | Actix Web berhasil menyelesaikan hampir semua permintaan.             |
| **Error Rate**              | 0.22%                        | 0.02%                        | Actix Web lebih andal dengan error rate lebih rendah.                 |
| **Rata-rata Durasi Respon** | 468.96 ms                   | 24.28 ms                    | Actix Web jauh lebih cepat (~20x lebih cepat).                        |
| **P95 Durasi Respon**       | 1.16 s                       | 35.23 ms                    | P95 Actix jauh lebih rendah.                                          |
| **P99 Durasi Respon**       | 1.26 s                       | 41 ms                        | Actix lebih unggul dalam latensi tinggi.                               |
| **Throughput**              | 531.61 req/s                | 8,745 req/s                 | Actix ~16x throughput NestJS.                                          |
| **Total Waktu**             | 5 menit (terbatas waktu maksimal) | 28.6 detik                 | Actix selesai jauh lebih cepat.                                       |

---

## Tabel Perbandingan Hasil Pengujian GET

| **Parameter**              | **NestJS**                  | **Actix Web**               | **Komentar**                                                           |
|----------------------------|-----------------------------|-----------------------------|-----------------------------------------------------------------------|
| **Jumlah Data Berhasil**    | 4,907 / 5,281 (92.91%)      | 86,760 / 86,871 (99.87%)     | Actix Web memproses jauh lebih banyak data dengan keberhasilan lebih tinggi. |
| **Error Rate**              | 7.08%                        | 0.12%                        | Actix Web lebih andal dengan error rate jauh lebih rendah.            |
| **Rata-rata Durasi Respon** | 3.87 s                       | 289.73 ms                    | Actix Web jauh lebih cepat (~13x lebih cepat).                        |
| **P95 Durasi Respon**       | 5.17 s                       | 474.07 ms                    | P95 Actix jauh lebih rendah.                                          |
| **P99 Durasi Respon**       | 60 s                         | 517.1 ms                     | P99 Actix lebih baik, terutama dalam skenario lonjakan beban.         |
| **Throughput**              | 29.12 req/s                 | 482.36 req/s                 | Actix ~16.5x throughput NestJS.                                        |
| **Total Waktu**             | 3 menit                     | 3 menit                      | Waktu pengujian sama untuk GET; namun Actix memproses jauh lebih banyak permintaan. |

---

## Kesimpulan dan Pemenang

Berdasarkan pengujian ini, **Actix Web (Rust)** menang telak dalam semua parameter penting:

- **Kecepatan Penyelesaian**: Actix menyelesaikan semua permintaan POST dalam waktu 28.6 detik, sedangkan NestJS membutuhkan waktu maksimal 5 menit tetapi hanya menyelesaikan 63.92% dari total iterasi.
- **Keandalan**: Actix memiliki error rate lebih rendah baik dalam POST (0.02%) maupun GET (0.12%), dibandingkan NestJS (0.22% POST, 7.08% GET).
- **Kinerja di Bawah Beban**: Pada skenario GET, Actix dapat menangani lonjakan hingga 250 VUs tanpa degradasi yang signifikan, sementara NestJS menunjukkan latensi tinggi dan throughput rendah.
- **Throughput dan Latensi**: Throughput Actix untuk POST mencapai 8,745 req/s dan untuk GET 482.36 req/s, jauh di atas NestJS (531.61 req/s POST, 29.12 req/s GET). Latensi rata-rata Actix untuk POST (24.28 ms) dan GET (289.73 ms) jauh lebih rendah dibandingkan NestJS (468.96 ms POST, 3.87 s GET).

### **Pemenang**: **Actix Web (Rust)**

Actix menunjukkan performa yang jauh lebih baik dalam hal kecepatan, keandalan, dan skalabilitas dibandingkan NestJS, terutama dalam pengujian POST dan GET dengan beban tinggi.
