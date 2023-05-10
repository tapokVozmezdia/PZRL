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
    //std::cout << ar[1] << std::endl;
    Vector newVector(ar, 3, 2.);
    //std::cout << "In vector 2: "<< newVector[2] << std::endl;
    Vector newerVector(newVector);
    //std::cout << "In vector 2: "<< newVector[2] << std::endl;
    Vector testVector;
    /*testVector.pushBack(111);
    testVector.pushBack(131);
    testVector.pushBack(121);
    testVector.pushFront(-82);
    testVector.pushFront(-22);
    testVector.pushBack(1000);
    printVector(testVector);
    testVector.popBack();
    printVector(testVector);
    testVector.popFront();
    printVector(testVector);
    testVector.insert(1488, 2);
    printVector(testVector);
    testVector.insert(ar, 3, 2);
    printVector(testVector);
    cleanVector(testVector);
    testVector.insert(ar, 3, 0);
    printVector(testVector);
    Vector testVector_dup(testVector);
    printVector(testVector_dup);
    testVector.insert(testVector_dup, 1);
    printVector(testVector);
    */
    int mas[3] = {11, 22, 33};
    Vector myVector(mas, 3, 1);
    printVector(myVector);
    Vector hisVector(myVector);
    printVector(hisVector);
    myVector.insert(hisVector, 1);
    printVector(myVector);
    myVector.erase(2, 3);
    printVector(myVector);
    myVector.erase(1, 10);
    printVector(myVector);
    myVector.insert(hisVector, 1);
    printVector(myVector);
    myVector.eraseBetween(1,2);
    printVector(myVector);
    myVector.eraseBetween(1,10);
    printVector(myVector);
    myVector.insert(hisVector, 1);
    printVector(myVector);
    std::cout << myVector.find(11) << std::endl;
    std::cout << myVector.find(33) << std::endl;
    return 0;
}