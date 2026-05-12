#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

class Vector {
private:
    int* data;
    int size;
    int maxSize;

public:
    Vector();
    Vector(int vectorSize, int vectorMaxSize);
    Vector(const Vector& other);
    ~Vector();

    Vector& operator=(const Vector& other);

    int& operator[](int index);
    int operator()() const;

    Vector& operator--();
    Vector operator--(int);

    void fill();
    void print() const;
};

Vector::Vector() {
    cout << "Вызван конструктор Vector без параметров" << endl;

    maxSize = 10;
    size = 0;
    data = new int[maxSize];
}

Vector::Vector(int vectorSize, int vectorMaxSize) {
    cout << "Вызван конструктор Vector с параметрами" << endl;

    if (vectorSize > vectorMaxSize) {
        throw invalid_argument("Ошибка: размер вектора больше максимального размера.");
    }

    if (vectorSize < 0 || vectorMaxSize <= 0) {
        throw invalid_argument("Ошибка: некорректные размеры вектора.");
    }

    size = vectorSize;
    maxSize = vectorMaxSize;
    data = new int[maxSize];

    for (int i = 0; i < size; i++) {
        data[i] = 0;
    }
}

Vector::Vector(const Vector& other) {
    cout << "Вызван конструктор копирования Vector" << endl;

    size = other.size;
    maxSize = other.maxSize;
    data = new int[maxSize];

    for (int i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
}

Vector::~Vector() {
    cout << "Вызван деструктор Vector" << endl;
    delete[] data;
}

Vector& Vector::operator=(const Vector& other) {
    cout << "Вызван оператор присваивания" << endl;

    if (this != &other) {
        delete[] data;

        size = other.size;
        maxSize = other.maxSize;
        data = new int[maxSize];

        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    return *this;
}

int& Vector::operator[](int index) {
    if (index < 0) {
        throw out_of_range("Ошибка: индекс меньше нуля.");
    }

    if (index >= size) {
        throw out_of_range("Ошибка: индекс больше текущего размера вектора.");
    }

    return data[index];
}

int Vector::operator()() const {
    return size;
}

Vector& Vector::operator--() {
    cout << "Вызван префиксный оператор --" << endl;

    if (size == 0) {
        throw runtime_error("Ошибка: попытка удалить элемент из пустого вектора.");
    }

    for (int i = 0; i < size - 1; i++) {
        data[i] = data[i + 1];
    }

    size--;

    return *this;
}

Vector Vector::operator--(int) {
    cout << "Вызван постфиксный оператор --" << endl;

    if (size == 0) {
        throw runtime_error("Ошибка: попытка удалить элемент из пустого вектора.");
    }

    Vector temp(*this);
    size--;

    return temp;
}

void Vector::fill() {
    cout << "Вызван метод fill()" << endl;

    for (int i = 0; i < size; i++) {
        data[i] = (i + 1) * 10;
    }
}

void Vector::print() const {
    cout << "Вектор: ";

    if (size == 0) {
        cout << "пустой";
    }
    else {
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
    }

    cout << endl;
    cout << "Текущий размер: " << size << endl;
    cout << "Максимальный размер: " << maxSize << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");

    try {
        cout << "Создание вектора" << endl;
        Vector v1(5, 10);

        v1.fill();
        v1.print();

        cout << endl << "Обращение к элементу по индексу" << endl;
        cout << "v1[2] = " << v1[2] << endl;

        cout << endl << "Определение размера вектора" << endl;
        cout << "Размер вектора = " << v1() << endl;

        cout << endl << "Постфиксное удаление элемента из конца" << endl;
        v1--;
        v1.print();

        cout << endl << "Префиксное удаление элемента из начала" << endl;
        --v1;
        v1.print();

        cout << endl << "Проверка конструктора копирования" << endl;
        Vector v2 = v1;
        v2.print();

        cout << endl << "Проверка оператора присваивания" << endl;
        Vector v3;
        v3 = v1;
        v3.print();
    }
    catch (const exception& error) {
        cout << error.what() << endl;
    }

    cout << endl << "Проверка исключительных ситуаций" << endl;

    try {
        cout << endl << "Попытка создать вектор больше максимального размера" << endl;
        Vector errorVector(15, 10);
    }
    catch (const exception& error) {
        cout << error.what() << endl;
    }

    try {
        cout << endl << "Попытка обратиться к элементу с отрицательным индексом" << endl;
        Vector v4(3, 10);
        v4.fill();
        cout << v4[-1] << endl;
    }
    catch (const exception& error) {
        cout << error.what() << endl;
    }

    try {
        cout << endl << "Попытка обратиться к элементу за пределами размера" << endl;
        Vector v5(3, 10);
        v5.fill();
        cout << v5[10] << endl;
    }
    catch (const exception& error) {
        cout << error.what() << endl;
    }

    try {
        cout << endl << "Попытка удалить элемент из пустого вектора" << endl;
        Vector emptyVector(0, 10);
        emptyVector--;
    }
    catch (const exception& error) {
        cout << error.what() << endl;
    }

    cin.get();

    return 0;
}