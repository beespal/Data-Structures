/*
Чтобы не было проблем в наследовании std::exception, пользуюсь стандартом c++20.
Наверно можно и ниже. Но дефолтный ругается.
*/

#include <iostream>

class IndexError : public std::exception
{
    std::string msg;

public:
    IndexError(const char *error) : msg(error)
    {
    }
    const char *what() const noexcept override { return msg.data(); }
};

/**
 *Динамический массив на основе обычного статического массива.
 *Реализовал через шаблон.
 *@tparam T - тип данных которые будут храниться в массиве data.
 *@params:
 *capacity - количество выделенных в памяти элементов под массив
 *len - реальное количество элементов в массиве
 *start_capacity - стартовое значение для capacity
 *mul - множитель для увеличения capacity в случае отсутствия места для вставки нового элемента
 **/
template <typename T>
class DMassive
{
    enum
    {
        start_capacity = 8,
        mul = 2
    };
    unsigned long capacity;
    unsigned long len;

public:
    T *data; // указатель на массив с данными
    DMassive()
    {
        data = new T[start_capacity];
        len = 0;
        capacity = start_capacity;
    }
    /*
    Вспомогательная функция для увеличения физического размера массива.
    */
    void increase_capacity()
    {
        T *new_data = new T[capacity * mul];
        for (int i = 0; i < len; ++i)
        {
            new_data[i] = data[i];
        }
        capacity *= mul;
        delete[] data;
        data = new_data;
    }
    /*
    Добавление элемента в конец.
    */
    void append(T value)
    {
        if (len == capacity)
            increase_capacity();
        data[len] = value;
        len += 1;
    }
    /*
    Вставка элемента по индексу.
    */
    void insert(T value, unsigned long index)
    {
        if (index < 0 || index >= len)
            throw IndexError("Incorrect index");
        if (len == capacity)
            increase_capacity();
        for (int i = len; i > index; --i)
            data[i] = data[i - 1];
        data[index] = value;
        len += 1;
    }
    /*
    Удаление элемента по индексу.
    */
    void erase(unsigned long index)
    {
        if (index < 0 || index >= len)
            throw IndexError("Incorrect index");
        for (int i = index; i < len; ++i)
            data[i] = data[i + 1];
        len -= 1;
    }

    /*
    Перегрузка оператора обращения к элементу по индексу.
    */
    int &operator[](int index)
    {
        if (index < 0 || index >= len)
            throw IndexError("Incorrect index");
        return data[index];
    }
    unsigned long size() const
    {
        return len;
    }
    unsigned long get_capacity() const
    {
        return capacity;
    }
};

// Для вывода значений массива в консоль (для удобства при тестировании).
template <typename T>
void print_massive(const DMassive<T> &massive, std::string sep = " ")
{
    unsigned long len = massive.size();
    for (int i = 0; i < len; ++i)
        std::cout << massive.data[i] << sep;
}
