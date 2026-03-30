//
// Created by cactus on 30/03/2026.
//
#include <cstring>
#include <iostream>
class ComputerGame;
using namespace std;
class Player {
private:
    char name[16];
    int currentLevel;
    int pts;
public:
    Player(const char *name = "", int currentLevel=0, int pts = 0) {
        strcpy(this->name,name);
        this->currentLevel=currentLevel;
        this->pts=pts;
    }
    friend void bestPlayer(ComputerGame *array, int n);
};
class ComputerGame {
private:
    char game[21];
    Player players[30];
    int numberOfPlayers;
public:
    ComputerGame(const char *game = "", Player *players=nullptr, int numberOfPlayers=0) {
        strcpy(this->game,game);
        this->numberOfPlayers=numberOfPlayers;
        for (int i = 0; i<numberOfPlayers; i++) {
            this->players[i]=players[i];
        }
    }
    friend void bestPlayer(ComputerGame *array, int n);
};
void bestPlayer(ComputerGame *array, int n) {
    ComputerGame mostPopular = array[0];
    for (int i = 1; i<n; i++) {
        if (array[i].numberOfPlayers>mostPopular.numberOfPlayers) {
            mostPopular=array[i];
        }
    }
    Player bestPlayer = mostPopular.players[0];
    for (int i = 1;i<mostPopular.numberOfPlayers;i++) {
        if (mostPopular.players[i].pts>bestPlayer.pts) {
            bestPlayer=mostPopular.players[i];
        }
        if (mostPopular.players[i].pts==bestPlayer.pts) {
            if (mostPopular.players[i].currentLevel>bestPlayer.currentLevel) {
                bestPlayer=mostPopular.players[i];
            }
        }
    }
    cout<<"Najdobar igrac e igracot so korisnicko ime "<<bestPlayer.name<<" koj ja igra igrata "<<mostPopular.game<<'\n';
}
int main() {
    int n;
    cin>>n;
    ComputerGame Games[50];
    for (int i = 0; i<n; i++) {
        char gameName[21];
        cin>>gameName;
        int numberOfPlayers;
        cin>>numberOfPlayers;
        Player players[30];
        for (int j = 0; j<numberOfPlayers; j++) {
            char playerName[31];
            int level;
            int pts;
            cin>>playerName>>level>>pts;
            players[j]=Player(playerName, level, pts);
        }
        Games[i]=ComputerGame(gameName,players,numberOfPlayers);
    }
    bestPlayer(Games,n);
    return 0;
}