#include <iostream>
#include "btree.h"

int main()
{
    Dictionary< int, std::string > map;
    map.insert(std::pair(5, "Hello"));
    map.insert(std::pair(3, "World"));
    map.insert(std::pair(4, "World"));
    map.insert(std::pair(1, "World1"));
    map.insert(std::pair(0, "World2"));
    map.insert(std::pair(10, "World3"));
    map.insert(std::pair(15, "World4"));
    map.insert(std::pair(7, "World5"));

    map.each([](auto& el)
        {
            std::cout << el.key << " ";
        });

    return 0;
}