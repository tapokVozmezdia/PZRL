#include "Stack.h"
#include "ListStack.h"
#include "VectorStack.h"
#include "StackImplementation.h"

#include <stdexcept>


Stack::Stack(StackContainer container)
    : _containerType(container)
{
    switch (container)
    {
    case StackContainer::List: {
        _pimpl = dynamic_cast<IStackImplementation*>(new ListStack());    // конкретизируйте под ваши конструкторы, если надо
        break;
    }
    case StackContainer::Vector: {
        _pimpl = dynamic_cast<IStackImplementation*>(new VectorStack());    // конкретизируйте под ваши конструкторы, если надо
        break;
    }
    default:
        throw std::runtime_error("Неизвестный тип контейнера");
    }
}

Stack::Stack(const ValueType* valueArray, const size_t arraySize, StackContainer container)
{
    // принцип тот же, что и в прошлом конструкторе
    switch (container)
    {
    case StackContainer::List: {
        _pimpl = dynamic_cast<IStackImplementation*>(new ListStack());    // конкретизируйте под ваши конструкторы, если надо
        for (int i = 0; i < arraySize; ++i)
        {
            _pimpl->push(valueArray[i]);
        }
        break;
    }
    case StackContainer::Vector: {
        _pimpl = dynamic_cast<IStackImplementation*>(new VectorStack());    // конкретизируйте под ваши конструкторы, если надо
        for (int i = 0; i < arraySize; ++i)
        {
            _pimpl->push(valueArray[i]);
        }
        break;
    }
    default:
        throw std::runtime_error("Неизвестный тип контейнера");
    }
}

Stack::Stack(const Stack& copyStack)
{
    this->_containerType = copyStack._containerType;
    switch (_containerType)
    {
        case StackContainer::Vector :
        {
            this->_pimpl = static_cast<IStackImplementation*>(new VectorStack());
            break;
        }
        case StackContainer::List :
        {
            this->_pimpl = static_cast<IStackImplementation*>(new ListStack());
            break;
        }
        default :
        {
            throw std::runtime_error("Неизвестный тип контейнера");
        }
    }
    ValueType* tmp = new ValueType[copyStack.size()];
    size_t size_tmp = copyStack.size();
    for (int i = 0; i < size_tmp; ++i)
    {
        tmp[i] = copyStack.top();
        copyStack._pimpl->pop();
    }
    for (int i = 0; i < size_tmp; ++i)
    {
        copyStack._pimpl->push(tmp[size_tmp - 1 - i]);
        this->_pimpl->push(tmp[size_tmp - 1 - i]);
    }
    delete [] tmp;
}

Stack& Stack::operator=(const Stack& copyStack)
{
    // TODO: вставьте здесь оператор return
    if (this->_pimpl != nullptr)
    {
        delete _pimpl;
        _pimpl = nullptr;
    }
    this->_containerType = copyStack._containerType;
    switch (_containerType)
    {
        case StackContainer::Vector :
        {
            this->_pimpl = static_cast<IStackImplementation*>(new VectorStack());
            break;
        }
        case StackContainer::List :
        {
            this->_pimpl = static_cast<IStackImplementation*>(new ListStack());
            break;
        }
        default :
        {
            throw std::runtime_error("Неизвестный тип контейнера");
        }
    }
    ValueType* tmp = new ValueType[copyStack.size()];
    size_t size_tmp = copyStack.size();
    for (int i = 0; i < size_tmp; ++i)
    {
        tmp[i] = copyStack.top();
        copyStack._pimpl->pop();
    }
    for (int i = 0; i < size_tmp; ++i)
    {
        copyStack._pimpl->push(tmp[size_tmp - 1 - i]);
        this->_pimpl->push(tmp[size_tmp - 1 - i]);
    }
    delete [] tmp;
    return *this;
}

Stack::~Stack()
{
    delete _pimpl;        // композиция!
}

void Stack::push(const ValueType& value)
{
    // можно, т.к. push определен в интерфейсе
    _pimpl->push(value);
}

void Stack::pop()
{
    _pimpl->pop();
}

const ValueType& Stack::top() const
{
    return _pimpl->top();
}

bool Stack::isEmpty() const
{
    return _pimpl->isEmpty();
}

size_t Stack::size() const
{
    return _pimpl->size();
}