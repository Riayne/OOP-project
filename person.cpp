#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Book {
private:
    string title;
    string genre;
    int pages;
public:
    Book(string t, string g, int p) : title(t), genre(g), pages(p) {}

    void getInfo() const {
        cout << "Title: " << title << ", Genre: " << genre << ", Pages: " << pages << endl;
    }

    string getTitle() const { return title; }
};

class Person {
protected:
    string name;
    int age;
public:
    Person(string n, int a) : name(n), age(a) {}
    virtual void whoAreYou() const = 0; // pure virtual
};

class Author : public Person {
private:
    vector<Book> books;
public:
    Author(string n, int a) : Person(n, a) {}

    void newBook(const Book& b) {
        books.push_back(b);
    }

    void showBooks() const {
        cout << name << "'s Books:" << endl;
        for (const auto& book : books) {
            book.getInfo();
        }
    }

    void whoAreYou() const override {
        cout << "Name: " << name << ", Age: " << age << ", Role: Author" << endl;
    }

    const vector<Book>& getBooks() const { return books; }
};

class Reader : public Person {
private:
    vector<Book> ownedBooks;
    vector<Book> borrowedBooks;
public:
    Reader(string n, int a) : Person(n, a) {}

    void purchaseBook(const Book& b) {
        cout << name << " purchased the book: " << b.getTitle() << endl;
        ownedBooks.push_back(b);
    }

    void borrowBook(const Book& b) {
        cout << name << " borrowed the book: " << b.getTitle() << endl;
        borrowedBooks.push_back(b);
    }

    void returnBook(const string& title) {
        for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it) {
            if (it->getTitle() == title) {
                cout << name << " returned the book: " << title << endl;
                borrowedBooks.erase(it);
                return;
            }
        }
        cout << "Book not found in borrowed list!" << endl;
    }

    void showBooks() const {
        cout << name << "'s Owned Books:" << endl;
        for (const auto& book : ownedBooks) {
            book.getInfo();
        }
        cout << name << "'s Borrowed Books:" << endl;
        for (const auto& book : borrowedBooks) {
            book.getInfo();
        }
    }

    void whoAreYou() const override {
        cout << "Name: " << name << ", Age: " << age << ", Role: Reader" << endl;
    }
};

int main() {
    Author author("J.K. Rowling", 55);
    Book b1("Harry Potter", "Fantasy", 500);
    Book b2("Fantastic Beasts", "Fantasy", 300);

    author.newBook(b1);
    author.newBook(b2);

    Reader reader("Alice", 20);

    // Actions
    author.whoAreYou();
    author.showBooks();

    reader.whoAreYou();
    reader.purchaseBook(b1);
    reader.borrowBook(b2);
    reader.showBooks();
    reader.returnBook("Fantastic Beasts");
    reader.showBooks();

    return 0;
}
