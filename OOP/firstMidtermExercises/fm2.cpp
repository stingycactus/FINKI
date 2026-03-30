//
// Created by cactus on 30/03/2026.
//
#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;

class FilmFestival;

class Film {
public:
    char title[100];
    int duration;
    float price;
    bool discount;

    Film() : duration(0), price(0), discount(false) { title[0] = '\0'; }

    void setFilm(const char* t, int d, float p, int disc) {
        strcpy(title, t);
        duration = d;
        price = p;
        discount = disc != 0;
    }

    string getTitle() { return title; }
    int getDuration() { return duration; }
    float getPrice() { return price; }

    friend void bestFestival(FilmFestival festivals[], int numberOfFestivals);
};

class FilmFestival {
public:
    char name[100];
    char place[100];
    Film films[100];
    int no;

    FilmFestival() : no(0) { name[0] = '\0'; place[0] = '\0'; }

    friend void print(FilmFestival& ff);
    friend void bestFestival(FilmFestival festivals[], int numberOfFestivals);
};

void print(FilmFestival& ff) {
    cout << ff.name << " " << ff.place << '\n';
    for (int i = 0; i < ff.no; i++) {
        cout<<fixed<<setprecision(2);
        cout << ff.films[i].title << " "
             << ff.films[i].duration << " "
             << ff.films[i].price << '\n';
    }
}

void bestFestival(FilmFestival festivals[], int numberOfFestivals) {
    FilmFestival best = festivals[0];
    int bestDiscountFilms = 0;
    int bestDuration = 0;

    for (int j = 0; j < festivals[0].no; j++) {
        if (festivals[0].films[j].discount) bestDiscountFilms++;
        bestDuration += festivals[0].films[j].duration;
    }

    for (int i = 1; i < numberOfFestivals; i++) {
        int filmsWithDiscount = 0, duration = 0;
        for (int j = 0; j < festivals[i].no; j++) {
            if (festivals[i].films[j].discount) filmsWithDiscount++;
            duration += festivals[i].films[j].duration;
        }
        if (filmsWithDiscount > bestDiscountFilms ||
           (filmsWithDiscount == bestDiscountFilms && duration > bestDuration)) {
            best = festivals[i];
            bestDiscountFilms = filmsWithDiscount;
            bestDuration = duration;
        }
    }
    cout << "Najdobar festival: " << best.name<<" "<<best.place;
}

int main() {
    int i, j, n;
    FilmFestival ff[50];

    cin >> n;

    for (i = 0; i < n; i++) {
        char festivalName[100];
        char festivalPlace[100];
        int numberOfFilms;

        /* name of the festival */
        cin >> festivalName;

        /* place it is held */
        cin >> festivalPlace;

        /* number of movies */
        cin >> numberOfFilms;

        strcpy(ff[i].name, festivalName);
        strcpy(ff[i].place, festivalPlace);
        ff[i].no = numberOfFilms;

        for (j = 0; j < ff[i].no; j++) {
            char filmName[100];
            int filmTime;
            float filmPrice;
            int filmDiscount;

            /* title of the movie */
            cin >> filmName;

            /* duration */
            cin >> filmTime;

            /* price */
            cin >> filmPrice;

            /* discount */
            cin >> filmDiscount;

            ff[i].films[j].setFilm(filmName, filmTime, filmPrice, filmDiscount);
        }
    }

    for (i = 0; i < n; ++i) {
        print(ff[i]);
    }

    bestFestival(ff, n);

    return 0;
}
