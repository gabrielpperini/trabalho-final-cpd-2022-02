#include "infra.cpp"

using namespace std;

void player(vector<string> args, HashTable table, TrieStructure searchTree)
{
    wcout << L"funcão de pesquisa do player" << endl;
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
        auto p = std::next(std::begin( data.players), i);

        cout << setw(10) << p->second->sofifa_id << " |";
        cout << setw(40) << p->second->name << " |";
        cout << setw(15) << p->second->rating << " |";
        cout << setw(7) << p->second->count << " |";
        cout << setw(8) << p->first << " |";
        cout << endl;
    }
}

void topN(int top, vector<string> args, HashTable table, TrieStructure searchTree)
{
    wcout << L"funcão de pesquisa de player por posição" << endl;
}

void tags(vector<string> args, HashTable table, TrieStructure searchTree)
{
    wcout << L"funcão de pesquisa de player por tags" << endl;
}

void help()
{
    wcout << L"funcão de help" << endl;
}