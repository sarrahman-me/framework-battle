package main

import (
	"fmt"
	"strconv"
	"sync"

	"github.com/gofiber/fiber/v2"
	"github.com/gofiber/fiber/v2/middleware/logger"
)

type Book struct {
	ID     int    `json:"id"`
	Title  string `json:"title"`
	Author string `json:"author"`
	Year   int    `json:"year"`
}

type ResponseType struct {
	Message string      `json:"message"`
	Data    interface{} `json:"data,omitempty"`
}

var (
	books []Book
	mutex sync.Mutex
)

func main() {
	app := fiber.New(fiber.Config{
		Prefork: true,
	})

	app.Use(logger.New())

	app.Post("/books", func(c *fiber.Ctx) error {
		mutex.Lock()

		defer mutex.Unlock()

		var payload Book
		if err := c.BodyParser(&payload); err != nil {
			return c.Status(fiber.StatusBadRequest).JSON(ResponseType{
				Message: "Data tidak valid",
			})
		}

		for _, book := range books {
			if book.Title == payload.Title {
				return c.Status(fiber.StatusConflict).JSON(ResponseType{
					Message: "Buku sudah ada",
				})
			}
		}

		payload.ID = len(books) + 1

		books = append(books, payload)

		return c.Status(fiber.StatusCreated).JSON(ResponseType{
			Message: "Berhasil menambahkan buku baru",
			Data:    payload,
		})
	})

	app.Get("/books", func(c *fiber.Ctx) error {
		mutex.Lock()

		defer mutex.Unlock()

		return c.Status(fiber.StatusOK).JSON(ResponseType{
			Message: "Berhasil mendapatkan semua buku",
			Data:    books,
		})
	})

	app.Patch("/books/:id", func(c *fiber.Ctx) error {
		mutex.Lock()
		defer mutex.Unlock()

		id, err := strconv.Atoi(c.Params("id"))
		if err != nil {
			return c.Status(fiber.StatusBadRequest).JSON(ResponseType{
				Message: "Invalid id",
			})
		}

		var updatedBook *Book
		for i, book := range books {
			if book.ID == id {
				updatedBook = &books[i]
				break
			}
		}

		if updatedBook == nil {
			return c.Status(fiber.StatusNotFound).JSON(ResponseType{
				Message: "Buku tidak ditemukan",
			})
		}

		var payload Book
		if err := c.BodyParser(&payload); err != nil {
			return c.Status(fiber.StatusBadRequest).JSON(ResponseType{
				Message: "Invalid Body",
			})
		}

		if payload.Title != "" {
			updatedBook.Title = payload.Title
		}
		if payload.Author != "" {
			updatedBook.Author = payload.Author
		}
		if payload.Year != 0 {
			updatedBook.Year = payload.Year
		}

		return c.Status(fiber.StatusOK).JSON(ResponseType{
			Message: "Berhasil mengupdate data buku",
			Data:    updatedBook,
		})
	})

	app.Delete("/books/:id", func(c *fiber.Ctx) error {
		mutex.Lock()
		defer mutex.Unlock()

		id, err := strconv.Atoi(c.Params("id"))
		if err != nil {
			return c.Status(fiber.StatusBadRequest).JSON(ResponseType{
				Message: "invalid ID",
			})
		}

		for i, book := range books {
			if book.ID == id {
				deletedBook := book
				books = append(books[:i], books[i+1:]...)
				return c.Status(fiber.StatusOK).JSON(ResponseType{
					Message: "Berhasil menghapus data buku",
					Data:    deletedBook,
				})
			}
		}

		return c.Status(fiber.StatusNotFound).JSON(ResponseType{
			Message: "Buku tidak ditemukan",
		})
	})

	fmt.Println("Server running on port 8080")
	app.Listen(":8080")
}
