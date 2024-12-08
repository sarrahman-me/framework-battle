import {
  Injectable,
  NotFoundException,
  ConflictException,
} from '@nestjs/common';
import { Book } from './books.model';

@Injectable()
export class BooksService {
  private books: Book[] = [];
  private nextId = 1;

  // Get all books
  findAll(): Book[] {
    return this.books;
  }

  // Add a new book
  create(book: Omit<Book, 'id'>): Book {
    // Cek apakah title sudah ada
    const titleExists = this.books.some(
      (b) => b.title.toLowerCase() === book.title.toLowerCase(),
    );
    if (titleExists) {
      throw new ConflictException('A book with the same title already exists');
    }

    const newBook: Book = { id: this.nextId++, ...book };
    this.books.push(newBook);
    return newBook;
  }

  // Update an existing book
  update(id: number, updatedFields: Partial<Book>): Book {
    const bookIndex = this.books.findIndex((b) => b.id === id);
    if (bookIndex === -1) {
      throw new NotFoundException('Book not found');
    }
    this.books[bookIndex] = { ...this.books[bookIndex], ...updatedFields };
    return this.books[bookIndex];
  }

  // Delete a book
  delete(id: number): void {
    const bookIndex = this.books.findIndex((b) => b.id === id);
    if (bookIndex === -1) {
      throw new NotFoundException('Book not found');
    }
    this.books.splice(bookIndex, 1);
  }
}
