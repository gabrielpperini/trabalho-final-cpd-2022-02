#include <iostream>
#include <list>
#include <string>
#include <vector>

struct ItemData
{
    std::string sofifa_id;
    float rating;
    int count;
};

float MAX_LOAD_FACTOR = 0.75f;

class HashTable
{
// private:
public:
    // initial number of buckets in the hash table
    static const int INITIAL_BUCKET_COUNT = 100;

    int inserts = 0;
    int adds = 0;
    // current number of buckets in the hash table
    int bucket_count;

    // number of elements in the hash table
    int element_count;

    // bucket vector
    std::vector<std::list<ItemData>> buckets;

    // hash function for strings (djb2 hash)
    unsigned long hash(const std::string &key)
    {
        unsigned long hashNum = 5381;
        for (char c : key)
        {
            hashNum = ((hashNum << 5) + hashNum) + c;
        }
        return hashNum % bucket_count;
    }

    // resize the hash table
    void resize(int new_bucket_count)
    {
        std::vector<std::list<ItemData>> new_buckets(new_bucket_count);
        for (auto &bucket : buckets)
        {
            for (auto &data : bucket)
            {
                unsigned long index = hash(data.sofifa_id);
                new_buckets[index].push_back(data);
            }
        }
        buckets = std::move(new_buckets);
        bucket_count = new_bucket_count;
    }

// public:
    // constructor
    HashTable() : bucket_count(INITIAL_BUCKET_COUNT), element_count(0), buckets(bucket_count) {}

    // insert a key-value pair into the hash table
    void insert(const std::string &key, float rating)
    {
        unsigned long index = hash(key);
        ItemData data = {key, rating, 1};
        buckets[index].push_back(data);
        element_count++;

        if (static_cast<float>(element_count) / bucket_count > MAX_LOAD_FACTOR)
        {
            resize(bucket_count * 2);
        }
        inserts++;
    }

    // retrieve the rating and count associated with a key in the hash table
    ItemData search(const std::string &key)
    {
        unsigned long index = hash(key);
        for (auto data : buckets[index])
        {
            if (data.sofifa_id == key)
            {
                return data;
            }
        }
        // key not found, return {-1, -1} (or some other error value)
        ItemData data = {"", -1.0f, -1};
        return data;
    }

    // update the rating and increase count associated with a key in the hash table
    void addRating(const std::string &key, float rating)
    {
        adds++;
        unsigned long index = hash(key);
        for (auto &data : buckets[index])
        {
            if (data.sofifa_id == key)
            {
                data.rating = (data.rating * data.count) + rating;
                data.count++;
                data.rating /= data.count;
                return;
            }
        }
        // key not found, do nothing (or throw an exception)
    }
};

// int main()
// {
//     // create a hash table and insert some elements
//     HashTable table;
//     table.insert("1234", 4.5f);
//     table.insert("5678", 3.2f);
//     table.insert("9012", 2.8f);

//     table.addRating("1234", 11.5f);
//     table.addRating("1234", 5.0f);

//     // search the rating and count of a key and print them to the console
//     ItemData result = table.search("1234");
//     std::cout << "Rating of item with sofifa_id 1234: " << result.rating << std::endl;
//     std::cout << "Count of item with sofifa_id 1234: " << result.count << std::endl;

//     return 0;
// }