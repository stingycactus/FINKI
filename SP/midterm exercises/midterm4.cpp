//
// Created by cactus on 03/11/2025.
//
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        float points, max_points;
        cin >> points >> max_points;
        float percent_grade = points / max_points * 100;
        int grade = (int(percent_grade/10)) % 10 + 1;
        if (grade<5) {
            cout<<percent_grade<<" FAIL";
        }
        else {
            cout<<percent_grade<<" "<<grade;
        }
        cout<<'\n';
    }
    return 0;
}
