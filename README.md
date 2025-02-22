# Helltaker in C++


### What is this project?
This project is a programmer's take on a popular video game "Helltaker". Its purpose is to generate random puzzles from the game for the user to play.

### What is "Helltaker"?
Helltaker is a game made by Łukasz "Vanripper" Piskorz about a man who had adream of having a harem ("private space" in Arabic) full of demon girls and then went to hell to make it come true. The game, apart from the puzzles, also contains dialogue sequences with the demons, also making it a dating simulator. But don't worry, I only focused on the former ;).

### How do the puzzles work?
You have a board of different square cells on which there are the Taker and a demon girl. Your goal is to move th Taker to orthogonally adjacent cells to get next to her in a given number of moves while avoiding or defeating some of the obstacles.

### How do I use the code?
As you've got an access to this zip folder, go to Helltaker_in_cpp->bin->debug and then open the "Helltaker_in_cpp" application. Once the puzzle generates, along with the number of moves, move across the board with "wasd" keys. You can input several moves in a single line of input. Then press enter to verify your moves and the board should update correspondig to the directions you chose to go. You can also retry the puzzle (press 'r'), exit the program (press 'e') or retry the current puzzle (type in 'skip' and nothing else). As you type in the commands, be sure not to alternate the capitalization of the letters, otherwise the program won't recognize the input properly. In case if the program freezes, exit manually and re-open the application.

### How exactly do the obstacles on the grid work?
Well, I hoped that you'd explore the game by yourself, but fine, here's the list of all the game's obstacles:
 * **Rock ('R')**: When the player tries to move to the position of the rock, he instead pushes it one cell in that direction for as long as there is an empty space.
 * **Guard ('G')**: Behaves like a rock, except when there's no empty space to be moved to, it gets destroyed instead of remaining still.
 * **Spikes ('S' or 's')**: When the Taker moves into the spikes while they're exposed (represented by 'S'), the number of moves left is additionally subtracted by 1.
 * **Key ('K') and Chest ('C')**: When the player moves into the cell with a key, he automatically obtains it and that field turns into a default empty cell. When the player stands orthogonally adjacent to the chest while having a key, it also disappears, leaving an empty cell behind.
### How does all this code work?
Great question, fellow user! I basically used a lot of object-oriented programming to divide pretty much every aspect of the game into different classes. For instance, I split the game board's cells into two categories: those with which the player can interact (Rocks and Guards) and those that always stay in the same spot (spikes, a key and a chest). For that purpose, I defined "object" and "field" classes respectively, which both derive from a class "settings" which is used to configure each cell type's generation frequency. Those by the way are also subclasses of the two classes mentioned before. Then there's the Taker, which is also a class of it's own (the "taker" class). With those being implemented, I defined a class "board", which basically treats the game board as a 2D array of pairs of the Object and the Field (as both of them can be in the same spot at the same time) and the demon girl as a pair of integers, representing her position in the grid. Then, I used the created board to calculate a minimal number of moves necessary to complete a level using a class "boardtree". This class is being implemented as a tree which saves the current state of the board in the node and the state of it after each possible move in the branches. And finally, I use it all together in the class "gameplay", which implements the way the whole program actually works.

### Is there anything else you'd like to address about the program?
Yes, actually, as a matter of fact, I'd like to confess to you about something... The code isn't perfect. I mentioned in the program usage paragraph that it might freeze. And I did it for a reason, because that might happen because of an ongoing puzzle generation or minimal move calculation. I unfortunately did not manage to fix this issue, no matter how hard I've tried, and so the project technically remains unfinished. I will remove this bug one day, whether by myself or with someone's help. But for me, it's fine, as at the very least I did something nobody has ever done before...
