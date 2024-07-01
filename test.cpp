// Tsadik88@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "node.hpp"
#include "tree.hpp"
#include "complex.hpp"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

void print_tree_structure(Node<int> *node, int depth = 0)
{
    if (!node)
        return;
    for (int i = 0; i < depth; ++i)
        std::cout << "  ";
    std::cout << node->get_value() << std::endl;
    for (auto child : node->get_children())
    {
        print_tree_structure(child, depth + 1);
    }
}

// Test for a specific tree structure
TEST_CASE("Testing specific tree structure")
{
    Node<int> root(8);
    Tree<int> tree(4); // 4-ary tree

    tree.add_root(root);

    Node<int> n1(2);
    Node<int> n2(3);
    Node<int> n3(4);
    Node<int> n4(5);
    Node<int> n5(6);
    Node<int> n6(7);
    Node<int> n7(1);
    Node<int> n8(9);

    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(root, n3);
    tree.add_sub_node(root, n4);

    tree.add_sub_node(n1, n5);
    tree.add_sub_node(n1, n6);
    tree.add_sub_node(n1, n8);

    tree.add_sub_node(n6, n7);

    std::cout << "Specific Tree structure before traversals:" << std::endl;
    print_tree_structure(&root);

    std::cout << tree << std::endl;

    auto pre_order = {8, 2, 6, 7, 1, 9, 3, 4, 5};
    auto it = pre_order.begin();
    std::cout << "Pre-order traversal: ";
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        std::cout << node->get_value() << " ";
        CHECK(node->get_value() == *it++);
    }
    std::cout << std::endl;

    auto post_order = {8, 2, 6, 7, 1, 9, 3, 4, 5};
    it = post_order.begin();
    std::cout << "Post-order traversal: ";
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        std::cout << node->get_value() << " ";
        CHECK(node->get_value() == *it++);
    }
    std::cout << std::endl;

    auto in_order = {8, 2, 6, 7, 1, 9, 3, 4, 5};
    it = in_order.begin();
    std::cout << "In-order traversal: ";
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        std::cout << node->get_value() << " ";
        CHECK(node->get_value() == *it++);
    }
    std::cout << std::endl;

    auto heap_order = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    it = heap_order.begin();
    std::cout << "Heap order traversal: ";
    for (auto node = tree.myHeap(); node != tree.end_heap(); ++node)
    {
        std::cout << node->get_value() << " ";
        CHECK(node->get_value() == *it++);
    }
    std::cout << std::endl;
}

// Test for various data types with non-trivial order
TEST_CASE("Testing tree with strings")
{
    Node<string> root("root");
    Tree<string> tree;
    tree.add_root(root);

    Node<string> n1("child1");
    Node<string> n2("child2");
    Node<string> n3("grandchild1");
    Node<string> n4("grandchild2");
    Node<string> n5("grandchild3");

    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    std::cout << tree << std::endl;

    vector<string> expected_pre_order = {"root", "child1", "grandchild1", "grandchild2", "child2", "grandchild3"};
    vector<string> actual_pre_order;
    cout << "Pre-order traversal: ";
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        cout << node->get_value() << " ";
        actual_pre_order.push_back(node->get_value());
    }
    cout << endl;
    CHECK(expected_pre_order == actual_pre_order);

    vector<string> expected_post_order = {"grandchild1", "grandchild2", "child1", "grandchild3", "child2", "root"};
    vector<string> actual_post_order;
    cout << "Post-order traversal: ";
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        cout << node->get_value() << " ";
        actual_post_order.push_back(node->get_value());
    }
    cout << endl;
    CHECK(expected_post_order == actual_post_order);

    vector<string> expected_in_order = {"grandchild1", "child1", "grandchild2", "root", "grandchild3", "child2"};
    vector<string> actual_in_order;
    cout << "In-order traversal: ";
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        cout << node->get_value() << " ";
        actual_in_order.push_back(node->get_value());
    }
    cout << endl;
    CHECK(expected_in_order == actual_in_order);

    vector<string> expected_heap_order = {"child1", "child2", "grandchild1", "grandchild2", "grandchild3", "root"};
    vector<string> actual_heap_order;
    cout << "Heap order traversal: ";
    for (auto node = tree.myHeap(); node != tree.end_heap(); ++node)
    {
        cout << node->get_value() << " ";
        actual_heap_order.push_back(node->get_value());
    }
    cout << endl;
    CHECK(expected_heap_order == actual_heap_order);
}

