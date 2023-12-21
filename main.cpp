#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class FiniteAutomaton {
private:
    string startState = "S0";
    string inputString;
    set<string> alphabet;
    vector<string> states;
    vector<string> lexemes;
    vector<vector<string>> transitionMatrix;

public:
    // Constructor
    FiniteAutomaton() {
        // ¬вод алфавита
        cout << "Enter the alphabet (type 'done' to finish):\n";
        string symbol;
        while (true) {
            cout << "Symbol (type 'done' to finish): ";
            cin >> symbol;

            if (symbol == "done") {
                break;
            }

            alphabet.insert(symbol);
        }

        // ¬вод матрицы переходов
        cout << "Enter the transition matrix (rows: states, columns: alphabet), type 'done' to finish:\n";
        string currentState;
        while (true) {
            cout << "State (type 'done' to finish): ";
            cin >> currentState;

            if (currentState == "done") {
                break;
            }

            states.push_back(currentState);

            vector<string> row;
            for (const auto& symbol : alphabet) {
                string nextState;
                cout << currentState << ": " << symbol << " -> ";
                cin >> nextState;
                row.push_back(nextState);
            }

            transitionMatrix.push_back(row);
        }

        // ¬вод строки
        cout << "Enter the input string to check: ";
        cin >> inputString;

        // Convert the input string to alphabet characters
        for (int stringIndex = 0; stringIndex < inputString.length();) {
            bool isSymbolFound = false;

            for (const auto& symbol : alphabet) {
                if (inputString.compare(stringIndex, symbol.length(), symbol) == 0) {
                    lexemes.push_back(symbol);
                    stringIndex += symbol.length();
                    isSymbolFound = true;
                    break;
                }
            }

            if (!isSymbolFound) {
                cerr << "Error: Invalid input string!" << endl;
                break;
            }
        }
    }

    void lexemesCheck() {
        for (auto elem : lexemes)
            cout << elem << " ";
        cout << endl;
    }

    bool isReachable(vector<string> targetStates) {
        string currentState = startState;
        for (const auto& lexeme : lexemes) {
            auto stateIndex = distance(states.begin(), find(states.begin(), states.end(), currentState));
            auto symbolIndex = distance(alphabet.begin(), find(alphabet.begin(), alphabet.end(), lexeme));

            currentState = transitionMatrix[stateIndex][symbolIndex];

            for (auto targetState : targetStates)
                if (currentState == targetState)
                    return true;
        }
        return false;
    }
};
/*
Enter the alphabet (type 'done' to finish):
Symbol (type 'done' to finish): yes
Symbol (type 'done' to finish): no
Symbol (type 'done' to finish): done
Enter the transition matrix (rows: states, columns: alphabet), type 'done' to finish:
State (type 'done' to finish): S0
S0: no -> S1
S0: yes -> S1
State (type 'done' to finish): S1
S1: no -> S2
S1: yes -> S2
State (type 'done' to finish): done
*/

int main() {
    FiniteAutomaton ATM;

    ATM.lexemesCheck();

    vector<string> acceptStates = { "S1", "S3" };

    if (ATM.isReachable(acceptStates))
        cout << "Target is achievable!" << endl;
    else
        cout << "Target is not achievable!";

    return 0;
}