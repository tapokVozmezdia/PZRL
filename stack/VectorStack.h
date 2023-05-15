#pragma once

#include <vector>

#include "StackImplementation.h"


class VectorStack : public IStackImplementation {
public:
    VectorStack() = default;

    VectorStack(const VectorStack& vectorStack);

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
    std::vector<ValueType> _data;
};


VectorStack::VectorStack(const VectorStack& vectorStack) {
    _data = vectorStack._data;
}

void VectorStack::push(const ValueType& value) {
    _data.push_back(value);
}

void VectorStack::pop() {
    _data.pop_back();
}

const ValueType& VectorStack::top() const {
    return _data[_data.size() - 1];
}

bool VectorStack::isEmpty() const {
    return _data.empty();
}

size_t VectorStack::size() const {
    return _data.size();
}

