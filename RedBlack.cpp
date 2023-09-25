#include <iostream>
#include <list>
#include <vector>
#include <random>
#include <chrono>
#include <map>

template <typename KeyType, typename ValueType, typename Compare = std::less<KeyType>>
class unordered_map {
private:
    using Bucket = std::list<std::pair<const KeyType, ValueType>>;
    using BucketIterator = typename Bucket::iterator;
    using BucketConstIterator = typename Bucket::const_iterator;
    std::map<KeyType, ValueType, Compare> map;
    size_t num_elements;

public:
    unordered_map(const Compare& compare = Compare())
        : map(compare), num_elements(0) {}

    ValueType& operator[](const KeyType& key) {
        return map[key];
    }

    void insert(const std::pair<const KeyType, ValueType>& item) {
        map.insert(item);
        ++num_elements;
    }

    void erase(const KeyType& key) {
        map.erase(key);
        --num_elements;
    }

    size_t size() const {
        return num_elements;
    }

    void clear() {
        map.clear();
        num_elements = 0;
    }

    bool empty() const {
        return num_elements == 0;
    }

    size_t count(const KeyType& key) const {
        return map.count(key);
    }

    BucketIterator find(const KeyType& key) {
        return map.find(key);
    }

    BucketConstIterator find(const KeyType& key) const {
        return map.find(key);
    }
};


int main() {
    // Experiment 1: int keys
    std::cout << "Experiment 1: int keys" << std::endl;
    std::cout << "------------------------" << std::endl;

    unordered_map<int, float> my_map_int;
    std::vector<int> keys_int;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100000);

    // Insert 100,000 elements
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; ++i) {
        int key = dis(gen);
        my_map_int[key] = 0.0f;
        keys_int.push_back(key);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration_insert = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // Find 100,000 elements
    start = std::chrono::high_resolution_clock::now();
    for (int key : keys_int) {
        my_map_int[key];
    }
    end = std::chrono::high_resolution_clock::now();
    auto duration_find = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // Erase 100,000 elements
    start = std::chrono::high_resolution_clock::now();
    for (int key : keys_int) {
        my_map_int.erase(key);
    }
    end = std::chrono::high_resolution_clock::now();
    auto duration_erase = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Insertion time: " << duration_insert << " ms" << std::endl;
    std::cout << "Find time: " << duration_find << " ms" << std::endl;
    std::cout << "Erase time: " << duration_erase << " ms" << std::endl;

    // Experiment 2: string keys
    std::cout << "\nExperiment 2: string keys" << std::endl;
    std::cout << "---------------------------" << std::endl;

    unordered_map<std::string, float> my_map_string;
    std::vector<std::string> keys_string;
    std::uniform_int_distribution<> dis_string(0, 7);
    std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    // Insert 100,000 elements
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; ++i) {
        std::string key;
        for (int j = 0; j < 8; ++j) {
            key.push_back(charset[dis_string(gen)]);
        }
        my_map_string[key] = 0.0f;
        keys_string.push_back(key);
    }
    end = std::chrono::high_resolution_clock::now();
    duration_insert = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // Find 100,000 elements
    start = std::chrono::high_resolution_clock::now();
    for (std::string key : keys_string) {
        my_map_string[key];
    }
    end = std::chrono::high_resolution_clock::now();
    duration_find = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // Erase 100,000 elements
    start = std::chrono::high_resolution_clock::
    for (std::string key : keys_string) {
    my_map_string.erase(key);
}
end = std::chrono::high_resolution_clock::now();
duration_erase = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

std::cout << "Insertion time: " << duration_insert << " ms" << std::endl;
std::cout << "Find time: " << duration_find << " ms" << std::endl;
std::cout << "Erase time: " << duration_erase << " ms" << std::endl;

return 0;
}

