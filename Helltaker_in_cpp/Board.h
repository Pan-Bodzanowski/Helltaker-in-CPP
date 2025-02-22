#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include <vector>
#include <cstdlib>
#include <time.h>
#include <memory>
#include <algorithm>
#include <utility>


/// random integer from mn to mx
int random(int mn, int mx) {
    return mn + (rand() % (mx - mn + 1));
}

using namespace std;
/*!
* The 'board' class implements the game board, including it's random generation\n
* (constructor) and taking input from user and either making a move, quiting\n
* the program or resetting the puzzle (initialized here and implemented in\n
* 'BoardTree.cpp').
*/
class board {
    /// all the fields used in puzzle generation
    inline static vector < field * > field_io = {
        new field(),
        new null(),
        new spikes_osc(false),
        new spikes_osc(true),
        new spikes_const(),
        new key(),
        new chest()
    };

    /// all the objects used in puzzle generation
    inline static vector < object * > object_io = {
        new rock(),
        new guard()
    };

    /// the game board
    vector < vector < pair < field * , object * >>> b;

    /// board width
    unsigned int w;
    /// board height
    unsigned int h;

    /// player and his position in the board
    taker t;
    unsigned int tposw;
    unsigned int tposh;

    /// position of the demoness
    unsigned int dposw;
    unsigned int dposh;

    /// position of the board to it's representation
    char to_print(unsigned int i, unsigned int j) {
        if (tposw == j && tposh == i) return 'T';
        if (dposw == j && dposh == i) return 'D';
        for (auto & q: object_io)
            if ( * b[i][j].second == * q) return q -> rep();
        for (auto & p: field_io)
            if ( * b[i][j].first == * p) return p -> rep();
    }

    public:

        /// copying constructor
        board(const board & bb):
            b(bb.b),
            w(bb.w),
            h(bb.h),
            t(bb.t),
            tposw(bb.tposw),
            tposh(bb.tposh),
            dposw(bb.dposw),
            dposh(bb.dposh) {}

    /// all the oscillating spikes switch their state upon a move
    void move_update() {
        field * ptr;
        for (int i = 1; i < h - 1; i++)
            for (int j = 1; j < w - 1; j++) {
                if ( * b[i][j].first == spikes_osc(false))
                    b[i][j].first = new spikes_osc(true);
                else if ( * b[i][j].first == spikes_osc(true))
                b[i][j].first = new spikes_osc(false);
                else continue;
            }
        t.moves--;
    }

    /// main constructor
    board():
        w(random(S_MIN, S_MAX) + 2),
        h(random(S_MIN, S_MAX) + 2),
        dposw(0),
        dposh(0),
        t(99) {
            srand(time(NULL));
            int i, j, k, hc, wc;
            bool keyy = false;
            for (i = 0; i < h; i++) {
                vector < pair < field * , object * >> x;
                for (j = 0; j < w; j++)
                    x.push_back(make_pair(new field(), new object()));
                b.push_back(x);
            }
            for (auto p: field_io) {
                if ( * p == field()) continue;
                else {
                    j = p -> MIN_RATE * (w - 2) * (h - 2) / 100;
                    k = min(p->MAX_RATE * (w - 2) * (h - 2) / 100, p->ABS_MAX);
                    if ( * p == null()) {
                        hc = random(1, h - 2);
                        wc = random(1, w - 2);
                        b[hc][wc].first = new null();
                        for (i = 0; i < random(j, k) - 1; i++) {
                            do {
                                hc = random(1, h - 2);
                                wc = random(1, w - 2);
                            }while (*b[hc][wc].first == null() ||
                                    (*b[hc + 1][wc].first == field() &&
                                    *b[hc - 1][wc].first == field() &&
                                    *b[hc][wc + 1].first == field() &&
                                    *b[hc][wc - 1].first == field()));
                            b[hc][wc].first = new null();
                        }

                    }else for
                        (i=0; i<((keyy && *p == chest())?1:random(j, k)); i++){
                            do {
                                hc = random(1, h - 2);
                                wc = random(1, w - 2);
                            } while ( * b[hc][wc].first != null());
                            b[hc][wc].first = p;
                            if ( * b[hc][wc].first == key()) keyy = true;
                        }

                }

            }
            for (auto q: object_io) {
                j = q -> MIN_RATE * (w - 2) * (h - 2) / 100;
                k = min(q -> MAX_RATE * (w - 2) * (h - 2) / 100, q -> ABS_MAX);
                for (i = 0; i < random(j, k); i++) {
                    do {
                        hc = random(1, h - 2);
                        wc = random(1, w - 2);
                    } while (!(b[hc][wc].first -> can_hold()) ||
                              *b[hc][wc].second != object() ||
                              ( *q == guard() &&
                                *b[hc][wc].first == spikes_const()));
                    b[hc][wc].second = q;
                }
            }
            do {
                do {
                    hc = random(1, h - 2);
                    wc = random(1, w - 2);
                } while ( * b[hc][wc].first != null() ||
                          * b[hc][wc].second != object());
                tposw = wc;
                tposh = hc;

                b[dposh][dposw].first = new null();
                do {
                    hc = random(1, h - 2);
                    wc = random(1, w - 2);
                } while ( * b[hc][wc].first != null() ||
                          * b[hc][wc].second != object() ||
                          abs((int)(hc - tposh)) <= 1 ||
                          abs((int)(wc - tposw)) <= 1);
                dposw = wc;
                dposh = hc;
                b[hc][wc].first = new field();
            } while (!this -> solvable());
            b[0][0].first = new field();
        }

