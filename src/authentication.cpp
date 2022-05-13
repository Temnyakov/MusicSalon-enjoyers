#include "../include/authentication.h"
#include "../include/prompt.h"

std::vector<std::vector<std::string>> find_user_by_email(const sqlite3_database& db, const std::string& email) {
    const std::string find_by_email = "SELECT user_id, user_email, user_password FROM users WHERE user_email == \"" + email + "\";";
    return db.select(find_by_email);
}

bool m_log_in(const sqlite3_database& db) {
    std::string email, password;

    while (true) {
        std::cout << "Enter email:\n";
        std::cin >> email;
        std::cout << "Enter password:\n";
        std::cin >> password;

        auto res = find_user_by_email(db, email);
        if (!res.empty() && aes.encrypt(password) == res[0][2]) {
            return true;
        }

        std::cout << "Invalid email or password\n";

        int option = 0;
        auto option_check = [](int option) {return option == 1 || option == 2;};
        prompt(option, option_check, "Enter '1' to try again or '2' to exit:\n", "Invalid option\n");
        if (option == 2) break;
    }

    return false;
}

bool m_sign_up(const sqlite3_database& db) {
    std::string email, password;

    auto email_check = [&db](const std::string& email) {
        return std::regex_match(email, email_regex) && find_user_by_email(db, email).empty();
    };
    prompt(email, email_check, "Enter email:\n", "Invalid format for email or this email is already exists\n");

    auto password_check = [](const std::string& pass) {return std::regex_match(pass, password_regex);};
    prompt(password, password_check, "Enter password:\n", "Invalid format for password\n");
    db.param_insert(new_user_data_insert, {email, aes.encrypt(password)});

    return true;
}

bool authenticate_user() {
    sqlite3_database users_data(users_db_path);
    users_data.insert(users_db_create);

    int option = 0;
    auto option_check = [](int option) {return option == 1 || option == 2;};
    prompt(option, option_check, "Select option:\n1: Log in\n2: Sign up\n", "Invalid option\n");

    return option == 1 ? m_log_in(users_data) : m_sign_up(users_data);
}
