#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<pair<int, string>> name_age;
    int count;
    cin >> count;
    for (int i = 0; i < count; ++i) {
        string name;
        int age;
        cin >> name >> age;
        name_age.push_back({age, name});
        // сохраните в вектор пар
    }
    reverse(name_age.begin(), name_age.end());
    for(auto n_a : name_age) {
        cout << n_a.second << endl;
    }

    // выведите только имена в порядке убывания возраста
    // Jack
    // John
    // ...
}

