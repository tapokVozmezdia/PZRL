#include <list>
#include <iostream>
#include "Stack.h"

/*
using valueType = int;

const valueType& getTop(std::list<valueType>& list)
{
    std::list<valueType>::const_iterator i = list.end();
    --i;
    return *i;
}

void printList(std::list<valueType>& list)
{
    std::list<valueType>::const_iterator it = list.begin();
    for (int i = 0; i < list.size(); ++i)
    {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << std::endl;
}
*/

int main()
{
    //std::list<valueType> _data;
    //_data.push_front(10);
    //_data.push_back(121);
    //_data.push_back(5512);
    //printList(_data);
    //std::cout << getTop(_data) << std::endl;

    double ar[3] = {1, 2, 3};
    std::cout << "KRISK" << std::endl;
    Stack myStack(ar, 3, StackContainer::List);
    std::cout << myStack.top() << std::endl;
    myStack.push(111);
    std::cout << myStack.top() << std::endl;
    Stack newStack(myStack);
    std::cout << newStack.top() << std::endl;
    newStack.pop();
    std::cout << myStack.top() << std::endl;
    std::cout << newStack.top() << std::endl;
    return 0;
}