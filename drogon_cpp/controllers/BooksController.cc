#include "BooksController.h"

// Get all books
void BooksController::getAllBooks(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback) {
  Json::Value response;
  Json::Value data(Json::arrayValue);

  {
    std::lock_guard<std::mutex> lock(booksMutex);
    for (const auto &book : books) {
      Json::Value bookJson;
      bookJson["id"] = book.id;
      bookJson["title"] = book.title;
      bookJson["author"] = book.author;
      bookJson["year"] = book.year;
      data.append(bookJson);
    }
  }

  response["message"] = "Berhasil mendapatkan semua buku";
  response["data"] = data;

  auto resp = HttpResponse::newHttpJsonResponse(response);
  callback(resp);
}

// Add a new book
void BooksController::addBook(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback) {
  auto json = req->getJsonObject();
  if (!json || !json->isMember("title") || !json->isMember("author") ||
      !json->isMember("year")) {
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k400BadRequest);
    resp->setBody("Invalid request body");
    callback(resp);
    return;
  }

  std::lock_guard<std::mutex> lock(booksMutex);

  // Check for duplicate title
  for (const auto &book : books) {
    if (book.title == (*json)["title"].asString()) {
      Json::Value response;
      response["message"] = "A book with the same title already exists";
      auto resp = HttpResponse::newHttpJsonResponse(response);
      resp->setStatusCode(k409Conflict);
      callback(resp);
      return;
    }
  }

  Book newBook;
  newBook.id = nextId++;
  newBook.title = (*json)["title"].asString();
  newBook.author = (*json)["author"].asString();
  newBook.year = (*json)["year"].asInt();
  books.push_back(newBook);

  Json::Value response;
  response["message"] = "Berhasil menambahkan buku baru";
  response["data"]["id"] = newBook.id;
  response["data"]["title"] = newBook.title;
  response["data"]["author"] = newBook.author;
  response["data"]["year"] = newBook.year;

  auto resp = HttpResponse::newHttpJsonResponse(response);
  resp->setStatusCode(k201Created); 
  resp->addHeader("Location",
                  "/books/" +
                      std::to_string(newBook.id)); 
  callback(resp);
}

// Update a book
void BooksController::updateBook(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback, int id) {
  auto json = req->getJsonObject();
  if (!json) {
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k400BadRequest);
    resp->setBody("Invalid request body");
    callback(resp);
    return;
  }

  std::lock_guard<std::mutex> lock(booksMutex);
  auto it = std::find_if(books.begin(), books.end(),
                         [id](const Book &book) { return book.id == id; });
  if (it == books.end()) {
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k404NotFound);
    resp->setBody("Book not found");
    callback(resp);
    return;
  }

  if (json->isMember("title"))
    it->title = (*json)["title"].asString();
  if (json->isMember("author"))
    it->author = (*json)["author"].asString();
  if (json->isMember("year"))
    it->year = (*json)["year"].asInt();

  Json::Value response;
  response["message"] = "Berhasil mengupdate buku";
  response["data"]["id"] = it->id;
  response["data"]["title"] = it->title;
  response["data"]["author"] = it->author;
  response["data"]["year"] = it->year;

  auto resp = HttpResponse::newHttpJsonResponse(response);
  callback(resp);
}

// Delete a book
void BooksController::deleteBook(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback, int id) {
  std::lock_guard<std::mutex> lock(booksMutex);
  auto it = std::find_if(books.begin(), books.end(),
                         [id](const Book &book) { return book.id == id; });
  if (it == books.end()) {
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k404NotFound);
    resp->setBody("Book not found");
    callback(resp);
    return;
  }

  books.erase(it);

  Json::Value response;
  response["message"] = "Berhasil menghapus buku";
  response["data"] = Json::nullValue;

  auto resp = HttpResponse::newHttpJsonResponse(response);
  callback(resp);
}
