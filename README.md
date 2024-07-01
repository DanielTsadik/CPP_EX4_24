# Tree and Node Implementation for Hierarchical Data Structures

**Assignment: Tree and Node Implementation**  
**Email: Tsadik88@gmail.com**

## Overview

This project provides an implementation of a hierarchical data structure using templates in C++. The primary components are the `Node` and `Tree` classes, designed to handle generic data types and support various traversal methods. The project also includes a visualization feature using the SFML library.

## Features

- **Tree Structure**: Supports k-ary trees.
- **Node Types**: Supports integer, string, and complex number nodes.
- **Traversals**: Pre-order, post-order, in-order, BFS, DFS.
- **Heap Iterator**: Convert the tree into a heap and iterate over it.
- **Exception Handling**: Ensures tree integrity by throwing exceptions for invalid operations.

## Libraries Used

- **Standard Template Library (STL)**: For data structures such as vector, stack, queue, and map.
- **SFML (Simple and Fast Multimedia Library)**: For visualizing the tree structure.

## Class Hierarchy

### Node Class

The `Node` class represents a single node in the tree.

#### Methods

- **Constructor**
  ```cpp
  explicit Node(const T& val);
  ```
  Initializes a node with a value.

- **Get Value**
  ```cpp
  T get_value() const;
  ```
  Returns the value of the node.

- **Get Children**
  ```cpp
  const std::vector<Node*>& get_children() const;
  ```
  Returns a vector of pointers to the node's children.

- **Add Child**
  ```cpp
  void add_child(Node* child, size_t k);
  ```
  Adds a child to the node, ensuring the number of children does not exceed `k` and the child node type matches.

- **Set Child**
  ```cpp
  void set_child(size_t index, Node* child);
  ```
  Sets a child at the specified index, ensuring the index is valid.

#### Example
```cpp
Node<int> root(1);
Node<int> child(2);
root.add_child(&child, 3); // Adds child to root
```

### Tree Class

The `Tree` class represents the entire tree structure.

#### Methods

- **Constructor**
  ```cpp
  explicit Tree(size_t k = 2);
  ```
  Initializes a tree with a specified arity (default is 2, i.e., binary tree).

- **Add Root**
  ```cpp
  void add_root(Node<T>& node);
  ```
  Sets the root of the tree.

- **Add Sub Node**
  ```cpp
  void add_sub_node(Node<T>& parent, Node<T>& child);
  template <typename U>
  void add_sub_node(Node<T>& parent, Node<U>& child);
  ```
  Adds a sub-node to a parent node, ensuring the parent exists and the child type matches. Throws an exception if the child node type does not match the tree type.

#### Example
```cpp
Tree<int> tree(2); // Binary tree
Node<int> root(1);
tree.add_root(root);
Node<int> child(2);
tree.add_sub_node(root, child);
```

### Iterators

The `Tree` class provides several iterators for different traversal methods:

- **Pre-order Iterator**: Traverses nodes in pre-order.
- **Post-order Iterator**: Traverses nodes in post-order.
- **In-order Iterator**: Traverses nodes in in-order (only for binary trees).
- **BFS Iterator**: Traverses nodes in breadth-first search (BFS) order.
- **DFS Iterator**: Traverses nodes in depth-first search (DFS) order.
- **Heap Iterator**: Converts the tree into a heap and iterates over it.

#### Example
```cpp
Tree<int> tree(2); // Binary tree
Node<int> root(1);
tree.add_root(root);
Node<int> child1(2);
Node<int> child2(3);
tree.add_sub_node(root, child1);
tree.add_sub_node(root, child2);

std::cout << "Pre-order traversal:" << std::endl;
for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
    std::cout << node->get_value() << std::endl;
}

std::cout << "Heap traversal:" << std::endl;
for (auto node = tree.myHeap(); node != tree.end_heap(); ++node) {
    std::cout << node->get_value() << std::endl;
}
```

### Example Tree with k = 1
```cpp
Tree<int> unary_tree(1); // Unary tree
Node<int> root(10);
unary_tree.add_root(root);
Node<int> child1(20);
Node<int> child2(30);
unary_tree.add_sub_node(root, child1);
unary_tree.add_sub_node(child1, child2);

std::cout << unary_tree << std::endl;

std::cout << "Pre-order traversal:" << std::endl;
for (auto node = unary_tree.begin_pre_order(); node != unary_tree.end_pre_order(); ++node) {
    std::cout << node->get_value() << std::endl;
}
```

### Example Tree with Complex Numbers
```cpp
Tree<Complex> complex_tree(3); // 3-ary tree
Node<Complex> root(Complex(1.0, 1.0));
complex_tree.add_root(root);
Node<Complex> c1(Complex(2.0, 2.0));
Node<Complex> c2(Complex(3.0, 3.0));
Node<Complex> c3(Complex(4.0, 4.0));
complex_tree.add_sub_node(root, c1);
complex_tree.add_sub_node(root, c2);
complex_tree.add_sub_node(root, c3);

std::cout << complex_tree << std::endl;

std::cout << "Pre-order traversal:" << std::endl;
for (auto node = complex_tree.begin_pre_order(); node != complex_tree.end_pre_order(); ++node) {
    std::cout << node->get_value() << std::endl;
}
```

### Testing Tree

By following these guidelines, we ensure that the tree structure is robust, type-safe, and supports a wide range of operations and visualizations. We also make sure that the test we wrote get along with all the instructions, and the things we mentioned above.




נעזרתי במטלה זו באתר ChatGPT
