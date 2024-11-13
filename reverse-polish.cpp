#include <iostream>
#include <string>
#include <cctype>
#include <sstream>
#include <cmath>
#include "stack.hpp"

using namespace std;

// Функция для определения приоритета оператора
int prec(char c) {
    if (c == '/' || c == '*') return 2;
    else if (c == '+' || c == '-') return 1;
    else return -1;
}

string infixToPostfix(string& line) {
    Stack<char> st;  // Используем стек для символов
    string result;
    int i = 0;

    while (i < line.length()) {
        char c = line[i];

        if (isdigit(c)) {
            // Если это цифра, собираем все символы в число
            while (i < line.length() && isdigit(line[i])) {
                result += line[i];
                i++;
            }
            result += ' '; // Разделитель для чисел
        }
        else if (c == '(') {
            st.push(c);  // push открывающую скобку
            i++;
        }
        else if (c == ')') {
            // Пока на верхушке стека не окажется открывающая скобка, выталкиваем операторы в результат
            while (!st.empty() && st.Top() != '(') {
                result += st.Top();
                st.pop();
                result += ' ';  // Разделитель для оператора
            }
            st.pop();  // Убираем из стека '('
            i++;
        }
        else {
            // Выталкиваем операторы с более высоким или равным приоритетом
            while (!st.empty() && prec(c) <= prec(st.Top())) {
                result += st.Top();
                st.pop();
                result += ' ';  // Разделитель для оператора
            }
            st.push(c);  // push текущий оператор в стек
            i++;
        }
    }

    // Выталкиваем оставшиеся операторы из стека в результат
    while (!st.empty()) {
        result += st.Top();
        st.pop();
        result += ' ';  // Разделитель для оператора
    }

    // Убираем последний лишний пробел в конце строки
    if (!result.empty() && result[result.length() - 1] == ' ') {
        result.pop_back();
    }

    return result;
}


int RPN(string line) {
    Stack<int> values;
    istringstream tokens(line);
    string token;
    
    while (tokens >> token) {
        if (isdigit(token[0])) {
            // Если токен — это число, добавляем его в стек
            values.push(stoi(token));
        }
        else {
            // Если токен — это оператор, извлекаем два числа из стека
            if (values.empty()) {
                cout << "Error: insufficient values in stack." << endl;
                return -1;
            }
            int a = values.Top(); values.pop();
            if (values.empty()) {
                cout << "Error: insufficient values in stack." << endl;
                return -1;
            }
            int b = values.Top(); values.pop();
            int result = 0;

            switch (token[0]) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': 
                    if (b == 0) {
                        cout << "Error: division by zero." << endl;
                        return -1;
                    }
                    result = a / b; 
                    break;
                default: 
                    cout << "Invalid operator: " << token[0] << endl; 
                    return -1;
            }

            // Помещаем результат обратно в стек
            values.push(result);
        }
    }

    // В стеке должно остаться только одно число — это результат
    return values.Top();
}

int main() {
    string line;
    cin >> line;  // Ввод строки
    string result = infixToPostfix(line);  // Преобразование инфиксной записи в постфиксную
    cout << RPN(result);  // Вычисление результата
    return 0;
}
