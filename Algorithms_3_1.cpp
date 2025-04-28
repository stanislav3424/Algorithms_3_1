#include <cmath>
#include <iostream>
#include <vector>

void merge_sort(std::vector<int>* vector)
{
    if (!vector || vector->size() <= 1)
        return;

    int iterations = 0;
    while (static_cast<int>(vector->size()) > std::pow(2, iterations))
    {
        ++iterations;
    }

    for (int iteration = 0; iteration < iterations; ++iteration)
    {
        int blockSize = std::pow(2, iteration);

        for (int index = 0; index < static_cast<int>(vector->size()); index += 2 * blockSize)
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

    std::vector<std::vector<int>> vectors = {{3, 43, 38, 29, 18, 72, 57, 61, 2, 33},
                                             {88, 91, 87, 59, 53, 49, 29, 16, 4, 27, 28, 89, 2, 25, 74},
                                             {24, 66, 20, 79, 30, 16, 19, 62, 94, 59, 0, 7, 59, 90, 84, 60, 95, 62}};
    for (auto& vector : vectors)
    {
        std::cout << "Исходный массив: ";
        print(&vector);
        merge_sort(&vector);
        std::cout << "Отсортированный массив: ";
        print(&vector);
    }

    return 0;
}