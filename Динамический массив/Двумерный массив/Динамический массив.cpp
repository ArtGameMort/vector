#include <iostream>

template<typename T>
class my_vector {
public:
    my_vector() : data(nullptr), _size(0), cap(0) {}  // Конструктор по умолчанию

    my_vector(const my_vector&);   // Конструктор копирования

    ~my_vector() { delete[] data; }   // Деструктор

    my_vector& operator=(const my_vector&);  // Оператор присваивания

    void push_back(const T& value);   // Метод добавления элемента в конец

    size_t size() const { return _size; }   // Метод получения размера

    size_t capacity() const { return cap; }   // Метод получения вместимости

    T& operator[](size_t i); // Перегрузка оператора [] для не константных объектов

    const T& operator[](size_t i) const; // Перегрузка оператора [] для константных объектов

    template<typename C>
    friend std::istream& operator>>(std::istream& in, my_vector<C>& rhs);  // Перегрузка оператора ввода

    template<typename C>
    friend std::ostream& operator<<(std::ostream& out, const my_vector<C>& rhs); // Перегрузка оператора вывода

private:
    T* data;       // Динамический массив с данными
    size_t _size;  // Размер
    size_t cap;    // Вместимость
};

template<typename T>
T& my_vector<T>::operator[](size_t i) {
    if (i >= _size) {
        throw std::out_of_range("Index out of range.");
    }
    return data[i];
}

template<typename T>
const T& my_vector<T>::operator[](size_t i) const {
    if (i >= _size) {
        throw std::out_of_range("Index out of range.");
    }
    return data[i];
}

template<typename T>
std::istream& operator>>(std::istream& in, my_vector<T>& rhs) {
    size_t _size;
    in >> _size;
    for (size_t i = 0; i < _size; ++i) {
        int num;
        in >> num;
        rhs.push_back(num);
    }
    return in;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const my_vector<T>& rhs) {
    for (size_t i = 0; i < rhs._size; ++i) {
        out << rhs.data[i] << ' ';
    }
    return out;
}

template<typename T>
my_vector<T>& my_vector<T>::operator=(const my_vector& rhs) {
    if (&rhs == this) {
        return *this;
    }
    delete[] data;
    data = new T[rhs.cap];
    cap = rhs.cap;
    _size = rhs._size;
    for (size_t i = 0; i < _size; ++i) {
        data[i] = rhs.data[i];
    }
    return *this;
}

template<typename T>
my_vector<T>::my_vector(const my_vector& rhs) : data(new T[rhs.cap]), _size(rhs._size), cap(rhs.cap) {
    for (size_t i = 0; i < _size; ++i) {
        data[i] = rhs.data[i];
    }
}

template<typename T>
void my_vector<T>::push_back(const T& value) {
    if (_size + 1 > cap) {
        T* tmp = new T[_size];
        for (size_t i = 0; i < _size; ++i) {
            tmp[i] = data[i];
        }
        delete[] data;

        if (cap == 0) cap = 1;
        else cap *= 2;
        data = new T[cap];

        for (size_t i = 0; i < _size; ++i) {
            data[i] = tmp[i];
        }
        delete[] tmp;
    }
    data[_size] = value;
    ++_size;
}
int menu() {
    int command;
    std::cout << "\n";
    std::cout << "1 - Введите содержимое массива" << std::endl;
    std::cout << "2 - Вывод массива" << std::endl;
    std::cout << "3 - Добавления элемента в конец" << std::endl;
    std::cout << "4 - Размер" << std::endl;
    std::cout << "5 - Очистка" << std::endl;
    std::cout << "6 - Выход из программы" << std::endl;
    std::cin >> command;
    return command;
}

int main() {
    setlocale(LC_ALL, "rus");
    my_vector<int> data;
    int n;
    while (true) {
        n = menu();
        switch (n) {
        case 1:
        {
            std::cin >> data;
            break;
        }
        case 2:
        {
            std::cout << data;
            break;
        }
        case 3:
        {
            int value;
            std::cin >> value;
            data.push_back(value);
            break;
        }
        case 4:
        {
            int sizet;
            sizet = data.size();
            std::cout << sizet << std::endl;
            break;
        }
        case 5:
        {
            data.~my_vector();
            break;
        }
        case 6:
            std::cout << "Хорошего дня!!! " << std::endl;
            std::cout << "Спасибо, что пользовались нашей программой! " << std::endl;
            std::cout << "До свидания! " << std::endl;
            return 0;
        }
    }
    return 0;
}