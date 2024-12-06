import express from "express";
const app = express();

app.use(express.json());

let books = [];

function createResponse(message, data = null) {
  return { message, data };
}

app.post("/books", (req, res) => {
  const { title, author, year } = req.body;

  const existingBook = books.find((book) => book.title === title);
  if (existingBook) {
    return res.status(409).json(createResponse("Buku sudah ada"));
  }

  const newBook = { id: books.length + 1, title, author, year };
  books.push(newBook);

  res.status(201).json(createResponse("Buku berhasil ditambahkan", newBook));
});

app.get("/books", (_, res) => {
  res.status(200).json(createResponse("Berhasil mendapatkan semua buku", books));
});

app.patch("/books/:id", (req, res) => {
  const { id } = req.params;
  const { title, author, year } = req.body;

  const book = books.find((b) => b.id === parseInt(id));

  if (!book) {
    return res.status(404).json(createResponse("Buku tidak ditemukan"));
  }

  if (title) book.title = title;
  if (author) book.author = author;
  if (year) book.year = year;

  res.status(200).json(createResponse("Berhasil mengupdate data buku", book));
});

app.delete("/books/:id", (req, res) => {
  const { id } = req.params;

  const index = books.findIndex((b) => b.id === parseInt(id));

  if (index === -1) {
    return res.status(404).json(createResponse("Buku tidak ditemukan"));
  }

  const deletedBook = books.splice(index, 1)[0];

  res.status(200).json(createResponse("Buku berhasil di hapus", deletedBook));
});

const PORT = 8080;
app.listen(PORT, () => {
  console.log(`Server is running on port ${PORT}`);
});
