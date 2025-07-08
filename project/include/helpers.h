#ifndef HELPERS_H
#define HELPERS_H

#include <string>
using namespace std;

inline string centerText(const string &text, int width) {
    if (text.length() >= width) return text;
    int padding = (width - text.length()) / 2;
    return string(padding, ' ') + text + string(padding, ' ');
}

#endif // HELPERS_H