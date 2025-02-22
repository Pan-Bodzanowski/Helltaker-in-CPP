#ifndef TAKER_H_INCLUDED
#define TAKER_H_INCLUDED
using namespace std;

/// The 'taker' class implements the player and it's properties e.g. amount of moves left and ownership of the key.
class taker {
    bool has_key;

    public:
    /*!
    * this member has to be public, since it has to be accessible by\n
    * other, non-derived classes
    */
    short moves;
    taker(short m):
        has_key(false),
        moves(m) {}

    /// the player obtains a key
    void obtain_key() {
        has_key = true;
    }

    /// does the player have key?
    explicit operator bool() const {
        return has_key;
    }

};



#endif // TAKER_H_INCLUDED
