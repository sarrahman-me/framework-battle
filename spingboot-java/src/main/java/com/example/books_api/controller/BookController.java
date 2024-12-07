package com.example.books_api.controller;

import com.example.books_api.model.Book;
import com.example.books_api.service.BookService;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/books")
public class BookController {
  private final BookService bookService;

  public BookController(BookService bookService) {
    this.bookService = bookService;
  }

  @GetMapping
  public ResponseEntity<List<Book>> findAllBooks() {
    return ResponseEntity.ok(bookService.findAllBooks());
  }

  @PostMapping
  public ResponseEntity<Book> addNewBook(@RequestBody Book book) {
    return ResponseEntity.ok(bookService.addNewBook(book));
  }

  @PatchMapping("/{id}")
  public ResponseEntity<Book> updateBook(@PathVariable Integer id, @RequestBody Book book) {
    return ResponseEntity.ok(bookService.updateBook(id, book));
  }

  @DeleteMapping("/{id}")
  public ResponseEntity<Book> deleteBook(@PathVariable Integer id) {
    return ResponseEntity.ok(bookService.deleteBook(id));
  }
}
