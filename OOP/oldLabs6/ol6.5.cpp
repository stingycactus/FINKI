//
// Created by cactus on 4/21/2026.
//
#include <iostream>
using namespace std;

class Team {
protected:
    string team;
    int losses;
    int wins;
public:
    Team(const string &team="", int losses=0, int wins=0) :
    team(team), losses(losses), wins(wins){}
    void print() {
        cout << "Team: " << team << '\n';
        cout << "Losses: " << losses << '\n';
        cout << "Wins: " << wins << '\n';
    }
};

class FootballTeam : public Team{
private:
    int redCards;
    int yellowCards;
    int draws;
public:
    FootballTeam(const string &team="", int losses=0, int wins=0, int redCards=0, int yellowCards=0, int draws=0) :
    Team(team, losses, wins), redCards(redCards), yellowCards(yellowCards), draws(draws) {}
    int totalPoints() {
        return(3*Team::wins + draws);
    }
    void print() {
        Team::print();
        cout << "RedCards: " << redCards << '\n';
        cout << "YellowCards: " << yellowCards << '\n';
        cout << "Draws: " << draws << '\n';
        cout<< "Total Points: " << totalPoints() << '\n';
    }
};