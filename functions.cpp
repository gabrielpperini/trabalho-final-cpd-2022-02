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

void topN(int top, vector<string> args, HashTable table, string ordem)
{
    std::vector<PlayerData> list;

    PlayerData aux;
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
        
        Quicksort sorting(ordem);
        sorting.sort(&list, list.size());

        int j=0;
        for (int i = 0; i < top; i++)
        {
            if(list[j].count > 999){
                std::cout << setfill(' ');
                std::cout << setw(10) << list[j].sofifa_id << " |";
                std::cout << setw(40) << list[j].name << " |";
                std::cout << setw(15) << list[j].player_positions << " |";
                std::cout << setw(8) << setprecision(2) << list[j].rating << " |";
                std::cout << setw(8) << list[j].count << " |";
                std::cout << endl;
            }else{
                i--;
            }
            j++;
            
        }

        // quicksort(vetor, 0, top);
    }
}

void tags(vector<string> args, HashTable table)
{
    string firstArg = args[0];
    args.erase(args.begin());

    TagData data = table.searchTag(firstArg);
    std::vector<string> fifa_ids = data.sofifa_ids;

    for (auto &&arg : args)
    {
        TagData data = table.searchTag(arg);
        std::vector<string> fifa_ids_temp = {};
        for (auto &&fifaId : data.sofifa_ids)
        {
            if (std::find(fifa_ids.begin(), fifa_ids.end(), fifaId) != fifa_ids.end())
            {
                fifa_ids_temp.push_back(fifaId);
            }
        }
        fifa_ids.clear();
        fifa_ids = fifa_ids_temp;
    }

    if (fifa_ids.empty())
    {
        cout << "Nenhum resultado encontrado!" << endl;
    }
    else
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

        for (auto &&id : fifa_ids)
        {
            PlayerData playerData = table.search(id);

            std::cout << setfill(' ');
            std::cout << setw(10) << playerData.sofifa_id << " |";
            std::cout << setw(40) << playerData.name << " |";
            std::cout << setw(20) << playerData.player_positions << " |";
            std::cout << setw(8) << setprecision(2) << playerData.rating << " |";
            std::cout << setw(7) << playerData.count << " |";
            std::cout << endl;
        }
    }
}

void help()
{
    wcout << L"funcão de help" << endl;
}