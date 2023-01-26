#include "password.h"
const int MIN_LEN = 8;
const int MAX_LEN = 14;
const int MIN_ASCII = 33;
const int MAX_ASCII = 126;
bool ValidatePassword(const std::string& password) {
    bool big_let = false;
    bool small_let = false;
    bool num = false;
    bool symb = false;
    if (password.size() < MIN_LEN || password.size() > MAX_LEN) {
        return false;
    }
    for (int i = 0; i < password.size(); ++i) {
        char elem = password[i];
        if (elem < MIN_ASCII || elem > MAX_ASCII) {
            return false;
        }
        if (islower(elem)) {
            small_let = true;
        } else {
            if (isupper(elem)) {
                big_let = true;
            } else {
                if (isdigit(elem)) {
                    num = true;
                } else {
                    symb = true;
                }
            }
        }
    }
    if (big_let + small_let + num + symb < 3) {
        return false;
    }
    return true;
}
