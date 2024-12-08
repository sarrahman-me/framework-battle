import {
  Controller,
  Get,
  Post,
  Patch,
  Delete,
  Body,
  Param,
} from '@nestjs/common';
import { BooksService } from './books.service';
import { Book } from './books.model';

@Controller('books')
export class BooksController {
  constructor(private readonly booksService: BooksService) {}

  // Get all books
  @Get()
  findAll() {
    const books = this.booksService.findAll();
    return {
      message: 'Berhasil mendapatkan semua buku',
      data: books,
    };
  }

  // Create a new book
  @Post()
  create(@Body() bookData: Omit<Book, 'id'>) {
    const book = this.booksService.create(bookData);
    return {
      message: 'Berhasil menambahkan buku baru',
      data: book,
    };
  }

  // Update a book
  @Patch(':id')
  update(@Param('id') id: string, @Body() updatedFields: Partial<Book>) {
    const updatedBook = this.booksService.update(+id, updatedFields);
    return {
      message: 'Berhasil mengupdate buku',
      data: updatedBook,
    };
  }

  // Delete a book
  @Delete(':id')
  delete(@Param('id') id: string) {
    this.booksService.delete(+id);
    return {
      message: 'Berhasil menghapus buku',
      data: null,
    };
  }
}
