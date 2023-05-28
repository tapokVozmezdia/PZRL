#include "HashTable.h"
#include <iostream>
#include <stdexcept>

HashTable::HashTable(size_t size) noexcept
{
    this->_capacity = size;
    for (int i = 0; i < this->_capacity; ++i)
    {
        auto tmp = new std::list<std::pair<KeyType, ValueType>>;
        this->table.push_back(*tmp);
        delete tmp;
    }
}

HashTable::HashTable(const HashTable& other)
{
    this->_capacity = other._capacity;
    for (int i = 0; i < this->_capacity; ++i)
    {
        auto tmp = other.table[i];
        this->table.push_back(tmp);
    }
    this->_filled = other._filled;
}

HashTable& HashTable::operator=(const HashTable& other)
{
    while (this->table.size() > 0)
    {
        this->table.pop_back();
    }
    this->_filled = 0;
    this->_capacity = other._capacity;
    for (int i = 0; i < this->_capacity; ++i)
    {
        auto tmp = other.table[i];
        this->table.push_back(tmp);
    }
    this->_filled = other._filled;
    return *this;
}

HashTable::HashTable(HashTable&& other) noexcept
{
    this->_capacity = other._capacity;
    for (int i = 0; i < this->_capacity; ++i)
    {
        auto tmp = other.table[i];
        this->table.push_back(tmp);
    }
    this->_filled = other._filled;
    while (other.table.size() > 0)
    {
        auto i = other.table.end();
        while ((*i).size() > 0)
        {
            (*i).pop_back();
        }
        other.table.pop_back();
    }
    other._filled = 0;
}

HashTable& HashTable::operator=(HashTable&& other) noexcept
{
    while (this->table.size() > 0)
    {
        this->table.pop_back();
    }
    this->_filled = 0;
    this->_capacity = other._capacity;
    auto it = other.table.begin();
    while(it != other.table.end())
    {
        this->table.push_back(*it);
        it++;
    }
    this->_filled = other._filled;
    while (other.table.size() > 0)
    {
        auto i = other.table.end();
        while ((*i).size() > 0)
        {
            (*i).pop_back();
        }
        other.table.pop_back();
    }
    other._filled = 0;
    return *this;
}

HashTable::~HashTable()
{
    while (this->table.size() > 0)
    {
        auto i = this->table.end();
        while ((*i).size() > 0)
        {
            (*i).pop_back();
        }
        this->table.pop_back();
    }
    this->_filled = 0;
}

bool HashTable::find(const KeyType &key, const ValueType &value) const
{
    size_t hash = hash_function(key);
    auto cell = table[hash % this->_capacity];
    auto i = cell.begin();
    while (i != cell.end())
    {
        if ((*i).first == key && (*i).second == value)
        {
            return true;
        }
    }
    return false;
}

void HashTable::insert(const KeyType& key, const ValueType& value)
{
    size_t hash = hash_function(key);
    table[hash % this->_capacity].push_back(std::pair<KeyType, ValueType>(key, value));
    _filled++;
    if (this->getLoadFactor() > 0.75)
    {
        this->_capacity *= 2;
        for (int i = this->_filled; i < this->_capacity; ++i)
        {
            auto tmp = new std::list<std::pair<KeyType, ValueType>>;
            this->table.push_back(*tmp);
            delete tmp;
        }
    }
}

void HashTable::remove(const KeyType& key)
{
    size_t hash = hash_function(key);
    std::list<std::pair<KeyType, ValueType>>* cell = &table[hash % this->_capacity];
    auto i = cell->begin();
    while(i != cell->end())
    {
        if ((*i).first == key)
        {
            cell->erase(i);
            return;
        }
        i++;
    }
}

ValueType& HashTable::operator[](const KeyType& key)
{
    size_t hash = hash_function(key);
    std::list<std::pair<KeyType, ValueType>>* cell = &table[hash % this->_capacity];
    auto i = cell->begin();
    while(i != cell->end())
    {
        if ((*i).first == key)
        {
            return (*i).second;
        }
        i++;
    }
    throw std::out_of_range("Invalid key for hash table");
}

double HashTable::getLoadFactor()
{
    return static_cast<double>(_filled)/static_cast<double>(_capacity);
}

size_t HashTable::hash_function(const KeyType& key) const // FOR STD::STRING ONLY!!!
{ 
    auto i = key.begin();
    int factor = 1;
    size_t hash = 0;
    while (i != key.end())
    {
        hash += factor * static_cast<int>(*i);
        i++;
        factor++;
    }
    return hash;
}