#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>

using namespace std;

class Book {
private:
    string title;
    string author;
    int id;
    bool available;

public:
    Book(string t, string a, int i) : title(t), author(a), id(i), available(true) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getId() const { return id; }
    bool isAvailable() const { return available; }

    void setAvailable(bool status) { available = status; }

    void displayInfo() const {
        cout << "ID: " << id << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Available: " << (available ? "Yes" : "No") << endl;
    }
};

class Library {
private:
    vector<Book> books;
    int nextID;

public:
    Library() : nextID(1) {}

    void addBook(const string& title, const string& author) {
        books.push_back(Book(title, author, nextID++));
    }

    void displayAllBooks() const {
        cout << "Books in the library:" << endl;
        for (const auto& book : books) {
            book.displayInfo();
            cout << "---------------------" << endl;
        }
    }

    void borrowBook(int id) {
        auto it = findBookById(id);
        if (it != books.end()) {
            if (it->isAvailable()) {
                it->setAvailable(false);
                cout << "Book with ID " << id << " borrowed successfully." << endl;
            } else {
                cout << "Book with ID " << id << " is already borrowed." << endl;
            }
        } else {
            cout << "Book with ID " << id << " not found." << endl;
        }
    }

    void returnBook(int id) {
        auto it = findBookById(id);
        if (it != books.end()) {
            if (!it->isAvailable()) {
                it->setAvailable(true);
                cout << "Book with ID " << id << " returned successfully." << endl;
            } else {
                cout << "Book with ID " << id << " is already in the library." << endl;
            }
        } else {
            cout << "Book with ID " << id << " not found." << endl;
        }
    }

private:
    vector<Book>::iterator findBookById(int id) {
        return find_if(books.begin(), books.end(), [&](const Book& b) { return b.getId() == id; });
    }
};

int main() {
    Library library;
    int choice;
    do {
        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Borrow Book\n";
        cout << "4. Return Book\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string title, author;
                cin.ignore();
                cout << "Enter title: ";
                getline(cin, title);
                cout << "Enter author: ";
                getline(cin, author);
                library.addBook(title, author);
                break;
            }
            case 2:
                library.displayAllBooks();
                break;
            case 3: {
                int id;
                cout << "Enter book ID to borrow: ";
                cin >> id;
                library.borrowBook(id);
                break;
            }
            case 4: {
                int id;
                cout << "Enter book ID to return: ";
                cin >> id;
                library.returnBook(id);
                break;
            }
            case 5:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}

