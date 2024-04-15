#ifndef ASSOCIATIVE_ARRAY_H
#define ASSOCIATIVE_ARRAY_H

#include <string>
#include <string_view>
#include <vector>
#include <stdexcept>
#include <format>

template <typename T>
class AssociativeArray
{
public:
    virtual ~AssociativeArray() = default;

    T& operator[](std::string_view key);
    const T& operator[](std::string_view key) const;

private:
    class Element
    {
    public:
        Element(std::string key, T value)
            : m_key{ std::move(key) }, m_value{ std::move(value) } {}
        std::string m_key;
        T m_value;
    };

    std::vector<Element> m_data;
};

template <typename T>
T& AssociativeArray<T>::operator[](std::string_view key)
{
    // See if key already exists
    for (auto& element : m_data) {
        if (element.m_key == key) {
            return element.m_value;
        }
    }

    // If we arrive here, the key doesn't exist yet, add it
    m_data.push_back(Element{ std::string{ key }, T{} });
    // Return reference to the value we just added
    return m_data.back().m_value;
}

template <typename T>
const T& AssociativeArray<T>::operator[](std::string_view key) const
{
    for (const auto& element : m_data) {
        if (element.m_key == key) {
            return element.m_value;
        }
    }
    throw std::invalid_argument{ std::format("Key '{}' doesn't exist.", key.data()) };
}

#endif // ASSOCIATIVE_ARRAY_H
