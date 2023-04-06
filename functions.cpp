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

    std::vector<std::string> v;
    createVectorIDS(result, &v);

    for (auto &&i : v)
    {
        PlayerData playerData = table.search(i);

        std::cout << setfill(' ');
        std::cout << setw(10) << playerData.sofifa_id << " |";
        std::cout << setw(40) << playerData.name << " |";
        std::cout << setw(20) << playerData.player_positions << " |";
        std::cout << setw(8) << playerData.rating << " |";
        std::cout << setw(7) << playerData.count << " |";
        std::cout << endl;
    }

    // printResult(result, table);
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

    size_t limit = data.players.size() > 20 ? 20 : data.players.size();

    for (size_t i = 0; i < limit; i++)
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

    for (size_t i = 0; i < table.players.size(); ++i)
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

        int j = 0;
        size_t li = 0;
        while (j < top && li < list.size())
        {
            if (list[li].count >= 1000)
            {
                std::cout << setfill(' ');
                std::cout << setw(10) << list[li].sofifa_id << " |";
                std::cout << setw(40) << list[li].name << " |";
                std::cout << setw(20) << list[li].player_positions << " |";
                std::cout << setw(8) << list[li].rating << " |";
                std::cout << setw(7) << list[li].count << " |";
                std::cout << endl;
                j++;
            }
            li++;
        }

        if (!j)
            cout << "Nenhum dado encontrado!" << endl;
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
            std::cout << setw(8) << playerData.rating << " |";
            std::cout << setw(7) << playerData.count << " |";
            std::cout << endl;
        }
    }
}

void help()
{
    wcout << L"Menu de Ajuda" << endl;
    std::vector<std::vector<std::wstring>> helpVector = {
        {L"player <name or prefix>", L"Retorna uma lista de jogadores devido a pesquisa do nome"},
        {L"user <userID>", L"Retorna as maiores 20 notas dadas pelo usuário e os jogadores respectivos"},
        {L"top<N> <position>", L"Retorna os N melhores jogadores avaliados de certa posição com pelo menos 1000 avaliações"},
        {L"low<N> <position>", L"Retorna os N piores jogadores avaliados de certa posição com pelo menos 1000 avaliações"},
        {L"tags <list of tags>", L"Retorna todos os jogadores que tem as tags requisitadas"},
        {L"help", L"Abre o menu de ajuda"},
        {L"exit ou quit", L"Encerra o programa"},
    };

    for (auto &&hv : helpVector)
    {
        wcout << left << setw(30) << hv[0];
        wcout << hv[1] << endl;
    }
}