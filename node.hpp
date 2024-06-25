#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <cstddef>
#include <iostream>
#include <stdexcept>

template <typename T>
class Node {
public:
    explicit Node(const T& val) : value(val), destroyed(false) {}

    T get_value() const { return value; }

    const std::vector<Node*>& get_children() const { return children; }

    void add_child(Node* child, size_t k) {
        if (!child) {
            throw std::runtime_error("Cannot add a null child");
        }
        if (children.size() >= k) {
            throw std::runtime_error("Maximum children exceeded");
        }
        if (typeid(*child) != typeid(Node<T>)) {
            throw std::runtime_error("Child node type does not match");
        }
        children.push_back(child);
    }

    void set_child(size_t index, Node* child) {
        if (index >= children.size()) {
            throw std::out_of_range("Index out of range");
        }
        children[index] = child;
    }

private:
    T value;
    std::vector<Node*> children; // Pointers to children nodes
    bool destroyed;
};

#endif // NODE_HPP
