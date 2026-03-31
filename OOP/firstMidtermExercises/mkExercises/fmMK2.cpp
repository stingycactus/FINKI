//
// Created by cactus on 31/03/2026.
//
#include <algorithm>
#include <iostream>
using namespace std;
class List {
private:
    int *numbers;
    int size;
    int capacity;
public:
    List(int *numbers=nullptr, int size=0) {
        this->size=size;
        this->capacity=size;
        this->numbers = new int[capacity];
        for (int i = 0; i<size; i++) {
            this->numbers[i]=numbers[i];
        }
    }
    ~List() {
        delete [] numbers;
    }
    List(const List &other) {
        this->size=other.size;
        this->capacity=other.capacity;
        this->numbers = new int[capacity];
        for (int i = 0; i<size; i++) {
            this->numbers[i]=other.numbers[i];
        }
    }
    List &operator=(const List &other) {
        if (this==&other) {
            return *this;
        }
        delete [] numbers;
        this->size=other.size;
        this->capacity=other.capacity;
        this->numbers = new int[capacity];
        for (int i = 0; i<size; i++) {
            this->numbers[i]=other.numbers[i];
        }
        return *this;
    }
    int sum() {
        int sumOfNumbers = 0;
        for (int i = 0; i<size; i++) {
            sumOfNumbers+=numbers[i];
        }
        return sumOfNumbers;
    }
    double average() {
        return double(sum())/size;
    }
    void pecati() {
        cout<<size<<": ";
        for (int i = 0; i<size; i++) {
            cout<<numbers[i] << " ";
        }
        cout<<"sum: "<<sum()<<" average: "<<average();
    }
    int getSize() {
        return size;
    }
};

class ListContainer {
private:
    List *lists;
    int size;
    int capacity;
    static int attempts;
public:
    ListContainer(int capacity=10) {
        lists = new List[capacity];
        this->size=0;
        this->capacity = capacity;
    }
    ~ListContainer() {
        delete [] lists;
    }
    ListContainer(const ListContainer &other) {
        this->capacity=other.capacity;
        this->size=other.size;
        this->lists=new List[capacity];
        for (int i = 0; i<size; i++) {
            this->lists[i]=other.lists[i];
        }
    }
    ListContainer &operator=(const ListContainer &other) {
        if (this == &other) {
            return *this;
        }
        delete [] lists;
        this->capacity=other.capacity;
        this->size=other.size;
        this->lists=new List[capacity];
        for (int i = 0; i<size; i++) {
            this->lists[i]=other.lists[i];
        }
        return *this;
    }
    void print() {
        if (size==0) {
            cout<<"The list is empty"<<'\n';
        }
        else {
            for (int i = 0; i<size; i++) {
                cout<<"List number: "<<i+1<<" List info: ";
                lists[i].pecati();
                cout<<'\n';
            }
            cout << "Sum: " << sum() << " Average: " << average() << '\n';
            cout << "Successful attempts: " << size << " Failed attempts: " << attempts << '\n';
        }
    }
    int sum() {
        int listsSum=0;
        for (int i = 0; i<size; i++) {
            listsSum+=lists[i].sum();
        }
        return listsSum;
    }
    double average() {
        int totalElements = 0;
        for (int i = 0; i < size; i++) {
            totalElements += lists[i].getSize();
        }
        return double(sum()) / totalElements;
    }
    void addNewList(List l) {
        int listSum = l.sum();
        bool uniqueSum = true;
        for (int i = 0; i<size; i++) {
            if (lists[i].sum()==listSum) {
                uniqueSum = false;
            }
        }
        if (uniqueSum) {
            lists[size]=l;
            size++;
        }
        else {
            attempts++;
        }
    }
};

int ListContainer::attempts=0;
int main() {

    ListContainer lc;
    int N;
    cin>>N;

    for (int i=0;i<N;i++) {
        int n;
        int niza[100];

        cin>>n;

        for (int j=0;j<n;j++){
            cin>>niza[j];

        }

        List l=List(niza,n);

        lc.addNewList(l);
    }


    int testCase;
    cin>>testCase;

    if (testCase==1) {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();

    }
    else {
        lc.print();
    }
}