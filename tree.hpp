// Tsadik88@gmail.com
#ifndef TREE_HPP
#define TREE_HPP

#include <queue> // For BFS iterator
#include <iostream> // For input-output stream
#include <stack> // For stack data structure used in iterators
#include <vector> // For dynamic array used for storing children nodes
#include <stdexcept> // For throwing exceptions
#include <algorithm> // For std::make_heap and std::pop_heap in heap iterator
#include <SFML/Graphics.hpp> // For tree visualization
#include "node.hpp" // Including the Node class definition
#include <map> // For mapping nodes to positions in visualization
#include "complex.hpp" // For handling complex numbers
#include <sstream> // For string stream

template <typename T>
class Tree
{
public:
    explicit Tree(size_t k = 2) : root(nullptr), k(k) {} // Constructor with default k value

    void add_root(Node<T> &node)
    {
        root = &node; // Setting the root node of the tree
    }

    void add_sub_node(Node<T> &parent, Node<T> &child)
    {
        if (!root)
        {
            throw std::runtime_error("Error: Root not set."); // Throw error if root is not set
        }

        Node<T> *parentNode = find_node(root, parent.get_value());
        if (parentNode)
        {
            parentNode->add_child(&child, k); // Add child to parent node if found
        }
        else
        {
            throw std::runtime_error("Parent node not found."); // Throw error if parent node not found
        }
    }

    template <typename U>
    void add_sub_node(Node<T> &parent, Node<U> &child)
    {
        throw std::runtime_error("Child node type does not match"); // Prevent adding child of different type
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
                nodes.push(node); // Initialize with root node
        }

        bool operator!=(const pre_order_iterator &other) const
        {
            return !nodes.empty() != !other.nodes.empty(); // Check if nodes stack is not empty
        }

        Node<T> *operator->() const
        {
            return nodes.top(); // Return top node in stack
        }

        Node<T> &operator*() const
        {
            return *nodes.top(); // Dereference top node in stack
        }

        pre_order_iterator &operator++()
        {
            Node<T> *current = nodes.top();
            nodes.pop();
            for (auto it = current->get_children().rbegin(); it != current->get_children().rend(); ++it)
            {
                if (*it != nullptr)
                    nodes.push(*it); // Push children to stack in reverse order
            }
            return *this;
        }

