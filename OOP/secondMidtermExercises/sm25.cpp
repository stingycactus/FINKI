//
// Created by cactus on 4/30/2026.
//
#include <iostream>
using namespace std;

class MonthlyInvoice {
protected:
    string username;
    int number;
    float initialPrice;
    int usedInternet;

public:
    MonthlyInvoice(const string &username = "", int number = 0, float initialPrice = 0, int usedInternet = 0)
        : username(username), number(number), initialPrice(initialPrice), usedInternet(usedInternet) {
    }

    virtual ~MonthlyInvoice() {
    }

    virtual float total_price() const = 0;

    bool operator>(const MonthlyInvoice &other) const {
        return total_price() > other.total_price();
    }
};

class BusinessInvoice : public MonthlyInvoice {
private:
    bool optical;
    int freeTransfer;

public:
    BusinessInvoice(const string &username = "", int number = 0, float initialPrice = 0, int usedInternet = 0,
                    bool optical = false, int freeTransfer = 0)
        : MonthlyInvoice(username, number, initialPrice, usedInternet), optical(optical), freeTransfer(freeTransfer) {
    }

    float total_price() const {
        return initialPrice + (optical * initialPrice * 0.5) + max(0, usedInternet - freeTransfer) * 100.0;
    }

    BusinessInvoice operator++(int) {
        BusinessInvoice temp = *this;
        usedInternet++;
        return temp;
    }

    friend ostream &operator<<(ostream &os, const BusinessInvoice &b) {
        os << b.number << " - " << b.username << ", " << b.initialPrice << '\n';
        string linetype = "optical link";
        if (!b.optical) {
            linetype = "cable link";
        }
        os << linetype << ", " << max(0, b.usedInternet - b.freeTransfer) << '\n';
        return os;
    }
};

class PrivateInvoice : public MonthlyInvoice {
private:
    string id;
    int *movieSizes;
    int numberOfMovies;

public:
    PrivateInvoice(const string &username = "", int number = 0, float initialPrice = 0, int usedInternet = 0,
                   const string &id = "", int *movieSizes = nullptr,
                   int numberOfMovies = 0) : MonthlyInvoice(username, number, initialPrice, usedInternet), id(id) {
        this->numberOfMovies = numberOfMovies;
        this->movieSizes = new int[numberOfMovies];
        for (int i = 0; i < numberOfMovies; i++) {
            this->movieSizes[i] = movieSizes[i];
        }
    }

    ~PrivateInvoice() {
        delete [] movieSizes;
    }

    PrivateInvoice(const PrivateInvoice &other) : MonthlyInvoice(other.username, other.number, other.initialPrice,
                                                                 other.usedInternet) {
        this->id = other.id;
        this->numberOfMovies = other.numberOfMovies;
        this->movieSizes = new int[numberOfMovies];
        for (int i = 0; i < numberOfMovies; i++) {
            this->movieSizes[i] = other.movieSizes[i];
        }
    }

    PrivateInvoice &operator=(const PrivateInvoice &other) {
        if (this != &other) {
            MonthlyInvoice::operator=(other);
            delete [] movieSizes;
            this->id = other.id;
            this->numberOfMovies = other.numberOfMovies;
            this->movieSizes = new int[numberOfMovies];
            for (int i = 0; i < numberOfMovies; i++) {
                this->movieSizes[i] = other.movieSizes[i];
            }
        }
        return *this;
    }

    int totalGBFromMovies() const {
        int totalGB = 0;
        for (int i = 0; i < numberOfMovies; i++) {
            totalGB += movieSizes[i];
        }
        return totalGB;
    }

    float total_price() const {
        return initialPrice + usedInternet * 50.0 + totalGBFromMovies() * 10.0;
    }

    int operator[](int index) {
        if (index < 0 || index >= numberOfMovies) {
            return -1;
        }
        return movieSizes[index];
    }

    PrivateInvoice &operator+=(int movieSize) {
        int *temp = new int[numberOfMovies];
        for (int i = 0; i < numberOfMovies; i++) {
            temp[i] = movieSizes[i];
        }
        delete[] movieSizes;
        numberOfMovies++;
        movieSizes = new int[numberOfMovies];
        for (int i = 0; i < numberOfMovies - 1; i++) {
            movieSizes[i] = temp[i];
        }
        movieSizes[numberOfMovies - 1] = movieSize;
        delete[] temp;
        return *this;
    }

    PrivateInvoice operator++(int) {
        PrivateInvoice temp = *this;
        usedInternet++;
        return temp;
    }

    friend ostream &operator<<(ostream &os, const PrivateInvoice &p) {
        os << p.number << " - " << p.username << ", " << p.initialPrice << '\n';
        os << p.usedInternet << '\n';
        os << p.numberOfMovies << ", " << p.totalGBFromMovies() << '\n';
        return os;
    }

    int getMoviesNo() const {
        return numberOfMovies;
    }
};

MonthlyInvoice &biggestInvoice(MonthlyInvoice *invoices[], int n) {
    int index = 0;
    for (int i = 0; i < n; i++) {
        if (*invoices[i] > *invoices[index]) {
            index = i;
        }
    }
    return *invoices[index];
}

