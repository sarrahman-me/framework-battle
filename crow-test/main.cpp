#include "crow.h"
#include <mutex>
#include <string>
#include <vector>

struct Book {
  int id;
  std::string title;
  std::string author;
  int year;
};

std::vector<Book> books;
std::mutex mutex;

int main() {
  crow::SimpleApp app;

  // POST /books
  CROW_ROUTE(app, "/books")
      .methods(crow::HTTPMethod::POST)([](const crow::request &req) {
        std::lock_guard<std::mutex> lock(mutex);
        auto payload = crow::json::load(req.body);
        if (!payload || !payload["title"].is_string() ||
            !payload["author"].is_string() || !payload["year"].is_number()) {
          return crow::response(
              400, crow::json::wvalue{{"message", "Invalid request body"}});
        }

        for (const auto &book : books) {
          if (book.title == payload["title"].s()) {
            return crow::response(
                409, crow::json::wvalue{{"message", "Buku sudah ada"}});
          }
        }

        Book newBook{static_cast<int>(books.size() + 1), payload["title"].s(),
                     payload["author"].s(), payload["year"].i()};
        books.push_back(newBook);

        return crow::response(
            201, crow::json::wvalue{{"message", "Buku berhasil ditambahkan"}});
      });

  // Jalankan server
  CROW_LOG_INFO << "Server running on http://127.0.0.1:8080";
  app.port(8080).multithreaded().run();
}
