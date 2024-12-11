#pragma once

#include <drogon/HttpSimpleController.h>
#include <json/json.h>
#include <shared_mutex>
#include <string>
#include <vector>
#include <unordered_map>

using namespace drogon;

struct Book {
  int id;
  std::string title;
  std::string author;
  int year;
};

class BooksController : public drogon::HttpSimpleController<BooksController> {
public:
  void asyncHandleHttpRequest(
      const HttpRequestPtr &req,
      std::function<void(const HttpResponsePtr &)> &&callback) override {
    if (req->getMethod() == HttpMethod::Get) {
      getAllBooks(req, std::move(callback));
    } else if (req->getMethod() == HttpMethod::Post) {
      addBook(req, std::move(callback));
    } else {
      auto resp = HttpResponse::newHttpResponse();
      resp->setStatusCode(k405MethodNotAllowed);
      resp->setBody("Method not allowed");
      callback(resp);
    }
  }

  void getAllBooks(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback);
  void addBook(const HttpRequestPtr &req,
               std::function<void(const HttpResponsePtr &)> &&callback);

  PATH_LIST_BEGIN
  PATH_ADD("/books", Get, Post); // GET dan POST /books
  PATH_LIST_END

private:
  std::vector<Book> books; // Penyimpanan data buku
  std::unordered_map<std::string, int> titleIndex; // Indeks untuk pencarian cepat berdasarkan title
  int nextId = 1;          // ID berikutnya untuk buku baru
  mutable std::shared_mutex booksMutex; // Mutex untuk sinkronisasi pembacaan dan penulisan
};
