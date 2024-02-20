#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> sort_characters(const string& text) {
    vector<int> order(text.length());
    vector<int> count(256, 0);

   
    for (char c : text) {
        count[c]++;
    }

    for (int i = 1; i < 256; ++i) {
        count[i] += count[i - 1];
    }

    for (int i = text.length() - 1; i >= 0; --i) {
        char c = text[i];
        count[c]--;
        order[count[c]] = i;
    }

    return order;
}

vector<int> compute_char_classes(const string& text, const vector<int>& order) {
    vector<int> classes(text.length());
    classes[order[0]] = 0;

    for (int i = 1; i < text.length(); ++i) {
        if (text[order[i]] != text[order[i - 1]]) {
            classes[order[i]] = classes[order[i - 1]] + 1;
        } else {
            classes[order[i]] = classes[order[i - 1]];
        }
    }

    return classes;
}

vector<int> sort_doubled(const string& text, int l, const vector<int>& order, const vector<int>& classes) {
    int n = text.length();
    vector<int> count(n, 0);
    vector<int> new_order(n);

    for (int i = 0; i < n; ++i) {
        int start = (order[i] - l + n) % n;
        int cl = classes[start];
        count[cl]++;
    }

    for (int i = 1; i < n; ++i) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; --i) {
        int start = (order[i] - l + n) % n;
        int cl = classes[start];
        count[cl]--;
        new_order[count[cl]] = start;
    }

    return new_order;
}

vector<int> update_classes(const vector<int>& new_order, const vector<int>& classes, int l) {
    int n = new_order.size();
    vector<int> new_classes(n);
    new_classes[new_order[0]] = 0;

    for (int i = 1; i < n; ++i) {
        int cur = new_order[i];
        int prev = new_order[i - 1];
        int mid = (cur + l) % n;
        int mid_prev = (prev + l) % n;

        if (classes[cur] != classes[prev] || classes[mid] != classes[mid_prev]) {
            new_classes[cur] = new_classes[prev] + 1;
        } else {
            new_classes[cur] = new_classes[prev];
        }
    }

    return new_classes;
}

vector<int> build_suffix_array(const string& text) {
    vector<int> order = sort_characters(text);
    vector<int> classes = compute_char_classes(text, order);
    int l = 1;

    while (l < text.length()) {
        order = sort_doubled(text, l, order, classes);
        classes = update_classes(order, classes, l);
        l *= 2;
    }

    return order;
}

int main() {
    string text;
    
   
   
    cin >> text;

    
    if (text.back() != '$') {
        text += '$';
    }

    vector<int> suffix_array = build_suffix_array(text);

    
    for (int pos : suffix_array) {
        cout << pos << " ";
    }
    cout << endl;

    return 0;
}
