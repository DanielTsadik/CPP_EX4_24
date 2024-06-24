#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "node.hpp"
#include "tree.hpp"
#include "complex.hpp"
#include <string>
#include <iostream>

using namespace std;

void print_tree(const Tree<int>& tree, const string& traversal_name) {
    cout << traversal_name << ": ";
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
        cout << node->get_value() << " ";
    }
    cout << endl;
}

void print_traversal(const string& name, const vector<int>& expected, const vector<int>& actual) {
    cout << name << " Expected: ";
    for (const auto& val : expected) {
        cout << val << " ";
    }
    cout << endl;

    cout << name << " Actual: ";
    for (const auto& val : actual) {
        cout << val << " ";
    }
    cout << endl;
}

TEST_CASE("Testing tree with integers") {
    Node<int> root(1);
    Tree<int> tree;
    tree.add_root(root);

    Node<int> n1(2);
    Node<int> n2(3);
    Node<int> n3(4);
    Node<int> n4(5);
    Node<int> n5(6);

    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    auto pre_order = {1, 2, 4, 5, 3, 6};
    auto it = pre_order.begin();
    cout << "Pre-order traversal: ";
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
        cout << node->get_value() << " ";
        CHECK(node->get_value() == *it++);
    }
    cout << endl;

    auto post_order = {4, 5, 2, 6, 3, 1};
    it = post_order.begin();
    cout << "Post-order traversal: ";
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node) {
        cout << node->get_value() << " ";
        CHECK(node->get_value() == *it++);
    }
    cout << endl;

    auto in_order = {4, 2, 5, 1, 6, 3};
    it = in_order.begin();
    cout << "In-order traversal: ";
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
        cout << node->get_value() << " ";
        CHECK(node->get_value() == *it++);
    }
    cout << endl;
}

TEST_CASE("Testing tree with doubles") {
    Node<double> root(1.1);
    Tree<double> tree;
    tree.add_root(root);

    Node<double> n1(2.2);
    Node<double> n2(3.3);
    Node<double> n3(4.4);
    Node<double> n4(5.5);
    Node<double> n5(6.6);

    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    auto pre_order = {1.1, 2.2, 4.4, 5.5, 3.3, 6.6};
    auto it = pre_order.begin();
    cout << "Pre-order traversal: ";
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
        cout << node->get_value() << " ";
        CHECK(node->get_value() == *it++);
    }
    cout << endl;

    auto post_order = {4.4, 5.5, 2.2, 6.6, 3.3, 1.1};
    it = post_order.begin();
    cout << "Post-order traversal: ";
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node) {
        cout << node->get_value() << " ";
        CHECK(node->get_value() == *it++);
    }
    cout << endl;

    auto in_order = {4.4, 2.2, 5.5, 1.1, 6.6, 3.3};
    it = in_order.begin();
    cout << "In-order traversal: ";
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
        cout << node->get_value() << " ";
        CHECK(node->get_value() == *it++);
    }
    cout << endl;
}

TEST_CASE("Testing tree with Complex numbers") {
    Node<Complex> root(Complex(1.1, 2.2));
    Tree<Complex> tree;
    tree.add_root(root);

    Node<Complex> n1(Complex(2.2, 3.3));
    Node<Complex> n2(Complex(3.3, 4.4));
    Node<Complex> n3(Complex(4.4, 5.5));
    Node<Complex> n4(Complex(5.5, 6.6));
    Node<Complex> n5(Complex(6.6, 7.7));

    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    auto pre_order = {Complex(1.1, 2.2), Complex(2.2, 3.3), Complex(4.4, 5.5), Complex(5.5, 6.6), Complex(3.3, 4.4), Complex(6.6, 7.7)};
    auto it = pre_order.begin();
    cout << "Pre-order traversal: ";
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
        cout << node->get_value() << " ";
        CHECK(node->get_value() == *it++);
    }
    cout << endl;

    auto post_order = {Complex(4.4, 5.5), Complex(5.5, 6.6), Complex(2.2, 3.3), Complex(6.6, 7.7), Complex(3.3, 4.4), Complex(1.1, 2.2)};
    it = post_order.begin();
    cout << "Post-order traversal: ";
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node) {
        cout << node->get_value() << " ";
        CHECK(node->get_value() == *it++);
    }
    cout << endl;

    auto in_order = {Complex(4.4, 5.5), Complex(2.2, 3.3), Complex(5.5, 6.6), Complex(1.1, 2.2), Complex(6.6, 7.7), Complex(3.3, 4.4)};
    it = in_order.begin();
    cout << "In-order traversal: ";
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
        cout << node->get_value() << " ";
        CHECK(node->get_value() == *it++);
    }
    cout << endl;
}

