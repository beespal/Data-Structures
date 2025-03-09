#include <iostream>
#include <deque>
template <typename T>
class Node
{
public:
    T data{};
    Node *left{nullptr};
    Node *right{nullptr};
    Node() {}
    Node(T value = 0) : data(value), left(nullptr), right(nullptr)
    {
    }
};

template <typename T>
class Tree
{
private:
    Node<T> *root{nullptr};

public:
    Tree() {}
    Node<T> *get_root_ptr()
    {
        return root;
    }
    void add_node(T value, Node<T> *ptr)
    {
        if (value == ptr->data)
        {
            return;
        }
        else if (value < ptr->data)
        {
            if (ptr->left == nullptr)
            {
                Node<T> *new_node = new Node<T>(value);
                ptr->left = new_node;
            }
            else
            {
                add_node(value, ptr->left);
            }
        }
        else
        {
            if (ptr->right == nullptr)
            {
                Node<T> *new_node = new Node<T>(value);
                ptr->right = new_node;
            }
            else
            {
                add_node(value, ptr->right);
            }
        }
    }
    void add(T value)
    {
        if (root == nullptr)
        {
            Node<T> *new_node = new Node<T>(value);
            root = new_node;
        }
        add_node(value, root);
    }
    void show_node_depth(Node<T> *ptr)
    {
        if (ptr == nullptr)
        {
            return;
        }
        show_node_depth(ptr->left);
        std::cout << ptr->data << ' ';
        show_node_depth(ptr->right);
    }
    void show_tree_depth()
    {
        show_node_depth(root);
    }
    void show_tree_width()
    {
        std::deque<Node<T> *> nodes;
        nodes.push_front(root);
        while (!nodes.empty())
        {
            if (nodes.front()->left != nullptr)
            {
                nodes.push_back(nodes.front()->left);
            }
            if (nodes.front()->right != nullptr)
            {
                nodes.push_back(nodes.front()->right);
            }
            std::cout << nodes.front()->data << ' ';
            nodes.pop_front();
        }
    }
};