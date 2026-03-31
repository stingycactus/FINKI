//
// Created by cactus on 31/03/2026.
//
#include <cstring>
#include <iostream>
using namespace std;
enum tip {
	POP, RAP, ROK
};
class CD;
class Pesna {
private:
	char *name;
	int duration;
	tip genre;
public:
	Pesna(const char *name="", int duration=0, tip genre=tip(0)) {
		this->name=new char[strlen(name)+1];
		strcpy(this->name,name);
		this->duration=duration;
		this->genre=tip(genre);
	}
	~Pesna() {
		delete [] name;
	}
	Pesna(const Pesna &other) {
		this->name=new char[strlen(other.name)+1];
		strcpy(this->name,other.name);
		this->duration=other.duration;
		this->genre=tip(other.genre);
	}
	Pesna &operator=(const Pesna &other) {
		delete [] name;
		this->name=new char[strlen(other.name)+1];
		strcpy(this->name,other.name);
		this->duration=other.duration;
		this->genre=tip(other.genre);
		return *this;
	}
	void pecati() {
		cout<<"\""<<name<<"\""<<"-"<<duration<<"min"<<'\n';
	}
	friend class CD;

};

class CD {
private:
	Pesna pesni[10];
	int size;
	int maxDuration;
public:
	CD(int maxDuration=0, const Pesna *pesni=nullptr, int size = 0) {
		this->size=size;
		this->maxDuration=maxDuration;
		for (int i = 0; i<size; i++) {
			this->pesni[i]=pesni[i];
		}
	}
	void dodadiPesna (Pesna p) {
		int totalDuration = 0;
		for (int i = 0; i<size; i++) {
			totalDuration+=pesni[i].duration;
		}
		if ((totalDuration+p.duration)<maxDuration && size<10) {
			pesni[size]=p;
			size++;
		}
	}
	void pecatiPesniPoTip(tip t) {
		for (int i = 0; i<size; i++) {
			if (pesni[i].genre==t) {
				pesni[i].pecati();
			}
		}
	}
	Pesna getPesna(int i) {
		return pesni[i];
	}
	int getBroj() {
		return size;
	}
};

int main() {
	// se testira zadacata modularno
    int testCase;
    cin >> testCase;

	int n, minuti, kojtip;
	char ime[50];

	if(testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime,minuti,(tip)kojtip);
		p.pecati();
    } else if(testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        	for (int i=0; i<n; i++)
				(omileno.getPesna(i)).pecati();
	}
    else if(testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        	for (int i=0; i<omileno.getBroj(); i++)
				(omileno.getPesna(i)).pecati();
    }
    else if(testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }
    else if(testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }

return 0;
}