#include <iostream>
#include <unordered_map>
#include <list>
#include <algorithm>
using namespace std;

class ARCCache {
private:
    int capacity;
    int p; // Target size for T1

    list<int> T1, T2, B1, B2;
    unordered_map<int, int> valueMap; // key -> value
    unordered_map<int, list<int>::iterator> positionMap;

    // REPLACE subroutine based on ARC paper
    void replace(int key) {
        if (!T1.empty() &&
            (T1.size() > p || (find(B2.begin(), B2.end(), key) != B2.end() && T1.size() == p))) {
            int victim = T1.back();
            T1.pop_back();
            B1.push_front(victim);
            positionMap.erase(victim);
            valueMap.erase(victim);
        } else if (!T2.empty()) {
            int victim = T2.back();
            T2.pop_back();
            B2.push_front(victim);
            positionMap.erase(victim);
            valueMap.erase(victim);
        }
    }

public:
    ARCCache(int cap) : capacity(cap), p(0) {}

    int get(int key) {
        if (positionMap.find(key) != positionMap.end()) {
            // Cache hit in T1 or T2
            if (find(T1.begin(), T1.end(), key) != T1.end()) {
                T1.erase(positionMap[key]);
            } else {
                T2.erase(positionMap[key]);
            }
            T2.push_front(key);
            positionMap[key] = T2.begin();
            return valueMap[key];
        }
        return -1; // Miss
    }

    void put(int key, int value) {
        // Case I: Key is in T1 or T2 (cache hit)
        if (positionMap.find(key) != positionMap.end()) {
            get(key); // promote to T2
            valueMap[key] = value;
            return;
        }

        // Case II: Key is in B1 (ghost hit)
        if (find(B1.begin(), B1.end(), key) != B1.end()) {
            p = min(capacity, p + max(1, (int)B2.size() / max(1, (int)B1.size())));
            replace(key);
            B1.remove(key);
            T2.push_front(key);
            valueMap[key] = value;
            positionMap[key] = T2.begin();
            return;
        }

        // Case III: Key is in B2 (ghost hit)
        if (find(B2.begin(), B2.end(), key) != B2.end()) {
            p = max(0, p - max(1, (int)B1.size() / max(1, (int)B2.size())));
            replace(key);
            B2.remove(key);
            T2.push_front(key);
            valueMap[key] = value;
            positionMap[key] = T2.begin();
            return;
        }

        // Case IV: Key is not in any list (cold miss)
        if ((int)(T1.size() + T2.size()) >= capacity) {
            replace(key);
        }

        // Maintain total list size ≤ 2 * capacity
        if ((int)(T1.size() + T2.size() + B1.size() + B2.size()) >= 2 * capacity) {
            if (!B2.empty()) B2.pop_back();
            else if (!B1.empty()) B1.pop_back();
        }

        T1.push_front(key);
        positionMap[key] = T1.begin();
        valueMap[key] = value;
    }

    void printState() {
        cout << "T1: ";
        for (auto x : T1) cout << x << " ";
        cout << endl;

        cout << "T2: ";
        for (auto x : T2) cout << x << " ";
        cout << endl;

        cout << "B1: ";
        for (auto x : B1) cout << x << " ";
        cout << endl;

        cout << "B2: ";
        for (auto x : B2) cout << x << " ";
        cout << endl;

        cout << "p = " << p << "\n";
        cout << "-----------------------------\n";
    }
};

// int main() {
//     ARCCache arc(4); // Cache capacity = 4

//     arc.put(1, 10);
//     arc.put(2, 20);
//     arc.put(3, 30);
//     arc.put(4, 40);
//     arc.printState();

//     arc.put(5, 50); // triggers REPLACE
//     arc.printState();

//     arc.get(2);     // promotes 2 to T2
//     arc.put(6, 60); // REPLACE again
//     arc.printState();

//     arc.put(2, 200); // update value
//     arc.printState();

//     arc.get(10); // miss
//     arc.printState();

//     return 0;
// }
