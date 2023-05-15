#include "Vector.h"

void printVector(Vector &vector)
{
    std::cout << "Your vector:\t\n";
    //std::cout << "\tSize: " << vector.size() << std::endl;
    //std::cout << "\tCapacity: " << vector.capacity() << std::endl;
    for (int i = 0; i < vector.size(); ++i)
    {
        std::cout << "\t" << vector[i];
    }
    std::cout << std::endl;
    std::cout << "\t SIZE: " << vector.size() << std::endl;
}

void cleanVector(Vector &vector)
{
    int tmp = vector.size();
    for (int i = 0; i < tmp; ++i)
    {
        vector.popBack();
    }
}

int main()
{
    int ar[3] = {11,22,33};
    int ar1[1] = {1};
    Vector v(ar, 3);
    Vector s(ar, 3);
    printVector(v);
    v.insert(111, 3);
    printVector(v);
    v.insert(ar, 3, 4);
    printVector(v);
    v.insert(s, 0);
    printVector(v);
    v.eraseBetween(2,4);
    printVector(v);
    v.popBack();
    v.popFront();
    printVector(v);
    v.erase(0, 5);
    printVector(v);
    v.pushBack(11);
    v.pushFront(33);
    printVector(v);
    Vector i(ar1, 1);
    v = std::move(i);
    printVector(i);
    printVector(v);
    return 0;
}