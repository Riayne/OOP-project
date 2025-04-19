# include<iostream>
# include<string>
using namespace std;
class Book {
protected:
    int book_ID;
    string author;
    string name;
    float price;
    bool status; // true: available, false: issued
    int edition;
    int date_of_purchase;
    string owner;

public:
    Book() : book_ID(0), author(""), name(""), price(0.0), status(true), edition(1), date_of_purchase(getCurrentYear()), owner("Library") {}

    Book(int id, const string& a, const string& n, float p, int ed) : book_ID(id), author(a), name(n), price(p), status(true), edition(ed), date_of_purchase(getCurrentYear()), owner("Library") {}

    virtual void display() const {
        cout << "Book ID: " << book_ID
             << "\nTitle: " << name
             << "\nAuthor: " << author
             << "\nPrice: $" << price
             << "\nEdition: " << edition
             << "\nPurchased: " << date_of_purchase
             << "\nStatus: " << (status ? "Available" : "Issued")
             << "\nOwner: " << get_owner() << endl;
    }

    virtual float calculate_discount() const {
        return 0.0;  // Base class does not offer a discount
    }

    string get_owner() const {
        return owner;
    }

    void change_owner(const string& new_owner) {
        owner = new_owner;
    }

    void update_status(bool stat) {
        status = stat;
    }

    bool isAvailable() const { return status; }

    string get_title() const { return name; }
};

// ======================= DERIVED BOOK TYPES =======================
class Journal : public Book {
private:
    int publishing_year;
public:
    Journal(int id, const string& a, const string& n, float p, int ed, int pub_year) 
        : Book(id, a, n, p, ed), publishing_year(pub_year) {}

    void display() const override {
        Book::display();
        cout << "Publishing Year: " << publishing_year << endl;
    }

    float calculate_discount() const override {
        // Apply a discount for journals based on publication year (older journals have a discount)
        int age = getCurrentYear() - publishing_year;
        if (age > 5) {
            return 0.15; // 15% discount for journals older than 5 years
        }
        return 0.0;
    }
};

class StudyBook : public Book {
public:
    StudyBook(int id, const string& a, const string& n, float p, int ed) 
        : Book(id, a, n, p, ed) {}

    void display() const override {
        Book::display();
    }

    float calculate_discount() const override {
        // Apply a discount based on the edition of the study book (e.g., older editions get a discount)
        if (edition > 2) {
            return 0.10; // 10% discount for study books with editions higher than 2
        }
        return 0.0;
    }
};

class Magazine : public Book {
private:
    int issue_number;
public:
    Magazine(int id, const string& a, const string& n, float p, int ed, int issue_no) 
        : Book(id, a, n, p, ed), issue_number(issue_no) {}

    void display() const override {
        Book::display();
        cout << "Issue Number: " << issue_number << endl;
    }

    float calculate_discount() const override {
        // Magazines can have a subscription-based discount
        if (issue_number > 10) {
            return 0.05; // 5% discount for magazines with issue number greater than 10
        }
        return 0.0;
    }
};