int main() {
    int test_case;
    char username[101];
    int userNumber;
    float basic_price;
    int spent_gigabytes;
    bool optical;
    int free_gigabytes;
    int num_inc;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case Business Invoice - Constructor, operator <<
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        cin >> optical >> free_gigabytes;
        BusinessInvoice bi(username, userNumber, basic_price, spent_gigabytes, optical, free_gigabytes);
        cout << "BusinessInvoice Created:\n";
        cout << bi;
    } else if (test_case == 2) {
        // Test Case Business Invoice - Constructor, operators <<, ++
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        cin >> optical >> free_gigabytes;
        BusinessInvoice bi(username, userNumber, basic_price, spent_gigabytes, optical, free_gigabytes);
        cout << "BusinessInvoice:\n";
        cout << bi;
        cout << "testing operator++\n";

        // Additional spent gigabytes
        cin >> num_inc;
        for (int i = 0; i < num_inc; ++i) {
            bi++;
        }
        cout << bi;
    } else if (test_case == 3) {
        // Test Case Business Invoice - Constructor, total_price, operators <<, ++,
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        cin >> optical >> free_gigabytes;
        BusinessInvoice bi(username, userNumber, basic_price, spent_gigabytes, optical, free_gigabytes);
        cout << "Testing total_price()\n";
        cout << bi;
        cout << bi.total_price() << endl;
        bi++;
        cout << bi;
        cout << bi.total_price() << endl;
    } else if (test_case == 4) {
        // Test Case Private Invoice - Constructor, operator <<
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;

        PrivateInvoice pi(username, userNumber, basic_price, spent_gigabytes);
        cout << "Private Invoice Created:\n";
        cout << pi;
    } else if (test_case == 5) {
        // Test Case Private Invoice - Constructor, operators <<, ++
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        PrivateInvoice pi(username, userNumber, basic_price, spent_gigabytes);
        cin >> num_inc;
        for (int i = 0; i < num_inc; ++i) {
            pi++;
        }
        cout << pi;
    } else if (test_case == 6) {
        // Test Case Private Invoice - Constructor, operators <<, +=
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        PrivateInvoice pi(username, userNumber, basic_price, spent_gigabytes);
        cin >> num_inc;
        int film_length;
        for (int i = 0; i < num_inc; ++i) {
            cin >> film_length;
            pi += film_length;
        }
        cout << pi;
    } else if (test_case == 7) {
        // Test Case Private Invoice - Constructor, operators <<, +=, []
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        PrivateInvoice pi(username, userNumber, basic_price, spent_gigabytes);
        cin >> num_inc;
        int film_length;
        for (int i = 0; i < num_inc; ++i) {
            cin >> film_length;
            pi += film_length;
        }
        cout << pi;
        cout << "Movie sizes: [";
        for (int i = 0; i < pi.getMoviesNo(); ++i) {
            cout << pi[i] << " ";
        }
        cout << "]" << endl;
    } else if (test_case == 8) {
        // Test Case Private Invoice - Constructor, total_price
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        PrivateInvoice pi(username, userNumber, basic_price, spent_gigabytes);
        cout << pi;
        cout << pi.total_price() << endl;
        cin >> num_inc;
        int film_length;
        for (int i = 0; i < num_inc; ++i) {
            cin >> film_length;
            pi += film_length;
        }
        cin >> num_inc;
        for (int i = 0; i < num_inc; ++i) {
            pi++;
        }
        cout << pi;
        cout << pi.total_price() << endl;
    } else if (test_case == 9) {
        // Test Case

        int num_invoices;
        int invoice_type;

        cin >> num_invoices;
        MonthlyInvoice **mi = new MonthlyInvoice *[num_invoices];
        for (int j = 0; j < num_invoices; ++j) {
            cin >> invoice_type;
            if (invoice_type == 1) {
                cin >> username >> userNumber >> basic_price >> spent_gigabytes;
                cin >> optical >> free_gigabytes;
                BusinessInvoice *bip;
                bip = new BusinessInvoice(username, userNumber, basic_price, spent_gigabytes, optical, free_gigabytes);
                cin >> num_inc;
                for (int i = 0; i < num_inc; ++i) {
                    (*(bip))++;
                }
                cout << *(bip);
                cout << bip->total_price() << endl;

                mi[j] = bip;
            }
            if (invoice_type == 2) {
                cin >> username >> userNumber >> basic_price >> spent_gigabytes;
                PrivateInvoice *pip = new PrivateInvoice(username, userNumber, basic_price, spent_gigabytes);
                cin >> num_inc;
                int film_length;
                for (int i = 0; i < num_inc; ++i) {
                    cin >> film_length;
                    (*pip) += film_length;
                }
                cin >> num_inc;
                for (int i = 0; i < num_inc; ++i) {
                    (*pip)++;
                }
                cout << (*pip);
                cout << pip->total_price() << endl;
                mi[j] = pip;
            }
        }

        cout << "The biggest invoice is:\n";
        MonthlyInvoice &invoice = biggestInvoice(mi, num_invoices);

        MonthlyInvoice *m = &invoice;
        BusinessInvoice *bip;
        PrivateInvoice *pip;
        if (dynamic_cast<BusinessInvoice *>(m)) {
            bip = dynamic_cast<BusinessInvoice *>(m);
            cout << *bip << bip->total_price();
        }
        if (dynamic_cast<PrivateInvoice *>(m)) {
            pip = dynamic_cast<PrivateInvoice *>(m);
            cout << *pip << pip->total_price();
        }
    }
    return 0;
}
