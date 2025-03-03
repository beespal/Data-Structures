
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
class EmptyListError : public std::exception
{
    std::string msg;

public:
    EmptyListError(const char *error) : msg(error)
    {
    }
    const char *what() const noexcept override { return msg.data(); }
};

template <typename T>
class Node
{
private:
    T data{};

public:
    Node *next{nullptr};
    Node *prev{nullptr};
    Node() {}
    Node(T value = 0) : data(value), next(nullptr), prev(nullptr)
    {
    }
    T get_data()
    {
        return data;
    }
};

template <typename T>
class D_Linked_List
{

    Node<T> *head{};
    Node<T> *tail{};
    unsigned len{0};

public:
    D_Linked_List() {}
    Node<T> *get_head()
    {
        return head;
    }
    Node<T> *get_tail()
    {
        return tail;
    }
    unsigned get_size()
    {
        return len;
    }
    void push_back(T value)
    {
        Node<T> *curr = new Node<T>(value);
        if (head == nullptr)
        {
            head = curr;
            tail = curr;
        }
        else
        {
            tail->next = curr;
            curr->prev = tail;
            tail = curr;
        }

        len++;
    }
    void push_front(T value)
    {
        Node<T> *curr = new Node<T>(value);
        if (head == nullptr)
        {
            head = curr;
            tail = curr;
        }
        else
        {
            head->prev = curr;
            curr->next = head;
            head = curr;
        }
        len++;
    }
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
            curr = curr->next;
            i++;
        }
        return curr->get_data();
    }
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
                curr = curr->next;
                i++;
            }
            Node<T> *new_node = new Node<T>(value);
            new_node->next = curr->next;
            new_node->prev = curr;
            curr->next->prev = new_node;
            curr->next = new_node;
        }
        len++;
    }
    void pop_front()
    {
        if (head == nullptr)
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
            head = head->next;
            head->prev = nullptr;
            delete deleted;
        }
        len--;
    }
    void pop_back()
    {
        if (tail == nullptr)
        {
            throw EmptyListError("Cannot delete element from empty list");
        }
        else if (head == tail)
        {
            delete tail;
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            Node<T> *deleted = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete deleted;
        }
        len--;
    }
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
        else if (index == len - 1)
        {
            pop_back();
        }
        else
        {
            unsigned i = 0;
            Node<T> *curr = head;
            while (i < index - 1)
            {
                curr = curr->next;
                i++;
            }
            Node<T> *deleted = curr->next;
            curr->next = deleted->next;
            deleted->next->prev = curr;
            delete deleted;
            len--;
        }
    }
};

template <typename T>
void print_linked_list(D_Linked_List<T> &list, std::string sep = " ")
{
    Node<T> *curr = list.get_head();
    while (curr != nullptr)
    {
        std::cout << curr->get_data() << sep;
        curr = curr->next;
    }
    std::cout << std::endl;
}
