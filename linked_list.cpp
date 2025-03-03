
#include <iostream>

/*
Чтобы не было проблем в наследовании std::exception, пользуюсь стандартом c++20.
Наверно можно и ниже. Но дефолтный ругается.
*/

class IndexError : public std::exception
{
    std::string msg;

public:
    IndexError(const char *error) : msg(error)
    {
    }
    const char *what() const noexcept override { return msg.data(); }
};
class EmptyListError : public std::exception
{
    std::string msg;

public:
    EmptyListError(const char *error) : msg(error)
    {
    }
    const char *what() const noexcept override { return msg.data(); }
};

/**
 *Узел(элемент) списка.
 *Реализовал через шаблон.
 *@tparam T - тип данных которые будут храниться в переменной data.
 *@params:
 *data - переменная для хранения данных типа T
 *next - ссылка на следующий элемент списка
 **/
template <typename T>
class Node
{
    T data{};
    Node *next{nullptr};

public:
    Node() {}
    Node(T value = 0) : data(value), next(nullptr)
    {
    }
    /*
    Получить ссылку на следующий элемент
    */
    Node *get_next()
    {
        return next;
    }
    void set_next(Node *next_ptr)
    {
        next = next_ptr;
    }
    /*
    Получить значение хранящееся в переменной data
    */
    T get_data()
    {
        return data;
    }
};

/**
 *Связанный список.
 *Реализовал через шаблон.
 *@tparam T - тип данных которые будут храниться в узле в переменной data.
 *@params:
 *head - ссылка на первый элемент списка
 *tail - ссылка на последний элемент списка
 *len - количество элементов в списке
 **/
template <typename T>
class Linked_List
{

    Node<T> *head{};
    Node<T> *tail{};
    unsigned len{0};

public:
    Linked_List() {}
    /*
    Получить ссылку на начало списка
    */
    Node<T> *get_head()
    {
        return head;
    }
    /*
    Поместить элемент в конец списка
    */
    void push_back(T value)
    {
        Node<T> *curr = new Node<T>(value);
        if (!head && !tail)
        {
            head = curr;
            tail = curr;
        }
        else if (head == tail)
        {
            head->set_next(curr);
            tail = curr;
        }
        else
        {
            tail->set_next(curr);
            tail = curr;
        }
        len++;
    }
    /*
    Поместить элемент в начало списка
    */
    void push_front(T value)
    {
        Node<T> *curr = new Node<T>(value);
        if (!head && !tail)
        {
            head = curr;
            tail = curr;
        }
        else
        {
            curr->set_next(head);
            head = curr;
        }
        len++;
    }
    /*
    Получить количество элементов в списке
    */
    unsigned get_size()
    {
        return len;
    }
    /*
    Получить значение элемента под индексом index
    */
    T get_at_k(unsigned index)
    {
        if (index < 0 || index >= len)
        {
            throw IndexError("Incorrect index");
        }
        unsigned i = 0;
        Node<T> *curr = head;
        while (i < index)
        {
            curr = curr->get_next();
            i++;
        }
        return curr->get_data();
    }
    /*
    Вставить элемент со значением value по индексу index.
    Элемент который ранее был под индексом index(если он существовал) сдвинется вправо.
    */
    void insert(unsigned index, T value)
    {
        if (index < 0)
        {
            throw IndexError("Incorrect index");
        }
        if (index >= len)
        {
            push_back(value);
        }
        else if (index == 0)
        {
            push_front(value);
        }
        else
        {
            unsigned i = 0;
            Node<T> *curr = head;
            while (i < index - 1)
            {
                curr = curr->get_next();
                i++;
            }
            Node<T> *new_node = new Node<T>(value);
            new_node->set_next(curr->get_next());
            curr->set_next(new_node);
        }
        len++;
    }
    /*
    Удалить элемент из начала списка
    */
    void pop_front()
    {
        if (!head)
        {
            throw EmptyListError("Cannot delete element from empty list");
        }
        else if (head == tail)
        {
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            Node<T> *deleted = head;
            head = head->get_next();
            delete deleted;
        }
        len--;
    }
    /*
    Удалить элемент под индексом index
    */
    void erase(unsigned index)
    {
        if (!head)
        {
            throw EmptyListError("Cannot delete element from empty list");
        }
        if (index < 0 || index >= len)
        {
            throw IndexError("Incorrect index");
        }
        else if (index == 0)
        {
            pop_front();
        }
        else
        {
            unsigned i = 0;
            Node<T> *curr = head;
            while (i < index - 1)
            {
                curr = curr->get_next();
                i++;
            }
            Node<T> *deleted = curr->get_next();
            if (deleted->get_next())
                curr->set_next(deleted->get_next());
            else
                curr->set_next(nullptr);
            delete deleted;
            len--;
        }
    }
    /*
    Удалить элемент из конца списка
    */
    void pop_back()
    {
        erase(len - 1);
    }
};

/*
Вспомагательная функция для печати в консоль элементов списка
*/
template <typename T>
void print_linked_list(Linked_List<T> &list, std::string sep = " ")
{
    Node<T> *curr = list.get_head();
    while (curr)
    {
        std::cout << curr->get_data() << sep;
        curr = curr->get_next();
    }
    std::cout << std::endl;
}
