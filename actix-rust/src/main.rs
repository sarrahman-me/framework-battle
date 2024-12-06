use std::{
    collections::HashMap,
    sync::{Arc, Mutex},
};

use actix_web::{
    delete, get, middleware::Logger, patch, post, web, App, HttpResponse, HttpServer, Responder,
};
use env_logger::Env;
use serde::{Deserialize, Serialize};

type DB = Arc<Mutex<HashMap<u32, Book>>>;

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
    let mut db = db.lock().unwrap();
    let payload = payload.into_inner();

    let new_id: u32 = db.keys().max().unwrap_or(&0) + 1;

    let new_book = Book {
        id: Some(new_id),
        title: payload.title.to_owned(),
        author: payload.author.to_owned(),
        year: payload.year,
    };

    if db.values().any(|item| item.title == payload.title.clone()) {
        return HttpResponse::Conflict().json(ResponseType {
            message: "Data buku sudah ada".to_string(),
            data: None::<Book>,
        });
    }

    db.insert(new_id, new_book.clone());

    HttpResponse::Ok().json(ResponseType {
        message: "Berhasil menambahkan data buku baru".to_string(),
        data: Some(new_book.clone()),
    })
}

#[get("/books")]
async fn find_all_books(db: web::Data<DB>) -> impl Responder {
    let db = db.lock().unwrap();

    let all_books: Vec<Book> = db.values().cloned().collect();

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
    let mut db = db.lock().unwrap();
    let id = id.into_inner();
    let payload = payload.into_inner();

    if db.get(&id).is_none() {
        return HttpResponse::NotFound().json(ResponseType {
            message: "Buku tidak ditemukan".to_string(),
            data: None::<Book>,
        });
    }

    let book_to_update = Book {
        id: Some(id),
        title: payload.title.to_owned(),
        author: payload.author.to_owned(),
        year: payload.year,
    };

    db.insert(id, book_to_update);

    let updated_book = db.get(&id).unwrap();

    HttpResponse::Ok().json(ResponseType {
        message: "Berhasil mengupdate data buku".to_string(),
        data: Some(updated_book),
    })
}

#[delete("/books/{id}")]
async fn delete_book(id: web::Path<u32>, db: web::Data<DB>) -> impl Responder {
    let mut db = db.lock().unwrap();
    let id = id.into_inner();

    match db.remove(&id) {
        Some(book) => HttpResponse::Ok().json(ResponseType {
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
    let app_data: DB = Arc::new(Mutex::new(HashMap::<u32, Book>::new()));

    env_logger::init_from_env(Env::default().default_filter_or("debug"));

    HttpServer::new(move || {
        App::new()
            .wrap(Logger::default())
            .app_data(web::Data::new(app_data.clone()))
            .service(add_new_book)
            .service(find_all_books)
            .service(update_book)
            .service(delete_book)
    })
    .bind(("0.0.0.0", 8080))?
    .run()
    .await
}
