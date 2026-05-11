//
// Created by cactus on 5/4/2026.
//
#include <iostream>
using namespace std;

class QuizAttempt {
private:
    string index;

public:
    QuizAttempt(const string &index = "") : index(index) {
    }

    virtual ~QuizAttempt() = default;

    virtual double score() const = 0;

    virtual void print() const = 0;
    bool operator>=(const QuizAttempt &other) const {
        return score() >= other.score();
    }
};

class MCQuizAttempt : public QuizAttempt {
    string correctAnswers;
    string answers;

public:
    MCQuizAttempt(const string &index = "", const string &correctAnswers = "", const string &answers = "")
        : QuizAttempt(index), correctAnswers(correctAnswers), answers(answers) {
    }

    double score() const {
        double correctAnswersCount = 0;
        for (int i = 0; i < answers.size(); i++) {
            correctAnswersCount += 1 - (1.25 * (answers[i] != correctAnswers[i]));
        }
        return correctAnswersCount;
    }

    void print() const {
        for (int i = 0; i < 10; i++) {
            cout << i + 1 << ". " << "Correct: " << correctAnswers[i] << " Answer: " << answers[i] << " Points: "
                    << 1 - (1.25 * (answers[i] != correctAnswers[i]))<<'\n';
        }
        cout << "Total score: " << score() << '\n';
    }
};

class TFQuizAttempt : public QuizAttempt {
    bool correctAnswers[10];
    bool answers[10];

public:
    TFQuizAttempt(const string &index = "", bool *correctAnswers = nullptr, bool *answers = nullptr)
        : QuizAttempt(index), correctAnswers(correctAnswers), answers(answers) {
        for (int i = 0; i < 10; i++) {
            this->correctAnswers[i] = correctAnswers[i];
            this->answers[i] = answers[i];
        }
    }

    double score() const {
        double correctAnswersCount = 0;
        for (int i = 0; i < 10; i++) {
            correctAnswersCount += 1 - (1.5 * (answers[i] != correctAnswers[i]));
        }
        return correctAnswersCount;
    }
    void print() const {
        for (int i = 0; i < 10; i++) {
            cout << i + 1 << ". " << "Correct: " << (correctAnswers[i] ? "True" : "False") << " Answer: "
                 << (answers[i] ? "Correct" : "False") << " Points: "
                 << 1 - (1.5 * (answers[i] != correctAnswers[i])) <<'\n';
        }
        cout << "Total score: " << score() << '\n';
    }
};

double averagePointsOfPassedStudents(QuizAttempt* attempts[], int n) {
    double avgPoints = 0;
    for (int i = 0; i < n; i++) {
        avgPoints += attempts[i]->score() * (attempts[i]->score() >= 5.0);
    }
    return avgPoints / n;
}

QuizAttempt *readMCQuizAttempt() {
    char ID[7];
    char correct[11];
    char answers[11];

    cin >> ID >> correct >> answers;
    return new MCQuizAttempt(ID, correct, answers);
}

QuizAttempt *readTFQuizAttempt() {
    char ID[7];
    bool correct[10];
    bool answers[10];
    cin >> ID;
    for (int i = 0; i < 10; i++) {
        cin >> correct[i];
    }
    for (int i = 0; i < 10; i++) {
        cin >> answers[i];
    }

    return new TFQuizAttempt(ID, correct, answers);
}


int main() {
    int testCase;

    cin >> testCase;

    if (testCase == 1) {
        cout << "Test MCQuizAttempt" << endl;
        QuizAttempt *attempt = readMCQuizAttempt();
        cout << "Score: " << attempt->score() << endl;
        attempt->print();
    } else if (testCase == 2) {
        cout << "Test TFQuizAttempt" << endl;
        QuizAttempt *attempt = readTFQuizAttempt();
        cout << "Score: " << attempt->score() << endl;
        attempt->print();
    } else if (testCase == 3) {
        cout << "Test operator >=" << endl;
        int n;
        cin >> n;
        QuizAttempt **attempts = new QuizAttempt *[n];
        for (int i = 0; i < n; i++) {
            int type;
            cin >> type;
            if (type == 1) {
                attempts[i] = readMCQuizAttempt();
            } else {
                attempts[i] = readTFQuizAttempt();
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    if ((*attempts[i]) >= (*attempts[j])) {
                        cout << i << " >= " << j << endl;
                    } else {
                        cout << i << " < " << j << endl;
                    }
                }
            }
        }
    } else {
        int n;
        cin >> n;
        QuizAttempt **attempts = new QuizAttempt *[n];
        for (int i = 0; i < n; i++) {
            int type;
            cin >> type;
            if (type == 1) {
                attempts[i] = readMCQuizAttempt();
            } else {
                attempts[i] = readTFQuizAttempt();
            }
            attempts[i]->print();
            cout << endl;
        }

        cout << "Average score of passed students is: " << averagePointsOfPassedStudents(attempts, n) << endl;
    }

    return 0;
}
