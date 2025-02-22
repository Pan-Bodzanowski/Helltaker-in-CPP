#ifndef BOARDTREE_H_INCLUDED
#define BOARDTREE_H_INCLUDED

/*!
* The 'boardtree' class is used to calculate the minimal number of moves needed\n
* to complete a puzzle. It contains a tree, in which the node is the game's\n
* current state and it's branches are game's state after each move.\n
*/
class boardtree {
    board node;
    boardtree * w;
    boardtree * a;
    boardtree * s;
    boardtree * d;

    /// vector of nodes of leaves of the tree (with container)
    void leaves_c(vector < board > & container) {
        if (this -> isempty()) return;

        if (w -> leaf()) container.push_back(w -> node);
        if (a -> leaf()) container.push_back(a -> node);
        if (s -> leaf()) container.push_back(s -> node);
        if (d -> leaf()) container.push_back(d -> node);

        if (w != nullptr) w -> leaves_c(container);
        if (a != nullptr) a -> leaves_c(container);
        if (s != nullptr) s -> leaves_c(container);
        if (d != nullptr) d -> leaves_c(container);
    }

    /// deleting leaves of given value given number of times
    void delleaf_c(board rb, int & c) {
        if (w -> leaf() && w -> node == rb && c > 1) {
            w = nullptr;
            c--;
        } else if (w != nullptr) w -> delleaf_c(rb, c);
        if (a -> leaf() && a -> node == rb && c > 1) {
            a = nullptr;
            c--;
        } else if (a != nullptr) a -> delleaf_c(rb, c);
        if (s -> leaf() && s -> node == rb && c > 1) {
            s = nullptr;
            c--;
        } else if (s != nullptr) s -> delleaf_c(rb, c);
        if (d -> leaf() && d -> node == rb && c > 1) {
            d = nullptr;
            c--;
        } else if (d != nullptr) d -> delleaf_c(rb, c);
    }

    /// extending the tree by all possibilities of the next move
    void expand() {
        if (this -> isempty()) return;
        board pom;
        if (w != nullptr) w -> expand();
        else {
            pom = node.move('w');
            if (pom != node) w = new boardtree(pom);
        }
        if (a != nullptr) a -> expand();
        else {
            pom = node.move('a');
            if (pom != node) a = new boardtree(pom);
        }
        if (s != nullptr) s -> expand();
        else {
            pom = node.move('s');
            if (pom != node) s = new boardtree(pom);
        }
        if (d != nullptr) d -> expand();
        else {
            pom = node.move('d');
            if (pom != node) d = new boardtree(pom);
        }
    }

    /// how many times does the given board appear in the tree?
    int rep(board sb) {
        int cou = 0;
        if (!(this -> isempty()) && node == sb) cou++;
        if (!(w -> isempty())) cou += w -> rep(sb);
        if (!(a -> isempty())) cou += a -> rep(sb);
        if (!(s -> isempty())) cou += s -> rep(sb);
        if (!(d -> isempty())) cou += d -> rep(sb);
        return cou;
    }

    public:

    /// copying constructor
    boardtree
    (board b, boardtree* x1, boardtree* x2, boardtree* x3, boardtree* x4):
            node(b), w(x1), a(x2), s(x3), d(x4) {}

    /// constructor for a given board
    boardtree(board b): boardtree(b, nullptr, nullptr, nullptr, nullptr) {}

    /// is the node empty?
    bool isempty() {
        return & node == nullptr;
    }

    /// is the node a leaf?
    bool leaf() {
        return (!(this -> isempty()) &&
                 w == nullptr &&
                  a == nullptr &&
                   s == nullptr &&
                    d == nullptr);
    }

    /// deleting leaves of given value until there's only one left
    void delleaf(board rb) {
        int c = this -> rep(rb);
        this -> delleaf_c(rb, c);
    }

    /// vector of nodes of leaves of the tree (empty container as default)
    vector < board > leaves() {
        vector < board > cont;
        this -> leaves_c(cont);
        return cont;
    }

    /// expand the tree and remove all the board repetitions
    void expand_and_del() {
        this -> expand();
        for (auto bo: this -> leaves())
            if (this -> rep(bo) > 1) this -> delleaf(bo);
    }

    /// minimal number of moves needed to complete a level
    int move_minimum() {
        if (this -> isempty()) return 100;
        if (node.won()) return 99 - ((int) node);
        return min(
                   min(w -> move_minimum(), a -> move_minimum()),
                   min(s -> move_minimum(), d -> move_minimum()));
    }

};


#endif // BOARDTREE_H_INCLUDED
