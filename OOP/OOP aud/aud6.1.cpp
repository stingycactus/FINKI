//
// Created by cactus on 4/20/2026.
//
#include <iostream>
using namespace std;

class TennisPlayer {
private:
    string name;
    string surname;
    bool playsInLeague;

public:
    TennisPlayer(const string &name = "", const string &surname = "", bool playsInLeague = false) {
        this->name = name;
        this->surname = surname;
        this->playsInLeague = playsInLeague;
    }
    friend ostream &operator<<(ostream &os, const TennisPlayer &player) {
        os << player.name << " " << player.surname << " " << player.playsInLeague<<'\n';
        return os;
    }
};

class RankedTennisPlayer : public TennisPlayer {
private:
    int rank;
public:
    RankedTennisPlayer(const string &name = "", const string &surname = "", bool playsInLeague = false, int rank=0)
    : TennisPlayer(name, surname, playsInLeague), rank(rank) {}
    RankedTennisPlayer(const TennisPlayer &player, int rank) : TennisPlayer(player), rank(rank) {}
    friend ostream &operator<<(ostream &os, const RankedTennisPlayer &player) {
        const TennisPlayer &p = player;
        os<<p<<player.rank<<'\n';
        return os;
    }
};

int main() {
    TennisPlayer rf("Roger", "Federer");
    TennisPlayer ng("Novak", "Djokovikj");
    cout << rf;
    cout << ng;
    //TennisPlayer t;
    RankedTennisPlayer rn("Rafael", "Nadal", true, 2750);
    cout << rn;
    TennisPlayer tp = rn;
    cout << tp;
    //RankedTennisPlayer copy(tp);
    RankedTennisPlayer copy(ng, 3320);
    cout << copy;
    return 0;
}
