#include <iostream>
#include <iomanip>
#include <string>
#include "./csv-parser/parser.hpp"
#include "./trie.cpp"
#include "./hashTable.cpp"

using namespace aria::csv;

TrieStructure getPlayersTrie()
{
    TrieStructure data;

    std::ifstream f("./data/players.csv");
    CsvParser parser(f);

    parser.begin();
    for (auto &row : parser)
    {
        // std:cout << row.at(1) << "\n";
        data.insert(row.at(1), row.at(0), row.at(2));
    }

    return data;
}

HashTable getRatingsHashTable()
{
    HashTable table;
    // std::ifstream f("./data/rating.csv");
    std::ifstream f("./data/minirating.csv");
    CsvParser parser(f);

    parser.begin();
    for (auto &row : parser)
    {
        float rating = std::stof(row.at(2));
        string fifaId = row.at(1);

        if (table.search(fifaId).count == -1)
        {
            table.insert(fifaId, rating);
        }
        else
        {
            table.addRating(fifaId, rating);
        }
    }

    return table;
}

int printResult(TrieNode *result, HashTable data, int maxCount = 0)
{
    if (!result || maxCount >= 10)
        return maxCount;

    if (result->isEndOfWord)
    {
        ItemData ratingData = data.search(result->sofifa_id);

        std::cout << setw(10) << result->sofifa_id << " |";
        std::cout << setw(40) << result->playerName << " |";
        std::cout << setw(15) << result->positions << " |";
        std::cout << setw(8) << setprecision(2) << ratingData.rating << " |";
        std::cout << setw(8) << ratingData.count << " |" << endl;
        maxCount++;
    }

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        maxCount = printResult(result->children[i], data, maxCount);
    }
    return maxCount;
}

int main()
{
    HashTable table = getRatingsHashTable();
    // TrieStructure data = getPlayersTrie();

    std::cout << table.inserts << std::endl;
    std::cout << table.adds << std::endl;

    // TrieNode *result = data.search("Sergio");

    // printResult(result, table);

    return 0;
}