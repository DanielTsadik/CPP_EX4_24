#ifndef TREE_HPP
#define TREE_HPP

#include <queue>
#include <iostream>
#include <stack>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "node.hpp"
#include <map>
#include "complex.hpp"
#include <sstream>

template <typename T>
class Tree
{
public:
    explicit Tree(size_t k = 2) : root(nullptr), k(k) {}

    void add_root(Node<T> &node)
    {
        root = &node;
    }

    void add_sub_node(Node<T> &parent, Node<T> &child)
    {
        if (!root)
        {
            throw std::runtime_error("Error: Root not set.");
        }

        Node<T> *parentNode = find_node(root, parent.get_value());
        if (parentNode)
        {
            parentNode->add_child(&child, k);
        }
        else
        {
            throw std::runtime_error("Parent node not found.");
        }
    }

    template <typename U>   
    void add_sub_node(Node<T> &parent, Node<U> &child)
    {
        throw std::runtime_error("Child node type does not match");
    }

    ~Tree()
    {
        // No dynamic memory to delete
    }

    // Pre-order iterator
    class pre_order_iterator
    {
    public:
        explicit pre_order_iterator(Node<T> *node, size_t k) : k(k)
        {
            if (node)
                nodes.push(node);
        }

        bool operator!=(const pre_order_iterator &other) const
        {
            return !nodes.empty() != !other.nodes.empty();
        }

        Node<T> *operator->() const
        {
            return nodes.top();
        }

        Node<T> &operator*() const
        {
            return *nodes.top();
        }

        pre_order_iterator &operator++()
        {
            Node<T> *current = nodes.top();
            nodes.pop();
            for (auto it = current->get_children().rbegin(); it != current->get_children().rend(); ++it)
            {
                if (*it != nullptr)
                    nodes.push(*it);
            }
            return *this;
        }

    private:
        std::stack<Node<T> *> nodes;
        size_t k;
    };

    pre_order_iterator begin_pre_order() const
    {
        return pre_order_iterator(root, k);
    }

    pre_order_iterator end_pre_order() const
    {
        return pre_order_iterator(nullptr, k);
    }

    // Post-order iterator
    class post_order_iterator
    {
    public:
        explicit post_order_iterator(Node<T> *node, size_t k) : current(nullptr), k(k)
        {
            if (node)
            {
                if (k == 2)
                {
                    pushLeftmostPath(node);
                }
                else
                {
                    nodes.push(node);
                }
            }
            ++(*this); // Move to the first valid node
        }

        bool operator!=(const post_order_iterator &other) const
        {
            return current != other.current;
        }

        Node<T> *operator->() const
        {
            return current;
        }

        Node<T> &operator*() const
        {
            return *current;
        }

        post_order_iterator &operator++()
        {
            if (k == 2)
            {
                if (!nodes.empty())
                {
                    Node<T> *node = nodes.top();
                    nodes.pop();
                    if (!nodes.empty())
                    {
                        Node<T> *parent = nodes.top();
                        if (parent->get_children().size() > 1 && node == parent->get_children()[0])
                        {
                            pushLeftmostPath(parent->get_children()[1]);
                        }
                    }
                    current = node;
                }
                else
                {
                    current = nullptr;
                }
            }
            else
            {
                if (!nodes.empty())
                {
                    Node<T> *node = nodes.top();
                    nodes.pop();
                    for (auto it = node->get_children().rbegin(); it != node->get_children().rend(); ++it)
                    {
                        if (*it)
                        {
                            nodes.push(*it);
                        }
                    }
                    current = node;
                }
                else
                {
                    current = nullptr;
                }
            }
            return *this;
        }

    private:
        std::stack<Node<T> *> nodes;
        Node<T> *current;
        size_t k;

        void pushLeftmostPath(Node<T> *node)
        {
            while (node)
            {
                nodes.push(node);
                if (!node->get_children().empty())
                {
                    node = node->get_children()[0];
                }
                else
                {
                    break;
                }
            }
        }
    };

    post_order_iterator begin_post_order() const
    {
        return post_order_iterator(root, k);
    }

    post_order_iterator end_post_order() const
    {
        return post_order_iterator(nullptr, k);
    }

    // In-order iterator
    class in_order_iterator
    {
    public:
        explicit in_order_iterator(Node<T> *node, size_t k) : k(k)
        {
            if (node)
            {
                if (k == 2)
                { // Binary tree in-order traversal
                    push_left(node);
                }
                else
                { // General tree DFS traversal
                    nodes.push(node);
                    while (!nodes.empty() && !nodes.top())
                        nodes.pop();
                }
            }
        }

