import {
  ConflictException,
  Injectable,
  NotFoundException,
} from '@nestjs/common';
import { Book } from './books.model';

@Injectable()
export class BooksService {
  private books: Book[] = [];
  private nextId = 1;

  findAll(): Book[] {
    return this.books;
  }

  create(book: Omit<Book, 'id'>): Book {
    const titleExist = this.books.some(
      (b) => b.title.toLowerCase() === book.title.toLowerCase(),
    );

    if (titleExist) {
      throw new ConflictException('Buku sudah ada');
    }

    const newBook: Book = { id: this.nextId++, ...book };
    this.books.push(newBook);
    return newBook;
  }

  update(id: number, updatedFields: Partial<Book>): Book {
    const bookIndex = this.books.findIndex((b) => b.id === id);
    if (bookIndex === -1) {
      throw new NotFoundException('Buku tidak ditemukan');
    }

    this.books[bookIndex] = { ...this.books[bookIndex], ...updatedFields };
    return this.books[bookIndex];
  }

  delete(id: number): void {
    const bookIndex = this.books.findIndex((b) => b.id === id);

    if (bookIndex === -1) {
      throw new NotFoundException('Buku tidak ditemukan');
    }

    this.books.splice(bookIndex, 1);
  }
}
