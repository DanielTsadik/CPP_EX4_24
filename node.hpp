#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <cstddef>
#include <iostream>
#include <stdexcept>

/**
 * @class Node
 * @brief A template class representing a node in a tree structure.
 * 
 * This class can hold a value of any type and has a vector of pointers to its child nodes.
 * 
 * @tparam T The type of the value stored in the node.
 */
template <typename T>
class Node {
public:
    /**
     * @brief Constructs a Node with a given value.
     * @param val The value to be stored in the node.
     */
    explicit Node(const T& val) : value(val), destroyed(false) {}

    /**
     * @brief Gets the value stored in the node.
     * @return The value of type T.
     */
    T get_value() const { return value; }

    /**
     * @brief Gets the children of the node.
     * @return A constant reference to a vector of pointers to the node's children.
     */
    const std::vector<Node*>& get_children() const { return children; }

    /**
     * @brief Adds a child to the node.
     * 
     * This method adds a child node to the vector of children. It checks for various conditions
     * to ensure the integrity of the tree structure.
     * 
     * @param child A pointer to the child node to be added.
     * @param k The maximum number of children the node can have.
     * @throws std::runtime_error if the child is null, the maximum number of children is exceeded, 
     *         or the child node type does not match.
     */
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

    /**
     * @brief Sets a child at a specific index.
     * 
     * This method replaces the child node at the specified index with a new child node.
     * 
     * @param index The index at which the child node should be set.
     * @param child A pointer to the new child node.
     * @throws std::out_of_range if the index is out of range of the children vector.
     */
    void set_child(size_t index, Node* child) {
        if (index >= children.size()) {
            throw std::out_of_range("Index out of range");
        }
        children[index] = child;
    }

private:
    T value; ///< The value stored in the node.
    std::vector<Node*> children; ///< Pointers to the children nodes.
    bool destroyed; ///< Indicates whether the node is destroyed.
};

#endif // NODE_HPP