        bool operator!=(const in_order_iterator &other) const
        {
            return !nodes.empty() != !other.nodes.empty();
        }

        Node<T> *operator->() const
        {
            return nodes.top();
        }

        Node<T> &operator*() const
        {
            return *nodes.top();
        }

        in_order_iterator &operator++()
        {
            if (nodes.empty())
                return *this;

            if (k == 2)
            { // Binary tree in-order traversal
                Node<T> *node = nodes.top();
                nodes.pop();
                if (node->get_children().size() > 1 && node->get_children()[1] != nullptr)
                {
                    push_left(node->get_children()[1]);
                }
            }
            else
            { // General tree DFS traversal
                Node<T> *current = nodes.top();
                nodes.pop();
                for (auto it = current->get_children().rbegin(); it != current->get_children().rend(); ++it)
                {
                    if (*it != nullptr)
                        nodes.push(*it);
                }
            }
            return *this;
        }

    private:
        std::stack<Node<T> *> nodes;
        size_t k;

        void push_left(Node<T> *node)
        {
            while (node != nullptr)
            {
                nodes.push(node);
                if (node->get_children().size() > 0)
                    node = node->get_children()[0];
                else
                    break;
            }
        }
    };

    in_order_iterator begin_in_order() const
    {
        return in_order_iterator(root, k);
    }

    in_order_iterator end_in_order() const
    {
        return in_order_iterator(nullptr, k);
    }

    // BFS iterator
    class bfs_iterator
    {
    public:
        explicit bfs_iterator(Node<T> *node)
        {
            if (node)
                nodes.push(node);
        }

        bool operator!=(const bfs_iterator &other) const
        {
            return !nodes.empty() != !other.nodes.empty();
        }

        Node<T> *operator->() const
        {
            return nodes.front();
        }

        Node<T> &operator*() const
        {
            return *nodes.front();
        }

        bfs_iterator &operator++()
        {
            Node<T> *current = nodes.front();
            nodes.pop();
            for (const auto &child : current->get_children())
            {
                if (child != nullptr)
                    nodes.push(child);
            }
            return *this;
        }

    private:
        std::queue<Node<T> *> nodes;
    };

    bfs_iterator begin_bfs_scan() const
    {
        return bfs_iterator(root);
    }

    bfs_iterator end_bfs_scan() const
    {
        return bfs_iterator(nullptr);
    }

    // DFS iterator
    class dfs_iterator
    {
    public:
        explicit dfs_iterator(Node<T> *node)
        {
            if (node)
                nodes.push(node);
        }

        bool operator!=(const dfs_iterator &other) const
        {
            return !nodes.empty() != !other.nodes.empty();
        }

        Node<T> *operator->() const
        {
            return nodes.top();
        }

        Node<T> &operator*() const
        {
            return *nodes.top();
        }

        dfs_iterator &operator++()
        {
            Node<T> *current = nodes.top();
            nodes.pop();
            for (auto it = current->get_children().rbegin(); it != current->get_children().rend(); ++it)
            {
                if (*it != nullptr)
                    nodes.push(*it);
            }
            return *this;
        }

    private:
        std::stack<Node<T> *> nodes;
    };

    dfs_iterator begin_dfs_scan() const
    {
        return dfs_iterator(root);
    }

    dfs_iterator end_dfs_scan() const
    {
        return dfs_iterator(nullptr);
    }

    bfs_iterator begin() const
    {
        return bfs_iterator(root);
    }

    bfs_iterator end() const
    {
        return bfs_iterator(nullptr);
    }

    // Heap iterator
    class heap_iterator
    {
    public:
        explicit heap_iterator(Node<T> *node)
        {
            if (node)
            {
                collect_nodes(node);
                std::make_heap(heap_nodes.begin(), heap_nodes.end(), CompareNodes());
            }
        }

        bool operator!=(const heap_iterator &other) const
        {
            return !heap_nodes.empty() != !other.heap_nodes.empty();
        }

        Node<T> *operator->() const
        {
            return heap_nodes.front();
        }

        Node<T> &operator*() const
        {
            return *heap_nodes.front();
        }

