#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

#define S_MIN 5
#define S_MAX 9
#define DIFFICULTY 1.9

using namespace std;
/*!
* This code is used to store and manage settings related to game board's size\n
* (S_MIN and S_MAX), it's fields' generation rate (members of class 'settings')\n
* and game's overall difficulty (DIFFICULTY).
*/
class settings {
    public:
    /// minimal rate
    unsigned int MIN_RATE;
    /// maximal rate (%)
    unsigned int MAX_RATE;
    /// absolute maximum (quantity)
    unsigned int ABS_MAX;
    /// default constructor
    settings(unsigned int mn, unsigned int mx, unsigned int amx): MIN_RATE(mn),
    MAX_RATE(mx),
    ABS_MAX(amx) {
        if (MIN_RATE > 100 || MAX_RATE > 100 || MIN_RATE < 0 || MAX_RATE < 0)
            throw invalid_argument("Invalid percentage!");
        if (MIN_RATE > MAX_RATE)
            throw invalid_argument("Minimum greater than maximum!");
    }
};



#endif // SETTINGS_H_INCLUDED
