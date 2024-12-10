import {
  Body,
  Controller,
  Delete,
  Get,
  HttpCode,
  Param,
  Patch,
  Post,
} from '@nestjs/common';
import { BooksService } from './books.service';
import { Book } from './books.model';

@Controller('books')
export class BooksController {
  constructor(private readonly bookService: BooksService) { }

  @Get()
  findAll() {
    const books = this.bookService.findAll();

    return {
      message: 'Berhasil mendapatkan data buku',
      data: books,
    };
  }

  @Post()
  @HttpCode(201)
  create(@Body() bookData: Omit<Book, 'id'>) {
    const book = this.bookService.create(bookData);

    return {
      message: 'Berhasil menambahkan buku',
      data: book,
    };
  }

  @Patch(':id')
  update(@Param('id') id: string, @Body() updatedFields: Partial<Book>) {
    const updatedBook = this.bookService.update(+id, updatedFields);

    return {
      message: 'Berhasil megupdate buku',
      data: updatedBook,
    };
  }

  @Delete(':id')
  delete(@Param('id') id: string) {
    this.bookService.delete(+id);

    return {
      message: 'Berhasil menghapus buku',
      data: null,
    };
  }
}
