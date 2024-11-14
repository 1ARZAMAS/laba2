#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

const int SIZE = 500;

struct HashTableItem {
    std::string data; // Только значение
    HashTableItem* next; // Указатель на следующий элемент
};

struct HashTable {
    HashTableItem* items[SIZE]; // Массив указателей на элементы хеш-таблицы
    int count; // Количество элементов

    HashTable() : count(0) {
        for (int i = 0; i < SIZE; i++) {
            items[i] = nullptr; // Инициализируем таблицу пустыми указателями
        }
    }

    int HashFun(const std::string& data); // Хеш-функция
    HashTableItem* createItem(const std::string& data); // Создание элемента
    void push(const std::string& data); // Добавление элемента
    void pop(const std::string& data); // Удаление элемента
    void get(const std::string& data); // Проверка наличия элемента
    void clear(); // Очистка таблицы
};

int HashTable::HashFun(const std::string& data) {
    const int prime = 43; // Простое число для улучшения хеширования
    int hash = 0;
    for (char letter : data) {
        hash = (hash * prime + static_cast<int>(letter)) % SIZE; // Хэшируем через ASCII код
    }
    return hash;
}

HashTableItem* HashTable::createItem(const std::string& data) {
    return new HashTableItem{ data, nullptr };
}

void HashTable::push(const std::string& data) {
    int index = HashFun(data); // Получаем индекс для этого значения
    HashTableItem* item = createItem(data);

    if (items[index] == nullptr) {
        items[index] = item; // Вставляем элемент в пустую ячейку
        count++;
    } else {
        HashTableItem* current = items[index];
        // Проверяем, есть ли уже такое значение
        while (current != nullptr) {
            if (current->data == data) {
                // Если значение уже есть, ничего не делаем
                delete item;
                return;
            }
            current = current->next;
        }
        // Если значение уникально, добавляем его в конец цепочки
        item->next = items[index];
        items[index] = item;
        count++;
    }
}

void HashTable::pop(const std::string& data) {
    int index = HashFun(data); // Получаем индекс для этого значения
    HashTableItem* current = items[index];
    HashTableItem* prev = nullptr;

    while (current != nullptr) {
        if (current->data == data) {
            if (prev == nullptr) {
                items[index] = current->next; // Удаляем первый элемент в цепочке
            } else {
                prev->next = current->next; // Удаляем элемент, указывая на следующий
            }
            delete current;
            count--;
            return;
        }
        prev = current;
        current = current->next;
    }

    cout << "This value is not in the table" << endl; // Если элемент не найден
}

void HashTable::get(const std::string& data) {
    int index = HashFun(data); // Получаем индекс для этого значения
    HashTableItem* current = items[index];

    while (current != nullptr) {
        if (current->data == data) {
            cout << "Element " << data << " is in the table" << endl;
            return;
        }
        current = current->next;
    }

    cout << "Element " << data << " is not in the table" << endl;
}

void HashTable::clear() {
    for (int i = 0; i < SIZE; ++i) {
        HashTableItem* current = items[i];
        while (current != nullptr) {
            HashTableItem* temp = current;
            current = current->next;
            delete temp; // Удаление элемента
        }
        items[i] = nullptr;
    }
    count = 0;
}