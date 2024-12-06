from typing import Optional
from fastapi import FastAPI, HTTPException
from pydantic import BaseModel

app = FastAPI()

books = []


class Book(BaseModel):
    id: Optional[int] = None
    title: str
    author: str
    year: int


class ResponseType(BaseModel):
    message: str
    data: Optional[object] = None


@app.post("/books", response_model=ResponseType)
def add_new_book(payload: Book):
    existing_book = next(
        (book for book in books if book["title"] == payload.title), None
    )

    if existing_book:
        raise HTTPException(status_code=409, detail="Buku sudah ada")

    new_book = payload.model_dump()

    new_book["id"] = len(books) + 1
    books.append(new_book)

    return ResponseType(message="Buku berhasil ditambahkan", data=new_book)


@app.get("/books", response_model=ResponseType)
def get_all_books():
    return ResponseType(message="Berhasil mendapatkan semua buku", data=books)


@app.patch("/books/{book_id}", response_model=ResponseType)
def update_book(book_id: int, payload: Book):
    book = next((book for book in books if book["id"] == book_id), None)

    if not book:
        raise HTTPException(status_code=404, detail="Buku tidak ditemukan")

    if payload.title:
        book["title"] = payload.title
    if payload.author:
        book["author"] = payload.author
    if payload.year:
        book["year"] = payload.year

    return ResponseType(message="Berhasil mengupdate data buku", data=book)


@app.delete("/books/{book_id}", response_model=ResponseType)
def delete_book(book_id: int):
    global books
    book = next((book for book in books if book["id"] == book_id), None)

    if not book:
        raise HTTPException(status_code=404, detail="Buku tidak ditemukan")

    books = [b for b in books if b["id"] != book_id]
    return ResponseType(message="Buku berhasil dihapus", data=book)
