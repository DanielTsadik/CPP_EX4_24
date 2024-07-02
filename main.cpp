// Tsadik88@gmail.com
#include <iostream>
#include "node.hpp"
#include "tree.hpp"
#include <SFML/Graphics.hpp>

using namespace std;

int main() {
    Node<double> root_node(1.1);
    Tree<double> tree; // Default to binary tree

    tree.add_root(root_node);

    Node<double> n1(1.2);
    Node<double> n2(1.3);
    Node<double> n3(1.4);
    Node<double> n4(1.5);
    Node<double> n5(1.6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    cout << "Pre-order traversal:" << endl;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
        cout << node->get_value() << endl;
    }

    cout << "Post-order traversal:" << endl;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node) {
        cout << node->get_value() << endl;
    }

    cout << "In-order traversal:" << endl;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
        cout << node->get_value() << endl;
    }

    cout << "BFS scan traversal:" << endl;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node) {
        cout << node->get_value() << endl;
    }

    cout << "Range-based for loop (BFS):" << endl;
    for (auto node : tree) {
        cout << node.get_value() << endl;
    }

    cout << "DFS scan traversal:" << endl;
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node) {
        cout << node->get_value() << endl;
    }

    cout << "Heap traversal:" << endl;
    for (auto node = tree.myHeap(); node != tree.end_heap(); ++node) {
        cout << node->get_value() << endl;
    }

    // Visualize the binary tree
    std::cout << "Visualizing Binary Tree..." << std::endl;
    std::cout << tree << std::endl;

    Node<double> root_node_1(1.1);
    Tree<double> three_ary_tree(3); // 3-ary tree

    three_ary_tree.add_root(root_node_1);

    Node<double> n12(1.2);
    Node<double> n22(1.3);
    Node<double> n32(1.4);
    Node<double> n42(1.5);
    Node<double> n52(1.6);

    three_ary_tree.add_sub_node(root_node_1, n12);
    three_ary_tree.add_sub_node(root_node_1, n22);
    three_ary_tree.add_sub_node(root_node_1, n32);
    three_ary_tree.add_sub_node(n12, n42);
    three_ary_tree.add_sub_node(n22, n52);

    cout << "Pre-order traversal (3-ary tree):" << endl;
    for (auto node = three_ary_tree.begin_pre_order(); node != three_ary_tree.end_pre_order(); ++node) {
        cout << node->get_value() << endl;
    }

    cout << "Post-order traversal (3-ary tree):" << endl;
    for (auto node = three_ary_tree.begin_post_order(); node != three_ary_tree.end_post_order(); ++node) {
        cout << node->get_value() << endl;
    }

    cout << "In-order traversal (3-ary tree):" << endl;
    for (auto node = three_ary_tree.begin_in_order(); node != three_ary_tree.end_in_order(); ++node) {
        cout << node->get_value() << endl;
    }

    cout << "BFS scan traversal (3-ary tree):" << endl;
    for (auto node = three_ary_tree.begin_bfs_scan(); node != three_ary_tree.end_bfs_scan(); ++node) {
        cout << node->get_value() << endl;
    }

    cout << "Range-based for loop (3-ary tree):" << endl;
    for (auto node : three_ary_tree) {
        cout << node.get_value() << endl;
    }

    cout << "DFS scan traversal (3-ary tree):" << endl;
    for (auto node = three_ary_tree.begin_dfs_scan(); node != three_ary_tree.end_dfs_scan(); ++node) {
        cout << node->get_value() << endl;
    }

    // Visualize the 3-ary tree
    std::cout << "Visualizing 3-ary Tree..." << std::endl;
    std::cout << three_ary_tree << std::endl;

    return 0;
}
