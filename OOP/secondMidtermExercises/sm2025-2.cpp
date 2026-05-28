//
// Created by cactus on 5/27/2026.
//
#include <iostream>
#include <cstring>
#include <fstream>


using namespace std;

class Song {
private:
    string title;
    string name;
    string performer;
    int duration;
public:
    Song(const string &title="", const string &name="", const string &performer="", int duration=0)
    : title(title), name(name), performer(performer), duration(duration) {}
    friend istream &operator>>(istream &is, Song &s) {
        getline(is, s.title);
        getline(is, s.name);
        getline(is, s.performer);
        is>>s.duration;
        is.ignore();
        return is;
    }
    void print(ofstream &out) {
        out<<"Song title: "<<title<<", Author: "<<name<<", Interpreted by: "<<performer<<", "<<duration<<" sek."<<'\n';
    }
    string getTitle() const {
        return title;
    }
    string getName() const {
        return name;
    }
    string getPerformer() const {
        return performer;
    }
    int getDuration() const {
        return duration;
    }
};

class Festival {
private:
    string name;
    string city;
    string date;
    Song *songs;
    int n;
public:
    Festival(const string &name="", const string &city="", const string &date="", Song *songs=nullptr, int n=0) {
        this->name=name;
        this->city=city;
        this->date=date;
        this->n=n;
        this->songs = new Song[n];
        for (int i = 0; i<n; i++) {
            this->songs[i]=songs[i];
        }
    }
    ~Festival() {
        delete [] this->songs;
    }
    Festival (const Festival &other) {
        this->name=other.name;
        this->city=other.city;
        this->date=other.date;
        this->n=other.n;
        this->songs = new Song[n];
        for (int i = 0; i<n; i++) {
            this->songs[i]=other.songs[i];
        }
    }
    Festival &operator=(const Festival &other) {
        if (this!=&other) {
            delete [] this->songs;
            this->name=other.name;
            this->city=other.city;
            this->date=other.date;
            this->n=other.n;
            this->songs = new Song[n];
            for (int i = 0; i<n; i++) {
                this->songs[i]=other.songs[i];
            }
        }
        return *this;
    }
    Festival &operator-=(const Song &song) {
        if (!n) {
            cout<<"Trying to delete from an empty list!"<<'\n';
            return *this;
        }
        int index = 0;
        for (int i = 0; i<n; i++) {
            if (songs[i].getName()!=song.getName()
                || songs[i].getTitle()!=song.getTitle()
                || songs[i].getPerformer() != song.getPerformer()
                || songs[i].getDuration() != song.getDuration()) {
                this->songs[index]=songs[i];
                index++;
            }
        }
        Song *temp=new Song[index];
        for (int i = 0; i<index; i++) {
            temp[i]=songs[i];
        }
        delete [] songs;
        songs=temp;
        n=index;
        return *this;
    }
    void print(ofstream& out) {
        out<<"Festival: "<<name<<" - "<<city<<", "<<date<<'\n';
        for (int i = 0; i<n; i++) {
            songs[i].print(out);
        }
    }
    friend istream &operator>>(istream &is, Festival &f) {
        getline(is, f.name);
        getline(is, f.city);
        getline(is, f.date);
        is>>f.n;
        f.songs = new Song[f.n];
        is.ignore();
        for (int i = 0; i<f.n; i++) {
            is>>f.songs[i];
        }
        return is;
    }
    Festival notFromAuthor(string author) {
        Festival copy = *this;
        if (!copy.n) {
            cout<<"Trying to delete from an empty list!"<<'\n';
            return *this;
        }
        for (int i = 0; i<copy.n; i++) {
            if (copy.songs[i].getName()==author) {
                copy-=copy.songs[i];
                i--;
            }
        }
        return copy;
    }
    string getName() const {
        return name;
    }
};

void wtf() {
    ofstream fout("vlezna.txt");
    string line;
    while (getline(std::cin, line)) {
        if (line == "----"){
            break;
        }
        fout << line << endl;
    }
}

void rff(string path) {
    ifstream fin(path);
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
}


int main() {

    wtf();
    Festival festival;
    //TODO your code here
    //TODO Read the data from the file and store them in `festival`
    ifstream fin("vlezna.txt");
    fin>>festival;


    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE NEXT COMMENT
    string author;
    getline(cin, author);
    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE PREVIOUS COMMENT

    //TODO Save the results in the files izlezna1.txt and izlezna2.txt after this line
    ofstream out1("izlezna1.txt");
    festival.print(out1);

    Festival filtered = festival.notFromAuthor(author);
    ofstream out2("izlezna2.txt");
    filtered.print(out2);
    out1.close();
    out2.close();
    //DO NOT MODIFY THE CODE BELLOW
    cout << "All the data for the festival:" << endl;
    rff("izlezna1.txt");
    cout << "Songs NOT from the author " << author << ": " << endl;
    rff("izlezna2.txt");


    return 0;
}