#include <iostream>
#include <queue>
#include <stack>
#include <functional>

template< class TKey, class TValue >
class Dictionary final
{
public:
    Dictionary() = default;
    ~Dictionary()
    {
        clear();
    }
    Dictionary(const Dictionary&) = delete;
    Dictionary(Dictionary&&) = delete;
    Dictionary& operator=(const Dictionary&) = delete;
    Dictionary& operator=(Dictionary&&) = delete;

    struct Node
    {
        Node* left = nullptr;
        Node* right = nullptr;
        Node* parent = nullptr;
        TKey key;
        TValue value;

        Node(const std::pair< TKey, TValue >& pair) :
            key(pair.first),
            value(pair.second)
        { }
    };

    void insert(const std::pair< TKey, TValue >& pair) noexcept
    {
        ++size_;

        auto* newNode = new Node(pair);

        if (!root_)
            root_ = newNode;
        else
        {
            auto* ptr = root_;

            while (ptr)
            {
                if (ptr->key < pair.first)
                {
                    if (ptr->right)
                        ptr = ptr->right;
                    else
                    {
                        newNode->parent = ptr;
                        ptr->right = newNode;
                        ptr = nullptr;
                    }
                }
                else
                {
                    if (ptr->left)
                        ptr = ptr->left;
                    else
                    {
                        newNode->parent = ptr;
                        ptr->left = newNode;
                        ptr = nullptr;
                    }
                }
            }
        }
    }

    Node* find(const TKey& key) noexcept
    {
        auto* temp = root_;
        while (temp)
        {
            if (temp->key != key)
            {
                if (temp->key < key)
                    temp = temp->right;
                else
                    temp = temp->left;
            }
            else
            {
                return temp;
            }
        }

        return temp;
    }

    std::size_t size() const noexcept
    {
        return size_;
    }

    void clear() noexcept
    {
        if (root_ == nullptr)
            return;

        std::queue<Node*> queue;
        queue.push(root_);

        Node* front = nullptr;

        while (!queue.empty())
        {

            front = queue.front();
            queue.pop();

            if (front->left) {
                queue.push(front->left);
            }

            if (front->right) {
                queue.push(front->right);
            }

            delete front;
        }

        root_ = nullptr;
        size_ = 0;
    }

    void each(std::function<void(Node&)> func) noexcept
    {
        if (root_ == nullptr)
            return;

        std::stack<Node*> stack;
        stack.push(root_);

        Node* front = nullptr;
        while (!stack.empty())
        {
            front = stack.top();
            stack.pop();

            if (front->right)
                stack.push(front->right);
            if (front->left)
                stack.push(front->left);

            func(*front);
        }
    }

private:
    Node* root_ = nullptr;
    std::size_t size_ = 0;
};

