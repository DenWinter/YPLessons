#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

float CalcMedian(vector<float> numbers) {
    sort(numbers.begin(), numbers.end());
    int array_size = numbers.size();
    int half_size = array_size / 2;
    if (array_size % 2 == 0) {
        return ((numbers[half_size - 1]) + (numbers[half_size])) / 2;
    } else {
        return numbers[half_size];
    }
}

vector<string> SplitIntoWords(const string& text) {
    vector<string> words;
    string word;
    for (const char c : text) {
        if (c == ' ') {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        } else {
            word += c;
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }
    return words;
}

vector<float> ArrayCastToFloat(const vector<string>& array_string) {
    vector<float> array_float;
    for(const string& s : array_string) {
        array_float.push_back(atof(s.c_str()));
    }
    return array_float;
}


int main() {
    string s;
    getline(cin, s);
    cout << CalcMedian(ArrayCastToFloat(SplitIntoWords(s))) << endl;
}

