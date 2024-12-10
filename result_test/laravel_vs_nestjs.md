![laravel vs nestjs](https://ik.imagekit.io/sarrahmanme/9.png?updatedAt=1733853538463)

# Hasil Pengujian Laravel (PHP) vs NestJS (TypeScript)

Berikut adalah hasil pengujian kinerja framework **Laravel** dan **NestJS** dalam skenario `POST` (menambahkan data) dan `GET` (mengambil data).

---

## 1. Pengujian POST

### Ringkasan Hasil
| **Metrik**               | **Laravel (PHP)** | **NestJS (TypeScript)** | **Pemenang**              |
|--------------------------|-------------------|-------------------------|---------------------------|
| Jumlah Iterasi Berhasil  | 33,566           | 100,000                 | NestJS (3x lebih banyak)  |
| Durasi Total             | 5 menit 2 detik  | 1 menit 22.5 detik      | NestJS (lebih cepat)      |
| Rata-rata Waktu Respons  | 896.56 ms        | 82.32 ms                | NestJS (10x lebih cepat)  |
| Data Dikirim             | 6.5 MB           | 19 MB                   | NestJS (lebih besar)      |
| Data Diterima            | 12 MB            | 35 MB                   | NestJS (lebih besar)      |
| Error Rate               | 0%               | 0%                      | Seri (keduanya andal)     |

**Pemenang untuk POST:** NestJS  
NestJS unggul dalam iterasi berhasil, waktu respons, throughput, dan volume data yang diproses.

---

## 2. Pengujian GET

### Ringkasan Hasil
| **Metrik**               | **Laravel (PHP)** | **NestJS (TypeScript)** | **Pemenang**                            |
|--------------------------|-------------------|-------------------------|-----------------------------------------|
| Total Data Diterima      | 29 GB            | 57 GB                   | NestJS (Laravel hanya 33.57% dari NestJS)|
| Rata-rata Waktu Respons  | 729.08 ms        | 1.14 s                  | Laravel (lebih cepat)                   |
| Error Rate               | 0%               | 0%                      | Seri (keduanya andal)                   |
| Throughput (req/s)       | 73.43 req/s      | 48.95 req/s             | Laravel (lebih tinggi)                  |

### Analisis Data GET
- Laravel hanya menarik **33.57%** dari total data yang ditarik oleh NestJS:  
  - Laravel menerima **29 GB** data selama pengujian GET.  
  - NestJS menerima **57 GB** data selama pengujian GET.  
- Perbedaan volume data yang diproses memengaruhi penilaian throughput dan waktu respons, di mana Laravel memproses data dalam jumlah lebih kecil.

**Pemenang untuk GET:** NestJS  
Meskipun Laravel lebih cepat dalam waktu respons dan throughput, NestJS memproses volume data yang jauh lebih besar dengan tingkat error nol, menjadikannya lebih andal dalam beban berat.

---

## Kesimpulan dan Pemenang

| **Kategori**    | **Pemenang** | **Alasan**                                                               |
|------------------|--------------|---------------------------------------------------------------------------|
| Pengujian POST   | NestJS       | Iterasi berhasil lebih tinggi dan waktu lebih cepat.                      |
| Pengujian GET    | NestJS       | Keandalan memproses lebih banyak data (57 GB vs 29 GB).                   |

### Visualisasi Data (Tabel Perbandingan)
| **Metrik**                  | **Laravel (PHP)** | **NestJS (TypeScript)** | **Komentar**                     |
|-----------------------------|-------------------|-------------------------|-----------------------------------|
| POST Iterasi Berhasil       | 33,566           | 100,000                 | NestJS unggul 3x lebih banyak.   |
| GET Data Diterima           | 29 GB            | 57 GB                   | Laravel hanya menarik 33.57% data.|
| POST Waktu Respons Rata-rata| 896.56 ms        | 82.32 ms                | NestJS 10x lebih cepat.          |
| GET Waktu Respons Rata-rata | 729.08 ms        | 1.14 s                  | Laravel lebih cepat, tapi datanya lebih sedikit. |
| GET Throughput (req/s)      | 73.43 req/s      | 48.95 req/s             | Laravel unggul, tapi volume datanya kecil. |

---

## Pemenang Umum: **NestJS**  
NestJS menunjukkan keandalan dalam memproses volume data yang jauh lebih besar dengan tingkat error nol di semua skenario.
