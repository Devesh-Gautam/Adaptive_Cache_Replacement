#include <iostream>
#include <unordered_map>
#include <vector>
#include <cstdlib> // for rand()
#include <ctime>   // for seeding rand()

using namespace std;

class RandomEvictionCache
{
private:
    int capacity;
    unordered_map<int, int> cache; // key -> value
    vector<int> keys;              // keeps track of keys for random eviction

public:
    RandomEvictionCache(int cap)
    {
        capacity = cap;
        srand(time(0)); // Seed the random number generator
    }

    int get(int key)
    {
        if (cache.find(key) != cache.end())
        {
            return cache[key];
        }
        return -1; // Not found
    }

    void put(int key, int value)
    {
        // If key already exists, update value only
        if (cache.find(key) != cache.end())
        {
            cache[key] = value;
            return;
        }

        // If cache is full, evict a random key
        if (cache.size() >= capacity)
        {
            int randIndex = rand() % keys.size();
            int evictKey = keys[randIndex];

            // Erase from both map and vector
            cache.erase(evictKey);
            keys.erase(keys.begin() + randIndex);
        }

        // Insert new key-value
        cache[key] = value;
        keys.push_back(key);
    }

    void displayCache()
    {
        cout << "Current cache contents: ";
        for (int key : keys)
        {
            cout << "(" << key << ":" << cache[key] << ") ";
        }
        cout << "\n";
    }
};