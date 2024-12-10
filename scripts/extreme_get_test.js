import http from 'k6/http';
import { check } from 'k6';

export const options = {
  scenarios: {
    // Skenario Beban Ringan
    light_load: {
      executor: 'constant-vus',
      vus: 50, // Jumlah Virtual Users
      duration: '1m', // Durasi pengujian
    },

    // Skenario Beban Tinggi
    high_load: {
      executor: 'constant-vus',
      vus: 100, // Jumlah Virtual Users
      duration: '3m', // Durasi pengujian
    },

    // Skenario Lonjakan Beban
    spike_load: {
      executor: 'ramping-vus',
      startVUs: 10, // Mulai dengan 10 pengguna virtual
      stages: [
        { duration: '30s', target: 100 }, // Naik hingga 100 VUs dalam 30 detik
        { duration: '1m', target: 500 },  // Naik hingga 500 VUs dalam 1 menit
        { duration: '30s', target: 0 },   // Turunkan kembali ke 0 pengguna virtual dalam 30 detik
      ],
    },
  },
};

export default function() {
  const res = http.get('http://localhost:8080/books');
  check(res, {
    'status is 200': (r) => r.status === 200,
  });
}
