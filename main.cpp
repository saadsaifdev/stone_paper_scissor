#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// ================== COLORS (ANSI) ==================
const string RED    = "\033[31m";
const string GREEN  = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE   = "\033[34m";
const string CYAN   = "\033[36m";
const string RESET  = "\033[0m";

string ColorText(string Text, string Color)
{
    return Color + Text + RESET;
}

// ================== ENUMS ==================
enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

// ================== STRUCTS ==================
struct stRoundInfo
{
    short RoundNumber = 0;
    enGameChoice Player1Choice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName;
};

struct stGameResults
{
    short GameRounds = 0;
    short Player1WinTimes = 0;
    short ComputerWinTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName = "";
};

// ================== FUNCTIONS ==================
int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

enGameChoice GetComputerChoice()
{
    return (enGameChoice)RandomNumber(1, 3);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
    if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
        return enWinner::Draw;

    switch (RoundInfo.Player1Choice)
    {
    case enGameChoice::Stone:
        return (RoundInfo.ComputerChoice == enGameChoice::Paper) ? enWinner::Computer : enWinner::Player1;
    case enGameChoice::Paper:
        return (RoundInfo.ComputerChoice == enGameChoice::Scissors) ? enWinner::Computer : enWinner::Player1;
    case enGameChoice::Scissors:
        return (RoundInfo.ComputerChoice == enGameChoice::Stone) ? enWinner::Computer : enWinner::Player1;
    }
    return enWinner::Draw;
}

enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
    if (Player1WinTimes > ComputerWinTimes)
        return enWinner::Player1;
    else if (ComputerWinTimes > Player1WinTimes)
        return enWinner::Computer;
    else
        return enWinner::Draw;
}

string ChoiceName(enGameChoice Choice)
{
    string arrGameChoices[3] = { "Stone", "Paper", "Scissors" };
    return arrGameChoices[Choice - 1];
}

string WinnerName(enWinner Winner)
{
    string arrWinnerName[3] = { "Player1", "Computer", "No Winner (Draw)" };
    return arrWinnerName[Winner - 1];
}

enGameChoice ReadPlayer1Choice()
{
    short Choice;
    do
    {
        cout << "\nYour Choice: "
             << ColorText("[1] Stone", CYAN) << " "
             << ColorText("[2] Paper", CYAN) << " "
             << ColorText("[3] Scissors", CYAN) << " ? ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 3);

    return (enGameChoice)Choice;
}

short ReadHowManyRounds()
{
    short Rounds;
    do
    {
        cout << "\nHow many rounds do you want to play? ";
        cin >> Rounds;
    } while (Rounds < 1);

    return Rounds;
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
    string Color;

    if (RoundInfo.Winner == enWinner::Player1)
        Color = GREEN;
    else if (RoundInfo.Winner == enWinner::Computer)
        Color = RED;
    else
        Color = YELLOW;

    cout << "\n____________ Round [" << RoundInfo.RoundNumber << "] ____________\n\n";
    cout << "Player1 Choice : " << ChoiceName(RoundInfo.Player1Choice) << endl;
    cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner   : "
         << ColorText("[" + RoundInfo.WinnerName + "]", Color) << endl;
    cout << "_________________________________________\n";
}

stGameResults PlayGame(short HowManyRounds)
{
    stRoundInfo RoundInfo;
    short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

    for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
    {
        cout << "\n" << ColorText("Round [" + to_string(GameRound) + "] begins:", BLUE) << endl;

        RoundInfo.RoundNumber = GameRound;
        RoundInfo.Player1Choice = ReadPlayer1Choice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        if (RoundInfo.Winner == enWinner::Player1)
            Player1WinTimes++;
        else if (RoundInfo.Winner == enWinner::Computer)
            ComputerWinTimes++;
        else
            DrawTimes++;

        PrintRoundResults(RoundInfo);
    }

    stGameResults GameResults;
    GameResults.GameRounds = HowManyRounds;
    GameResults.Player1WinTimes = Player1WinTimes;
    GameResults.ComputerWinTimes = ComputerWinTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameWinner = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);

    return GameResults;
}

void StartGame()
{
    char PlayAgain = 'Y';

    do
    {
        system("clear"); // macOS
        cout << ColorText("=== Rock Paper Scissors Game ===\n", CYAN);

        short Rounds = ReadHowManyRounds();
        stGameResults GameResults = PlayGame(Rounds);

        string FinalColor;
        if (GameResults.GameWinner == enWinner::Player1)
            FinalColor = GREEN;
        else if (GameResults.GameWinner == enWinner::Computer)
            FinalColor = RED;
        else
            FinalColor = YELLOW;

        cout << "\n========== Game Over ==========\n";
        cout << "Player1 Wins : " << GameResults.Player1WinTimes << endl;
        cout << "Computer Wins: " << GameResults.ComputerWinTimes << endl;
        cout << "Draw Times   : " << GameResults.DrawTimes << endl;
        cout << "Final Winner : "
             << ColorText(GameResults.WinnerName, FinalColor) << endl;
        cout << "===============================\n";

        cout << "\nDo you want to play again? (Y/N): ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

// ================== MAIN ==================
int main()
{
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}