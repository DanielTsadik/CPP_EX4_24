#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <cstddef>
#include <iostream>
#include <stdexcept>

template <typename T>
class Node {
public:
    explicit Node(const T& val) : value(val) {}

    T get_value() const { return value; }

    const std::vector<Node*>& get_children() const { return children; }

    void add_child(Node* child, size_t k) {
        if (children.size() < k) {
            children.push_back(child);
        } else {
            throw std::runtime_error("Maximum children exceeded");
        }
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
};

#endif // NODE_HPP
