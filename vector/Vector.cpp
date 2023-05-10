#include "Vector.h"

size_t Vector::size() const
{
    return this->_size;
}

size_t Vector::capacity() const 
{
    return this->_capacity;
}

double Vector::loadFactor() const
{
    //

        // TO BE DONE!!!

    //
    return 1.;
}

Vector::Vector(const Value* rawArray, const size_t size, float coef)
{
    _multiplicativeCoef = coef;
    _size = size;
    _capacity = size;
    _data = new Value[_capacity];
    for (int i = 0; i < size; ++i)
    {
        //std::cout <<"To be put: "<< rawArray[i] << std::endl;
        _data[i] = rawArray[i];
        //std::cout <<"What's in: "<< _data[i] << std::endl;
    }
}

Vector::Vector(const Vector& other)
{
    _size = other.size();
    _capacity = other.capacity();
    _multiplicativeCoef = 1.;
    this->_data = new Value[_capacity];
    for (int i = 0; i < _size; ++i)
    {
        _data[i] = other[i];
    }
}

Value& Vector::operator[](size_t idx)
{
    Iterator i(_data);
    for (int counter = 0; counter < idx; ++counter)
    {
        i++;
    }
    return *i;
}

const Value& Vector::operator[](size_t idx) const
{
    Iterator i(_data);
    for (int counter = 0; counter < idx; ++counter)
    {
        i++;
    }
    return *i;
}

Vector& Vector::operator=(const Vector& other)
{
    if (this->_data != nullptr)
    {
        delete [] this->_data;
    }
    _size = other.size();
    _capacity = other.capacity();
    _multiplicativeCoef = 1.;
    this->_data = new Value[_capacity];
    for (int i = 0; i < _size; ++i)
    {
        _data[i] = other[i];
    }
    return *this;
}

Vector::Vector(Vector&& other) noexcept
{
    _size = other.size();
    _capacity = other.capacity();
    _multiplicativeCoef = 1.;
    this->_data = new Value[_capacity];
    for (int i = 0; i < _size; ++i)
    {
        _data[i] = other[i];
    }
    other.~Vector();
}

Vector& Vector::operator=(Vector&& other) noexcept
{
    if (this->_data != nullptr)
    {
        delete [] this->_data;
    }
    _size = other.size();
    _capacity = other.capacity();
    _multiplicativeCoef = 1.;
    this->_data = new Value[_capacity];
    for (int i = 0; i < _size; ++i)
    {
        _data[i] = other[i];
    }
    other.~Vector();
    return *this;
}

void Vector::pushBack(const Value& value)
{
    _size += 1;
    _capacity = _size;
    Value* tmp = new Value[_capacity];
    for (int i = 0; i < _size - 1; ++i)
    {
        tmp[i] = _data[i];
    }
    tmp[_size - 1] = value;
    delete [] _data;
    _data = tmp;
}

void Vector::pushFront(const Value& value)
{
    _size += 1;
    _capacity = _size;
    Value* tmp = new Value[_capacity];
    for (int i = 1; i < _size; ++i)
    {
        tmp[i] = _data[i - 1];
    }
    tmp[0] = value;
    delete [] _data;
    _data = tmp;
}

void Vector::popBack()
{
    _size -= 1;
    _capacity = _size;
    Value* tmp = new Value[_capacity];
    for (int i = 0; i < _size; ++i)
    {
        tmp[i] = _data[i];
    }
    delete [] _data;
    _data = tmp;
}

void Vector::popFront()
{
    _size -= 1;
    _capacity = _size;
    Value* tmp = new Value[_capacity];
    for (int i = 1; i < _size + 1; ++i)
    {
        tmp[i - 1] = _data[i];
    }
    delete [] _data;
    _data = tmp;
}

void Vector::insert(const Value& value, size_t pos)
{
    _size += 1;
    _capacity = _size;
    Value* tmp = new Value[_capacity];
    int j = 0;
    for (int i = 0; i < _size; ++i)
    {
        if (i == pos)
        {
            tmp[i] = value;
            j++;
            continue;
        }
        tmp[i] = _data[i - j];
    }
    delete [] _data;
    _data = tmp;    
}

void Vector::insert(const Value* values, size_t size, size_t pos)
{
    _size += size;
    _capacity = _size;
    Value* tmp = new Value[_capacity];
    int j = 0;
    for (int i = 0; i < _size; ++i)
    {
        if (i == pos)
        {
            for (int k = 0; k < size; ++k)
            {
                tmp[i + k] = values[k];
                j++;
            }
            i += (size - 1);
            continue;
        }
        tmp[i] = _data[i - j];
    }
    delete [] _data;
    _data = tmp;    
}

