#include "bytearraymanipulator.h"

void displayQByteArray(const QByteArray& array, std::ios_base&(*base)(std::ios_base&), char separator)
{
    for(auto it : array)
    {
        std::cout << base << static_cast<int16_t>(static_cast<uint8_t>(it)) << separator;
    }
    std::cout << std::endl;
}

