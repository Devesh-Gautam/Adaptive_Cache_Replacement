#include <bits/stdc++.h>
using namespace std;

class LFUCache {
    int capacity, minFreq;
    unordered_map<int, int> keyToVal;
    unordered_map<int, int> keyToFreq;
    unordered_map<int, list<int>> freqToKeys;
    unordered_map<int, list<int>::iterator> keyToIter;

public:
    LFUCache(int capacity) {
        this->capacity = capacity;
        minFreq = 0;
    }

    int get(int key) {
        if (keyToVal.find(key) == keyToVal.end())
            return -1;

        int freq = keyToFreq[key];
        freqToKeys[freq].erase(keyToIter[key]);

        keyToFreq[key]++;
        freqToKeys[freq + 1].push_front(key);
        keyToIter[key] = freqToKeys[freq + 1].begin();

        if (freqToKeys[minFreq].empty())
            minFreq++;

        return keyToVal[key];
    }

    void put(int key, int value) {
        if (capacity <= 0) return;

        if (keyToVal.find(key) != keyToVal.end()) {
            keyToVal[key] = value;
            get(key); // update frequency
            return;
        }

        if (keyToVal.size() >= capacity) {
            int evictKey = freqToKeys[minFreq].back();
            freqToKeys[minFreq].pop_back();

            keyToVal.erase(evictKey);
            keyToFreq.erase(evictKey);
            keyToIter.erase(evictKey);
        }

        keyToVal[key] = value;
        keyToFreq[key] = 1;
        freqToKeys[1].push_front(key);
        keyToIter[key] = freqToKeys[1].begin();
        minFreq = 1;
    }
};
