//
// Created by cactus on 5/23/2026.
//
#include<iostream>
#include<cstring>
using namespace std;

class InvestmentFund;

class InvestmentPlan {
private:
    string investor;
    float sum;
    float shares;
    bool currentDay;
public:
    InvestmentPlan(const string &investor="", float sum=0, float shares=0, bool currentDay=false)
    : investor(investor), sum(sum), shares(shares), currentDay(currentDay) {}
    friend class InvestmentFund;
};

class InvestmentFund {
protected:
    string name;
    InvestmentPlan *plans;
    int n;
    float sharePrice;
public:
    InvestmentFund(const string &name="", const InvestmentPlan *plans = nullptr, int n=0, float sharePrice=0) {
        this->name = name;
        this->n=n;
        this->sharePrice=sharePrice;
        this->plans = new InvestmentPlan[n];
        for (int i = 0;i < n; i++) {
            this->plans[i]=plans[i];
        }
    }
    ~InvestmentFund() {
        delete [] plans;
    }
    InvestmentFund(const InvestmentFund &other) {
        this->name = other.name;
        this->n=other.n;
        this->sharePrice=other.sharePrice;
        this->plans = new InvestmentPlan[n];
        for (int i = 0;i < n; i++) {
            this->plans[i]=other.plans[i];
        }
    }
    InvestmentFund &operator=(const InvestmentFund &other) {
        if (this != &other) {
            this->name = other.name;
            this->n=other.n;
            this->sharePrice=other.sharePrice;
            delete [] plans;
            this->plans = new InvestmentPlan[n];
            for (int i = 0;i < n; i++) {
                this->plans[i]=other.plans[i];
            }
        }
        return *this;
    }
    virtual double profit() const = 0;
    double totalSumOfInvestments() const {
        float totalSum=0;
        for (int i = 0; i<n; i++) {
            totalSum+=plans[i].shares * sharePrice;
        }
        return totalSum;
    }
    double totalNewPlanCost() const {
        float totalCost = 0;
        for (int i = 0; i<n; i++) {
            totalCost+=plans[i].sum * plans[i].currentDay;
        }
        return totalCost;
    }
};

class MoneyFund : public InvestmentFund {
private:
    static float yearlyProvisions;
public:
    MoneyFund(const string &name="", const InvestmentPlan *plans = nullptr, int n=0, float sharePrice=0)
    : InvestmentFund(name, plans,n,sharePrice) {}
    double profit() const override {
        return (totalSumOfInvestments() * yearlyProvisions / 100) / 365;
    }
};

float MoneyFund::yearlyProvisions = 1;

class ActionFund : public InvestmentFund {
private:
    static float yearlyProvisions;
    static float entryProvisions;
public:
    ActionFund(const string &name="", const InvestmentPlan *plans = nullptr, int n=0, float sharePrice=0)
    : InvestmentFund(name, plans,n,sharePrice) {}
    double profit() const override {
        return (totalSumOfInvestments() * yearlyProvisions / 100) / 365 +  totalNewPlanCost() * entryProvisions / 100;
    }
};

double totalProfit(InvestmentFund* funds[], int n) {
    float total=0;
    for (int i = 0; i<n; i++) {
        total+=funds[i]->profit();
    }
    return total;
}

float ActionFund::yearlyProvisions = 1.5;
float ActionFund::entryProvisions = 3;

int main(){

    char investitor[80], ime[50];
    double plan, brUdeli, udel;
    bool flag = false;
    int n, m;
    cin >> n;
    InvestmentFund **fondovi = new InvestmentFund*[n];
    for(int i = 0; i < n; i++){
        cin >> ime;
        cin >> m;
        InvestmentPlan *ip = new InvestmentPlan[m];
        for(int j = 0; j < m; j++){
            cin >> investitor >> plan >> brUdeli;
            if(j % 2) flag = true;
            else flag = false;
            InvestmentPlan IP(investitor, plan, brUdeli, flag);
            ip[j] = IP;
        }
        cin >> udel;
        if(i % 2){
            fondovi[i] = new ActionFund(ime, ip, m, udel);

        }
        else{
            fondovi[i] = new MoneyFund(ime, ip, m, udel);
        }
    }
    cout << totalProfit(fondovi, n);
    return 0;
}
