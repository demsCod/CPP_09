#include <fstream>
#include <map>
#include <string>
#include <iostream>
#include "BitcoinExchange.hpp"
#include <exception>
#include <algorithm>
#include <sstream>
#include <stdexcept>

// Vérifie si la date est valide
bool isValidDate(const std::string& date) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
        return false;
    }

    int year, month, day;
    try {
        year = std::stoi(date.substr(0, 4));
        month = std::stoi(date.substr(5, 2));
        day = std::stoi(date.substr(8, 2));
    } catch (...) {
        return false;
    }

    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }

    // Vérifier les jours dans chaque mois
    static const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

    if (month == 2 && isLeapYear) {
        if (day > 29)
            return false;
    } else if (month == 2) {
        if (day > 28)
            return false;
    } else if (day > daysInMonth[month - 1]) {
        return false;
    }

    return true;
}

// Constructeur de BitcoinExchange
BitcoinExchange::BitcoinExchange(std::string input)
{  
    std::string line;
    std::string date;
    float value;
    int pos;  
    std::fstream file;

    fs.open(input, std::fstream::in);
    if (!fs)
        throw std::runtime_error("Error: Cannot open input file.");
    
    std::getline(fs, buffer);
    if (buffer.compare("date | value"))
        throw std::runtime_error("Error: Invalid input file format.");

    file.open("data.csv", std::fstream::in);
    if (!file)
        throw std::runtime_error("Error: Cannot open data file.");
    
    std::getline(file, line); // Ignore la première ligne de l'en-tête
    while (std::getline(file, line)) {
        pos = line.find(',');
        date = line.substr(0, pos);
        value = std::atof(line.substr(pos + 1).c_str());

        if (!isValidDate(date))
            throw std::runtime_error("Error: Invalid date in data file: " + date);
        
        database[date] = value;
    }
}

void BitcoinExchange::DisplayValue()
{
    std::string date;
    std::string value;
    int pos;

    while (std::getline(fs, buffer)) {
        // Vérifier la présence et la position du séparateur "|"
        if (std::count(buffer.begin(), buffer.end(), '|') != 1 || buffer.find('|') != 11 || buffer.size() < 12) {
            std::cout << "Error: bad input => " << buffer << std::endl;
            continue;
        }

        // Extraire la date et la valeur
        pos = buffer.find("|");
        date = buffer.substr(0, pos - 1);
        value = buffer.substr(pos + 1);

        // Vérifier la validité de la date
        if (!isValidDate(date)) {
            std::cout << "Error: invalid date => " << date << std::endl;
            continue;
        }

        // Vérifier la valeur numérique
        std::stringstream ss(value);
        float d;
        ss >> d;

        if (ss.fail()) {
            std::cout << "Error: bad value => " << value << std::endl;
            continue;
        }

        if (d < 0) {
            std::cout << "Error: not a positive number.\n";
            continue;
        } else if (d > 2147483647.0) {
            std::cout << "Error: too large number.\n";
            continue;
        }

        // Afficher le résultat
        if (database.count(date)) {
            std::cout << buffer << " => " << d << " = " << d * database[date] << std::endl;
        } else {
            // Trouver la date la plus proche inférieure
            std::map<std::string, float>::iterator it = database.upper_bound(date);
            if (it == database.begin()) {
                std::cout << "Error: no data available for date => " << date << std::endl;
            } else {
                it--;
                std::cout << buffer << " => " << d << " = " << d * it->second << std::endl;
            }
        }
    }
}

int main(int ac, char** av)
{
    if (ac == 2) {
        try {
            BitcoinExchange a(av[1]);
            a.DisplayValue();
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            return 1;
        }
    } else {
        std::cerr << "Usage: ./bitcoin_exchange <input_file>" << std::endl;
        return 1;
    }
}
