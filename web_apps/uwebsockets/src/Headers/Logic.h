#ifndef LOGIC_H
#define LOGIC_H

#include <string>
#include <cstdint>
#include <unordered_map>
#include <utility>

struct Offer {
    std::int64_t price;
    std::int64_t amount;
    std::int64_t amount_real;
};

struct AMM {
    std::int64_t amount;
    std::int64_t amount2;
    std::int64_t price = amount/amount2;
};

struct Book {
    std::string name;
    Offer best_offer;
    std::unordered_map<std::string, Offer> offers;
    std::int64_t transfer_fee;
    std::int64_t amm_fee;
};


class Logic {
public:
    Logic();
    ~Logic();
    
    std::int64_t transaction_fee(std::int64_t base_load, std::int64_t load_factor, std::int64_t base_fee); //raw

    // Add your public methods here
    
private:

    std::unordered_map<std::string, Book> askBooks;
    std::unordered_map<std::string, Book> bidBooks;
    std::unordered_map<std::string, AMM> amms;

    // Add your private members here
};

#endif // LOGIC_H