TEST_CASE("Testing tree with Complex numbers")
{
    Node<Complex> root(Complex(5.5, 6.6));
    Tree<Complex> tree;
    tree.add_root(root);

    Node<Complex> n1(Complex(1.1, 2.2));
    Node<Complex> n2(Complex(3.3, 4.4));
    Node<Complex> n3(Complex(7.7, 8.8));
    Node<Complex> n4(Complex(9.9, 1.0));
    Node<Complex> n5(Complex(2.2, 3.3));
    Node<Complex> n6(Complex(4.4, 5.5));

    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
    tree.add_sub_node(n2, n6);

    std::cout << tree << std::endl;

    vector<Complex> expected_pre_order = {Complex(5.5, 6.6), Complex(1.1, 2.2), Complex(7.7, 8.8), Complex(9.9, 1.0), Complex(3.3, 4.4), Complex(2.2, 3.3), Complex(4.4, 5.5)};
    vector<Complex> actual_pre_order;
    cout << "Pre-order traversal: ";
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        cout << node->get_value() << " ";
        actual_pre_order.push_back(node->get_value());
    }
    cout << endl;
    CHECK(expected_pre_order == actual_pre_order);

    vector<Complex> expected_post_order = {Complex(7.7, 8.8), Complex(9.9, 1.0), Complex(1.1, 2.2), Complex(2.2, 3.3), Complex(4.4, 5.5), Complex(3.3, 4.4), Complex(5.5, 6.6)};
    vector<Complex> actual_post_order;
    cout << "Post-order traversal: ";
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        cout << node->get_value() << " ";
        actual_post_order.push_back(node->get_value());
    }
    cout << endl;
    CHECK(expected_post_order == actual_post_order);

    vector<Complex> expected_in_order = {Complex(7.7, 8.8), Complex(1.1, 2.2), Complex(9.9, 1.0), Complex(5.5, 6.6), Complex(2.2, 3.3), Complex(3.3, 4.4), Complex(4.4, 5.5)};
    vector<Complex> actual_in_order;
    cout << "In-order traversal: ";
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        cout << node->get_value() << " ";
        actual_in_order.push_back(node->get_value());
    }
    cout << endl;
    CHECK(expected_in_order == actual_in_order);

    vector<Complex> expected_heap_order = {Complex(1.1, 2.2), Complex(2.2, 3.3), Complex(3.3, 4.4), Complex(4.4, 5.5), Complex(5.5, 6.6), Complex(7.7, 8.8), Complex(9.9, 1.0)};
    vector<Complex> actual_heap_order;
    cout << "Heap order traversal: ";
    for (auto node = tree.myHeap(); node != tree.end_heap(); ++node)
    {
        cout << node->get_value() << " ";
        actual_heap_order.push_back(node->get_value());
    }
    cout << endl;
    CHECK(expected_heap_order == actual_heap_order);
}

TEST_CASE("Testing tree with characters")
{
    Node<char> root('A');
    Tree<char> tree;
    tree.add_root(root);

    Node<char> n1('B');
    Node<char> n2('C');
    Node<char> n3('D');
    Node<char> n4('E');
    Node<char> n5('F');
    Node<char> n6('G');

    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
    tree.add_sub_node(n2, n6);

    std::cout << tree << std::endl;

    vector<char> expected_pre_order = {'A', 'B', 'D', 'E', 'C', 'F', 'G'};
    vector<char> actual_pre_order;
    cout << "Pre-order traversal: ";
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        cout << node->get_value() << " ";
        actual_pre_order.push_back(node->get_value());
    }
    cout << endl;
    CHECK(expected_pre_order == actual_pre_order);

    vector<char> expected_post_order = {'D', 'E', 'B', 'F', 'G', 'C', 'A'};
    vector<char> actual_post_order;
    cout << "Post-order traversal: ";
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        cout << node->get_value() << " ";
        actual_post_order.push_back(node->get_value());
    }
    cout << endl;
    CHECK(expected_post_order == actual_post_order);

    vector<char> expected_in_order = {'D', 'B', 'E', 'A', 'F', 'C', 'G'};
    vector<char> actual_in_order;
    cout << "In-order traversal: ";
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        cout << node->get_value() << " ";
        actual_in_order.push_back(node->get_value());
    }
    cout << endl;
    CHECK(expected_in_order == actual_in_order);

    vector<char> expected_heap_order = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    vector<char> actual_heap_order;
    cout << "Heap order traversal: ";
    for (auto node = tree.myHeap(); node != tree.end_heap(); ++node)
    {
        cout << node->get_value() << " ";
        actual_heap_order.push_back(node->get_value());
    }
    cout << endl;
    CHECK(expected_heap_order == actual_heap_order);
}