        heap_iterator &operator++()
        {
            if (!heap_nodes.empty())
            {
                std::pop_heap(heap_nodes.begin(), heap_nodes.end(), CompareNodes());
                heap_nodes.pop_back();
            }
            return *this;
        }

    private:
        struct CompareNodes
        {
            bool operator()(Node<T> *a, Node<T> *b)
            {
                return a->get_value() > b->get_value();
            }
        };

        void collect_nodes(Node<T> *node)
        {
            if (node)
            {
                heap_nodes.push_back(node);
                for (auto child : node->get_children())
                {
                    collect_nodes(child);
                }
            }
        }

        std::vector<Node<T> *> heap_nodes;
    };

    // In the Tree class
    heap_iterator myHeap() const
    {
        return heap_iterator(root);
    }

    heap_iterator end_heap() const
    {
        return heap_iterator(nullptr);
    }

    friend std::ostream &operator<<(std::ostream &os, const Tree &tree)
{
    if (!tree.root)
        return os;

    sf::RenderWindow window(sf::VideoMode(1000, 800), "Tree Visualization");
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Error loading font\n";
        return os;
    }

    const float node_radius = 25.f; // Slightly decreased node radius
    const float vertical_spacing = 80.f; // Reduced vertical spacing
    const float initial_horizontal_spacing = 200.f; // Reduced initial horizontal spacing

    std::map<Node<T> *, sf::Vector2f> positions;

    // Recursively position nodes
    std::function<void(Node<T> *, float, float, float)> position_nodes = [&](Node<T> *node, float x, float y, float horizontal_spacing)
    {
        if (!node)
            return;

        positions[node] = sf::Vector2f(x, y);

        float child_x_offset = x - (node->get_children().size() - 1) * horizontal_spacing / 2.f;

        for (size_t i = 0; i < node->get_children().size(); ++i)
        {
            Node<T> *child = node->get_children()[i];
            if (child)
            {
                position_nodes(child, child_x_offset + i * horizontal_spacing, y + vertical_spacing, horizontal_spacing / 2.f);
            }
        }
    };

    position_nodes(tree.root, window.getSize().x / 2.f, node_radius + 50.f, initial_horizontal_spacing);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        for (const auto &pair : positions)
        {
            Node<T> *node = pair.first;
            sf::Vector2f position = pair.second;

            sf::CircleShape circle(node_radius);
            circle.setFillColor(sf::Color::Green);
            circle.setPosition(position - sf::Vector2f(node_radius, node_radius));
            window.draw(circle);

            sf::Text text;
            text.setFont(font);
            if constexpr (std::is_same<T, std::string>::value)
            {
                text.setString(node->get_value());
            }
            else if constexpr (std::is_same<T, Complex>::value)
            {
                std::ostringstream oss;
                oss << node->get_value();
                text.setString(oss.str());
            }
            else
            {
                text.setString(std::to_string(node->get_value()));
            }
            text.setCharacterSize(16); // Slightly larger text size
            text.setFillColor(sf::Color::Black);
            sf::FloatRect text_bounds = text.getLocalBounds();
            text.setOrigin(text_bounds.left + text_bounds.width / 2.0f, text_bounds.top + text_bounds.height / 2.0f);
            text.setPosition(position);
            window.draw(text);

            for (Node<T> *child : node->get_children())
            {
                if (child)
                {
                    sf::Vector2f child_position = positions[child];

                    sf::Vertex line[] =
                        {
                            sf::Vertex(position, sf::Color::Black),
                            sf::Vertex(child_position, sf::Color::Black)};
                    window.draw(line, 2, sf::Lines);
                }
            }
        }

        window.display();
    }
    return os;
}





private:
    Node<T> *root;
    size_t k;

    static void flatten_to_vector(Node<T> *node, std::vector<Node<T> *> &result)
    {
        if (!node)
            return;
        result.push_back(node);
        for (auto child : node->get_children())
        {
            flatten_to_vector(child, result);
        }
    }

    void delete_tree(Node<T> *node)
    {
        if (!node)
            return;
        for (auto child : node->get_children())
        {
            delete_tree(child);
        }
        delete node;
        node = nullptr;
    }

    Node<T> *find_node(Node<T> *current, const T &value) const
    {
        if (current->get_value() == value)
            return current;
        for (auto child : current->get_children())
        {
            if (child)
            {
                Node<T> *result = find_node(child, value);
                if (result)
                    return result;
            }
        }
        return nullptr;
    }
};

#endif // TREE_HPP