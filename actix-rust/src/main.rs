use actix_web::{delete, get, patch, post, web, App, HttpResponse, HttpServer, Responder};
use dashmap::DashMap;
use serde::{Deserialize, Serialize};
use std::sync::Arc;

type DB = Arc<DashMap<u32, Book>>;

#[derive(Serialize, Deserialize, Clone)]
struct Book {
    id: Option<u32>,
    title: String,
    author: String,
    year: i32,
}

#[derive(Serialize, Deserialize)]
struct ResponseType<T> {
    message: String,
    data: Option<T>,
}

#[post("/books")]
async fn add_new_book(payload: web::Json<Book>, db: web::Data<DB>) -> impl Responder {
    let payload = payload.into_inner();
    let mut new_id = 1;

    if let Some(max_id) = db.iter().map(|entry| *entry.key()).max() {
        new_id = max_id + 1;
    }

    if db.iter().any(|entry| entry.value().title == payload.title) {
        return HttpResponse::Conflict().json(ResponseType {
            message: "Data buku sudah ada".to_string(),
            data: None::<Book>,
        });
    }

    let new_book = Book {
        id: Some(new_id),
        title: payload.title,
        author: payload.author,
        year: payload.year,
    };

    db.insert(new_id, new_book.clone());

    HttpResponse::Created().json(ResponseType {
        message: "Berhasil menambahkan data buku baru".to_string(),
        data: Some(new_book),
    })
}

#[get("/books")]
async fn find_all_books(db: web::Data<DB>) -> impl Responder {
    let all_books: Vec<Book> = db.iter().map(|entry| entry.value().clone()).collect();

    HttpResponse::Ok().json(ResponseType {
        message: "Berhasil mendapatkan semua data buku".to_string(),
        data: Some(all_books),
    })
}

#[patch("/books/{id}")]
async fn update_book(
    id: web::Path<u32>,
    payload: web::Json<Book>,
    db: web::Data<DB>,
) -> impl Responder {
    let id = id.into_inner();
    let payload = payload.into_inner();

    if let Some(mut book) = db.get_mut(&id) {
        book.title = payload.title;
        book.author = payload.author;
        book.year = payload.year;

        return HttpResponse::Ok().json(ResponseType {
            message: "Berhasil mengupdate data buku".to_string(),
            data: Some(book.clone()),
        });
    }

    HttpResponse::NotFound().json(ResponseType {
        message: "Buku tidak ditemukan".to_string(),
        data: None::<Book>,
    })
}

#[delete("/books/{id}")]
async fn delete_book(id: web::Path<u32>, db: web::Data<DB>) -> impl Responder {
    let id = id.into_inner();

    match db.remove(&id) {
        Some((_, book)) => HttpResponse::Ok().json(ResponseType {
            message: "Berhasil menghapus data buku".to_string(),
            data: Some(book),
        }),
        None => HttpResponse::NotFound().json(ResponseType {
            message: "Data buku tidak ditemukan".to_string(),
            data: None::<Book>,
        }),
    }
}

#[actix_web::main]
async fn main() -> Result<(), std::io::Error> {
    let app_data: DB = Arc::new(DashMap::new());

    HttpServer::new(move || {
        App::new()
            .app_data(web::Data::new(app_data.clone()))
            .service(add_new_book)
            .service(find_all_books)
            .service(update_book)
            .service(delete_book)
    })
    .workers(8)
    .bind(("0.0.0.0", 8080))?
    .run()
    .await
}
