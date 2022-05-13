#ifndef PROMPT_H
#define PROMPT_H

template <typename T, typename CheckFunction>
void prompt(T& value, CheckFunction check, const std::string& msg, const std::string& error_msg) {
    std::cout << msg;
    while (true) {
        std::cin >> value;
        if (check(value)) {
            break;
        }
        std::cout << error_msg;
    }
}

#endif //PROMPT_H
