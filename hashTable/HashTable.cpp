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

HashTable::~HashTable()
{
    
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