    /// pushing a movable object by the player
    void object_move(int i, int j, char dir) {
        pair < int, int > destination;
        if (dir == 'w' || dir == 'W') destination = make_pair(i - 1, j);
        else if (dir == 'a' || dir == 'A') destination = make_pair(i, j - 1);
        else if (dir == 's' || dir == 'S') destination = make_pair(i + 1, j);
        else if (dir == 'd' || dir == 'D') destination = make_pair(i, j + 1);
        else destination = make_pair(i, j);
        if (b[destination.first][destination.second].first -> can_hold() &&
             * b[destination.first][destination.second].second == object()) {
            b[destination.first][destination.second].second = b[i][j].second;
            b[i][j].second = new object();
        } else if ((bool) * b[i][j].second) b[i][j].second = new object();
    }

    /// moving the player, direction determined by the symbol input
    void taker_move(char dir) {
        pair < int, int > destination;
        if (dir == 'w' || dir == 'W') destination = make_pair(tposh-1, tposw);
        else if (dir=='a' || dir=='A') destination=make_pair(tposh, tposw-1);
        else if (dir=='s' || dir=='S') destination=make_pair(tposh+1, tposw);
        else if (dir=='d' || dir=='D') destination=make_pair(tposh, tposw+1);
        else destination = make_pair(tposh, tposw);

        if (b[destination.first][destination.second].first -> can_hold() &&
            * b[destination.first][destination.second].second == object()) {
            tposh = destination.first;
            tposw = destination.second;
        } else if (*b[destination.first][destination.second].second!=object()){
            this -> object_move(destination.first, destination.second, dir);
        }
    }

    /*!
    * updating the board + moving the player + checking for field and\n
    * object interaction
    */
    board move(char dir) {
        board that( * this);
        that.move_update();
        that.taker_move(dir);
        that.b[that.tposh][that.tposw].first -> entry_action(that.t);
        that.b[that.tposh + 1][that.tposw].first -> adjacent_action(that.t);
        that.b[that.tposh - 1][that.tposw].first -> adjacent_action(that.t);
        that.b[that.tposh][that.tposw + 1].first -> adjacent_action(that.t);
        that.b[that.tposh][that.tposw - 1].first -> adjacent_action(that.t);
        return that;
    }

    ///printing the current board after each input
    void singlestep(char dir) {
        * this = this -> move(dir);
        this -> print();
        this -> score();
    }

    /// taking input and reading out each symbol to do each move
    void steps(string dirs) {
        for (char c: dirs) {
            if (t.moves <= 0) break;
            else if ((tposh == dposh && abs((int)(tposw - dposw)) <= 1) ||
                      (tposw == dposw && abs((int)(tposh - dposh)) <= 1)) break;

            if (c == 'w' ||
                 c == 'W' ||
                  c == 'a' ||
                   c == 'A' ||
                    c == 's' ||
                     c == 'S' ||
                      c == 'd' ||
                       c == 'D') this -> singlestep(c);

            else if (c == 'e' || c == 'E') exit(0);
            else if (c == 'r' || c == 'R') t.moves = 0;
            else continue;
        }
    }

    /// printing the board
    void print() {
        cout << endl;
        unsigned int i, j;
        for (i = 0; i < h; i++) {
            for (j = 0; j < w; j++) cout << this -> to_print(i, j);
            cout << endl;
        }
    }

    /// printing the number of moves left
    void score() {
        cout << "+--+" << endl << "|" << t.moves;
        if (t.moves < 10) cout << ' ';
        cout << "|" << endl << "+--+" << endl;
    }

