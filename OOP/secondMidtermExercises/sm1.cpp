//
// Created by cactus on 5/25/2026.
//
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;


class UserNotFoundException {
private:
    string username;
public:
    UserNotFoundException(const string &username="") :username(username) {}
    void print() {
        cout<<"User with username \""<<username<<"\" not found."<<'\n';
    }
};
class User {
private:
    int id;
    string username;
    string email;
    string password;
    int connections;
public:
    User(int id=0, const string &username="", const string &email="", const string &password="", int connections=0)
    : id(id), username(username), email(email), password(password), connections(connections) {}
    User &operator++() {
        connections++;
        return *this;
    }
    bool operator==(const string &otherUsername) {
        return username == otherUsername;
    }
    friend ostream &operator<<(ostream &os, const User &u) {
        os<<"ID: "<<u.id<<", Username: "<<u.username<<", Password length: "<<u.password.length()<<", Email: "<<u.email<<", Connections: "<<u.connections;
        return os;
    }
    string getUsername() const {
        return username;
    }
    string getEmail() const {
        return email;
    }
};

class UserSystem {
private:
    User *users;
    int n;
public:
    UserSystem(User *users=nullptr, int n=0) {
        this->n=n;
        this->users= new User[n];
        for (int i = 0; i<n; i++) {
            this->users[i] = users[i];
        }
    }
    ~UserSystem() {
        delete [] users;
    }
    UserSystem(const UserSystem &other) {
        this->n=other.n;
        this->users= new User[n];
        for (int i = 0; i<n; i++) {
            this->users[i] = other.users[i];
        }
    }
    UserSystem &operator=(const UserSystem &other) {
        if (this!=&other) {
            delete [] users;
            this->n=other.n;
            this->users= new User[n];
            for (int i = 0; i<n; i++) {
                this->users[i] = other.users[i];
            }
        }
        return *this;
    }
    UserSystem &operator+=(const User &u) {
        User *temp = new User[n+1];
        for (int i = 0; i<n; i++) {
            temp[i] = users[i];
        }
        delete [] users;
        this->users = temp;
        this->users[n]=u;
        n++;
        return *this;
    }
    User &operator[](const string &username) {
        for (int i = 0; i<n; i++) {
            if (users[i].getUsername()==username) {
                return users[i];
            }
        }
        throw UserNotFoundException(username);
    }
    friend ostream &operator<<(ostream &os, const UserSystem &us) {
        if (!us.n) {
            cout<<"No users in the system"<<'\n';
        }
        for (int i = 0; i<us.n; i++) {
            os<<us.users[i]<<'\n';
        }
        return os;
    }
    UserSystem filterByEmailDomain(string domain) {
        UserSystem result;
        for (int i = 0; i<n; i++) {
            string email = users[i].getEmail();
            if (email.substr(email.length()-domain.length())==domain) {
                result+=users[i];
            }
        }
        return result;
    }
};

User readUser(ifstream &in) {
    int id;
    string username;
    string email;
    string password;
    int connections;
    in>>id;
    in.ignore();
    getline(in, username);
    getline(in, email);
    getline(in, password);
    in>>connections;
    return User(id,username,email,password,connections);
}


void wtf() {
    //DO NOT DELETE THIS FUNCTION!
    ofstream fout("users.txt");
    string line;
    while (getline(std::cin, line)) {
        if (line == "----") {
            break;
        }
        fout << line << endl;
    }
}

int main() {

    //DO NOT MODIFY THE MAIN FUNCTION, EXCEPT FOR EXCEPTION HANDLING WHERE NECESSARY!

    wtf();

    ifstream in("users.txt");
    if (!in) {
        cerr << "Cannot open users.txt!" << endl;
        return 1;
    }

    int testCase;
    cin >> testCase;
    cin.ignore();

    if (testCase == 1) {
        User u = readUser(in);
        cout << u << endl;
    } else if (testCase == 2) {
        User u = readUser(in);
        cout << u << endl;
        cout << ++u << endl;
        cout << u << endl;
    } else if (testCase == 3) {
        User u = readUser(in);
        string queryUsername;
        getline(cin, queryUsername);
        if (u == queryUsername) {
            cout << "Usernames match!" << endl;
        } else {
            cout << "Usernames do not match." << endl;
        }
    } else if (testCase == 4) {
        UserSystem system;
        while (in) {
            User u = readUser(in);
            if (!in) break;
            system += u;
        }
        cout << system;
    } else if (testCase == 5) {
        UserSystem system;
        while (in) {
            User u = readUser(in);
            if (!in) break;
            system += u;
        }
        string searchUsername;
        getline(cin, searchUsername);
        try {
            User &u = system[searchUsername];
            cout << u << endl;
        } catch (UserNotFoundException &e) {
            e.print();
        }

    } else if (testCase == 6) {
        UserSystem system;
        while (in) {
            User u = readUser(in);
            if (!in) break;
            system += u;
        }
        try {
            string searchUsername;
            getline(cin, searchUsername);
            cout << system[searchUsername] << endl;
            ++system[searchUsername];
            cout << system[searchUsername] << endl;
        }catch (UserNotFoundException &e) {
            e.print();
        }

    } else if (testCase == 7) {
        UserSystem system;
        while (in) {
            User u = readUser(in);
            if (!in) break;
            system += u;
        }
        string domain;
        getline(cin, domain);
        UserSystem filtered = system.filterByEmailDomain(domain);
        cout << filtered;
    } else if (testCase == 8) {
        UserSystem system;
        while (in) {
            User u = readUser(in);
            if (!in) break;
            system += u;
        }

        cout << "Original system:\n";
        cout << system;

        UserSystem copy = system;  // <-- copy constructor

        cout << "\nCopied system:\n";
        cout << copy;

        UserSystem assigned;
        assigned = system;

        cout << "\nUser system with operator =:\n";
        cout << copy;
    }


    in.close();
    return 0;
}
