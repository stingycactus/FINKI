//
// Created by cactus on 3/16/2026.
//
#include <iostream>
#include <string>
using namespace std;

class Team {
private:
    string name;
    int yearFounded;
    string city;

public:
    Team(string name = "", int yearFounded = 0, string city = "") {
        this->name = name;
        this->yearFounded = yearFounded;
        this->city = city;
    }

    string getName() {
        return name;
    }

    void printTeam() {
        cout << name << " " << yearFounded << " " << city << '\n';
    }
};

class Game {
    Team host;
    Team guest;
    int hostGoals;
    int guestGoals;

public:
    Game(Team host = Team(), Team guest = Team(), int hostGoals = 0, int guestGoals = 0) {
        this->host = host;
        this->guest = guest;
        this->hostGoals = hostGoals;
        this->guestGoals = guestGoals;
    }

    Team getHost() {
        return host;
    }

    Team getGuest() {
        return guest;
    }

    int getHostGoals() {
        return hostGoals;
    }

    int getGuestGoals() {
        return guestGoals;
    }
};

bool rematch(Game &game1, Game &game2) {
    if (game1.getHost().getName() == game2.getGuest().getName() && game1.getGuest().getName() == game2.getHost().
        getName()) {
        return true;
    }
    return false;
}

Team winner(Game game1, Game game2) {
    if (rematch(game1, game2)) {
        int totalHostGoals = game1.getHostGoals() + game2.getGuestGoals();
        int totalGuestGoals = game1.getGuestGoals() + game2.getHostGoals();
        if (totalHostGoals > totalGuestGoals) {
            return game1.getHost();
        } else {
            return game2.getGuest();
        }
    }
}

int main() {
    Team t1("Barcelona", 1900, "Barcelona");
    Team t2("Real Madrid", 1890, "Madrid");
    Team t3("Elche", 1950, "Elche");
    Game g1(t1, t2, 5, 0);
    Game g2(t2, t1, 2, 2);
    Game g3(t1, t3, 6, 2);
    Team w = winner(g1, g2);
    w.printTeam();
    return 0;
}
