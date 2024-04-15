#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>
#include <stdexcept>

using namespace std;

class Person {
public:
    Person(string first, string last, string initials)
        : m_firstName(move(first)), m_lastName(move(last)), m_initials(move(initials)) {}

    const string& getFirstName() const { return m_firstName; }
    const string& getLastName() const { return m_lastName; }
    const string& getInitials() const { return m_initials; }

    void output(ostream& out) const {
        out << quoted(m_firstName) << quoted(m_lastName) << quoted(m_initials) << endl;
    }

private:
    string m_firstName;
    string m_lastName;
    string m_initials;
};

class Database {
public:
    void add(Person person) {
        m_persons.push_back(move(person));
    }

    void clear() {
        m_persons.clear();
    }

    void save(string_view filename) const {
        ofstream outFile{ filename.data(), ios_base::trunc };
        if (!outFile) {
            throw runtime_error{ "Cannot open file: " + string(filename) };
        }

        for (const auto& person : m_persons) {
            outFile << quoted(person.getFirstName()) << quoted(person.getLastName())
                    << quoted(person.getInitials()) << endl;
            if (!outFile) {
                throw runtime_error{ "Failed to write person to file." };
            }
        }
    }

    void load(string_view filename) {
        ifstream inFile{ filename.data() };
        if (!inFile) {
            throw runtime_error{ "Cannot open file: " + string(filename) };
        }

        while (inFile) {
            string line;
            getline(inFile, line);
            if (!inFile && !inFile.eof()) {
                throw runtime_error{ "Failed to read line from file." };
            }
            if (line.empty()) {
                continue;
            }

            istringstream inLine{ line };
            string firstName, lastName, initials;
            inLine >> quoted(firstName) >> quoted(lastName) >> quoted(initials);
            if (inLine.bad()) {
                cerr << "Error reading person. Ignoring." << endl;
                continue;
            }

            m_persons.push_back(Person{ move(firstName), move(lastName), move(initials) });
        }
    }

    void outputAll(ostream& output) const {
        for (const auto& person : m_persons) {
            person.output(output);
        }
    }

private:
    vector<Person> m_persons;
};

int main() {
    try {
        Database db;
        // Example usage
        db.load("data.txt");
        db.save("output.txt");
    } catch (const exception& ex) {
        cerr << "Exception: " << ex.what() << endl;
    }

    return 0;
}