    /// board comparison
    friend bool operator == (const board & e,
        const board & f) {
        for (unsigned int i = 1; i < e.h - 1; i++)
            for (unsigned int j = 1; j < e.w - 1; j++)
                if ( * e.b[i][j].second != * f.b[i][j].second) return false;

        return (e.tposh == f.tposh &&
            e.tposw == f.tposw &&
            (bool) e.t == (bool) f.t);
    }

    friend bool operator != (const board & e,
        const board & f) {
        return !(e == f);
    }

    /// did the player win?
    bool won() {
        return (
                ((tposh == dposh && abs((int)(tposw - dposw)) <= 1) ||
                 (tposw == dposw && abs((int)(tposh - dposh)) <= 1)) &&
                 t.moves >= 0) ? 1 : 0;
    }

    /// taking input until the game is over
    int single_try() {
        string s;
        while ((tposh != dposh || abs((int)(tposw - dposw)) > 1) &&
               (tposw!=dposw || abs((int)(tposh - dposh))>1) && t.moves > 0) {
            cin >> s;
            if (s == "skip" || s == "SKIP") return 2;
            this -> steps(s);
        };
        return this -> won();
    }

    /// number of moves left
    explicit operator int() const {
        return t.moves;
    }

    /// changing the amount of moves currently left (used for game generation)
    void assign_moves(unsigned short m) {
        this -> t.moves = m;
    }

    /*!
    * the board, but only with taker, demoness, walls, empty spaces and rocks\n
    * that can no longer be moved (one recursive step of generation)
    */
    board unmovable_ss() {
        board res( * this);
        for (int i = 1; i < h - 1; i++)
            for (int j = 1; j < w - 1; j++) {
                if (b[i][j].first->can_hold()) res.b[i][j].first = new null();
                else res.b[i][j].first = new field();
                if ((bool)( * b[i][j].second)) res.b[i][j].second=new object();
                else if ( * b[i][j].second != object() &&
                    (!(b[i][j + 1].first -> can_hold()) ||
                      !((bool)( * b[i][j + 1].second)) ||
                      !(b[i][j - 1].first -> can_hold()) ||
                      !((bool)( * b[i][j - 1].second))) &&
                    (!(b[i + 1][j].first -> can_hold()) ||
                      !((bool)( * b[i + 1][j].second)) ||
                      !(b[i - 1][j].first -> can_hold()) ||
                      !((bool)( * b[i - 1][j].second)))) res.b[i][j] = {
                    new field(),
                    new object()
                };
            }
        return res;
    }

    /*!
    * the board, but only with taker, demoness, walls, empty spaces and rocks\n
    * that can no longer be moved (unmovable_ss repeated until no change is made)
    */
    board unmovable() {
        board res( * this);
        while (res != res.unmovable_ss()) res = res.unmovable_ss();
        return res;
    }

    /// is the puzzle solvable? (one recursive step of calculation)
    bool solvable_ss(vector < pair < unsigned int, unsigned int >> & cov) {
        bool r = false;
        for (auto i: cov) {
            if ( * this -> b[i.first + 1][i.second].first == null() &&
                find(cov.begin(),
                     cov.end(),
                     make_pair(i.first + 1, i.second))==cov.end()){
                cov.emplace_back(i.first + 1, i.second);
                r = true;
            }
            if ( * this -> b[i.first - 1][i.second].first == null() &&
                find(cov.begin(),
                      cov.end(),
                     make_pair(i.first - 1, i.second))==cov.end()){
                cov.emplace_back(i.first - 1, i.second);
                r = true;
            }
            if ( * this -> b[i.first][i.second + 1].first == null() &&
                find(cov.begin(),
                     cov.end(),
                     make_pair(i.first, i.second + 1))==cov.end()){
                cov.emplace_back(i.first, i.second + 1);
                r = true;
            }
            if ( * this -> b[i.first][i.second - 1].first == null() &&
                find(cov.begin(),
                     cov.end(),
                     make_pair(i.first, i.second - 1))==cov.end()){
                cov.emplace_back(i.first, i.second - 1);
                r = true;
            }
        }
        return r;
    }

    /// is the puzzle solvable?
    bool solvable() {
        board g = this -> unmovable();
        vector < pair < unsigned int, unsigned int >> cov = {
            make_pair(g.tposh, g.tposw)
        };
        while (g.solvable_ss(cov))
            for (auto i: cov) {
                if ((abs((int)(i.first - g.dposh)) == 1 &&
                      i.second == g.dposw) ||
                     (abs((int)(i.second - g.dposw)) == 1 &&
                       i.first == g.dposh)) return true;
            }
        return false;
    }

};



#endif // BOARD_H_INCLUDED
