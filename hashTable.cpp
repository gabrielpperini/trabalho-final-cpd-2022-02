#include <iostream>
#include <list>
#include <string>
#include <vector>

struct ItemData
{
    std::string sofifa_id;
    std::string name;
    std::string player_positions;
    float rating;
    int count;
};

class HashTable
{
private:
    // number of buckets in the hash table
    static const int BUCKET_COUNT = 30011;

    // bucket vector
    std::vector<std::list<ItemData>> buckets;

    // hash function for strings (sdbm hash)
    unsigned long hash(const std::string &key)
    {
        unsigned long hash = 0;
        for (char c : key)
        {
            hash = c + (hash << 6) + (hash << 16) - hash;
        }
        return hash % BUCKET_COUNT;
    }

public:
    // constructor
    HashTable() : buckets(BUCKET_COUNT) {}

    // insert a key-value pair into the hash table
    void insert(const std::string &sofifa_id, const std::string &name, const std::string &player_positions)
    {
        unsigned long index = hash(sofifa_id);
        ItemData data = {sofifa_id, name, player_positions, 0, 0};
        buckets[index].push_back(data);
    }

    // retrieve the rating and count associated with a key in the hash table
    ItemData search(const std::string &sofifa_id)
    {
        unsigned long index = hash(sofifa_id);
        for (auto data : buckets[index])
        {
            if (data.sofifa_id == sofifa_id)
            {
                return data;
            }
        }
        // key not found, return {-1, -1} (or some other error value)
        ItemData data = {"", "", "", -1.0f, -1};
        return data;
    }

    // update the rating and increase count associated with a key in the hash table
    void addRating(const std::string &sofifa_id, float rating)
    {
        // adds++;
        unsigned long index = hash(sofifa_id);
        for (auto &data : buckets[index])
        {
            if (data.sofifa_id == sofifa_id)
            {
                data.rating = (data.rating * data.count) + rating;
                data.count++;
                data.rating /= data.count;
                return;
            }
        }
        // key not found, do nothing (or throw an exception)
    }

    void printBuckets()
    {
        int t[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        for (size_t i = 0; i < BUCKET_COUNT; i++)
        {
            int index = buckets[i].size();
            t[index]++;
            // std::cout << "Bucket " << i << ": " << buckets[i].size() << endl;
        }
        for (int g = 0; g < 10; g++)
        {
            std::cout << "Buckets com size " << g << ": " << t[g] << endl;
        }
    }
};

// int main()
// {
//     // create a hash table and insert some elements
//     HashTable table;
//     table.insert("256679", "Lionel Messi", "CF");
//     table.insert("257710", "Cristiano Ronaldo", "LW");
//     table.insert("253710", "Kylian Mbapp", "ST");

// table.printBuckets();

// search the rating and count of a key and print them to the console
// ItemData result = table.search("1234");
// std::cout << "Name: " << result.name << ", Player Positions: " << result.player_positions << ", Rating: " << result.rating << ", Count: " << result.count << std::endl;

//     return 0;
// }