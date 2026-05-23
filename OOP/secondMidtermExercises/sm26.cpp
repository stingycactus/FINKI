//
// Created by cactus on 5/23/2026.
//
#include<iostream>
#include<string>
using namespace std;

class InvalidTimeException {
private:
    string text;
public:
    InvalidTimeException(const string &text="InvalidTimeException") {
        this->text = text;
    }
    void print() {
        cout<<text<<'\n';
    }
};

class Race {
protected:
    string city;
    int year;
    int month;
    float bestTime;
    float length;
public:
    Race(const string &city="", int year=0, int month=0, float bestTime=0, float length=0)
    : city(city), year(year), month(month), bestTime(bestTime), length(length) {}
    virtual float complexity() const {
        return bestTime/length;
    }
    friend ostream &operator<<(ostream &os, const Race &r) {
        os<<r.city<<" "<<r.month<<"."<<r.year<<" "<<r.complexity()<<'\n';
        return os;
    }
};

class MotoGPRace : public Race {
private:
    float *bestTimes;
    int n;
    int laps;
    static float coefficient;
public:
    MotoGPRace(const string &city="", int year=0, int month=0, float bestTime=0, float length=0, float *bestTimes=nullptr, int n=0, int laps=0)
    : Race(city,year,month,bestTime,length) {
        this->n=n;
        this->laps = laps;
        this->bestTimes = new float[n];
        for (int i = 0; i<n; i++) {
            this->bestTimes[i] = bestTimes[i];
        }
    }
    ~MotoGPRace() {
        delete[] this->bestTimes;
    }
    MotoGPRace(const MotoGPRace &other) : Race(other) {
        this->n = other.n;
        this->laps = other.laps;
        this->bestTimes = new float[n];
        for (int i = 0; i<n; i++) {
            this->bestTimes[i] = other.bestTimes[i];
        }
    }
    MotoGPRace &operator=(const MotoGPRace &other) {
        if (this != &other) {
            Race::operator=(other);
            delete [] this->bestTimes;
            this->n = other.n;
            this->laps = other.laps;
            this->bestTimes = new float[n];
            for (int i = 0; i<n; i++) {
                this->bestTimes[i] = other.bestTimes[i];
            }
        }
        return *this;
    }
    float complexity() const override {
        float bestTimesTotal = 0;
        for (int i = 0; i<n; i++) {
            bestTimesTotal += this->bestTimes[i]*coefficient;
        }
        float bestTimesAvg=bestTimesTotal/n;
        float total = Race::complexity()+bestTimesAvg;
        return total + total * 0.2 * (laps>22);
    }
    static void setK(float newCoefficient) {
        coefficient = newCoefficient;
    }
    void setNumberLaps(int newLaps) {
        laps=newLaps;
    }
    MotoGPRace &operator+=(float newTime) {
        if (newTime<9.5) {
            throw InvalidTimeException("Invalid Time");
        }
        float *temp = new float[n+1];
        for (int i = 0; i<n; i++) {
            temp[i] = this->bestTimes[i];
        }
        delete [] bestTimes;
        bestTimes=temp;
        bestTimes[n]=newTime;
        n++;
        return *this;
    }
    MotoGPRace operator++(int) {
        MotoGPRace temp = *this;
        laps++;
        return temp;
    }
    int getNumberLaps() const {
        return laps;
    }
};
float MotoGPRace::coefficient = 0.4;

int main(){
    int testCase;
    cin >> testCase;
    char city[50];
    int year;
    int month;
    float bestTime;
    float length;
    float bestTimes[50];
    int n;
    int m;
    int choice;
    int numberLaps;

    if (testCase == 1){
        cout << "===== Testing - classes ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        Race t(city, year, month, bestTime, length);
        cout<<t;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        cin>>numberLaps;
        cin>>n;
        for (int j = 0; j < n; j++)
            cin >> bestTimes[j];
        MotoGPRace mgt(city, year, month, bestTime, length,bestTimes, n, numberLaps);
        cout << mgt;
        MotoGPRace mgt2;
    }
    if (testCase == 2){
        cout << "===== Testing - operatorot += ======" << endl;
        Race **rArray;
        cin >> m;
        rArray = new Race *[m];
        for (int i = 0; i<m; i++){
            cin >> choice;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >>length;
            if (choice == 1){
                rArray[i] = new Race(city, year, month, bestTime, length);
            }
            else{
                cin>>numberLaps;
                cin>>n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                rArray[i] = new MotoGPRace(city, year, month, bestTime, length,bestTimes, n, numberLaps);
            }
        }
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];

        // add a new best time
        float best;
        cin >> best;
        int flag = 1;
        for (int i = 0; i < m; i++){
            MotoGPRace* nn = dynamic_cast<MotoGPRace*>(rArray[i]);
            if (nn != 0){
                flag = 0;
                (*nn) += best;
                break;
            }
        }

        // print the races
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
    }
    if (testCase == 3){
        cout << "===== Testing - exceptions ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        cin>>numberLaps;
        MotoGPRace mgt(city, year, month, bestTime, length);
        mgt.setNumberLaps(numberLaps);
        float time1,time2;
        cin>>time1>>time2;
        try {
            mgt+=time1;
            mgt+=time2;
        } catch (InvalidTimeException &e) {
            e.print();
        }
        cout<<mgt;
    }
    if (testCase == 4){
        cout <<"===== Testing - operator++ ======"<<endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        cin>>numberLaps;
        cin>>n;
        for (int j = 0; j < n; j++)
            cin >> bestTimes[j];

        MotoGPRace mgt(city, year, month, bestTime, length,bestTimes,n,numberLaps);
        float v,koef2;
        cout<<(mgt++).getNumberLaps()<<endl;
        cout<<mgt;
        mgt++;
        cout<<mgt;
    }
    if (testCase == 5){
        cout << "===== Testing - coefficient ======" << endl;
        Race **rArray;
        cin >> m;
        rArray = new Race *[m];
        for (int i = 0; i<m; i++){
            cin >> choice;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >>length;
            if (choice == 1){
                rArray[i] = new Race(city, year, month, bestTime, length);
            }
            else{
                cin>>numberLaps;
                cin>>n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                rArray[i] = new MotoGPRace(city, year, month, bestTime, length,bestTimes, n, numberLaps);
            }
        }
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];

        MotoGPRace::setK(0.7);
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
    }

    if (testCase == 6){
        cout << "===== Testing - full functionality ======" << endl;
        Race **rArray;
        cin >> m;
        rArray = new Race *[m];
        for (int i = 0; i<m; i++){
            cin >> choice;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >>length;
            if (choice == 1){
                rArray[i] = new Race(city, year, month, bestTime, length);
            }
            else{
                cin>>numberLaps;
                cin>>n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                rArray[i] = new MotoGPRace(city, year, month, bestTime, length,bestTimes, n, numberLaps);
            }
        }
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
        float newCoef;
        cin>>newCoef;
        MotoGPRace::setK(newCoef);
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
        // print the races
        float newBest;
        cin>>newBest;
        int flag = 1;
        for (int i = 0; i < m; i++){
            MotoGPRace * pok= dynamic_cast<MotoGPRace *>(rArray[i]);
            if(pok!=0)
            {
                (*pok)++;
                (*pok)+=newBest;
                if(flag==1)
                {
                    flag = 0;
                    try {
                        *pok+=1.4;
                    } catch (InvalidTimeException &e) {
                        e.print();
                    }

                }
            }
        }
        cout << "\nList of the races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
    }

    return 0;
}
