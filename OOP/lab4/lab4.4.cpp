//
// Created by cactus on 01/04/2026.
//
#include <cstring>
#include <iostream>
using namespace std;

class Ingredient {
private:
    char *name;
    int quantity;
    int calories;
public:
    Ingredient(const char *name="", int quantity=0, int calories=0) {
        this->name = new char[strlen(name)+1];
        strcpy(this->name,name);
        this->quantity=quantity;
        this->calories=calories;
    }
    ~Ingredient() {
        delete [] name;
    }
    Ingredient (const Ingredient &other) {
        this->name = new char[strlen(other.name)+1];
        strcpy(this->name,other.name);
        this->quantity=other.quantity;
        this->calories=other.calories;
    }
    Ingredient &operator=(const Ingredient &other) {
        if (this==&other) {
            return *this;
        }
        delete [] name;
        this->name = new char[strlen(other.name)+1];
        strcpy(this->name,other.name);
        this->quantity=other.quantity;
        this->calories=other.calories;
        return *this;
    }
    int getTotalCalories() const {
        return quantity * calories;
    }
    friend ostream &operator<<(ostream &os, const Ingredient &ing) {
        os << ing.name<<": "<<ing.quantity<<"g/ml";
        return os;
    }
    int getQuantity() const {
        return quantity;
    }
};

class Dish {
private:
    Ingredient *ingredients;
    char *dishName;
    int ingredientCount;
public:
    Dish(const char *dishName = "", Ingredient *ingredients = nullptr, int ingredientCount = 0) {
        this->dishName = new char[strlen(dishName) + 1];
        strcpy(this->dishName, dishName);
        this->ingredientCount = ingredientCount;
        this->ingredients = new Ingredient[ingredientCount];
        for (int i = 0; i < ingredientCount; i++) {
            this->ingredients[i] = ingredients[i];
        }
    }
    ~Dish() {
        delete [] ingredients;
        delete [] dishName;
    }
    Dish(const Dish &other) {
        this->dishName = new char[strlen(other.dishName)+1];
        strcpy(this->dishName,other.dishName);
        this->ingredientCount=other.ingredientCount;
        this->ingredients = new Ingredient[ingredientCount];
        for (int i = 0; i<ingredientCount; i++) {
            this->ingredients[i]=other.ingredients[i];
        }
    }
    Dish &operator=(const Dish &other) {
        if (this == &other) {
            return *this;
        }
        delete [] dishName;
        delete [] ingredients;
        this->dishName = new char[strlen(other.dishName)+1];
        strcpy(this->dishName,other.dishName);
        this->ingredientCount=other.ingredientCount;
        this->ingredients = new Ingredient[ingredientCount];
        for (int i = 0; i<ingredientCount; i++) {
            this->ingredients[i]=other.ingredients[i];
        }
        return *this;
    }
    int getTotalCalories() const {
        int totalCalories = 0;
        for (int i = 0; i<ingredientCount; i++) {
            totalCalories+=ingredients[i].getTotalCalories();
        }
        return totalCalories;
    }
    Dish &operator+=(const Ingredient &other) {
        Ingredient *ing = new Ingredient[ingredientCount+1];
        for (int i = 0; i<ingredientCount; i++) {
            ing[i]=ingredients[i];
        }
        delete [] ingredients;
        ing[ingredientCount]=other;
        ingredientCount++;
        ingredients=ing;
        return *this;
    }
    Dish operator+(const Dish &other) {
        Dish result = other;
        for (int i = 0; i<ingredientCount;i++) {
            result+=ingredients[i];
        }
        return result;
    }
    bool operator==(const Dish &other) {
        return getTotalCalories()==other.getTotalCalories();
    }
    friend ostream &operator<<(ostream &os, const Dish &dish) {
        os<<"Dish: "<<dish.dishName<<'\n';
        for (int i = 0; i<dish.ingredientCount; i++) {
            os<<"- "<<dish.ingredients[i]<<'\n';
        }
        os<<"Total Calories: "<<dish.getTotalCalories()<<'\n';
        return os;
    }
};

int main() {

    char name [50];
    cin>>name;
    // Create Ingredients
    Ingredient tomato(name, 200, 20);
    cin>>name;
    Ingredient onion(name, 100, 30);
    cin>>name;
    Ingredient cheese(name, 50, 50);


    cin>>name;
    // Create Dishes
    Dish salad(name);
    salad += tomato;
    salad += onion;

    cin>>name;
    Dish pizza(name);
    pizza += tomato;
    pizza += cheese;

    // Test + operator
    Dish combinedDish = salad + pizza;
    cout<<combinedDish;

    cout<<"---------------------"<<endl;

    //Test = operator
    Ingredient ingredient = tomato;
    cout<<ingredient;
    cout<<endl;

    cout<<"---------------------"<<endl;

    // Test == operator
    if (salad == pizza) {
        cout << "Salad and Pizza have the same calories." << endl;
    } else {
        cout << "Salad and Pizza do not have the same calories." << endl;
    }

    cout<<"---------------------"<<endl;

    //Test << operator
    cout << "Salad:" << endl;
    cout << salad;

    cout << "Pizza:" << endl;
    cout << pizza;

    return 0;
}