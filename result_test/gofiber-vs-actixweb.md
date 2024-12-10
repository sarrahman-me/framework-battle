![gofiber vs actixweb](https://ik.imagekit.io/sarrahmanme/8.png?updatedAt=1733853538543)

# Hasil Pengujian Gofiber vs Actix Web

Berikut adalah hasil dan analisis pengujian kinerja framework **Gofiber** dan **Actix Web** dalam skenario `POST` (menambahkan data) dan `GET` (mengambil data).

---

## 1. Pengujian POST (Menambahkan Data)

### Ringkasan Hasil
| **Metric**                | **Gofiber**        | **Actix Web**      |
|---------------------------|--------------------|--------------------|
| Durasi Penyelesaian       | 15.1 detik        | 4.8 detik          |
| Jumlah Permintaan Berhasil| 100,000 (100%)    | 100,000 (100%)     |
| Rata-rata Waktu Respons   | 15.05 ms          | 4.78 ms            |
| P95 Waktu Respons         | 30.52 ms          | 9.27 ms            |
| P99 Waktu Respons         | 34.97 ms          | 11.67 ms           |
| Permintaan Per Detik (TPS)| 6,621 TPS         | 20,681 TPS         |
| Kesalahan (Error)         | 0 (0%)            | 0 (0%)             |

### Analisis
- **Kecepatan Penyelesaian:** Actix Web jauh lebih cepat, menyelesaikan pengujian dalam 4.8 detik dibandingkan Gofiber yang membutuhkan 15.1 detik.
- **Waktu Respons:** Actix Web memiliki rata-rata waktu respons yang lebih rendah (4.78 ms vs 15.05 ms).
- **Throughput:** Actix Web memiliki throughput yang jauh lebih tinggi (20,681 TPS vs 6,621 TPS).
- **Keandalan:** Kedua framework tidak mengalami error (100% sukses).

**Pemenang untuk POST:** Actix Web

---

## 2. Pengujian GET (Mengambil Data)

### Ringkasan Hasil
| **Metric**                | **Gofiber**        | **Actix Web**      |
|---------------------------|--------------------|--------------------|
| Total Permintaan Berhasil | 16,305            | 211,435            |
| Rata-rata Waktu Respons   | 591.63 ms         | 45.28 ms           |
| P95 Waktu Respons         | 1.23 detik        | 100.62 ms          |
| P99 Waktu Respons         | 1.31 detik        | 118.88 ms          |
| Throughput (TPS)          | 90 TPS            | 1,175 TPS          |
| Kesalahan (Error)         | 0 (0%)            | 0 (0%)             |

### Analisis Berdasarkan Beban
1. **Light Load (Beban Ringan):**  
   Actix Web lebih unggul dalam waktu respons rata-rata dan throughput.
   
2. **High Load (Beban Tinggi):**  
   Actix Web mempertahankan kinerja yang stabil dengan waktu respons jauh lebih rendah dibandingkan Gofiber.
   
3. **Spike Load (Lonjakan Beban):**  
   Actix Web mengelola lonjakan beban dengan lebih baik, menunjukkan waktu respons rata-rata yang konsisten dan tanpa error.

**Pemenang untuk GET:** Actix Web

---

## Kesimpulan

| **Pengujian** | **Pemenang** |
|---------------|--------------|
| POST          | Actix Web    |
| GET           | Actix Web    |

**Actix Web** unggul di semua aspek: kecepatan, throughput, dan waktu respons.  
Framework ini menjadi pilihan yang lebih baik untuk kinerja yang andal dan cepat.
