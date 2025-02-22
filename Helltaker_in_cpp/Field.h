#ifndef FIELD_H_INCLUDED
#define FIELD_H_INCLUDED

/// The 'field' class is for the unmovable objects on the board.

class field: public settings {
    protected: bool transparent;
    bool hurts;

    public:

    /// constructor for specific values
    field(bool t, bool h, unsigned int mn, unsigned int mx, unsigned int amx):
        settings(mn, mx, amx),
    transparent(t),
    hurts(h) {}

    /// default constructor for the walls of the board
    field(): field(false, false, 100, 100, UINT_MAX) {};
    field(const field & f):
        field(f.transparent, f.hurts, f.MIN_RATE, f.MAX_RATE, f.ABS_MAX) {}
    ~field() {}

    /// action that has to be performed when the player is within the field
    virtual void entry_action(taker & t) {}

    /// action that has to be performed when the player is next to the field
    virtual void adjacent_action(taker & t) {}

    /// field comparison (equal?)
    friend bool operator == (const field & e,
        const field & f) {
        return (e.transparent == f.transparent &&
            e.hurts == f.hurts &&
            e.MIN_RATE == f.MIN_RATE &&
            e.MAX_RATE == f.MAX_RATE &&
            e.ABS_MAX == f.ABS_MAX);
    }

    /// object comparison (not equal?)
    friend bool operator != (const field & e,
        const field & f) {
        return !(e == f);
    }

    /// field destruction (setting it to null)
    virtual void destroy() {
        this -> operator = (field(true, false, 60, 70, UINT_MAX));
    }

    /// can it hold an object?
    bool can_hold() {
        return transparent;
    }

    /// field representation by a symbol
    virtual char rep() {
        return '\u2532';
    }
};

class null: public field {
    public: null(): field(true, false, 60, 70, UINT_MAX) {};
    char rep() {
        return ' ';
    }
};

class spikes_const: public field {
    public: spikes_const(): field(true, true, 0, 8, UINT_MAX) {}
    void entry_action(taker & t) {
        t.moves--;
    }
    char rep() {
        return 'S';
    }
};

class spikes_osc: public field {
    public: spikes_osc(bool h): field(true, h, 0, 8, UINT_MAX) {}

    void entry_action(taker & t) {
        if (hurts) t.moves--;
    }
    char rep() {
        return (hurts ? 'S' : 's');
    }
};

class chest: public field {
    public: chest(): field(false, false, 0, 100, 1) {}
    void adjacent_action(taker & t) {
        if (t) this -> destroy();
    }
    char rep() {
        return 'C';
    }
};

class key: public field {
    public: key(): field(true, false, 0, 100, 1) {}
    void entry_action(taker & t) {
        t.obtain_key();
        this -> destroy();
    }
    char rep() {
        return 'K';
    }
};


#endif // FIELD_H_INCLUDED