void Vector::insert(const Vector& vector, size_t pos)
{
    _size += vector.size();
    _capacity = _size;
    Value* tmp = new Value[_capacity];
    int j = 0;
    for (int i = 0; i < _size; ++i)
    {
        if (i == pos)
        {
            for (int k = 0; k < vector.size(); ++k)
            {
                tmp[i + k] = vector[k];
                j++;
            }
            i += (vector.size() - 1);
            continue;
        }
        tmp[i] = _data[i - j];
    }
    delete [] _data;
    _data = tmp;    
}

void Vector::erase(size_t pos, size_t count)
{
    if (pos + count <= _size) {
        _size -= count;
        _capacity = _size;
        Value* tmp = new Value[_capacity];
        int j = 0;
        for (int i = 0; i < _size + count; ++i)
        {
            if (i >= pos && j < count)
            {
                ++j;
                continue;
            }
            tmp[i - j] = _data[i];
        }
        delete [] _data;
        _data = tmp;
    }
    else {
        count = _size - pos;
        _size -= count;
        _capacity = _size;
        Value* tmp = new Value[_capacity];
        for (int i = 0; i < _size; ++i)
        {
            tmp[i] = _data[i];
        }
        delete [] _data;
        _data = tmp;
    }
}

void Vector::eraseBetween(size_t beginPos, size_t endPos)
{
    if (endPos <= _size) {
        _size -= (endPos - beginPos);
        _capacity = _size;
        Value* tmp = new Value[_capacity];
        int j = 0;
        for (int i = 0; i < _size + (endPos - beginPos); ++i)
        {
            if (i >= beginPos && i < endPos)
            {
                ++j;
                continue;
            }
            tmp[i - j] = _data[i];
        }
        delete [] _data;
        _data = tmp;
    }
    else {
        _size = beginPos;
        _capacity = _size;
        Value* tmp = new Value[_capacity];
        for (int i = 0; i < _size; ++i)
        {
            tmp[i] = _data[i];
        }
        delete [] _data;
        _data = tmp;
    }
}

long long Vector::find(const Value& value) const
{
    for (int i = 0; i <= _size; ++i)
    {
        if (_data[i] == value)
        {
            return i;
        }
    }
    return -1;
}

void Vector::reserve(size_t capacity)
{
    if (capacity <= _capacity)
    {
        return;
    }
    _capacity = capacity;
    Value* tmp = new Value[_capacity];
    for (int i = 0; i < _size; ++i)
    {
        tmp[i] = _data[i];
    }
    delete [] _data;
    _data = tmp;
}

void Vector::shrinkToFit()
{
    _capacity = _size;
    Value* tmp = new Value[_capacity];
    for (int i = 0; i < _size; ++i)
    {
        tmp[i] = _data[i];
    }
    delete [] _data;
    _data = tmp;
}

Vector::Iterator::Iterator(Value* ptr)
{
    _ptr = ptr;
}

const Value& Vector::Iterator::operator*() const
{
    return *_ptr;
}

Value& Vector::Iterator::operator*()
{
    //std::cout << "correct!" << std::endl;
    //Value &n = *_ptr;
    //return n;
    return *_ptr;
}

Vector::Iterator Vector::Iterator::operator++()
{
    //std::cout << "Before: " << _ptr;
    ++_ptr;
    //std::cout << "After: "  << _ptr;
    return *this;
}

Vector::Iterator Vector::Iterator::operator++(int num)
{
    /*for (int i = 0; i < num; ++i)
    {
        ++_ptr;
    }
    return *this;*/
    //std::cout << "Before: " << _ptr;
    ++_ptr;
    //std::cout << "After: "  << _ptr;
    return *this;
}

Value* Vector::Iterator::operator->()
{
    return _ptr;
}

const Value* Vector::Iterator::operator->() const
{
    return _ptr;
}

bool Vector::Iterator::operator==(const Iterator& other) const
{
    
}

bool Vector::Iterator::operator!=(const Iterator& other) const
{
    
}

Vector::Iterator Vector::begin()
{
    Iterator i(_data);
    return i;
}

Vector::Iterator Vector::end()
{
    Iterator i(_data);
    for (int j = 0; j < _size; ++j)
    {
        ++i;
    }
    return i;
}

Vector::~Vector()
{ 
    _size = 0;
    _capacity = 0;
    _multiplicativeCoef = 2.0f;
    delete [] this->_data;
    _data = nullptr;
}