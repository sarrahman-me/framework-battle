import json
import pandas as pd
import matplotlib.pyplot as plt


def load_multiple_json(file_path):
    """Fungsi untuk membaca file JSON yang memiliki banyak objek JSON dalam satu file"""
    with open(file_path, "r") as f:
        # Membaca semua baris dari file
        content = f.read()
        # Mengurai JSON jika ada beberapa objek dalam file
        data = []
        for line in content.splitlines():
            if line.strip():  # Cek apakah baris tidak kosong
                data.append(json.loads(line))
        return data


# Baca file JSON hasil k6
post_data_list = load_multiple_json("drogon_hard_post_test.json")
get_data_list = load_multiple_json("drogon_hard_get_test.json")


# Fungsi untuk mengekstrak metrik dari hasil k6
def extract_metrics(data_list, metric_name):
    """Mengambil metrik dari list objek JSON"""
    metrics = []
    for data in data_list:
        # Cek apakah objek mengandung metric yang relevan
        if "metric" in data and data["metric"] == metric_name:
            # Cek apakah key 'data' dan 'time' ada di dalam objek
            if "data" in data and "time" in data["data"]:
                timestamp = data["data"]["time"]
                value = data["data"]["value"]
                metrics.append(
                    {"timestamp": timestamp, "value": value}
                )  # Mengambil waktu dan nilai
            else:
                print(
                    f"Warning: 'data' or 'time' key missing in the metric data: {data}"
                )
    return metrics


# Ekstrak metrik http_req_duration dan http_reqs dari POST dan GET test
post_duration = extract_metrics(post_data_list, "http_req_duration")
get_duration = extract_metrics(get_data_list, "http_req_duration")

post_requests = extract_metrics(post_data_list, "http_reqs")
get_requests = extract_metrics(get_data_list, "http_reqs")

# Membuat DataFrame untuk memudahkan pemrosesan
post_duration_df = pd.DataFrame(post_duration)
get_duration_df = pd.DataFrame(get_duration)

post_requests_df = pd.DataFrame(post_requests)
get_requests_df = pd.DataFrame(get_requests)

# Menampilkan statistik deskriptif untuk durasi permintaan HTTP
post_duration_stats = post_duration_df["value"].describe()
get_duration_stats = get_duration_df["value"].describe()

# Menampilkan statistik deskriptif untuk jumlah permintaan HTTP
post_requests_stats = post_requests_df["value"].describe()
get_requests_stats = get_requests_df["value"].describe()

# Mencetak statistik deskriptif
print("\nPOST Request Duration Stats:")
print(post_duration_stats)
print("\nGET Request Duration Stats:")
print(get_duration_stats)

print("\nPOST HTTP Requests Stats:")
print(post_requests_stats)
print("\nGET HTTP Requests Stats:")
print(get_requests_stats)

# Visualisasi durasi permintaan HTTP
plt.figure(figsize=(12, 6))

# POST test durasi
plt.subplot(2, 1, 1)
plt.plot(
    post_duration_df["timestamp"],
    post_duration_df["value"],
    label="POST Request Duration",
    color="b",
)
plt.xlabel("Time")
plt.ylabel("Duration (ms)")
plt.title("HTTP Request Duration Over Time - POST Test")
plt.legend()
plt.grid(True)

# GET test durasi
plt.subplot(2, 1, 2)
plt.plot(
    get_duration_df["timestamp"],
    get_duration_df["value"],
    label="GET Request Duration",
    color="g",
)
plt.xlabel("Time")
plt.ylabel("Duration (ms)")
plt.title("HTTP Request Duration Over Time - GET Test")
plt.legend()
plt.grid(True)

plt.tight_layout()
plt.show()

# Visualisasi jumlah permintaan HTTP
plt.figure(figsize=(12, 6))

# POST test jumlah permintaan
plt.subplot(2, 1, 1)
plt.plot(
    [request["timestamp"] for request in post_requests],
    [request["value"] for request in post_requests],
    label="POST HTTP Requests",
    color="r",
)
plt.xlabel("Time")
plt.ylabel("Requests")
plt.title("HTTP Requests Over Time - POST Test")
plt.legend()
plt.grid(True)

# GET test jumlah permintaan
plt.subplot(2, 1, 2)
plt.plot(
    [request["timestamp"] for request in get_requests],
    [request["value"] for request in get_requests],
    label="GET HTTP Requests",
    color="purple",
)
plt.xlabel("Time")
plt.ylabel("Requests")
plt.title("HTTP Requests Over Time - GET Test")
plt.legend()
plt.grid(True)

plt.tight_layout()
plt.show()

# Menampilkan tabel statistik untuk durasi dan jumlah permintaan
print("\nPOST Request Duration - Statistics Summary:")
print(post_duration_df.describe())

print("\nGET Request Duration - Statistics Summary:")
print(get_duration_df.describe())

print("\nPOST HTTP Requests - Statistics Summary:")
print(post_requests_df.describe())

print("\nGET HTTP Requests - Statistics Summary:")
print(get_requests_df.describe())
