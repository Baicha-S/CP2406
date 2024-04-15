#include <iostream>
#include <unordered_map>
#include <stdexcept>

template<typename T>
class AssociativeArray {
public:
    T& operator[](const std::string& key) {
        return data[key];
    }

    const T& operator[](const std::string& key) const {
        auto it = data.find(key);
        if (it == data.end()) {
            throw std::invalid_argument("Key not found");
        }
        return it->second;
    }

private:
    std::unordered_map<std::string, T> data;
};

int main() {
    try {
        AssociativeArray<int> myArray;
        myArray["Key 1"] = 11;
        myArray["Key 2"] = 22;
        myArray["Key 3"] = 33;

        std::cout << myArray["Key 1"] << std::endl;
        std::cout << myArray["Key 2"] << std::endl;

        // Test const operator[]
        const AssociativeArray<int>& c{ myArray };
        std::cout << c["Key 3"] << std::endl;
        std::cout << c["Key 4"] << std::endl; // This will throw an exception
    } catch (const std::invalid_argument& ex) {
        std::cout << "Caught exception: " << ex.what() << std::endl;
    }

    return 0;
}