    private:
        std::stack<Node<T> *> nodes; // Stack for nodes
        size_t k; // Maximum number of children
    };

    pre_order_iterator begin_pre_order() const
    {
        return pre_order_iterator(root, k); // Return iterator starting at root
    }

    pre_order_iterator end_pre_order() const
    {
        return pre_order_iterator(nullptr, k); // Return iterator at end
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
                    pushLeftmostPath(node); // Push leftmost path for binary trees
                }
                else
                {
                    nodes.push(node); // Push root node for general trees
                }
            }
            ++(*this); // Move to the first valid node
        }

        bool operator!=(const post_order_iterator &other) const
        {
            return current != other.current; // Check if current node is not the same as other's current node
        }

        Node<T> *operator->() const
        {
            return current; // Return current node
        }

        Node<T> &operator*() const
        {
            return *current; // Dereference current node
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
                            pushLeftmostPath(parent->get_children()[1]); // Push leftmost path for right child
                        }
                    }
                    current = node;
                }
                else
                {
                    current = nullptr; // End iteration if stack is empty
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
                            nodes.push(*it); // Push children in reverse order
                        }
                    }
                    current = node;
                }
                else
                {
                    current = nullptr; // End iteration if stack is empty
                }
            }
            return *this;
        }

    private:
        std::stack<Node<T> *> nodes; // Stack for nodes
        Node<T> *current; // Current node
        size_t k; // Maximum number of children

        void pushLeftmostPath(Node<T> *node)
        {
            while (node)
            {
                nodes.push(node);
                if (!node->get_children().empty())
                {
                    node = node->get_children()[0]; // Push leftmost children
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
        return post_order_iterator(root, k); // Return iterator starting at root
    }

    post_order_iterator end_post_order() const
    {
        return post_order_iterator(nullptr, k); // Return iterator at end
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
                {
                    push_left(node); // Push leftmost path for binary trees
                }
                else
                {
                    nodes.push(node); // Push root node for general trees
                    while (!nodes.empty() && !nodes.top())
                        nodes.pop();
                }
            }
        }

        bool operator!=(const in_order_iterator &other) const
        {
            return !nodes.empty() != !other.nodes.empty(); // Check if nodes stack is not empty
        }

        Node<T> *operator->() const
        {
            return nodes.top(); // Return top node in stack
        }

        Node<T> &operator*() const
        {
            return *nodes.top(); // Dereference top node in stack
        }

        in_order_iterator &operator++()
        {
            if (nodes.empty())
                return *this;

            if (k == 2)
            {
                Node<T> *node = nodes.top();
                nodes.pop();
                if (node->get_children().size() > 1 && node->get_children()[1] != nullptr)
                {
                    push_left(node->get_children()[1]); // Push leftmost path for right child
                }
            }
            else
            {
                Node<T> *current = nodes.top();
                nodes.pop();
                for (auto it = current->get_children().rbegin(); it != current->get_children().rend(); ++it)
                {
                    if (*it != nullptr)
                        nodes.push(*it); // Push children in reverse order
                }
            }
            return *this;
        }

    private:
        std::stack<Node<T> *> nodes; // Stack for nodes
        size_t k; // Maximum number of children

        void push_left(Node<T> *node)
        {
            while (node != nullptr)
            {
                nodes.push(node);
                if (node->get_children().size() > 0)
                    node = node->get_children()[0]; // Push leftmost children
                else
                    break;
            }
        }
    };

    in_order_iterator begin_in_order() const
    {
        return in_order_iterator(root, k); // Return iterator starting at root
    }

    in_order_iterator end_in_order() const
    {
        return in_order_iterator(nullptr, k); // Return iterator at end
    }

    // BFS iterator
    class bfs_iterator
    {
    public:
        explicit bfs_iterator(Node<T> *node)
        {
            if (node)
                nodes.push(node); // Initialize with root node
        }

        bool operator!=(const bfs_iterator &other) const
        {
            return !nodes.empty() != !other.nodes.empty(); // Check if nodes queue is not empty
        }

        Node<T> *operator->() const
        {
            return nodes.front(); // Return front node in queue
        }

        Node<T> &operator*() const
        {
            return *nodes.front(); // Dereference front node in queue
        }

        bfs_iterator &operator++()
        {
            Node<T> *current = nodes.front();
            nodes.pop();
            for (const auto &child : current->get_children())
            {
                if (child != nullptr)
                    nodes.push(child); // Push all children to queue
            }
            return *this;
        }

    private:
        std::queue<Node<T> *> nodes; // Queue for nodes
    };

    bfs_iterator begin_bfs_scan() const
    {
        return bfs_iterator(root); // Return iterator starting at root
    }

    bfs_iterator end_bfs_scan() const
    {
        return bfs_iterator(nullptr); // Return iterator at end
    }

    // DFS iterator
    class dfs_iterator
    {
    public:
        explicit dfs_iterator(Node<T> *node)
        {
            if (node)
                nodes.push(node); // Initialize with root node
        }

        bool operator!=(const dfs_iterator &other) const
        {
            return !nodes.empty() != !other.nodes.empty(); // Check if nodes stack is not empty
        }

        Node<T> *operator->() const
        {
            return nodes.top(); // Return top node in stack
        }

        Node<T> &operator*() const
        {
            return *nodes.top(); // Dereference top node in stack
        }

        dfs_iterator &operator++()
        {
            Node<T> *current = nodes.top();
            nodes.pop();
            for (auto it = current->get_children().rbegin(); it != current->get_children().rend(); ++it)
            {
                if (*it != nullptr)
                    nodes.push(*it); // Push children in reverse order
            }
            return *this;
        }

    private:
        std::stack<Node<T> *> nodes; // Stack for nodes
    };

    dfs_iterator begin_dfs_scan() const
    {
        return dfs_iterator(root); // Return iterator starting at root
    }

    dfs_iterator end_dfs_scan() const
    {
        return dfs_iterator(nullptr); // Return iterator at end
    }

    bfs_iterator begin() const
    {
        return bfs_iterator(root); // Default iterator is BFS starting at root
    }

    bfs_iterator end() const
    {
        return bfs_iterator(nullptr); // Default iterator at end
    }

    // Heap iterator
    class heap_iterator
    {
    public:
        explicit heap_iterator(Node<T> *node, size_t k) : k(k)
        {
            if (k != 2) {
                throw std::runtime_error("Cannot create heap iterator for non-binary tree"); // Throw error if tree is not binary
            }
            if (node)
            {
                collect_nodes(node); // Collect all nodes for heap
                std::make_heap(heap_nodes.begin(), heap_nodes.end(), CompareNodes()); // Create a heap
            }
        }

        bool operator!=(const heap_iterator &other) const
        {
            return !heap_nodes.empty() != !other.heap_nodes.empty(); // Check if heap is not empty
        }

        Node<T> *operator->() const
        {
            return heap_nodes.front(); // Return front node in heap
        }

        Node<T> &operator*() const
        {
            return *heap_nodes.front(); // Dereference front node in heap
        }

        heap_iterator &operator++()
        {
            if (!heap_nodes.empty())
            {
                std::pop_heap(heap_nodes.begin(), heap_nodes.end(), CompareNodes()); // Remove front node
                heap_nodes.pop_back();
            }
            return *this;
        }

    private:
        struct CompareNodes
        {
            bool operator()(Node<T> *a, Node<T> *b)
            {
                return a->get_value() > b->get_value(); // Compare nodes by value
            }
        };

        void collect_nodes(Node<T> *node)
        {
            if (node)
            {
                heap_nodes.push_back(node); // Collect current node
                for (auto child : node->get_children())
                {
                    collect_nodes(child); // Recursively collect children nodes
                }
            }
        }

        std::vector<Node<T> *> heap_nodes; // Vector for heap nodes
        size_t k; // Maximum number of children
    };

    heap_iterator myHeap() const
    {
        return heap_iterator(root, k); // Return heap iterator starting at root
    }

    heap_iterator end_heap() const
    {
        return heap_iterator(nullptr, k); // Return heap iterator at end
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
    Node<T> *root; // Root node of the tree
    size_t k; // Maximum number of children

    static void flatten_to_vector(Node<T> *node, std::vector<Node<T> *> &result)
    {
        if (!node)
            return;
        result.push_back(node); // Add current node to result
        for (auto child : node->get_children())
        {
            flatten_to_vector(child, result); // Recursively flatten children
        }
    }

    void delete_tree(Node<T> *node)
    {
        if (!node)
            return;
        for (auto child : node->get_children())
        {
            delete_tree(child); // Recursively delete children
        }
        delete node; // Delete current node
        node = nullptr; // Set node to null
    }

    Node<T> *find_node(Node<T> *current, const T &value) const
    {
        if (current->get_value() == value)
            return current; // Return node if value matches
        for (auto child : current->get_children())
        {
            if (child)
            {
                Node<T> *result = find_node(child, value); // Recursively search children
                if (result)
                    return result; // Return result if found
            }
        }
        return nullptr; // Return null if not found
    }
};

#endif // TREE_HPP