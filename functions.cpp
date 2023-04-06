#include "quicksort.cpp"

using namespace std;

void player(vector<string> args, HashTable table, TrieStructure searchTree)
{
    cout << endl;

    cout << setfill(' ');
    cout << setw(10) << "so_fifa_id"
         << " |";
    cout << setw(40) << "name"
         << " |";
    cout << setw(20) << "player_positions"
         << " |";
    cout << setw(8) << "rating"
         << " |";
    cout << setw(7) << "count"
         << " |";
    cout << endl;
    cout << setfill('-') << setw(95) << "" << endl;
    cout << setfill(' ');

    TrieNode *result = searchTree.search(args[0]);

    printResult(result, table);
}

void user(vector<string> args, HashTable table)
{
    UserData data = table.searchUser(args[0]);

    cout << "\n";

    cout << setfill(' ');
    cout << setw(10) << "so_fifa_id"
         << " |";
    cout << setw(40) << "name"
         << " |";
    cout << setw(15) << "global_rating"
         << " |";
    cout << setw(7) << "count"
         << " |";
    cout << setw(8) << "rating"
         << " |";
    cout << endl;
    cout << setfill('-') << setw(90) << "" << endl;
    cout << setfill(' ');

    for (size_t i = 0; i < data.players.size(); i++)
    {
        auto p = std::next(std::begin(data.players), i);

        cout << setw(10) << p->second->sofifa_id << " |";
        cout << setw(40) << p->second->name << " |";
        cout << setw(15) << p->second->rating << " |";
        cout << setw(7) << p->second->count << " |";
        cout << setw(8) << p->first << " |";
        cout << endl;
    }
}

int menorElementoPos(vector<PlayerData> vetor)
{
    int posicaoMenor = 0;
    for (int i = 1; i < vetor.size(); ++i)
    {
        if (vetor[i].rating < vetor[posicaoMenor].rating)
        {
            posicaoMenor = i; // Atualiza a posição do menor elemento
        }
    }
    return posicaoMenor; // Retorna a posição do menor elemento
}

void topN(int top, vector<string> args, HashTable table, TrieStructure searchTree)
{
    std::vector<PlayerData> list;

    PlayerData aux;
    int pos = 0;
    std::vector<PlayerData> vetor(top);

    for (int i = 0; i < table.players.size(); ++i)
    {
        for (auto it = table.players[i].begin(); it != table.players[i].end(); ++it)
        {
            aux = *it;
            size_t pos = 0;
            if ((pos = aux.player_positions.find(args[0]), pos) != std::string::npos)
            {
                list.push_back(*it);
            }
        }
    }

    if (list.empty())
    {
        wcout << L"Lista Vazia não foi possivel verificar" << endl;
    }
    else
    {
        
        Quicksort sorting("ASC");
        sorting.sort(&list, list.size());


        for (int i = 0; i < top; i++)
        {
            std::cout << setfill(' ');
            std::cout << setw(10) << list[i].sofifa_id << " |";
            std::cout << setw(40) << list[i].name << " |";
            std::cout << setw(15) << list[i].player_positions << " |";
            std::cout << setw(8) << setprecision(2) << list[i].rating << " |";
            std::cout << setw(8) << list[i].count << " |";
            std::cout << endl;
        }

        // quicksort(vetor, 0, top);
    }
}

void tags(vector<string> args, HashTable table, TrieStructure searchTree)
{
    wcout << L"funcão de pesquisa de player por tags" << endl;
}

void help()
{
    wcout << L"funcão de help" << endl;
}