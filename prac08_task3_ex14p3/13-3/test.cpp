// database.cpp

#include "database.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>

void Database::add(Person person) {
    m_persons.push_back(std::move(person));
}

void Database::clear() {
    m_persons.clear();
}

void Database::save(std::string_view filename) const {
    std::ofstream outFile{ filename.data(), std::ios_base::trunc };
    if (!outFile) {
        throw std::runtime_error{ "Cannot open file: " + std::string(filename) };
    }

    for (const auto& person : m_persons) {
        outFile << std::quoted(person.getFirstName()) << " "
                << std::quoted(person.getLastName()) << " "
                << std::quoted(person.getInitials()) << std::endl;
        if (!outFile) {
            throw std::runtime_error{ "Failed to write person to file." };
        }
    }
}

void Database::load(std::string_view filename) {
    std::ifstream inFile{ filename.data() };
    if (!inFile) {
        throw std::runtime_error{ "Cannot open file: " + std::string(filename) };
    }

    while (inFile) {
        std::string firstName, lastName, initials;
        if (!(inFile >> std::quoted(firstName) >> std::quoted(lastName) >> std::quoted(initials))) {
            if (!inFile.eof()) {
                throw std::runtime_error{ "Failed to read person from file." };
            } else {
                break; // Reached end of file
            }
        }
        m_persons.push_back(Person{ std::move(firstName), std::move(lastName), std::move(initials) });
    }
}

void Database::outputAll(std::ostream& output) const {
    for (const auto& person : m_persons) {
        output << std::quoted(person.getFirstName()) << " "
               << std::quoted(person.getLastName()) << " "
               << std::quoted(person.getInitials()) << std::endl;
    }
}
