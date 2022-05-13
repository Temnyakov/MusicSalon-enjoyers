#include "../include/authentication.h"
#include "../include/user_actions.h"

int main() {
    if (!authenticate_user()) {
        std::cout << "Authorization was failed\n";
        return 0;
    }

    std::cout << "You was successfully authorize in system\n";

    run_user_interface();

    return 0;
}
