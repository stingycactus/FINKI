//
// Created by cactus on 4/20/2026.
//

#include <cstring>
#include <iostream>
using namespace std;

class NBAPlayer {
private:
    char *name;
    string team;
    double avgPts;
    double avgAssists;
    double avgRebounds;

public:
    NBAPlayer(const char *name = "", const string &team = "", double avgPts = 0, double avgAssists = 0,
              double avgRebounds = 0) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->team = team;
        this->avgPts = avgPts;
        this->avgAssists = avgAssists;
        this->avgRebounds = avgRebounds;
    };

    NBAPlayer(const NBAPlayer &other) {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        this->team = other.team;
        this->avgPts = other.avgPts;
        this->avgAssists = other.avgAssists;
        this->avgRebounds = other.avgRebounds;
    }

    NBAPlayer &operator=(const NBAPlayer &other) {
        if (this != &other) {
            delete [] this->name;
            this->name = new char[strlen(other.name) + 1];
            strcpy(this->name, other.name);
            this->team = other.team;
            this->avgPts = other.avgPts;
            this->avgAssists = other.avgAssists;
            this->avgRebounds = other.avgRebounds;
        }
        return *this;
    }

    ~NBAPlayer() {
        delete [] this->name;
    }

    double rating() {
        return (0.45 * avgPts + 0.3 * avgAssists + 0.25 * avgRebounds);
    }

    void print() {
        cout << name << " - " << team << '\n';
        cout << "Points: " << avgPts << '\n';
        cout << "Assists: " << avgAssists << '\n';
        cout << "Rebounds: " << avgRebounds << '\n';
        cout << "Rating: " << rating() << '\n';
    }
};

class AllStarPlayer : public NBAPlayer {
private:
    double avgAllStarPts;
    double avgAllStarAssists;
    double avgAllStarRebounds;

public:
    AllStarPlayer(const char *name = "", const string &team = "", double avgPts = 0,
    double avgAssists = 0, double avgRebounds = 0,
    double avgAllStarPts = 0, double avgAllStarAssists = 0, double avgAllStarRebounds = 0)
    : NBAPlayer(name, team, avgPts, avgAssists, avgRebounds) {
        this->avgAllStarPts = avgAllStarPts;
        this->avgAllStarAssists = avgAllStarAssists;
        this->avgAllStarRebounds = avgAllStarRebounds;
    }
    AllStarPlayer(const NBAPlayer &player, double avgAllStarPts=0, double avgAllStarAssists=0, double avgAllStarRebounds=0) : NBAPlayer(player) {
        this->avgAllStarPts = avgAllStarPts;
        this->avgAllStarAssists = avgAllStarAssists;
        this->avgAllStarRebounds = avgAllStarRebounds;
    }
    AllStarPlayer(const AllStarPlayer &other) : NBAPlayer(other) {
        this->avgAllStarPts = other.avgAllStarPts;
        this->avgAllStarAssists = other.avgAllStarAssists;
        this->avgAllStarRebounds = other.avgAllStarRebounds;
    }
    AllStarPlayer &operator=(const AllStarPlayer &other) {
        if (this != &other) {
            NBAPlayer::operator=(other);
            this->avgAllStarPts = other.avgAllStarPts;
            this->avgAllStarAssists = other.avgAllStarAssists;
            this->avgAllStarRebounds = other.avgAllStarRebounds;
        }
        return *this;
    }
    double allStarRating() {
        return (0.3*avgAllStarPts + 0.4*avgAllStarAssists+0.3*avgAllStarRebounds);
    }
    double rating() {
        return ((NBAPlayer::rating()+allStarRating())/2);
    }
    void print() {
        NBAPlayer::print();
        cout<<"All Star Rating: "<<allStarRating()<<'\n';
        cout<<"New Rating: "<<rating()<<'\n';
    }
};

int main() {
    return 0;
}
