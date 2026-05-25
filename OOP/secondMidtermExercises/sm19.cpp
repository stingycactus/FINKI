//
// Created by cactus on 5/20/2026.
//
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

class RatingMissingException {
public:
    void print() {
        cout<<"Rating Missing Exception"<<'\n';
    }
};

class Person {
private:
    string name;
    int year;
public:
    Person(const string &name="", int year=0) : name(name), year(year) {}
    string getName() const {
        return name;
    }
    int getYear() const {
        return year;
    }
};

class Song {
protected:
    string name;
    Person performers[10];
    int n;
    int *ratings;
    int raters;
public:
    Song(const string &name="", Person *performers=nullptr, int n=0, int *ratings=nullptr, int raters=0) {
        this->name = name;
        this->n=n;
        this->raters=raters;
        for (int i = 0; i<n; i++) {
            this->performers[i]=performers[i];
        }
        this->ratings = new int [raters];
        for (int i = 0; i<raters; i++) {
            this->ratings[i]=ratings[i];
        }
    }
    virtual ~Song() {
        delete [] ratings;
    }
    Song(const Song &other) {
        this->name = other.name;
        this->n=other.n;
        this->raters=other.raters;
        for (int i = 0; i<n; i++) {
            this->performers[i]=other.performers[i];
        }
        this->ratings = new int [raters];
        for (int i = 0; i<raters; i++) {
            this->ratings[i]=other.ratings[i];
        }
    }
    Song &operator=(const Song &other) {
        if (this!=&other) {
            this->name = other.name;
            this->n=other.n;
            this->raters=other.raters;
            for (int i = 0; i<n; i++) {
                this->performers[i]=other.performers[i];
            }
            delete [] ratings;
            this->ratings = new int [raters];
            for (int i = 0; i<raters; i++) {
                this->ratings[i]=other.ratings[i];
            }
        }
        return *this;
    }
    virtual float getTotalRating() const {
        if (raters==0) {
            throw RatingMissingException();
        }
        int minRating=10;
        int maxRating=0;
        for (int i = 0; i<raters; i++) {
            minRating = min(minRating, ratings[i]);
            maxRating = max(maxRating, ratings[i]);
        }
        return (maxRating+minRating)/2.0f;
    }
    virtual void print() const {
        for (int i = 0; i<n; i++) {
            cout<<performers[i].getName()<<" ("<<performers[i].getYear()<<")";
            if (i!=n-1) {
                cout<<",";
            }
        }
        cout<<" : "<<name<<'\n';
    }
    int getRaters() const {
        return raters;
    }
    int getN() const {
        return n;
    }
    Person getPerson(int index) {
        return performers[index];
    }
};

class Movie {
protected:
    char *info;
    int popularity;
public:
    Movie(const char *info="", int popularity=0) {
        this->info = new char[strlen(info)+1];
        strcpy(this->info, info);
        this->popularity = popularity;
    }
    virtual ~Movie() {
        delete [] info;
    }
    Movie(const Movie &other) {
        this->info = new char[strlen(other.info)+1];
        strcpy(this->info, other.info);
        this->popularity = other.popularity;
    }
    Movie &operator=(const Movie &other) {
        if (this!=&other) {
            delete [] info;
            this->info = new char[strlen(other.info)+1];
            strcpy(this->info, other.info);
            this->popularity = other.popularity;
        }
        return *this;
    }
};

class MovieSong : public Song, public Movie {
private:
    int songPopularity;
public:
    MovieSong(const string &name="", Person *performers=nullptr, int n=0, int *ratings=nullptr, int raters=0,const char *info="", int popularity=0, int songPopularity=0)
    : Song(name,performers,n,ratings,raters), Movie(info, popularity),songPopularity(songPopularity) {}
    float getTotalRating() const {
        if (raters==0) {
            throw RatingMissingException();
        }
        int minRating=10;
        int maxRating=0;
        for (int i = 0; i<raters; i++) {
            minRating = min(minRating, ratings[i]);
            maxRating = max(maxRating, ratings[i]);
        }
        float ratingAverage = (maxRating + minRating) / 2.0;
        float songAverage = static_cast<float>(songPopularity) / popularity;
        return songAverage * ratingAverage;
    }
    void print() const {
        for (int i = 0; i<n; i++) {
            cout<<performers[i].getName()<<" ("<<performers[i].getYear()<<")";
            if (i!=n-1) {
                cout<<",";
            }
        }
        cout<<":"<<name<<'\n';
        cout<<"Movie:"<<Movie::info<<'\n';
    }
    int getRaters() const {
        return raters;
    }
};

double averageRating(Song** songs, int n) {
    float totalRating = 0;
    int count=0;
    for (int i = 0; i<n; i++) {
        if (dynamic_cast<MovieSong*>(songs[i])) {
            if (songs[i]->getRaters()==0) {
                totalRating+=5;
                count++;
            }
            else {
                totalRating += songs[i]->getTotalRating();
                count++;
            }
        }
    }
    return totalRating/count;
}

void printSongs(char* performer, Song** songs, int n) {
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<songs[i]->getN(); j++) {
            if (songs[i]->getPerson(j).getName()==performer) {
                songs[i]->print();
                break;
            }
        }
    }
}

// main had bug, title and info were in 1 variable

