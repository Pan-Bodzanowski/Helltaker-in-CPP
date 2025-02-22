#include <iostream>
#include "Settings.h"
#include "Taker.h"
#include "Object.h"
#include "Field.h"
#include "Board.h"
#include "BoardTree.h"
#include "Gameplay.h"
using namespace std;

int main()
{
    gameplay().play();
    return 0;
}

///HELLTAKER IN C++
///by Michał Bojanowski
/*
This is a game of Helltaker remade in C++. When the game generates, move in the
board with 'wasd' keys and press enter to verify your moves. You can also retry
the game (press 'r'), end the program (press 'e') and skip the puzzle and
generate a new one (type in 'skip' and nothing else). In case if the program
fails to generate a puzzle, exit the program and try again.
*/

