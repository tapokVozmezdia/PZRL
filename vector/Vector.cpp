#include "Vector.h"
#include <stdexcept>

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
    return static_cast<double>(_size) / static_cast<double>(_capacity);
}

Vector::Vector(const Value* rawArray, const size_t size, float coef)
{
    _multiplicativeCoef = coef;
    _size = size;
    _capacity = size;
    _data = new Value[_size];
    for (int i = 0; i < size; ++i)
    {
        //std::cout <<"To be put: "<< rawArray[i] << std::endl;
        _data[i] = rawArray[i];
        //std::cout <<"What's in: "<< _data[i] << std::endl;
    }
}

Vector::Vector(const Vector& other)
{
    if (this != &other)
    {
        _size = other.size();
        _capacity = other.size();
        _multiplicativeCoef = other._multiplicativeCoef;
        this->_data = new Value[_size];
        for (int i = 0; i < _size; ++i)
        {
            _data[i] = other[i];
        }
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
    if (this != &other)
    {    
        if (this->_data != nullptr)
        {
            delete [] this->_data;
        }
        _size = other.size();
        _capacity = other.size();
        _multiplicativeCoef = other._multiplicativeCoef;
        this->_data = new Value[_size];
        for (int i = 0; i < _size; ++i)
        {
            _data[i] = other[i];
        }
    }
    return *this;
}

Vector::Vector(Vector&& other) noexcept
{
    if (this != &other)
    {
        _size = other.size();
        _capacity = other.size();
        _multiplicativeCoef = other._multiplicativeCoef;
        this->_data = other._data;
        other._size = 0;
        other._capacity = 0;
        other._multiplicativeCoef = 2.0f;
        other._data = nullptr;
    }
}

Vector& Vector::operator=(Vector&& other) noexcept
{
    if (this != &other)
    {
        delete [] this->_data;
        _size = other.size();
        _capacity = other.size();
        this->_multiplicativeCoef = other._multiplicativeCoef;
        this->_data = other._data;
        other._capacity = 0;
        other._size = 0;
        other._multiplicativeCoef = 2.0f;
        other._data = nullptr;
    }
    return *this;
}

void Vector::pushBack(const Value& value)
{
    /*_size += 1;
    _capacity = _size;
    Value* tmp = new Value[_size];
    for (int i = 0; i < _size - 1; ++i)
    {
        tmp[i] = _data[i];
    }
    tmp[_size - 1] = value;
    delete [] _data;
    _data = tmp;*/
    if (_size == 0)
    {
        this->reserve(_multiplicativeCoef);
    }
    else if (this -> loadFactor() == 1)
    {
        this->reserve(_size * _multiplicativeCoef);
    }
    *this->end() = value;
    ++_size;
}

void Vector::pushFront(const Value& value)
{
    /*
    _size += 1;
    _capacity = _size;
    Value* tmp = new Value[_size];
    for (int i = 1; i < _size; ++i)
    {
        tmp[i] = _data[i - 1];
    }
    tmp[0] = value;
    delete [] _data;
    _data = tmp;
    */
    if (_size == 0)
    {
        this->reserve(_multiplicativeCoef);
    }
    else if (this->loadFactor() == 1)
    {
        this->reserve(_size * _multiplicativeCoef);
    }
    _size += 1;
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
    if (_size == 0)
    {
        throw std::out_of_range ("Pop Back on empty vector!");
    }
    _size -= 1;
    Value* tmp = new Value[_size];
    for (int i = 0; i < _size; ++i)
    {
        tmp[i] = _data[i];
    }
    delete [] _data;
    _data = tmp;
}

void Vector::popFront()
{
    if (_size == 0)
    {
        throw std::out_of_range ("Pop Front on empty vector!");
    }
    _size -= 1;
    Value* tmp = new Value[_size];
    for (int i = 1; i < _size + 1; ++i)
    {
        tmp[i - 1] = _data[i];
    }
    delete [] _data;
    _data = tmp;
}

/*void Vector::insert(const Value& value, size_t pos)
{
    _size += 1;
    _capacity = _size;
    Value* tmp = new Value[_size];
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
}*/

void Vector::insert(const Value& value, size_t pos)
{
    if (_size == 0)
    {
        this->reserve(_multiplicativeCoef);
    }
    else if (this->loadFactor() == 1)
    {
        this->reserve(_size * _multiplicativeCoef);
    }
    int j = 0;
    ++_size;
    Value* tmp = new Value[_size];
    for (int i = 0; i < _size; ++i)
    {
        if (pos == i)
        {
            j++;
            tmp[i] = value;
            continue;
        }
        tmp[i] = _data[i - j];
    }
    delete [] _data;
    _data = tmp;
}

void Vector::insert(const Value* values, size_t size, size_t pos)
{
    for (int i = 0; i < size; ++i)
    {
        this->insert(values[i], pos + i);
    }
}

void Vector::insert(const Vector& vector, size_t pos)
{
    for (int i = 0; i < vector.size(); ++i)
    {
        this->insert(vector[i], pos + i);
    }
}

/*
void Vector::insert(const Value* values, size_t size, size_t pos)
{
    _size += size;
    _capacity = _size;
    Value* tmp = new Value[_size];
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
    Value* tmp = new Value[_size];
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
*/

void Vector::erase(size_t pos, size_t count)
{
    if (_size == 0)
    {
        throw std::out_of_range ("Erase on empty vector!");
    }
    if (pos < 0 || pos >= _size)
    {
        throw std::out_of_range ("Erase on empty vector!");
    }
    if (pos + count <= _size) {
        _size -= count;
        _capacity = _size;
        Value* tmp = new Value[_size];
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
        Value* tmp = new Value[_size];
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
    if (_size == 0)
    {
        throw std::out_of_range ("Erase on empty vector!");
    }
    if (beginPos < 0)
    {
        throw std::out_of_range ("Erase on empty vector!");
    }
    if (endPos <= _size) {
        _size -= (endPos - beginPos);
        _capacity = _size;
        Value* tmp = new Value[_size];
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
        Value* tmp = new Value[_size];
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
    Value* tmp = new Value[_size];
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
     return _ptr == other._ptr;
}

bool Vector::Iterator::operator!=(const Iterator& other) const
{
    return _ptr != other._ptr;
}

Vector::Iterator Vector::begin()
{
    Iterator i(_data);
    return i;
}

Vector::Iterator Vector::end()
{
    Iterator i(_data + _size);
    return i;
}

Vector::~Vector()
{ 
    delete [] this->_data;
    _data = nullptr;
    _size = 0;
    _capacity = 0;
    _multiplicativeCoef = 2.0f;
}