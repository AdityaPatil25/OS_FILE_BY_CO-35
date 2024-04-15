#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;

class LRUCache {
public:
    LRUCache(int capacity) : _capacity(capacity) {}

    int get(int key) {
        auto it = _cache.find(key);
        if (it == _cache.end()) return -1;

        // Move accessed page to the front of the list
        _accessOrder.splice(_accessOrder.begin(), _accessOrder, it->second);

        return it->second->second;
    }

    void put(int key, int value) {
        auto it = _cache.find(key);
        if (it != _cache.end()) {
            // Update the value and move the page to the front of the list
            it->second->second = value;
            _accessOrder.splice(_accessOrder.begin(), _accessOrder, it->second);
            return;
        }

        if (_cache.size() >= _capacity) {
            // Remove the least recently used page from the cache
            int lruKey = _accessOrder.back().first;
            _cache.erase(lruKey);
            _accessOrder.pop_back();
        }

        // Add the new page to the cache and the front of the list
        _accessOrder.emplace_front(key, value);
        _cache[key] = _accessOrder.begin();
    }

private:
    int _capacity;
    list<pair<int, int>> _accessOrder; // List to keep track of the access order
    unordered_map<int, list<pair<int, int>>::iterator> _cache; // Map to quickly look up a page
};

int main() {
    LRUCache cache(2);

    cache.put(1, 1);
    cache.put(2, 2);
    cout << cache.get(1) << endl; // Returns 1
    cache.put(3, 3); // Evicts key 2
    cout << cache.get(2) << endl; // Returns -1 (not found)
    cache.put(4, 4); // Evicts key 1
    cout << cache.get(1) << endl; // Returns -1 (not found)
    cout << cache.get(3) << endl; // Returns 3
    cout << cache.get(4) << endl; // Returns 4

    return 0;
}