// Additional test for converting tree to heap and then iterating
TEST_CASE("Converting tree to heap and testing iterators")
{
    Node<int> root(10);
    Tree<int> tree;
    tree.add_root(root);

    Node<int> n1(20);
    Node<int> n2(5);
    Node<int> n3(15);
    Node<int> n4(25);
    Node<int> n5(2);
    Node<int> n6(8);

    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
    tree.add_sub_node(n2, n6);

    std::cout << tree << std::endl;

    vector<int> expected_heap_order = {2, 5, 8, 10, 15, 20, 25};
    vector<int> actual_heap_order;
    cout << "Heap order traversal after conversion: ";
    for (auto node = tree.myHeap(); node != tree.end_heap(); ++node)
    {
        cout << node->get_value() << " ";
        actual_heap_order.push_back(node->get_value());
    }
    cout << endl;
    CHECK(expected_heap_order == actual_heap_order);

    // Test pre-order, post-order, and in-order on the heap
    vector<int> expected_pre_order = {10, 20, 15, 25, 5, 2, 8};
    vector<int> actual_pre_order;
    cout << "Pre-order traversal on heap: ";
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        cout << node->get_value() << " ";
        actual_pre_order.push_back(node->get_value());
    }
    cout << endl;
    CHECK(expected_pre_order == actual_pre_order);

    vector<int> expected_post_order = {15, 25, 20, 2, 8, 5, 10};
    vector<int> actual_post_order;
    cout << "Post-order traversal on heap: ";
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        cout << node->get_value() << " ";
        actual_post_order.push_back(node->get_value());
    }
    cout << endl;
    CHECK(expected_post_order == actual_post_order);

    vector<int> expected_in_order = {15, 20, 25, 10, 2, 5, 8};
    vector<int> actual_in_order;
    cout << "In-order traversal on heap: ";
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        cout << node->get_value() << " ";
        actual_in_order.push_back(node->get_value());
    }
    cout << endl;
    CHECK(expected_in_order == actual_in_order);
}

// Test for exceeding the maximum number of children
TEST_CASE("Testing exceeding maximum number of children")
{
    Node<int> root(1);
    Tree<int> binary_tree(2); // Binary tree

    binary_tree.add_root(root);

    Node<int> child1(2);
    Node<int> child2(3);
    Node<int> child3(4);

    binary_tree.add_sub_node(root, child1);
    binary_tree.add_sub_node(root, child2);

    CHECK_THROWS_AS(binary_tree.add_sub_node(root, child3), std::runtime_error);
}

// Test for adding a node with the wrong type
TEST_CASE("Testing adding a node with the wrong type")
{
    Node<int> root(1);
    Tree<int> int_tree;

    int_tree.add_root(root);

    Node<double> wrong_node(2.5);

    CHECK_THROWS_AS(int_tree.add_sub_node(root, wrong_node), std::runtime_error);
}

