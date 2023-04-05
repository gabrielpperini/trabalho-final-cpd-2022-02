#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <tuple>

struct PlayerData
{
    std::string sofifa_id;
    std::string name;
    std::string player_positions;
    float rating;
    int count;
};
struct UserData
{
    std::string user_id;
    std::list<pair<float, PlayerData *>> players;
};

class HashTable
{
private:
    // number of buckets in the hash table
    static const int BUCKET_COUNT = 30011;

    

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
    // players vector
    std::vector<std::list<PlayerData>> players;
    // users vector
    std::vector<std::list<UserData>> users;
    
    // constructor
    HashTable() : players(BUCKET_COUNT), users(BUCKET_COUNT) {}

    // insert a key-value pair into the hash table
    void insert(const std::string &sofifa_id, const std::string &name, const std::string &player_positions)
    {
        unsigned long index = hash(sofifa_id);
        PlayerData data = {sofifa_id, name, player_positions, 0, 0};
        players[index].push_back(data);
    }

    // retrieve the rating and count associated with a key in the hash table
    PlayerData search(const std::string &sofifa_id)
    {
        unsigned long index = hash(sofifa_id);
        for (auto data : players[index])
        {
            if (data.sofifa_id == sofifa_id)
            {
                return data;
            }
        }
        // key not found, return {-1, -1} (or some other error value)
        PlayerData data = {"", "", "", -1.0f, -1};
        return data;
    }

    // retrieve the rating and count associated with a key in the hash table
    UserData searchUser(const std::string &user_id)
    {
        unsigned long index = hash(user_id);
        for (auto data : users[index])
        {
            if (data.user_id == user_id)
            {
                return data;
            }
        }
        // key not found, return {-1, -1} (or some other error value)
        UserData data = {"", {}};
        return data;
    }

    // update the rating and increase count associated with a key in the hash table
    void addRating(const std::string &sofifa_id, float rating, string user_id)
    {
        // adds++;
        unsigned long index = hash(sofifa_id);
        for (auto &data : players[index])
        {
            if (data.sofifa_id == sofifa_id)
            {
                data.rating = (data.rating * data.count) + rating;
                data.count++;
                data.rating /= data.count;

                unsigned long uIndex = hash(user_id);
                bool found = false;
                for (auto &u : users[uIndex])
                {
                    if (u.user_id == user_id)
                    {
                        // Find the appropriate position to insert the new player
                        auto it = u.players.begin();
                        while (it != u.players.end() && it->first > rating)
                        {
                            ++it;
                        }
                        // Insert the new player
                        u.players.insert(it, {rating, &data});
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    UserData uData = {user_id, {{rating, &data}}};
                    users[uIndex].push_back(uData);
                }

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
            int index = players[i].size();
            t[index]++;
            // std::cout << "Bucket " << i << ": " << players[i].size() << endl;
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
// PlayerData result = table.search("1234");
// std::cout << "Name: " << result.name << ", Player Positions: " << result.player_positions << ", Rating: " << result.rating << ", Count: " << result.count << std::endl;

//     return 0;
// }