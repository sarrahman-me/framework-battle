import http from 'k6/http';
import { check } from 'k6';

export const options = {
  scenarios: {
    posts: {
      executor: 'shared-iterations', // Semua VU berbagi jumlah iterasi
      vus: 100,                       // Jumlah Virtual Users
      iterations: 100000,              // Total permintaan POST
      maxDuration: '5m',             // Batas maksimal pengujian
    },
  },
};

export default function() {
  // Gunakan kombinasi __VU (ID Virtual User) dan __ITER (nomor iterasi) untuk membuat data unik
  const uniqueId = `${__VU}-${__ITER}`;
  const payload = JSON.stringify({
    title: `book ${uniqueId}`, // Judul unik berdasarkan kombinasi ID
    author: 'rahman',
    year: 2018,
  });

  const params = {
    headers: { 'Content-Type': 'application/json' },
  };

  const res = http.post('http://localhost:8080/books', payload, params);

  check(res, {
    'status is 201': (r) => r.status === 201,
  });
}