TEST_CASE("Testing tree with k = 1")
{
    Node<int> root(1);
    Tree<int> tree(1); // Unary tree

    tree.add_root(root);

    Node<int> n1(2);
    Node<int> n2(3);
    Node<int> n3(4);

    tree.add_sub_node(root, n1);
    tree.add_sub_node(n1, n2);
    tree.add_sub_node(n2, n3);

    std::cout << "Tree with k=1:" << std::endl;
    std::cout << tree << std::endl;

    vector<int> expected_pre_order = {1, 2, 3, 4};
    vector<int> actual_pre_order;
    cout << "Pre-order traversal: ";
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        cout << node->get_value() << " ";
        actual_pre_order.push_back(node->get_value());
    }
    cout << endl;
    CHECK(expected_pre_order == actual_pre_order);

    vector<int> expected_post_order = {1, 2, 3, 4};
    vector<int> actual_post_order;
    cout << "Post-order traversal: ";
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        cout << node->get_value() << " ";
        actual_post_order.push_back(node->get_value());
    }
    cout << endl;
    CHECK(expected_post_order == actual_post_order);

    vector<int> expected_in_order = {1, 2, 3, 4};
    vector<int> actual_in_order;
    cout << "In-order traversal: ";
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        cout << node->get_value() << " ";
        actual_in_order.push_back(node->get_value());
    }
    cout << endl;
    CHECK(expected_in_order == actual_in_order);
}

TEST_CASE("Testing tree with complex numbers and non-sorted inserts")
{
    Node<Complex> root(Complex(5.5, 6.6));
    Tree<Complex> tree;
    tree.add_root(root);

    Node<Complex> n1(Complex(3.3, 4.4));
    Node<Complex> n2(Complex(7.7, 8.8));
    Node<Complex> n3(Complex(1.1, 2.2));
    Node<Complex> n4(Complex(9.9, 1.0));
    Node<Complex> n5(Complex(2.2, 3.3));
    Node<Complex> n6(Complex(4.4, 5.5));

    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
    tree.add_sub_node(n2, n6);

    std::cout << "Tree with complex numbers and non-sorted inserts:" << std::endl;
    std::cout << tree << std::endl;

    vector<Complex> expected_pre_order = {Complex(5.5, 6.6), Complex(3.3, 4.4), Complex(1.1, 2.2), Complex(9.9, 1.0), Complex(7.7, 8.8), Complex(2.2, 3.3), Complex(4.4, 5.5)};
    vector<Complex> actual_pre_order;
    cout << "Pre-order traversal: ";
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        cout << node->get_value() << " ";
        actual_pre_order.push_back(node->get_value());
    }
    cout << endl;
    CHECK(expected_pre_order == actual_pre_order);

    vector<Complex> expected_post_order = {Complex(1.1, 2.2), Complex(9.9, 1.0), Complex(3.3, 4.4), Complex(2.2, 3.3), Complex(4.4, 5.5), Complex(7.7, 8.8), Complex(5.5, 6.6)};
    vector<Complex> actual_post_order;
    cout << "Post-order traversal: ";
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        cout << node->get_value() << " ";
        actual_post_order.push_back(node->get_value());
    }
    cout << endl;
    CHECK(expected_post_order == actual_post_order);

    vector<Complex> expected_in_order = {Complex(1.1, 2.2), Complex(3.3, 4.4), Complex(9.9, 1.0), Complex(5.5, 6.6), Complex(2.2, 3.3), Complex(7.7, 8.8), Complex(4.4, 5.5)};
    vector<Complex> actual_in_order;
    cout << "In-order traversal: ";
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        cout << node->get_value() << " ";
        actual_in_order.push_back(node->get_value());
    }
    cout << endl;
    CHECK(expected_in_order == actual_in_order);

    vector<Complex> expected_heap_order = {Complex(1.1, 2.2), Complex(2.2, 3.3), Complex(3.3, 4.4), Complex(4.4, 5.5), Complex(5.5, 6.6), Complex(7.7, 8.8), Complex(9.9, 1.0)};
    vector<Complex> actual_heap_order;
    cout << "Heap order traversal: ";
    for (auto node = tree.myHeap(); node != tree.end_heap(); ++node)
    {
        cout << node->get_value() << " ";
        actual_heap_order.push_back(node->get_value());
    }
    cout << endl;
    CHECK(expected_heap_order == actual_heap_order);
}

TEST_CASE("Testing tree destruction")
{
    Node<int> root(1);
    Tree<int> *tree = new Tree<int>();

    tree->add_root(root);

    Node<int> n1(2);
    Node<int> n2(3);

    tree->add_sub_node(root, n1);
    tree->add_sub_node(root, n2);

    std::cout << "Tree created:" << std::endl;
    std::cout << *tree << std::endl;

    delete tree;

    std::cout << "Tree destroyed." << std::endl;
    // No explicit CHECK here as we're looking for no memory leaks or crashes
}