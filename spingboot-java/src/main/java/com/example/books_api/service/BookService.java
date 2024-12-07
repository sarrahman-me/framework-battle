package com.example.books_api.service;

import com.example.books_api.model.Book;
import org.springframework.stereotype.Service;

import java.util.*;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicInteger;

@Service
public class BookService {
  private final Map<Integer, Book> bookStore = new ConcurrentHashMap<>();
  private final AtomicInteger idCounter = new AtomicInteger(0);

  public List<Book> findAllBooks() {
    return new ArrayList<>(bookStore.values());
  }

  public Book addNewBook(Book book) {
    book.setId(idCounter.incrementAndGet());
    if (bookStore.values().stream().anyMatch(b -> b.getTitle().equalsIgnoreCase(book.getTitle()))) {
      throw new IllegalArgumentException("Book with the same title already exists");
    }
    bookStore.put(book.getId(), book);
    return book;
  }

  public Book updateBook(Integer id, Book updatedBook) {
    Book existingBook = bookStore.get(id);
    if (existingBook == null) {
      throw new NoSuchElementException("Book not found");
    }

    existingBook.setTitle(updatedBook.getTitle());
    existingBook.setAuthor(updatedBook.getAuthor());
    existingBook.setYear(updatedBook.getYear());

    return existingBook;
  }

  public Book deleteBook(Integer id) {
    Book removedBook = bookStore.remove(id);
    if (removedBook == null) {
      throw new NoSuchElementException("Book not found");
    }
    return removedBook;
  }
}
