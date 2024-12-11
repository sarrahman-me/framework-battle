#include "BooksController.h"

// Ambil semua buku
void BooksController::getAllBooks(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback) {
  Json::Value response;
  response["message"] = "Berhasil mendapatkan semua buku";

  Json::Value data(Json::arrayValue);

  {
    std::shared_lock<std::shared_mutex> lock(booksMutex); // Mengizinkan pembacaan paralel
    for (const auto &book : books) {
      Json::Value bookJson;
      bookJson["id"] = book.id;
      bookJson["title"] = book.title;
      bookJson["author"] = book.author;
      bookJson["year"] = book.year;
      data.append(bookJson);
    }
  }

  response["data"] = data;

  auto resp = HttpResponse::newHttpJsonResponse(response);
  callback(resp);
}

// Tambahkan buku baru
void BooksController::addBook(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback) {
  auto json = req->getJsonObject();
  if (!json || !json->isMember("title") || !json->isMember("author") || !json->isMember("year")) {
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k400BadRequest);
    resp->setBody("Invalid request body");
    callback(resp);
    return;
  }

  const std::string title = (*json)["title"].asString();
  std::lock_guard<std::shared_mutex> lock(booksMutex); // Penulisan membutuhkan eksklusivitas

  // Periksa duplikat berdasarkan title
  if (titleIndex.find(title) != titleIndex.end()) {
    Json::Value response;
    response["message"] = "A book with the same title already exists";
    auto resp = HttpResponse::newHttpJsonResponse(response);
    resp->setStatusCode(k409Conflict);
    callback(resp);
    return;
  }

  // Tambahkan buku baru
  Book newBook;
  newBook.id = nextId++;
  newBook.title = title;
  newBook.author = (*json)["author"].asString();
  newBook.year = (*json)["year"].asInt();

  books.push_back(newBook);
  titleIndex[title] = books.size() - 1;

  Json::Value response;
  response["message"] = "Berhasil menambahkan buku baru";
  response["data"]["id"] = newBook.id;
  response["data"]["title"] = newBook.title;
  response["data"]["author"] = newBook.author;
  response["data"]["year"] = newBook.year;

  auto resp = HttpResponse::newHttpJsonResponse(response);
  resp->setStatusCode(k201Created);
  callback(resp);
}
