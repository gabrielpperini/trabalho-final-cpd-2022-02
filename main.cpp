#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <locale.h>
#include <conio.h>

#include "utils.cpp"

#include "functions.cpp"

using namespace std;

vector<string> getCommand()
{
    cout << setw(80) << setfill('=') << "" << endl;
    cout << "Insira seu comando" << endl;
    wcout << L"digite help para mais informações" << endl;
    cout << setw(80) << setfill('=') << "" << endl;
    cout << endl
         << "> ";

    string input;
    getline(cin, input);

    return parseCommand(input);
}

int main()
{
    system("cls");
    setlocale(LC_ALL, "");

    clock_t start_clock, end_clock;

    wcout << L"Pré processamento dos dados em andamento..." << endl;
    start_clock = clock();

    HashTable table;
    TrieStructure searchTree;

    getPlayersData(searchTree, &table);
    getRatingsHashTable(&table);

    end_clock = clock();

    system("cls");
    wcout << L"Pré Processamento concluido em " << (end_clock - start_clock) / (double)CLOCKS_PER_SEC << " segundos" << endl;

    while (true)
    {
        vector<string> args = getCommand();

        string command = args[0];
        args.erase(args.begin());

        if (command == "player")
        {
            player(args, table, searchTree);
        }
        else if (command == "user")
        {
            user(args, table);
        }
        else if (command.substr(0, 3) == "top")
        {
            int number = stof(command.substr(3));
            topN(number, args, table, searchTree);
        }
        else if (command == "tags")
        {
            tags(args, table, searchTree);
        }
        else if (command == "help")
        {
            help();
        }
        else if (command == "quit" || command == "exit")
        {
            return 0;
        }
        else
        {
            wcerr << endl
                  << L"Comando Inválido!";
        }

        cout << "\n\nClique em qualquer tecla para continuar...";
        _getch();
        system("cls");
    }

    return 0;
}
