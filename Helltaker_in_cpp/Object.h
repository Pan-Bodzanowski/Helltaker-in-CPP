#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

/// The 'object' class is for the movable objects on the board.
class object: public settings {
    protected:
    bool destroyable;

    public:
    /// constructor for specific values
    object(bool b, unsigned int mn, unsigned int mx, unsigned int amx):
        settings(mn, mx, amx),
    destroyable(b) {}

    /// default constructor for no object
    object(): object(false, 0, 0, 0) {};

    /// object comparison (equal?)
    friend bool operator == (const object & e,
        const object & f) {
        return (e.destroyable == f.destroyable &&
            e.MIN_RATE == f.MIN_RATE &&
            e.MAX_RATE == f.MAX_RATE);
    }

    /// object comparison (not equal?)
    friend bool operator != (const object & e,
        const object & f) {
        return !(e == f);
    }

    /// is it destroyable?
    explicit operator bool() const {
        return destroyable;
    }

    /// object representation
    virtual char rep() {
        return ' ';
    }
};

class rock: public object {
    public: rock(): object(false, 0, 20, UINT_MAX) {};
    char rep() {
        return 'R';
    }
};

class guard: public object {
    public: guard(): object(true, 0, 8, UINT_MAX) {}
    char rep() {
        return 'G';
    }
};



#endif // OBJECT_H_INCLUDED
