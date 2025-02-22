#ifndef GAMEPLAY_H_INCLUDED
#define GAMEPLAY_H_INCLUDED

/*!
* The 'gameplay class' implements the game's overall mechanics, including puzzle\n
* generation, calculation of the number of moves necessary to complete a level\n
* and reading input from the user.
*/

class gameplay {
    /// attempt to generate a game
    board curr;
    /// when the game generation is successful
    board game;
    public:

        /// constructor
        gameplay(): curr() {
            boardtree bt(curr.unmovable());
            curr.print();
            do {
                bt = boardtree(curr.unmovable());
                for (int i = 0; i < 99; i++) {
                    bt.expand_and_del();
                    if (bt.move_minimum() < 100) break;
                }
                if (bt.move_minimum() == 100) curr = board();
            } while (bt.move_minimum() == 100);

            curr.assign_moves(bt.move_minimum() * DIFFICULTY);
            curr.score();
            game = board(curr);
        }
    /// the whole gameplay in an infinite loop
    void play() {
        while (1) {
            while (game.single_try() == 0) {
                if (game.single_try() == 2) * this = gameplay();
                game = board(curr);
                game.print();
                game.score();
            }
            cout << "NEXT GAME..." << endl;
            * this = gameplay();
        }
    }
};


#endif // GAMEPLAY_H_INCLUDED
