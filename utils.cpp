#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> parseCommand(const string& command) {
    vector<string> args;
    string arg;

    bool inQuote = false;
    char quoteType = '\0';

    for (char c : command) {
        if ((c == '\'' || c == '\"' || c == '`') && !inQuote) {
            inQuote = true;
            quoteType = c;
        } else if (c == quoteType && inQuote) {
            inQuote = false;
            quoteType = '\0';
        } else if (c == ' ' && !inQuote) {
            if (!arg.empty()) {
                args.push_back(arg);
                arg.clear();
            }
        } else {
            arg += c;
        }
    }

    if (!arg.empty()) {
        args.push_back(arg);
    }

    return args;
}

// int main() {
//     string input;

//     while (true) {
//         cout << "Enter a command: ";
//         getline(cin, input);

//         vector<string> args = parseCommand(input);

//         if (args.empty()) {
//             continue;
//         }

//         string command = args[0];
//         args.erase(args.begin());

//         cout << "Command: " << command << endl;
//         cout << "Arguments:" << endl;

//         for (string arg : args) {
//             cout << "- " << arg << endl;
//         }

//         // TODO: Execute the command with the given arguments
//     }

//     return 0;
// }