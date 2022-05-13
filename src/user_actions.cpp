#include "../include/user_actions.h"
#include "../include/prompt.h"
#include <charconv>

std::ostream& operator << (std::ostream& os, const std::vector<std::vector<std::string>>& result) {
    for (const auto& row : result) {
        for (const auto& elem : row) {
            os << elem << ' ';
        }
        os << std::endl;
    }
    return os;
}

bool can_sell(const sqlite3_database& db, std::size_t count) {
    auto remainders = db.select(query_solds_and_remainder);
    std::size_t remainder = 0;
    for (const auto& row: remainders) {
        int rem = 0;
        std::from_chars(row[2].c_str(), row[2].c_str() + row[2].size(), rem);
        remainder += rem;
    }

    return count <= remainder;
}

void run_user_interface() {
    sqlite3_database db(music_saloon_path);

    int option = 0;
    while (true) {
        std::cout << "Options:\n";
        std::cout << "1: Sales and remainder CDs\n";
        std::cout << "2: Price and number of CDs sold at specific period\n";
        std::cout << "3: Info about the best selling CD\n";
        std::cout << "4: Number of sold CDs of the most popular performer\n";
        std::cout << "5: Number of sold CDs and received money for every performer\n";
        std::cout << "6: Number of received and sales for every CD\n";
        std::cout << "0: Exit\n";

        auto option_check = [](int option) {return option >= 0 && option <= 6;};
        prompt(option, option_check, "Enter option:\n", "Invalid option\n");

        if (option == 0) {
            break;
        }

        std::string start_period, end_period;
        switch (option) {
            case 1:
                std::cout << db.select(query_solds_and_remainder) << std::endl;
                break;
            case 2:
                std::cout << "Enter start and end periods:\n";
                std::cin >> start_period >> end_period;
                std::cout << db.select(query_max_sold_for_the_period);
                break;
            case 3:
                std::cout << db.select(query_cd_with_max_solds);
                break;
            case 4:
                std::cout << db.select(query_max_cds_sold_with_most_popular_performer);
                break;
            case 5:
                std::cout << db.select(query_out_sum_by_authors);
                break;
            case 6:
                std::cout << "Enter start and end periods:\n";
                std::cin >> start_period >> end_period;
                std::cout << db.select(query_received_and_sales_cds_by_date);
            default:
                std::cout << "No such option\n";
        }
    }
}
