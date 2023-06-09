#pragma once
#include <vector>
#include <list>
#include <string>
#include <utility>

using KeyType = std::string;
using ValueType = double;

class HashTable 
{
public:
    //! Конструктор
    explicit HashTable(size_t size = 100) noexcept;
    //! Деструктор
    ~HashTable();

    //Свои конструкторы

    //! Копирование
    explicit HashTable(const HashTable& other);
    HashTable& operator=(const HashTable& other);
    //! Перемещение
    explicit HashTable(HashTable&& other) noexcept;
    HashTable& operator=(HashTable&& other) noexcept;

    size_t capacity() const;

    //Конец своих конструкторов и операторов

    //! Вставка элемента в хеш-таблицу
    //! Если при вставке обнаруживается, что LoadFactor таблицы превышает 0.75, то таблица расширяется в 2 раза.
    void insert(const KeyType &key, const ValueType &value);
    //! Поиск элемента в хеш таблице
    bool find(const KeyType &key, const ValueType &value) const;
    //! Удаление элемента из хеш-таблицы
    void remove(const KeyType &key);

    //! Удаление элемента из хеш-таблицы
    // void remove(const KeyType &key, ValueType &value);

    //! Получение элемента по ключу
    ValueType& operator[](const KeyType &key);

    //! Загрузка хеш-таблицы. Считается как отношение количества занятых ячеек к вместимости хеш-таблицы.
    double getLoadFactor();

private:
    int32_t _capacity = 100;  //!< Вместимость хеш-таблицы
    int32_t _filled = 0;    //!< Текущее количество занятых ячеек хеш-таблицы

    //! Структура, на которой основана таблица с методом цепочек для решения коллизий
    std::vector<std::list<std::pair<KeyType, ValueType>>> table;
    //! Хеш-функция
    size_t hash_function(const KeyType &key) const; 
};
