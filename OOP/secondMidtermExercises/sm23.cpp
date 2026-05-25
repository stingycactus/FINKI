//
// Created by cactus on 5/23/2026.
//
#include <iostream>
using namespace std;

class ExistingPodcast {
private:
    string text;
public:
    ExistingPodcast(const string &text="ExistingPodcast") : text(text) {}
    void print() {
        cout<<text<<'\n';
    }
};

class Podcast {
protected:
    string name;
    string url;
    float cost;
    int discount;
public:
    Podcast(const string &name="", const string &url="", float cost=0, int discount=0)
    : name(name), url(url), cost(cost), discount(discount) {}
    friend ostream &operator<<(ostream &os, const Podcast &p) {
        os << "Podcast: "<<p.name<<'\n';
        os << "URL: "<<p.url<<'\n';
        os << "Regular price: "<<p.cost<<'\n';
        return os;
    }
    friend istream &operator>>(istream &is, Podcast &p) {
        is >> p.name >> p.url >> p.cost >> p.discount;
        return is;
    }
    Podcast &operator==(const Podcast &other) {
        return url == other.url;
    }
    virtual float price() const {
        return cost - cost * discount/100.0;
    }
};

class StreamingPodcast : public Podcast {
private:
    float fee;
    int month;
    int year;
public:
    StreamingPodcast(const string &name="", const string &url="", float cost=0, int discount=0, float fee=0, int month=0, int year=0)
    : Podcast(name,url,cost,discount), fee(fee), month(month), year(year) {}
    friend ostream &operator<<(ostream &os, const StreamingPodcast &p) {
        os << "Podcast: "<<p.name<<'\n';
        os << "URL: "<<p.url<<'\n';
        os << "Regular price: "<<p.cost<<'\n';
        return os;
    }
    friend istream &operator>>(istream &is, StreamingPodcast &p) {
        is >> p.name >> p.url >> p.cost >> p.discount;
        is >> p.fee >> p.month >> p.year;
        return is;
    }
    float price() const override {
        int months=0;
        if (year<2018){
            months = (12 - this->month) + (2017 - year)*12 + 5;
        }
        else {
            months = 5 - this->month;
        }
        return Podcast::price() + fee * months;
    }
};

class Playlist {
private:
    string name;
    Podcast **collection;
    int n;
public:
    Playlist(const string &name="", Podcast **collection=nullptr, int n=0) {
        this->name=name;
        this->n=n;
        this->collection = new Podcast*[n];
        for (int i = 0; i<n; i++) {
            this->collection[i]=collection[i];
        }
    }
    ~Playlist() {
        delete [] collection;
    }
    Playlist(const Playlist &other) {
        this->name=other.name;
        this->n=other.n;
        this->collection=new Podcast*[this->n];
        for (int i = 0; i<n; i++) {
            this->collection[i]=other.collection[i];
        }
    }
    Playlist &operator=(const Playlist &other) {
        if (this!=&other) {
            for (int i = 0; i<n; i++)
                delete collection[i];
            delete [] collection;
            this->name=other.name;
            this->n=other.n;
            this->collection = new Podcast*[n];
            for (int i = 0; i<n; i++) {
                this->collection[i]=other.collection[i];
            }
        }
        return *this;
    }
    Playlist &operator+=(Podcast *p) {
        bool unique = true;
        for (int i = 0; i<n; i++) {
            if (collection[i]->name==p->name) {
                unique = false;
                throw ExistingPodcast("The podcast is already in the collection");
            }
        }
        if (unique) {
            Podcast **temp = new Podcast*[n+1];
            for (int i = 0; i<n; i++) {
                temp[i]=collection[i];
            }
            delete [] collection;
            collection=temp;
            collection[n]=p;
            n++;
        }
        return *this;
    }
    float totalSpent() const {
        float total=0;
        for (int i = 0; i<n; i++) {
            total+=collection[i]->price();
        }
        return total;
    }
    Playlist &operator<<(const Playlist &p) {
        os<<"Playlist: "<<p.name;
        os<<"Podcast "<<p.name;
        os<<"URL: "<<p.name;
        os<<"regular price: "<<p.name;
        os<<"Podcast: "<<p.name;
        os<<"URL: "<<p.name;
        os<<"regular price: "<<p.name;
    }
};
// badly explained text, might finish later

