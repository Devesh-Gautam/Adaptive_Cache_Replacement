#include <bits/stdc++.h>
using namespace std;

class MRUCache
{
private:
    // made it private to avoid conflicts of redefinition with other cache implemntation
    class Node
    {
    public:
        int key, value;
        Node *prev;
        Node *next;

        Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
    };

    int capacity;
    unordered_map<int, Node *> cacheMap;
    Node *head;
    Node *tail;

    // Add node right after head
    void addNode(Node *node)
    {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

    // Remove a node from the list
    void removeNode(Node *node)
    {
        Node *prevNode = node->prev;
        Node *nextNode = node->next;

        prevNode->next = nextNode;
        nextNode->prev = prevNode;
    }

    // Move an existing node to the front
    void moveToFront(Node *node)
    {
        removeNode(node);
        addNode(node);
    }

    // Remove least recently used node (from tail)
    Node *removeMRUNode()
    {
        Node *mru = head->next;
        removeNode(mru);
        return mru;
    }

public:
    MRUCache(int capacity) : capacity(capacity)
    {
        // Dummy head and tail nodes for easier handling
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        head->next = tail;
        tail->prev = head;
    }

    int get(int key)
    {
        if (cacheMap.find(key) == cacheMap.end())
        {
            return -1;
        }
        Node *node = cacheMap[key];
        moveToFront(node);
        return node->value;
    }

    void put(int key, int value)
    {
        if (cacheMap.find(key) != cacheMap.end())
        {
            Node *node = cacheMap[key];
            node->value = value;
            moveToFront(node);
        }
        else
        {
            if (cacheMap.size() == capacity)
            {
                Node *mru = removeMRUNode();
                cacheMap.erase(mru->key);
                delete mru;
            }

            Node *newNode = new Node(key, value);
            cacheMap[key] = newNode;
            addNode(newNode);
        }
    }

    ~MRUCache()
    {
        // Cleanup all nodes
        Node *current = head;
        while (current)
        {
            Node *next = current->next;
            delete current;
            current = next;
        }
    }
};