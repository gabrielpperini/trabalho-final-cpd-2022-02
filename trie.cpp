// C++ implementation of search and insert
// operations on Trie
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

const int ALPHABET_SIZE = 26;

// trie node
struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];

    // sofifa_id
    string sofifa_id;
    string playerName;
    string positions;
    // isEndOfWord is true if the node represents
    // end of a word
    bool isEndOfWord;
};

void printTrieTree(TrieNode *root, int depth = 0)
{
    if (root == nullptr)
    {
        return;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i] != nullptr)
        {
            char c = 'a' + i;
            for (int j = 0; j < depth; j++)
            {
                cout << "  ";
            }
            cout << "+-" << c << endl;
            printTrieTree(root->children[i], depth + 1);
        }
    }
}

class TrieStructure
{

public:
    TrieNode *trie;

    TrieStructure()
    {
        trie = getNode();
    }

    // Returns new trie node (initialized to NULLs)
    struct TrieNode *getNode(void)
    {
        struct TrieNode *pNode = new TrieNode;

        pNode->isEndOfWord = false;

        for (int i = 0; i < ALPHABET_SIZE; i++)
            pNode->children[i] = NULL;

        return pNode;
    }

    // If not present, inserts key into trie
    // If the key is prefix of trie node, just
    // marks leaf node
    void insert(string key, string sofifa_id, string positions)
    {
        struct TrieNode *pCrawl = trie;
        int strSize = key.length();
        for (int i = 0; i < strSize; i++)
        {
            int index = tolower(key[i]) - 'a';
            if (index < 0 || index >= 26)
                continue;
            if (!pCrawl->children[index])
            {
                pCrawl->children[index] = getNode();
            }

            pCrawl = pCrawl->children[index];
        }

        // mark last node as leaf
        pCrawl->isEndOfWord = true;
        // add sofifa_id
        pCrawl->sofifa_id = sofifa_id;
        pCrawl->positions = positions;
        pCrawl->playerName = key;
    }

    void print()
    {
        printTrieTree(trie);
    }

    // Returns true if key presents in trie, else
    // false
    TrieNode* search(string key)
    {
        struct TrieNode *pCrawl = trie;
        int strSize = key.length();
        for (int i = 0; i < strSize; i++)
        {
            int index = tolower(key[i]) - 'a';
            if (index < 0 || index >= 26)
                continue;
            if (!pCrawl->children[index]){
                return NULL;
            }

            pCrawl = pCrawl->children[index];
        }

        return pCrawl;
    }
};

// Driver
// int main()
// {
//     // Input keys (use only 'a' through 'z'
//     // and lower case)
//     string keys[] = {"the", "a", "there",
//                      "answer", "any", "by",
//                      "bye", "their"};
//     int n = sizeof(keys) / sizeof(keys[0]);

//     struct TrieNode *root = getNode();

//     // Construct trie
//     for (int i = 0; i < n; i++)
//         insert(root, keys[i]);

//     // Search for different keys
//     search(root, "the") ? cout << "Searching for THEN: found\n" : cout << "Searching for THEN: not found\n";
//     search(root, "these") ? cout << "Searching for THESE: found\n" : cout << "Searching for THESE: not found\n";
//     search(root, "an") ? cout << "Searching for AN: found\n" : cout << "Searching for AN: not found\n";
//     search(root, "a") ? cout << "Searching for A: found\n" : cout << "Searching for A: not found\n";
//     search(root, "any") ? cout << "Searching for ANY: found\n" : cout << "Searching for ANY: not found\n";
//     search(root, "anyb") ? cout << "Searching for ANYB: found\n" : cout << "Searching for ANYB: not found\n";
//     return 0;