int main() {
    int test_case_num;

    cin >> test_case_num;

    // for Podcast
    char podcast_name[100];
    char podcast_url[1000];
    float podcast_price;
    int podcast_discount;

    // for StreamingPodcast
    float sub_podcast_monthly_fee;
    int sub_podcast_month, sub_podcast_year;

    // for Playlist
    char name[100];
    int num_podcasts_in_playlist;

    if (test_case_num == 1) {
        cout << "Testing class Podcast and operator<< for Podcast" << std::endl;
        cin.get();
        cin.getline(podcast_name, 100);
        cin.getline(podcast_url, 1000);
        //cin.get();
        cin >> podcast_price >> podcast_discount;

        Podcast p(podcast_name, podcast_url, podcast_price, podcast_discount);

        cout << p;
    } else if (test_case_num == 2) {
        cout << "Testing class StreamingPodcast and operator<< for StreamingPodcast" << std::endl;
        cin.get();
        cin.getline(podcast_name, 100);
        cin.getline(podcast_url, 1000);
        //cin.get();
        cin >> podcast_price >> podcast_discount;

        cin >> sub_podcast_monthly_fee;
        cin >> sub_podcast_month >> sub_podcast_year;

        StreamingPodcast sp(podcast_name, podcast_url, podcast_price, podcast_discount, sub_podcast_monthly_fee,
                            sub_podcast_month, sub_podcast_year);
        cout << sp;
    } else if (test_case_num == 3) {
        cout << "Testing operator>> for Podcast" << std::endl;
        Podcast p;

        cin >> p;

        cout << p;
    } else if (test_case_num == 4) {
        cout << "Testing operator>> for StreamingPodcast" << std::endl;
        StreamingPodcast sp;

        cin >> sp;

        cout << sp;
    } else if (test_case_num == 5) {
        cout << "Testing class Playlist and operator+= for Playlist" << std::endl;
        cin.get();
        cin.getline(name, 100);
        Playlist u(name);

        int num_user_podcasts;
        int podcast_type;
        cin >> num_user_podcasts;

        try {
            for (int i = 0; i < num_user_podcasts; ++i) {
                cin >> podcast_type;

                Podcast *g;
                // 1 - Game, 2 - SubscriptionGame
                if (podcast_type == 1) {
                    cin.get();
                    cin.getline(podcast_name, 100);
                    cin.getline(podcast_url, 1000);

                    cin >> podcast_price >> podcast_discount;
                    g = new Podcast(podcast_name, podcast_url, podcast_price, podcast_discount);
                } else if (podcast_type == 2) {
                    cin.get();
                    cin.getline(podcast_name, 100);
                    cin.getline(podcast_url, 1000);

                    cin >> podcast_price >> podcast_discount;

                    cin >> sub_podcast_monthly_fee;
                    cin >> sub_podcast_month >> sub_podcast_year;
                    g = new StreamingPodcast(podcast_name, podcast_url, podcast_price, podcast_discount,
                                             sub_podcast_monthly_fee, sub_podcast_month, sub_podcast_year);
                }

                //cout<<(*g);


                u += (*g);
            }
        } catch (ExistingPodcast &ex) {
            ex.message();
        }

        cout << u;
    } else if (test_case_num == 6) {
        cout << "Testing exception ExistingPodcast for Playlist" << std::endl;
        cin.get();
        cin.getline(name, 100);
        Playlist u(name);

        int num_podcasts_in_playlist;
        int podcast_type;
        cin >> num_podcasts_in_playlist;

        for (int i = 0; i < num_podcasts_in_playlist; ++i) {
            cin >> podcast_type;

            Podcast *g;
            // 1 - Game, 2 - SubscriptionGame
            if (podcast_type == 1) {
                cin.get();
                cin.getline(podcast_name, 100);
                cin.getline(podcast_url, 1000);

                cin >> podcast_price >> podcast_discount;
                g = new Podcast(podcast_name, podcast_url, podcast_price, podcast_discount);
            } else if (podcast_type == 2) {
                cin.get();
                cin.getline(podcast_name, 100);
                cin.getline(podcast_url, 1000);

                cin >> podcast_price >> podcast_discount;

                cin >> sub_podcast_monthly_fee;
                cin >> sub_podcast_month >> sub_podcast_year;
                g = new StreamingPodcast(podcast_name, podcast_url, podcast_price, podcast_discount,
                                         sub_podcast_monthly_fee, sub_podcast_month, sub_podcast_year);
            }

            //cout<<(*g);

            try {
                u += (*g);
            } catch (ExistingPodcast &ex) {
                ex.message();
            }
        }

        cout << u;
    } else if (test_case_num == 7) {
        cout << "Testing total_spent method() for Playlist" << std::endl;
        cin.get();
        cin.getline(name, 100);
        Playlist u(name);

        int num_podcasts_in_playlist;
        int podcast_type;
        cin >> num_podcasts_in_playlist;

        for (int i = 0; i < num_podcasts_in_playlist; ++i) {
            cin >> podcast_type;

            Podcast *g;
            // 1 - Game, 2 - SubscriptionGame
            if (podcast_type == 1) {
                cin.get();
                cin.getline(podcast_name, 100);
                cin.getline(podcast_url, 1000);

                cin >> podcast_price >> podcast_discount;
                g = new Podcast(podcast_name, podcast_url, podcast_price, podcast_discount);
            } else if (podcast_type == 2) {
                cin.get();
                cin.getline(podcast_name, 100);
                cin.getline(podcast_url, 1000);

                cin >> podcast_price >> podcast_discount;

                cin >> sub_podcast_monthly_fee;
                cin >> sub_podcast_month >> sub_podcast_year;
                g = new StreamingPodcast(podcast_name, podcast_url, podcast_price, podcast_discount,
                                         sub_podcast_monthly_fee, sub_podcast_month, sub_podcast_year);
            }

            //cout<<(*g);

            try {
                u += (*g);
            } catch (ExistingPodcast &ex) {
                ex.message();
            }
        }

        cout << u;

        cout << "Total money spent: $" << u.total_spent() << endl;
    }
}
