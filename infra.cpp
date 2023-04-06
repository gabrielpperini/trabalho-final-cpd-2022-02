#include <iostream>
#include <iomanip>
#include <string>
#include "./external/csv-parser.hpp"
#include "./trie.cpp"
#include "./hashTable.cpp"

using namespace aria::csv;

void getPlayersData(TrieStructure trie, HashTable *table)
{

    std::ifstream f("./data/players.csv");
    CsvParser parser(f);

    parser.begin();
    for (auto &row : parser)
    {
        // std:cout << row.at(1) << "\n";
        trie.insert(row.at(0), row.at(1));
        table->insert(row.at(0), row.at(1), row.at(2));
    }
}

void getRatingsHashTable(HashTable *table)
{
    std::ifstream f("./data/rating.csv");
    // std::ifstream f("./data/minirating.csv");
    CsvParser parser(f);

    parser.begin();
    for (auto &row : parser)
    {
        float rating = std::stof(row.at(2));
        string fifaId = row.at(1);
        table->addRating(fifaId, rating, row.at(0));
    }
}

void getTagsHashTable(HashTable *table)
{
    std::ifstream f("./data/tags.csv");
    CsvParser parser(f);

    parser.begin();
    for (auto &row : parser)
    {
        string sofifa_id = row.at(1);
        string tag = row.at(2);
        table->insertTag(tag, sofifa_id);
    }
}

int printResult(TrieNode *result, HashTable data, int maxCount = 0)
{
    if (!result || maxCount >= 10)
        return maxCount;

    if (result->isEndOfWord)
    {
        PlayerData playerData = data.search(result->sofifa_id);

        std::cout << setfill(' ');
        std::cout << setw(10) << result->sofifa_id << " |";
        std::cout << setw(40) << playerData.name << " |";
        std::cout << setw(20) << playerData.player_positions << " |";
        std::cout << setw(8) << setprecision(2) << playerData.rating << " |";
        std::cout << setw(7) << playerData.count << " |";
        std::cout << endl;
        maxCount++;
    }

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (!result->children[i])
            continue;
        maxCount = printResult(result->children[i], data, maxCount);
    }
    return maxCount;
}

void createVectorIDS(TrieNode *result, std::vector<std::string> *v)
{
    if (!result)
        return;

    if (result->isEndOfWord)
    {
        v->push_back(result->sofifa_id);
    }

    for (auto &&s : result->children)
    {
        if (s)
            createVectorIDS(s, v);
    }
}

// int main()
// {
//     clock_t start_clock, end_clock;

//     start_clock = clock();

//     HashTable table;
//     TrieStructure searchTree;

//     getPlayersData(searchTree, &table);
//     getRatingsHashTable(&table);

//     end_clock = clock();

//     std::cout << "====================================================" << std::endl;
//     std::cout << "pre-proccessing time: "<< (end_clock - start_clock) / (double)CLOCKS_PER_SEC << std::endl;
//     std::cout << "====================================================" << std::endl;

//     TrieNode *result = searchTree.search("Sergio");

//     printResult(result, table);

//     return 0;
// }