#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <list>

using namespace std;

class BaseCache {
public:
    virtual bool has(const string& key) = 0;
    virtual string read(const string& key) = 0;
    virtual void write(const string& key, const string& value) = 0;
    virtual void delete_(const string& key) = 0;
    virtual ~BaseCache() {}
};

class MemoryCache : public BaseCache {
    unordered_map<string, string> cache;
public:
    bool has(const string& key) override {
        return cache.find(key) != cache.end();
    }

    string read(const string& key) override {
        return cache[key];
    }

    void write(const string& key, const string& value) override {
        cache[key] = value;
    }

    void delete_(const string& key) override {
        cache.erase(key);
    }
};

class FileCache : public BaseCache {
    string getFileName(const string& key) {
        hash<string> hasher;
        return to_string(hasher(key)) + ".txt";
    }

public:
    bool has(const string& key) override {
        ifstream file(getFileName(key));
        return file.good();
    }

    string read(const string& key) override {
        ifstream file(getFileName(key));
        string value;
        getline(file, value);
        return value;
    }

    void write(const string& key, const string& value) override {
        ofstream file(getFileName(key));
        file << value;
    }

    void delete_(const string& key) override {
        remove(getFileName(key).c_str());
    }
};

class NullCache : public BaseCache {
public:
    bool has(const string& key) override {
        return false;
    }

    string read(const string& key) override {
        return "";
    }

    void write(const string& key, const string& value) override {}

    void delete_(const string& key) override {}
};

class PoorManMemoryCache : public BaseCache {
    unordered_map<string, string> cache;
    list<string> keys;
    size_t capacity;

public:
    PoorManMemoryCache(size_t cap) : capacity(cap) {}

    bool has(const string& key) override {
        return cache.find(key) != cache.end();
    }

    string read(const string& key) override {
        return cache[key];
    }

    void write(const string& key, const string& value) override {
        if (cache.size() >= capacity) {
            string oldest = keys.front();
            keys.pop_front();
            cache.erase(oldest);
        }
        cache[key] = value;
        keys.push_back(key);
    }

    void delete_(const string& key) override {
        cache.erase(key);
        keys.remove(key);
    }
};

class CacheApplier {
    BaseCache* strategy;

public:
    void set_strategy(BaseCache& strategy) {
        this->strategy = &strategy;
    }

    string read_from_cache(const string& key) {
        if (strategy->has(key)) {
            return strategy->read(key);
        }
        return "Ключ не найден";
    }

    void write_from_cache(const string& key, const string& value) {
        strategy->write(key, value);
    }

    void delete_from_cache(const string& key) {
        strategy->delete_(key);
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    MemoryCache memoryCache;
    FileCache fileCache;
    NullCache nullCache;
    PoorManMemoryCache poorCache(2);

    CacheApplier applier;

    applier.set_strategy(memoryCache);
    applier.write_from_cache("vasja", "+79454585888");
    applier.write_from_cache("petja", "+79499585888");
    cout << applier.read_from_cache("vasja") << endl;

    applier.set_strategy(fileCache);
    applier.write_from_cache("vasja", "+79454585888");
    cout << applier.read_from_cache("vasja") << endl;

    applier.set_strategy(nullCache);
    applier.write_from_cache("vasja", "+79454585888");
    cout << applier.read_from_cache("vasja") << endl;

    applier.set_strategy(poorCache);
    applier.write_from_cache("vasja", "+79454585888");
    applier.write_from_cache("petja", "+79499585888");
    applier.write_from_cache("kolja", "+79491112233");
    cout << applier.read_from_cache("vasja") << endl;
    cout << applier.read_from_cache("petja") << endl;

    return 0;
}