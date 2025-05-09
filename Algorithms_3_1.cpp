#include <cmath>
#include <iostream>
#include <vector>
#include <map>
#include <functional>

using SortFunction = std::function<void(std::vector<int>*)>;

void merge_sort(std::vector<int>* vector)
{
    if (!vector || vector->size() <= 1)
        return;

    int iterations = 0;
    while (vector->size() > std::pow(2, iterations))
    {
        ++iterations;
    }

    for (int iteration = 0; iteration < iterations; ++iteration)
    {
        int blockSize = std::pow(2, iteration);

        for (int index = 0; index < vector->size(); index += 2 * blockSize)
        {
            int leftStart = index;
            int leftEnd = std::min(index + blockSize, static_cast<int>(vector->size()));
            int rightEnd = std::min(index + 2 * blockSize, static_cast<int>(vector->size()));

            std::vector<int> mergedBlock;
            int leftPosition = leftStart;
            int rightPosition = leftEnd;

            while (leftPosition < leftEnd && rightPosition < rightEnd)
            {
                if ((*vector)[leftPosition] <= (*vector)[rightPosition])
                {
                    mergedBlock.push_back((*vector)[leftPosition++]);
                }
                else
                {
                    mergedBlock.push_back((*vector)[rightPosition++]);
                }
            }

            while (leftPosition < leftEnd)
                mergedBlock.push_back((*vector)[leftPosition++]);
            while (rightPosition < rightEnd)
                mergedBlock.push_back((*vector)[rightPosition++]);

            for (int index2 = 0; index2 < mergedBlock.size(); ++index2)
            {
                (*vector)[leftStart + index2] = mergedBlock[index2];
            }
        }
    }
}

void quick_sort(std::vector<int>* vector)
{
    if (!vector || vector->size() <= 1)
        return;

    int pivot = (*vector)[vector->size() / 2];
    std::vector<int> left, right;

    for (int i = 0; i < vector->size(); ++i)
    {
        if (i == vector->size() / 2)
            continue;
        if ((*vector)[i] <= pivot)
            left.push_back((*vector)[i]);
        else
            right.push_back((*vector)[i]);
    }

    quick_sort(&left);
    quick_sort(&right);

    int index = 0;
    for (const auto& elem : left)
        (*vector)[index++] = elem;
    (*vector)[index++] = pivot;
    for (const auto& elem : right)
        (*vector)[index++] = elem;
}

void count_sort(std::vector<int>* vector)
{
    if (!vector || vector->size() <= 1)
        return;
    std::map<int, int> map;
    for (auto& value : *vector)
    {
        auto key = map.find(value);
        if (key != map.end())
        {
            key->second += 1; 
        }
        else
        {
            map[value] = 1;
        }
    }
    int counter = 0;
    for (auto& object : map)
    {
        for (int index = 0; index < object.second; ++index)
        {
            vector->at(counter) = object.first;
            ++counter;
        }
    }
}

void print(std::vector<int>* vector)
{
    if (!vector)
        return;
    for (const auto& elem : *vector)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

int main()
{
    setlocale(LC_ALL, "");

    std::vector<std::vector<int>> vectors1 = {{3, 43, 38, 29, 18, 72, 57, 61, 2, 33},
                                              {88, 91, 87, 59, 53, 49, 29, 16, 4, 27, 28, 89, 2, 25, 74},
                                              {24, 66, 20, 79, 30, 16, 19, 62, 94, 59, 0, 7, 59, 90, 84, 60, 95, 62}};

    std::vector<std::vector<int>> vectors2 = {{3, 43, 38, 29, 18, 72, 57, 61, 2, 33},
                                              {88, 91, 87, 59, 53, 49, 29, 16, 4, 27, 28, 89, 2, 25, 74},
                                              {24, 66, 20, 79, 30, 16, 19, 62, 94, 59, 0, 7, 59, 90, 84, 60, 95, 62}};

    std::vector<std::vector<int>> vectors3 = {
        {19, 14, 22, 22, 17, 22, 13, 21, 20, 24, 18, 10, 17, 16, 17,
         20, 22, 11, 20, 16, 14, 13, 10, 22, 18, 14, 16, 24, 19, 17},
        {16, 17, 14, 20, 22, 20, 17, 22, 16, 19, 23, 24, 20, 22, 21, 18, 14, 16, 17, 21,
         10, 11, 19, 23, 11, 11, 17, 17, 11, 21, 17, 11, 17, 16, 12, 11, 16, 22, 23, 16},
        {21, 15, 19, 18, 23, 12, 18, 18, 19, 23, 12, 20, 15, 22, 21, 18, 19, 20, 12, 16, 20, 14, 17,
         13, 10, 23, 19, 14, 10, 22, 19, 12, 24, 23, 22, 15, 13, 22, 18, 18, 11, 23, 24, 17, 10}};

    std::map<std::vector<std::vector<int>>*, SortFunction> sortFunctions = {
        {&vectors1, merge_sort}, {&vectors2, quick_sort}, {&vectors3, count_sort}};

    int index = 0;
    for (auto& pair : sortFunctions)
    {
        std::vector<std::vector<int>>& key = *pair.first;
        SortFunction& value = pair.second;

        ++index;
        std::cout << std::endl << std::endl << "Задание " << index << ":" << std::endl << std::endl;

        for (auto& vector : key)
        {
        std::cout << "Исходный массив: ";
            print(&vector);
        value(&vector);

        std::cout << "Отсортированный массив: ";
        print(&vector);
        }
    }

    return 0;
}