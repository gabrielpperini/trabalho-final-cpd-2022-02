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
    //std::ifstream f("./data/rating.csv");
    std::ifstream f("./data/minirating.csv");
    CsvParser parser(f);

    parser.begin();
    for (auto &row : parser)
    {
        float rating = std::stof(row.at(2));
        string fifaId = row.at(1);
        table->addRating(fifaId, rating, row.at(0));
    }
}

int printResult(TrieNode *result, HashTable data, int maxCount = 0)
{
    if (!result || maxCount >= 10)
        return maxCount;

    if (result->isEndOfWord)
    {
        PlayerData playerData = data.search(result->sofifa_id);

        std::cout << setw(10) << result->sofifa_id << " |";
        std::cout << setw(40) << playerData.name << " |";
        std::cout << setw(15) << playerData.player_positions << " |";
        std::cout << setw(8) << setprecision(2) << playerData.rating << " |";
        std::cout << setw(8) << playerData.count << " |";
        std::cout << endl;
        maxCount++;
    }

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        maxCount = printResult(result->children[i], data, maxCount);
    }
    return maxCount;
}


void troca(int i,int j, vector<PlayerData> lista){
    PlayerData aux;
    aux=lista[i];
    lista[i]=lista[j];
    lista[j]=aux;
}
// função para ordenar uma lista usando o algoritmo QuickSort
void quicksort(vector<PlayerData> lista, int inicio, int fim) {
    int i = inicio;
    int j = fim;
    PlayerData pivo = lista[(inicio + fim) / 2]; // escolhe um elemento aleatório como pivô

    // particiona a lista em dois subconjuntos: elementos menores que o pivô e elementos maiores que o pivô
    while (i <= j) {
        while (lista[i].rating < pivo.rating) {
            i++;
        }
        while (lista[j].rating > pivo.rating) {
            j--;
        }
        if (i <= j) {
            troca(i,j,lista);
            i++;
            j--;
        }
    }
    // recursivamente ordena os subconjuntos
    if (inicio < j) {
        quicksort(lista, inicio, j);
    }
    if (i < fim) {
        quicksort(lista, i, fim);
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