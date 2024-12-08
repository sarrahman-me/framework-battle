<?php

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Route;
use App\Http\Controllers\BookController;

Route::post('/books', [BookController::class, 'addBook']);
Route::get('/books', [BookController::class, 'getBooks']);
Route::patch('/books/{id}', [BookController::class, 'updateBook']);
Route::delete('/books/{id}', [BookController::class, 'deleteBook']);


Route::get('/user', function (Request $request) {
    return $request->user();
})->middleware('auth:sanctum');
