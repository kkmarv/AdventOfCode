#pragma once

#include <iostream>
#include <vector>

namespace util
{

/**
 * @brief Inserts an item into a vector and keeps order.
 * @tparam T The type of the vector contents.
 * @param vector The vector.
 * @param item An item to insert into the vector.
 */
template <typename T>
inline void sortedInsert(std::vector<T> &vector, T item)
{
    auto insertionIndex = std::upper_bound(vector.cbegin(), vector.cend(), item);
    vector.insert(insertionIndex, item);
}

/**
 * @brief Print a vector to stdout.
 * @tparam T The type of the vector contents.
 * @param vector The vector.
 */
template <typename T>
inline void print(std::vector<T> vector)
{
    for (item : vector)
        std::cout << item << std::endl;
}

} // namespace util