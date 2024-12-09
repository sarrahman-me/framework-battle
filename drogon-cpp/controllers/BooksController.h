#pragma once

#include <drogon/HttpSimpleController.h>
#include <json/json.h>
#include <mutex>
#include <string>
#include <vector>

using namespace drogon;

struct Book {
  int id;
  std::string title;
  std::string author;
  int year;
};

class BooksController : public drogon::HttpSimpleController<BooksController> {
public:
  // Implementasi fungsi utama yang menangani permintaan
  void asyncHandleHttpRequest(
      const HttpRequestPtr &req,
      std::function<void(const HttpResponsePtr &)> &&callback) override {
    // Periksa metode HTTP dan arahkan ke handler yang sesuai
    if (req->getMethod() == HttpMethod::Get) {
      getAllBooks(req, std::move(callback));
    } else if (req->getMethod() == HttpMethod::Post) {
      addBook(req, std::move(callback));
    } else if (req->getMethod() == HttpMethod::Patch) {
      // Ambil parameter ID dari URL
      auto id =
          req->getParameter("id"); // Ini akan mengakses parameter path {id}
      if (!id.empty()) {
        updateBook(req, std::move(callback), std::stoi(id));
      } else {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k400BadRequest);
        resp->setBody("ID parameter is missing");
        callback(resp);
      }
    } else if (req->getMethod() == HttpMethod::Delete) {
      // Ambil parameter ID dari URL
      auto id =
          req->getParameter("id"); // Ini akan mengakses parameter path {id}
      if (!id.empty()) {
        deleteBook(req, std::move(callback), std::stoi(id));
      } else {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k400BadRequest);
        resp->setBody("ID parameter is missing");
        callback(resp);
      }
    } else {
      // Metode HTTP tidak didukung
      auto resp = HttpResponse::newHttpResponse();
      resp->setStatusCode(k405MethodNotAllowed);
      resp->setBody("Method not allowed");
      callback(resp);
    }
  }
  // Handler untuk setiap endpoint
  void getAllBooks(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback);
  void addBook(const HttpRequestPtr &req,
               std::function<void(const HttpResponsePtr &)> &&callback);
  void updateBook(const HttpRequestPtr &req,
                  std::function<void(const HttpResponsePtr &)> &&callback,
                  int id);
  void deleteBook(const HttpRequestPtr &req,
                  std::function<void(const HttpResponsePtr &)> &&callback,
                  int id);

  // Daftar rute yang didukung
  PATH_LIST_BEGIN
  PATH_ADD("/books", Get, Post);          // GET dan POST /books
  PATH_ADD("/books/{id}", Patch, Delete); // PATCH dan DELETE /books/{id}
  PATH_LIST_END

private:
  std::vector<Book> books; // Penyimpanan data buku
  int nextId = 1;          // ID berikutnya untuk buku baru
  std::mutex booksMutex;   // Mutex untuk sinkronisasi
};
