#include "../include/authentication.h"

int main() {
    if (!authenticate_user()) {
        std::cout << "Authorization was failed\n";
        return 0;
    }

    std::cout << "You was successfully authorize in system\n";

    return 0;
}
