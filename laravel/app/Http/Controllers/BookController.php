<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Redis;
use Symfony\Component\HttpFoundation\Response;

class BookController extends Controller
{
    // Menambahkan buku baru
    public function addBook(Request $request)
    {
        $request->validate([
            'title' => 'required|string',
            'author' => 'required|string',
            'year' => 'required|integer',
        ]);

        // Cek apakah buku dengan title yang sama sudah ada
        $existingBooks = Redis::lrange('books', 0, -1);  // Gunakan lrange untuk list
        foreach ($existingBooks as $bookJson) {
            $book = json_decode($bookJson, true);
            if ($book['title'] === $request->title) {
                return response()->json([
                    'message' => 'Buku sudah ada',
                    'data' => null
                ], Response::HTTP_CONFLICT);
            }
        }

        // Menambah buku ke Redis
        $bookId = Redis::llen('books') + 1;
        $book = [
            'id' => $bookId,
            'title' => $request->title,
            'author' => $request->author,
            'year' => $request->year,
        ];
        Redis::rpush('books', json_encode($book));

        return response()->json([
            'message' => 'Berhasil menambahkan buku baru',
            'data' => $book
        ], Response::HTTP_OK);
    }

    // Mendapatkan semua buku
    public function getBooks()
    {
        $books = Redis::lrange('books', 0, -1);
        $books = array_map(fn($book) => json_decode($book, true), $books);

        return response()->json([
            'message' => 'Berhasil mendapatkan semua buku',
            'data' => $books
        ], Response::HTTP_OK);
    }

    // Mengupdate data buku
    public function updateBook($id, Request $request)
    {
        $request->validate([
            'title' => 'nullable|string',
            'author' => 'nullable|string',
            'year' => 'nullable|integer',
        ]);

        $books = Redis::lrange('books', 0, -1);
        $books = array_map(fn($book) => json_decode($book, true), $books);
        $bookIndex = null;

        foreach ($books as $index => $book) {
            if ($book['id'] == $id) {
                $bookIndex = $index;
                break;
            }
        }

        if ($bookIndex === null) {
            return response()->json([
                'message' => 'Buku tidak ditemukan',
                'data' => null
            ], Response::HTTP_NOT_FOUND);
        }

        $book = $books[$bookIndex];
        $book['title'] = $request->title ?? $book['title'];
        $book['author'] = $request->author ?? $book['author'];
        $book['year'] = $request->year ?? $book['year'];

        $books[$bookIndex] = $book;
        Redis::del('books'); // Hapus data buku lama
        foreach ($books as $updatedBook) {
            Redis::rpush('books', json_encode($updatedBook)); // Tambahkan buku yang telah diperbarui
        }

        return response()->json([
            'message' => 'Berhasil mengupdate buku',
            'data' => $book
        ], Response::HTTP_OK);
    }

    // Menghapus buku
    public function deleteBook($id)
    {
        $books = Redis::lrange('books', 0, -1);
        $books = array_map(fn($book) => json_decode($book, true), $books);
        $bookIndex = null;

        foreach ($books as $index => $book) {
            if ($book['id'] == $id) {
                $bookIndex = $index;
                break;
            }
        }

        if ($bookIndex === null) {
            return response()->json([
                'message' => 'Buku tidak ditemukan',
                'data' => null
            ], Response::HTTP_NOT_FOUND);
        }

        // Hapus buku
        unset($books[$bookIndex]);
        Redis::del('books');
        foreach ($books as $remainingBook) {
            Redis::rpush('books', json_encode($remainingBook));
        }

        return response()->json([
            'message' => 'Berhasil menghapus buku',
            'data' => null
        ], Response::HTTP_OK);
    }
}
