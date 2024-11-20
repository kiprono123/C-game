#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Function to roll a dice with a specified number of sides
int rollDice(int sides) {
    return rand() % sides + 1; // Generates a random number between 1 and "sides"
}

// Function to display an ASCII representation of the dice roll (supports up to 6-sided dice for visual display)
void displayDice(int roll) {
    switch (roll) {
        case 1:
            cout << "┌─────┐\n"
                    "│     │\n"
                    "│  •  │\n"
                    "│     │\n"
                    "└─────┘\n";
            break;
        case 2:
            cout << "┌─────┐\n"
                    "│ •   │\n"
                    "│     │\n"
                    "│   • │\n"
                    "└─────┘\n";
            break;
        case 3:
            cout << "┌─────┐\n"
                    "│ •   │\n"
                    "│  •  │\n"
                    "│   • │\n"
                    "└─────┘\n";
            break;
        case 4:
            cout << "┌─────┐\n"
                    "│ • • │\n"
                    "│     │\n"
                    "│ • • │\n"
                    "└─────┘\n";
            break;
        case 5:
            cout << "┌─────┐\n"
                    "│ • • │\n"
                    "│  •  │\n"
                    "│ • • │\n"
                    "└─────┘\n";
            break;
        case 6:
            cout << "┌─────┐\n"
                    "│ • • │\n"
                    "│ • • │\n"
                    "│ • • │\n"
                    "└─────┘\n";
            break;
        default:
            cout << roll << "\n"; // For non-standard dice, display the number
            break;
    }
}

// Function to display the leaderboard
void displayLeaderboard(const vector<pair<string, int>>& scores) {
    cout << "\n===== Final Leaderboard =====\n";
    for (const auto& player : scores) {
        cout << player.first << ": " << player.second << " points\n";
    }
    cout << "=============================\n";
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
    vector<pair<string, int>> players;
    int sides, rounds;

    cout << "Welcome to the Dice Roller Game!\n";

    // Input dice sides
    do {
        cout << "Enter the number of sides for the dice (minimum 2): ";
        cin >> sides;
        if (sides < 2)
            cout << "Dice must have at least 2 sides. Try again.\n";
    } while (sides < 2);

    // Input number of players
    int numPlayers;
    do {
        cout << "Enter the number of players (minimum 2): ";
        cin >> numPlayers;
        if (numPlayers < 2)
            cout << "You need at least 2 players. Try again.\n";
    } while (numPlayers < 2);
    cin.ignore();

    // Input player names
    for (int i = 0; i < numPlayers; ++i) {
        cout << "Enter the name of player " << i + 1 << ": ";
        string name;
        getline(cin, name);
        players.push_back({name, 0});
    }

    // Input rounds
    do {
        cout << "Enter the number of rounds (minimum 1): ";
        cin >> rounds;
        if (rounds < 1)
            cout << "There must be at least 1 round. Try again.\n";
    } while (rounds < 1);

    // Game loop
    for (int round = 1; round <= rounds; ++round) {
        cout << "\n===== Round " << round << " =====\n";
        for (auto& player : players) {
            cout << "It's " << player.first << "'s turn! Rolling...\n";
            int roll1 = rollDice(sides);
            int roll2 = rollDice(sides);

            cout << "Rolls:\n";
            displayDice(roll1);
            displayDice(roll2);

            int total = roll1 + roll2;
            cout << "Total for this turn: " << total << "\n";

            player.second += total;
        }
    }

    // Determine and display the winner
    sort(players.begin(), players.end(), [](const auto& a, const auto& b) {
        return b.second < a.second; // Sort in descending order of scores
    });

    displayLeaderboard(players);

    cout << "\nCongratulations, " << players.front().first << "! You are the winner with " 
         << players.front().second << " points!\n";

    cout << "Thank you for playing. Goodbye!\n";
    return 0;
}
