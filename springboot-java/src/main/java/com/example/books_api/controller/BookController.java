package com.example.books_api.controller;

import java.util.List;

import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PatchMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import com.example.books_api.model.Book;
import com.example.books_api.service.BookService;

@RestController
@RequestMapping("/books")
public class BookController {
  private final BookService bookService;

  public BookController(BookService bookService) {
    this.bookService = bookService;
  }

  @GetMapping
  public ResponseEntity<List<Book>> findAllBooks() {
    return ResponseEntity.ok(bookService.findAllBook());
  }

  @PostMapping
  public ResponseEntity<Book> addNewBook(@RequestBody Book book) {
    return ResponseEntity.ok(bookService.addNewBook(book));
  }

  @PatchMapping("/{id}")
  public ResponseEntity<Book> updatedBook(@PathVariable Integer id, @RequestBody Book book) {
    return ResponseEntity.ok(bookService.updateBook(id, book));
  }

  @DeleteMapping("/{id}")
  public ResponseEntity<Book> deleteBook(@PathVariable Integer id) {
    return ResponseEntity.ok(bookService.deleteBook(id));
  }
}
