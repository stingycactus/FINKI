//
// Created by cactus on 5/20/2026.
//
#include<iostream>
#include<string.h>
using namespace std;
class Cinema {
protected:
    string name;
    int hallNumber;
    static float studentDiscount;
    float ticketPrice;
public:
    Cinema(const string &name="", int hallNumber=0, float ticketPrice=0)
    : name(name), hallNumber(hallNumber), ticketPrice(ticketPrice) {}
    static float getStudentDiscount() {
        return studentDiscount/100.0;
    }
    static void setStudentDiscount(float newDiscount) {
        studentDiscount=newDiscount*100.0;
    }
    virtual float price(bool isStudent) {
        return ticketPrice - (ticketPrice * isStudent * (studentDiscount/100.0));
    }
    string getName() const {
        return name;
    }
};
float Cinema::studentDiscount=17;

class ThreeDCinema : public Cinema {
private:
    char *movie;
    float duration;
    bool premiere;
public:
    ThreeDCinema(const string &name="", int hallNumber=0, float ticketPrice=0, const char *movie="", float duration=0, bool premiere=false)
    : Cinema(name,hallNumber,ticketPrice) {
        this->movie=new char[strlen(movie)+1];
        strcpy(this->movie, movie);
        this->duration=duration;
        this->premiere=premiere;
    }
    float price(bool isStudent) {
        return Cinema::price(isStudent) + 50 * (duration>2.5) + 20 * (duration>3) + 60 * premiere;
    }
};

bool searchCinema (Cinema ** c, int n, char * title, bool premiere, bool isStudent) {
    for (int i = 0; i < n; i++) {
        if (premiere) {
            if (dynamic_cast<ThreeDCinema *>(c[i])) {
                if (c[i]->getName()==title) {
                    cout<<title<<" "<<c[i]->price(isStudent)<<'\n';
                    return true;
                }
            }
        }
        else {
            if (c[i]->getName()==title) {
                cout<<title<<" "<<c[i]->price(isStudent)<<'\n';
                return true;
            }
        }
    }
    return false;
}

void cheapestCinema(Cinema ** halls, int n,bool isStudent) {
    int index=0;
    int threeDCount=0;
    int count=0;
    for (int i = 0; i < n; i++) {
        if (halls[i]->price(isStudent)<halls[index]->price(isStudent)) {
            index=i;
        }
        if (dynamic_cast<ThreeDCinema *>(halls[i])) {
            threeDCount++;
        }
        count++;
    }
    cout<<"Cheapest movie hall: "<<halls[index]->getName()<<" "<<halls[index]->price(isStudent)<<'\n';
    cout<<"3D cinema halls: "<<threeDCount<<" from total "<<count<<'\n';
}
int main(){

    int tip,n;
    char name[100], movieName[40];
    int no;
    bool premiere;
    float ticketPrice;
    float hours;
    bool isStudent;

        cin>>tip;
        if (tip==1){//Cinema
        	cin>>name>>no>>ticketPrice;
        	Cinema k1(name,no,ticketPrice);
        	cout<<"Cinema created with name: "<<k1.getName()<<endl;
        }
        else if (tip==2){//price - Cinema
            cin>>name>>no>>ticketPrice>>isStudent;
        	Cinema k1(name,no,ticketPrice);
        	cout<<"Initial price for the cinema with name "<<k1.getName()<< " is: " <<k1.price(isStudent)<<endl;
        }
        else if (tip==3){//3D Cinema
            cin>>name>>no>>ticketPrice>>movieName>>hours>>premiere;
            ThreeDCinema s(name,no,ticketPrice,movieName,hours,premiere);
            cout<<"Cinema created with name "<<s.getName()<<" and discount "<<s.getStudentDiscount()<<endl;
        }
        else if (tip==4){//price - 3DCinema
             cin>>name>>no>>ticketPrice>>movieName>>hours>>premiere>>isStudent;
             ThreeDCinema s(name,no,ticketPrice,movieName,hours,premiere);
             cout<<"The price for the cinema "<<s.getName()<<" is: "<<s.price(isStudent)<<endl;
        }
        else if (tip==5) {//cheapest Cinema
            Cinema ** halls = new Cinema *[5];
            int n;
            halls[0] = new Cinema("Cineplexx1",1,350);
            halls[1] = new ThreeDCinema("Milenium3D",44,285,"Shrek",2.5,false);
            halls[2] = new ThreeDCinema("Vardar",12,333,"StarWars",4,true);
            halls[2] = new ThreeDCinema("Home",44,299,"Godfather",5,false);
            halls[3] = new Cinema("Cineplexx2",2,333);
            halls[4] = new ThreeDCinema("Cinedays",1,310,"ManInBlack",5,true);
        	cheapestCinema(halls,5,true);
        }
        else if (tip==6){//search
        	Cinema ** halls = new Cinema *[5];
            halls[0] = new Cinema("Cineplexx1",1,350);
            halls[1] = new ThreeDCinema("Milenium3D",44,285,"Shrek",2.5,false);
            halls[2] = new ThreeDCinema("Vardar",12,333,"StarWars",4,true);
            halls[3] = new Cinema("Cineplexx2",2,333);
            halls[4] = new ThreeDCinema("Cinedays",1,310,"ManInBlack",5,true);

        	if(searchCinema(halls,5, "Milenium3D",true,true))
                cout<<"Found"<<endl;
            else cout<<"Not found"<<endl;

            if(searchCinema(halls,5, "CinePlexx1",false,false))
                cout<<"Found"<<endl;
            else cout<<"Not found"<<endl;

        }
        else if (tip==7){//change price
            Cinema ** halls = new Cinema *[5];
        	halls[0] = new Cinema("Cineplexx1",1,350);
            halls[1] = new ThreeDCinema("Milenium3D",44,285,"Shrek",2.5,false);
            halls[2] = new ThreeDCinema("Vardar",12,333,"StarWars",4,true);
            halls[2] = new ThreeDCinema("Domasno",44,299,"Godfather",5,false);
            halls[3] = new Cinema("Cineplexx2",2,333);
            halls[4] = new ThreeDCinema("Cinedays",1,310,"ManInBlack",5,true);
            halls[2] -> setStudentDiscount(0.9);
        	cheapestCinema(halls,4,true);
        }

    return 0;
}
