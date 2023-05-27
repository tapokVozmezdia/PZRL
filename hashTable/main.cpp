#include <iostream>
#include "HashTable.h"

void debug()
{
    std::cout << "===Debug line===" << std::endl;
}

int main()
{
    HashTable table(100);
    table.insert("one", 1);
    table.insert("one hundred and one", 101);
    table.insert("seven", 7);
    std::cout << table.getLoadFactor() << std::endl;
    std::cout << table["one hundred and one"] << std::endl;
    std::cout << table["one"] << std::endl;
    return 0;
}