TEST_CASE("Testing tree with strings") {
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

    auto pre_order = {"root", "child1", "grandchild1", "grandchild2", "child2", "grandchild3"};
    auto it = pre_order.begin();
    cout << "Pre-order traversal: ";
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
        cout << node->get_value() << " ";
        CHECK(node->get_value() == *it++);
    }
    cout << endl;

    auto post_order = {"grandchild1", "grandchild2", "child1", "grandchild3", "child2", "root"};
    it = post_order.begin();
    cout << "Post-order traversal: ";
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node) {
        cout << node->get_value() << " ";
        CHECK(node->get_value() == *it++);
    }
    cout << endl;

    auto in_order = {"grandchild1", "child1", "grandchild2", "root", "grandchild3", "child2"};
    it = in_order.begin();
    cout << "In-order traversal: ";
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
        cout << node->get_value() << " ";
        CHECK(node->get_value() == *it++);
    }
    cout << endl;
}

TEST_CASE("Testing k-ary trees with different k values") {
    // 3-ary tree
    Node<int> root3(1);
    Tree<int> tree3(3); // 3-ary tree

    tree3.add_root(root3);

    Node<int> n1_3(2);
    Node<int> n2_3(3);
    Node<int> n3_3(4);
    Node<int> n4_3(5);
    Node<int> n5_3(6);
    Node<int> n6_3(7);

    // Adding nodes ensuring we do not exceed the 3-children limit
    tree3.add_sub_node(root3, n1_3);
    tree3.add_sub_node(root3, n2_3);
    tree3.add_sub_node(root3, n3_3);

    tree3.add_sub_node(n1_3, n4_3);
    tree3.add_sub_node(n1_3, n5_3);

    tree3.add_sub_node(n2_3, n6_3);

    // Expected Pre-order: 1, 2, 5, 6, 3, 7, 4
    auto pre_order_3 = {1, 2, 5, 6, 3, 7, 4};
    auto it = pre_order_3.begin();
    cout << "3-ary Tree Pre-order traversal: ";
    for (auto node = tree3.begin_pre_order(); node != tree3.end_pre_order(); ++node) {
        cout << node->get_value() << " ";
        CHECK(node->get_value() == *it++);
    }
    cout << endl;

    // Expected Post-order: 5, 6, 2, 7, 3, 4, 1
    auto post_order_3 = {5, 6, 2, 7, 3, 4, 1};
    it = post_order_3.begin();
    cout << "3-ary Tree Post-order traversal: ";
    for (auto node = tree3.begin_post_order(); node != tree3.end_post_order(); ++node) {
        cout << node->get_value() << " ";
        CHECK(node->get_value() == *it++);
    }
    cout << endl;

    // Expected In-order: 5, 2, 6, 1, 7, 3, 4
    auto in_order_3 = {5, 2, 6, 1, 7, 3, 4};
    it = in_order_3.begin();
    cout << "3-ary Tree In-order traversal: ";
    for (auto node = tree3.begin_in_order(); node != tree3.end_in_order(); ++node) {
        cout << node->get_value() << " ";
        CHECK(node->get_value() == *it++);
    }
    cout << endl;

    // 4-ary tree
    Node<int> root4(1);
    Tree<int> tree4(4); // 4-ary tree

    tree4.add_root(root4);

    Node<int> n1_4(2);
    Node<int> n2_4(3);
    Node<int> n3_4(4);
    Node<int> n4_4(5);
    Node<int> n5_4(6);
    Node<int> n6_4(7);
    Node<int> n7_4(8);

    // Adding nodes ensuring we do not exceed the 4-children limit
    tree4.add_sub_node(root4, n1_4);
    tree4.add_sub_node(root4, n2_4);
    tree4.add_sub_node(root4, n3_4);
    tree4.add_sub_node(root4, n4_4);

    tree4.add_sub_node(n1_4, n5_4);
    tree4.add_sub_node(n1_4, n6_4);

    tree4.add_sub_node(n2_4, n7_4);

    // Expected Pre-order: 1, 2, 6, 7, 3, 8, 4, 5
    auto pre_order_4 = {1, 2, 6, 7, 3, 8, 4, 5};
    it = pre_order_4.begin();
    cout << "4-ary Tree Pre-order traversal: ";
    for (auto node = tree4.begin_pre_order(); node != tree4.end_pre_order(); ++node) {
        cout << node->get_value() << " ";
        CHECK(node->get_value() == *it++);
    }
    cout << endl;

    // Expected Post-order: 6, 7, 2, 8, 3, 5, 4, 1
    auto post_order_4 = {6, 7, 2, 8, 3, 5, 4, 1};
    it = post_order_4.begin();
    cout << "4-ary Tree Post-order traversal: ";
    for (auto node = tree4.begin_post_order(); node != tree4.end_post_order(); ++node) {
        cout << node->get_value() << " ";
        CHECK(node->get_value() == *it++);
    }
    cout << endl;

    // Expected In-order: 6, 2, 7, 1, 8, 3, 5, 4
    auto in_order_4 = {6, 2, 7, 1, 8, 3, 5, 4};
    it = in_order_4.begin();
    cout << "4-ary Tree In-order traversal: ";
    for (auto node = tree4.begin_in_order(); node != tree4.end_in_order(); ++node) {
        cout << node->get_value() << " ";
        CHECK(node->get_value() == *it++);
    }
    cout << endl;
}
