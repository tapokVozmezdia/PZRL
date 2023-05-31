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
    HashTable newTable(table);
    //newTable = std::move(table);
    std::cout << "\tFIRST TABLE" << std::endl;
    std::cout << table.getLoadFactor() << std::endl;
    //std::cout << table["one hundred and one"] << std::endl;
    //std::cout << table["one"] << std::endl;
    std::cout << "\tSECOND TABLE" << std::endl;
    std::cout << newTable.getLoadFactor() << std::endl;
    std::cout << newTable["one hundred and one"] << std::endl;
    std::cout << newTable["one"] << std::endl;
    HashTable myTable(3);
    myTable.insert("one", 1);
    myTable.insert("one hundred and one", 101);
    std::cout << myTable.capacity() << std::endl;
    myTable.insert("seven", 7);
    myTable.insert("one1", 1);
    myTable.insert("one hundred and one1", 101);
    myTable.insert("seven1", 7);
    std::cout << myTable.capacity() << std::endl;
    std::cout << "I HAVE TERMINATED" << std::endl;
    return 0;
}