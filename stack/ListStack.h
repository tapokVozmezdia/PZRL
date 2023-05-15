#pragma once

#include <list>

#include "StackImplementation.h"


class ListStack : public IStackImplementation {
public:
    ListStack() = default;

    ListStack(const ListStack& listStack);

    // добавление в хвост
    void push(const ValueType& value) override;
    // удаление с хвоста
    void pop() override;
    // посмотреть элемент в хвосте
    const ValueType& top() const override;
    // проверка на пустоту
    bool isEmpty() const override;
    // размер 
    size_t size() const override;

private:
    std::list<ValueType> _data;
};


ListStack::ListStack(const ListStack& listStack) {
    _data = listStack._data;
}

void ListStack::push(const ValueType& value) {
    _data.push_back(value);
}

void ListStack::pop() {
    _data.pop_back();
}

const ValueType& ListStack::top() const {
    std::list<ValueType>::const_iterator i = _data.end();
    --i;
    return *i;
}

bool ListStack::isEmpty() const {
    return _data.empty();
}

size_t ListStack::size() const {
    return _data.size();
}