//
// Created by cactus on 01/04/2026.
//
#include <iostream>
#include <cstring>
using namespace std;

class Goal {
private:
    char *scorer;
    int time;
    char team[50];
public:
    Goal (const char *scorer = "", int time = 0, const char *team = "") {
        this->scorer=new char[strlen(scorer)+1];
        strcpy(this->scorer,scorer);
        this->time=time;
        strcpy(this->team,team);
    }
    ~Goal() {
        delete [] scorer;
    }
    Goal (const Goal &other) {
        this->scorer=new char[strlen(other.scorer)+1];
        strcpy(this->scorer,other.scorer);
        this->time=other.time;
        strcpy(this->team,other.team);
    }
    Goal &operator= (const Goal &other) {
        delete [] scorer;
        this->scorer=new char[strlen(other.scorer)+1];
        strcpy(this->scorer,other.scorer);
        this->time=other.time;
        strcpy(this->team,other.team);
        return *this;
    }
    friend ostream &operator<<(ostream &os,const Goal &goal) {
        os<<goal.time<<" "<<goal.scorer<<'\n';
        return os;
    }
    Goal operator++(int){
        Goal temp = *this;
        time++;
        return temp;
    }
    Goal &operator--() {
        time--;
        return *this;
    }
    char *getTeam() {
        return team;
    }
};

class InvalidTeamName {
    char name[100];
public:
    InvalidTeamName(const char *name) {
        strcpy(this->name, name);
    }
    char *what() {
        return name;
    }
};

class Game {
private:
    Goal *goals;
    char team1[51];
    char team2[51];
    int n;
public:
    Game (const char *team1="", const char *team2="") {
        strcpy(this->team1,team1);
        strcpy(this->team2,team2);
        goals = new Goal[0];
        n = 0;
    }
    ~Game() {
        delete [] goals;
    }
    Game (const Game &other) {
        strcpy(this->team1,other.team1);
        strcpy(this->team2,other.team2);
        n = other.n;
        goals = new Goal[n];
    }
    Game &operator+=(Goal &goal) {
        if (strcmp(goal.getTeam(),team1) != 0 && strcmp(goal.getTeam(),team2) != 0) {
            throw InvalidTeamName(goal.getTeam());
        }
        Goal *temp = new Goal[n+1];
        for (int i = 0; i<n; i++) {
            temp[i]=goals[i];
        }
        delete [] goals;
        goals=temp;
        goals[n]=goal;
        n++;
        return *this;
    }
    friend ostream &operator<<(ostream &os,const Game &g) {
        os<<g.team1<<" - "<<g.team2<<'\n';
        for (int i = 0; i<g.n; i++) {
            os<<g.goals[i];
        }
        return os;
    }
};

int main() {
    char team1[50];
    char team2[50];
    cin >> team1;
    cin >> team2;
    Game n(team1, team2);
    int x;
    cin >> x;
    char player[100];
    int m;
    for(int i = 0; i < x; ++i) {
        cin >> player;
        cin >> m;
        cin >> team1;
        Goal g(player, m, team1);
        try {
            n += g;
        } catch(InvalidTeamName &e) {
            cout << "Invalid team name: " << e.what() << endl;
        }
    }
    cout << n << endl;
    return 0;
}