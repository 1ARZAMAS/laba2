#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

template <typename T>
struct CustomArray {
    T* data; // Массив строк
    int size; // Текущий размер списка
    int capacity; // Максимальная вместимость массива

    // Конструкторы
    CustomArray(int max);
    ~CustomArray();

    void add(int index, T value); // добавление
    void addToTheEnd(T value); // добавить в конец
    void get(int index); // получение по индексу
    void remove(int index); // удаление
    void replace(int index, T value); // замена
    void length(); // длина
    void display(); // вывод на экран

    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of bounds");
        }
        return data[index];
    }

    T& operator[](int index) const {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of bounds");
        }
        return data[index];
    }
};

template <typename T>
CustomArray<T>::CustomArray(int capacity) : capacity(capacity), size(0) {
    data = new T[capacity];
}

template <typename T>
CustomArray<T>::~CustomArray() {
    delete[] data; // освобождаем память
}

template <typename T>
void CustomArray<T>::add(int index, T value) {
    if (index < 0 || index > size || size >= capacity) {
        cout << "Index invalid or array is full" << endl;
        return;
    }
    // сдвигаем элементы вправо
    for (int i = size; i > index; i--) {
        data[i] = data[i - 1];
    }
    data[index] = value; // вставляем элемент
    size++;
}

template <typename T>
void CustomArray<T>::addToTheEnd(T value) {
    if (size >= capacity) {
        cout << "Array is full" << endl;
        return;
    }
    data[size] = value; // вставляем элемент в конец
    size++;
}

template <typename T>
void CustomArray<T>::remove(int index) {
    if (index < 0 || index >= size) {
        cout << "Index invalid" << endl;
        return;
    }
    // сдвигаем элементы влево
    for (int i = index; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
}

template <typename T>
void CustomArray<T>::replace(int index, T value) {
    if (index < 0 || index >= size) {
        cout << "Index invalid" << endl;
        return;
    }
    data[index] = value; // замена элемента
}

template <typename T>
void CustomArray<T>::display() {
    if (int j = 0 == size) {
        cout << "Array is empty" << endl;
    } else {
        for (int i = 0; i < size; i++) {
        cout << data[i] << " ";
    }
    cout << endl;
    }
    
}

template <typename T>
void CustomArray<T>::length() {
    cout << "Size of the array is: " << size << endl;
}

template <typename T>
void CustomArray<T>::get(int index) {
    if (size == 0) {
        std::cout << "Массив пуст!" << std::endl;
        return;
    }
    if (index < 0 || index >= size) {
        std::cout << "Index invalid" << std::endl;
        return;
    }
    std::cout << "Element by index " << index << ": " << data[index] << std::endl;
}