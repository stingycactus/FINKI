#include <iostream>
using namespace std;

class Camera {
protected:
    string manufacturer;
    string model;
    int year;
    float mp;

public:
    Camera(const string &manufacturer, const string &model, int year, float mp)
        : manufacturer(manufacturer), model(model), year(year), mp(mp) {
    }

    virtual ~Camera() = default;

    virtual float price() const = 0;
    virtual float rentalPrice(int days) const = 0;
    friend string mostExpensiveCamera (Camera* camera[], int n);
};

class PhotoCamera : public Camera {
private:
    bool supportsRAW;

public:
    PhotoCamera(const string &manufacturer, const string &model, int year, float mp, bool supportsRAW)
    : Camera(manufacturer, model, year, mp), supportsRAW(supportsRAW) {}

    float price() const {
        return 100 + mp * 20 + (50 * supportsRAW);
    }
    float rentalPrice(int days) const {
        return 0.01 * price() * days * (1.0 - 0.2 * (days > 7));
    }
    bool operator<(const PhotoCamera &other) {
        return price() < other.price();
    }
};

class VideoCamera : public Camera {
private:
    int maxLength;
public:
    VideoCamera(const string &manufacturer, const string &model, int year, float mp, int maxLength)
    : Camera(manufacturer, model, year, mp), maxLength(maxLength) {}

    float price() const {
        return mp * 80 * (1.0 + 0.4 * (maxLength > 60 * 60));
    }
    float rentalPrice(int days) const {
        return 0.01 * price() * days * (1.0 - 0.2 * (days > 7));
    }
    bool operator<(const VideoCamera &other) {
        return price() < other.price();
    }
};

class FilmCamera : public Camera {
private:
    int maxFPS;
public:
    FilmCamera(const string &manufacturer, const string &model, int year, float mp, int maxFPS)
    : Camera(manufacturer, model, year, mp), maxFPS(maxFPS) {}

    float price() const {
        return 50000 + 5000 * (maxFPS > 30) * (maxFPS - 30);
    }
    float rentalPrice(int days) const {
        return 500 * days * (1 + 1 * (maxFPS > 60));
    }
    bool operator<(const FilmCamera &other) {
        return price() < other.price();
    }
};

float production(Camera* cameras[], int n, int days) {
    float totalPrice = 0;
    for (int i = 0; i < n; i++) {
        totalPrice += cameras[i]->rentalPrice(days);
    }
    return totalPrice;
}

string mostExpensiveCamera (Camera* camera[], int n) {
    int index = 0;
    for (int i = 0; i < n; i++) {
        if (camera[i]->price() > camera[index]->price()) {
            index = i;
        }
    }
    return camera[index]->model;
}

int main(int argc, char *argv[])
{
    char model[20], producer[20];
    int year, length, fps, n;
    float resolution;
    bool raw;

    int t;

    Camera *c [10];

    cin>>n;

    for(int i = 0; i < n; ++i){
        cin>>t;

        if (t==1){
            cin >> producer >> model >> year >> resolution;
            cin >> raw;
            c[i] = new PhotoCamera(producer, model, year, resolution, raw);
        }
        else if (t==2){
            cin >> producer >> model >> year >> resolution;
            cin >> length;
            c[i] = new VideoCamera(producer, model, year, resolution, length);
        }
        else if (t==3){
            cin >> producer >> model >> year >> resolution;
            cin >> fps;
            c[i] = new FilmCamera(producer, model, year, resolution, fps);
        }
    }

    int days;
    cin >> days;

    cout<< "Price of production is: " << production(c, n, days);
    cout<<"\n" << "Most expensive camera used in production is: " << mostExpensiveCamera(c, n);

    return 0;
}