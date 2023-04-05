#include "infra.cpp"

using namespace std;

void player(vector<string> args, HashTable table, TrieStructure searchTree)
{
    wcout << L"funcão de pesquisa do player" << endl;
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
        auto p = std::next(std::begin( data.players), i);

        cout << setw(10) << p->second->sofifa_id << " |";
        cout << setw(40) << p->second->name << " |";
        cout << setw(15) << p->second->rating << " |";
        cout << setw(7) << p->second->count << " |";
        cout << setw(8) << p->first << " |";
        cout << endl;
    }
}

int menorElementoPos(vector<PlayerData> vetor){
    int posicaoMenor=0;
    for (int i = 1; i < vetor.size(); ++i) {
    if (vetor[i].rating < vetor[posicaoMenor].rating) {
      posicaoMenor = i; // Atualiza a posição do menor elemento
    }
  }
  return posicaoMenor; // Retorna a posição do menor elemento

}

void topN(int top, vector<string> args, HashTable table, TrieStructure searchTree)
{
    std::list<PlayerData> list;  
    
    PlayerData aux;
    int pos=0;
    std::vector<PlayerData> vetor(top);

    for (int i = 0; i < table.players.size(); ++i) {
        for (auto it = table.players[i].begin(); it != table.players[i].end(); ++it) {
            aux=*it;
            size_t pos = 0;
            if((pos = aux.player_positions.find(args[0], pos)) != std::string::npos){
                list.push_back(aux);
                
                
            }            
        }
    }   
    
    if(list.empty()){
        wcout << L"Lista Vazia não foi possivel verificar" << endl;
    }else {
        auto interador =list.begin();
       int i=0;
        while (interador != list.end())
        {
            if(i<top){
                if(std::next(interador) != list.end()){
                    aux=*interador;
                    if(aux.count>2){
                    vetor[i]=*interador;
                    i++;
                    }
                    ++interador;
            }            
            }else if(std::next(interador) != list.end()){
                aux=*interador;
                pos=menorElementoPos(vetor);
                if(aux.count>2){
                    if(vetor[pos].rating < aux.rating ){
                    vetor[pos]=*interador;                
                    }
                }
                ++interador;
            }else ++interador;
        }
        

        for (int i = 0; i < top; i++)
        {
            std::cout << setw(10) << vetor[i].sofifa_id << " |";
            std::cout << setw(40) << vetor[i].name << " |";
            std::cout << setw(15) << vetor[i].player_positions << " |";
            std::cout << setw(8) << setprecision(2) << vetor[i].rating << " |";
            std::cout << setw(8) << vetor[i].count << " |";
            std::cout << endl;
        }

        //quicksort(vetor, 0, top);
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