![springboot vs drogon](https://ik.imagekit.io/sarrahmanme/drogonspring.png?updatedAt=1733885407527)

# Hasil Pengujian Java Spring Boot vs Drogon C++

Berikut adalah hasil perbandingan kinerja framework **Java Spring Boot** dan **Drogon C++** dalam skenario `POST` (menambahkan data) dan `GET` (mengambil data).

---

## 1. Pengujian POST (Menambahkan Data)

### Ringkasan Hasil
| **Framework**        | **Durasi** | **Rata-rata Waktu Respons** | **P95 Waktu Respons** | **P99 Waktu Respons** | **Jumlah Berhasil** | **Error Rate** | **Throughput**           |
|-----------------------|------------|-----------------------------|------------------------|------------------------|---------------------|----------------|--------------------------|
| Java Spring Boot      | 20.5 detik | 20.13 ms                   | 70.84 ms              | 186.36 ms             | 100,000             | 0%             | 4,872 permintaan/detik   |
| Drogon C++            | 2.0 detik  | 1.96 ms                    | 4.00 ms               | 5.84 ms               | 100,000             | 0%             | 49,646 permintaan/detik  |

### Analisis
- **Kecepatan Penyelesaian**: Drogon jauh lebih cepat menyelesaikan seluruh iterasi dalam 2 detik dibandingkan Java Spring Boot yang membutuhkan 20.5 detik.
- **Waktu Respons**: Drogon unggul dalam rata-rata waktu respons, P95, dan P99 dibandingkan Java Spring Boot.
- **Reliabilitas**: Kedua framework berhasil memproses semua permintaan tanpa error.

**Pemenang untuk POST**: **Drogon C++**

---

## 2. Pengujian GET (Mengambil Data)

### a. GET dengan Data (Tidak Kosong)
| **Framework**        | **Skenario Beban** | **Rata-rata Waktu Respons** | **P95 Waktu Respons** | **P99 Waktu Respons** | **Jumlah Berhasil** | **Error Rate** | **Throughput**           |
|-----------------------|--------------------|-----------------------------|------------------------|------------------------|---------------------|----------------|--------------------------|
| Java Spring Boot      | High Load         | 227.58 ms                  | 655.65 ms             | 968.66 ms             | 41,995              | 0.07%          | 233 permintaan/detik     |
| Drogon C++            | High Load         | 14.48 s                    | 37.32 s               | 42.27 s               | 732                 | 0%             | 4 permintaan/detik       |

### Analisis
- **Drogon** menunjukkan performa buruk pada pengujian GET data tidak kosong, kemungkinan karena masalah pada konfigurasi atau pengolahan data.
- **Java Spring Boot** berhasil memproses lebih banyak permintaan dengan throughput yang jauh lebih tinggi.

**Pemenang GET Data Tidak Kosong**: **Java Spring Boot**

---

### b. GET dengan Data Kosong
| **Framework**        | **Skenario Beban** | **Rata-rata Waktu Respons** | **P95 Waktu Respons** | **P99 Waktu Respons** | **Jumlah Berhasil** | **Error Rate** | **Throughput**           |
|-----------------------|--------------------|-----------------------------|------------------------|------------------------|---------------------|----------------|--------------------------|
| Java Spring Boot      | High Load         | 645.66 µs                  | 2.14 ms               | 4.24 ms               | 12,824,664          | 0%             | 71,247 permintaan/detik  |
| Drogon C++            | High Load         | 565.15 µs                  | 1.59 ms               | 2.29 ms               | 15,968,604          | 0%             | 88,713 permintaan/detik  |

### Analisis
- **Drogon** menunjukkan performa lebih baik dibandingkan Java Spring Boot, baik dari segi waktu respons maupun throughput.

**Pemenang GET Data Kosong**: **Drogon C++**

---

## Kesimpulan Akhir

| **Kategori**          | **Pemenang**        | **Alasan**                                                                 |
|-----------------------|---------------------|-----------------------------------------------------------------------------|
| **POST (Menambahkan Data)** | Drogon C++         | Lebih cepat dan efisien dibandingkan Java Spring Boot.                     |
| **GET Data Tidak Kosong** | Java Spring Boot   | Throughput lebih tinggi dan reliabilitas lebih baik dalam pengolahan data. |
| **GET Data Kosong**   | Drogon C++         | Unggul dari segi waktu respons dan throughput.                             |

**Pemenang Utama Berdasarkan Aturan**: **Java Spring Boot**  
Java Spring Boot dipilih sebagai pemenang karena performanya yang lebih stabil dalam pengujian GET dengan data tidak kosong, yang mencerminkan skenario aplikasi dunia nyata. Drogon unggul dalam POST dan GET data kosong, tetapi performanya pada skenario data sebenarnya kurang memadai.
