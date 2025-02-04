// yorps.cpp

// Portions you are to complete are marked with a TODO: comment.
// We've provided some incorrect return statements (so indicated) just
// to allow this skeleton program to compile and run, albeit incorrectly.
// The first thing you probably want to do is implement the utterly trivial
// functions (marked TRIVIAL).  Then get Arena::display going.  That gives
// you more flexibility in the order that you choose to tackle the rest of
// the functionality.  As you finish implementing each TODO: item, remove
// its TODO: comment; that makes it easier to find what you have left to do.

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>
#include <cassert>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;            // max number of rows in the arena
const int MAXCOLS = 20;            // max number of columns in the arena
const int MAXYORPS = 100;          // max number of yorps allowed
const int MAXCOLORS = 3;           // max number of colors
const double WALL_DENSITY = 0.14;  // density of walls

const int NORTH = 0;
const int EAST  = 1;
const int SOUTH = 2;
const int WEST  = 3;
const int NUMDIRS = 4;

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class Arena;  // This is needed to let the compiler know that Arena is a
// type name, since it's mentioned in the Yorp declaration.

class Yorp
{
public:
    // Constructor
    Yorp(Arena* ap, int r, int c, char color);
    
    // Accessors
    int  row() const;
    int  col() const;
    char color() const;
    bool isDead() const;
    
    // Mutators
    void forceMove(int dir);
    void move();
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    char   m_color;
    int    m_health;
};

class Player
{
public:
    // Constructor
    Player(Arena* ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;
    
    // Mutators
    string stand();
    string move(int dir);
    void   setDead();
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    bool   m_dead;
};

class Arena
{
public:
    // Constructor/destructor
    Arena(int nRows, int nCols);
    ~Arena();
    
    // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     yorpCount() const;
    bool    hasWallAt(int r, int c) const;
    int     numberOfYorpsAt(int r, int c) const;
    void    display(string msg) const;
    
    // Mutators
    void   placeWallAt(int r, int c);
    bool   addYorp(int r, int c, char color);
    bool   addPlayer(int r, int c);
    string moveYorps(char color, int dir);
    
private:
    bool    m_wallGrid[MAXROWS][MAXCOLS];
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Yorp*   m_yorps[MAXYORPS];
    int     m_nYorps;
    
    // Helper functions
    void checkPos(int r, int c, string functionName) const;
};

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nYorps);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Arena* m_arena;
    
    // Helper functions
    string takePlayerTurn();
    string takeYorpsTurn();
};

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char ch);
int randInt(int lowest, int highest);
bool attemptMove(const Arena& a, int dir, int& r, int& c);
int yorpsAround(const Arena& a, int r, int c);
bool recommendMove(const Arena& a, int r, int c, int& bestDir);
void clearScreen();

///////////////////////////////////////////////////////////////////////////
//  Yorp implementation
///////////////////////////////////////////////////////////////////////////

Yorp::Yorp(Arena* ap, int r, int c, char color)
{
    if (ap == nullptr)
    {
        cout << "***** A yorp must be created in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "***** Yorp created with invalid coordinates (" << r << ","
        << c << ")!" << endl;
        exit(1);
    }
    if (color != 'R'  &&  color != 'Y'  &&  color != 'B')
    {
        cout << "***** Yorp created with invalid color " << color << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_color = color;
    m_health = 3;
}

int Yorp::row() const
{
    return m_row;
}

int Yorp::col() const
{
    return m_col;
}

char Yorp::color() const
{
    return m_color;
}

bool Yorp::isDead() const
{
    if (m_health == 0)
        return true;
    else
        return false;
}

void Yorp::forceMove(int dir)
{
    if (attemptMove(*m_arena, dir, m_row, m_col))
        return;
    else
        m_health--;
}

void Yorp::move()
{
    // Attempt to move in a random direction; if can't move, don't move
    if (!isDead())
        attemptMove(*m_arena, randInt(0, NUMDIRS-1), m_row, m_col);
}

///////////////////////////////////////////////////////////////////////////
//  Player implementation
///////////////////////////////////////////////////////////////////////////

Player::Player(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** The player must be created in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
        << "," << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_dead = false;
}

int Player::row() const
{
    return m_row;
}

int Player::col() const
{
    return m_col;
}

string Player::stand()
{
    return "Player stands.";
}

string Player::move(int dir)
{
    // DONE:  Attempt to move the player one step in the indicated
    //        direction.  If this fails,
    //        return "Player couldn't move; player stands."
    //        A player who moves onto a yorp dies, and this
    //        returns "Player walked into a yorp and died."
    //        Otherwise, return one of "Player moved north.",
    //        "Player moved east.", "Player moved south.", or
    //        "Player moved west."
    

    switch (dir) {
        case NORTH:
            if (attemptMove(*m_arena, dir, m_row, m_col))
            {
                if (m_arena->numberOfYorpsAt(m_row, m_col) > 0)
                {
                    m_dead = true;
                    return "Player walked into a yorp and died.";
                }

                return "Player moved north.";
            }
                        else
                 return "Player couldn't move; player stands.";
            break;
        case EAST:
            if (attemptMove(*m_arena, dir, m_row, m_col))
            {
                if (m_arena->numberOfYorpsAt(m_row, m_col) > 0)
                {
                    m_dead = true;
                    return "Player walked into a yorp and died.";
                }
                return "Player moved east.";
            }
            
            else
                return "Player couldn't move; player stands.";
            break;
        case SOUTH:
            if (attemptMove(*m_arena, dir, m_row, m_col))
            {
                if (m_arena->numberOfYorpsAt(m_row, m_col) > 0)
                {
                    m_dead = true;
                    return "Player walked into a yorp and died.";
                }
                return "Player moved south.";
            }

            else
                return "Player couldn't move; player stands.";
            break;
        case WEST:
            if (attemptMove(*m_arena, dir, m_row, m_col))
            {
                if ((m_arena->numberOfYorpsAt(m_row, m_col)) > 0)
                {
                    m_dead = true;
                    return "Player walked into a yorp and died.";
                }
                return "Player moved west.";
            }
            
            else
                return "Player couldn't move; player stands.";
        default:
            break;
    }
    return "Player couldn't move; player stands.";
}

bool Player::isDead() const
{
    return m_dead;
}

void Player::setDead()
{
    m_dead = true;
}

///////////////////////////////////////////////////////////////////////////
//  Arena implementation
///////////////////////////////////////////////////////////////////////////

Arena::Arena(int nRows, int nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Arena created with invalid size " << nRows << " by "
        << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nYorps = 0;
    for (int r = 1; r <= m_rows; r++)
        for (int c = 1; c <= m_cols; c++)
            m_wallGrid[r-1][c-1] = false;
}

Arena::~Arena()
{
    for (int i = 0; i < m_nYorps; i++)
    {
        delete m_yorps[i];
    }
    delete m_player;
}

int Arena::rows() const
{
    return m_rows;
}

int Arena::cols() const
{
    return m_cols;
}

Player* Arena::player() const
{
    return m_player;
}

int Arena::yorpCount() const
{
    return m_nYorps;
}

bool Arena::hasWallAt(int r, int c) const
{
    checkPos(r, c, "Arena::hasWallAt");
    return m_wallGrid[r-1][c-1];
}

int Arena::numberOfYorpsAt(int r, int c) const
{
    int count = 0;
    for (int i = 0; i < m_nYorps; i++)
    {
        if (m_yorps[i]->row() == r && m_yorps[i]->col() == c)
                count++;
    }
    return count;
}

void Arena::display(string msg) const
{
    char displayGrid[MAXROWS][MAXCOLS];
    int r, c;
    
    // Fill displayGrid with dots (empty) and stars (wall)
    for (r = 1; r <= rows(); r++)
        for (c = 1; c <= cols(); c++)
            displayGrid[r-1][c-1] = (hasWallAt(r, c) ? '*' : '.');
    
    // Indicate yorp positions by their colors.  If more than one yorp
    // occupies a cell, show just one (any one will do).
    
    // DONE:  For each yorp, set the grid cell to that yorp's color character.
   for (int i = 0; i < m_nYorps; i++)
   {
       displayGrid[m_yorps[i]->row()-1][m_yorps[i]->col()-1] = m_yorps[i]->color();
   }
    
    
    // Indicate player's position
    if (m_player != nullptr)
        displayGrid[m_player->row()-1][m_player->col()-1] = (m_player->isDead() ? 'X' : '@');
    
    // Draw the grid
    clearScreen();
    for (r = 1; r <= rows(); r++)
    {
        for (c = 1; c <= cols(); c++)
            cout << displayGrid[r-1][c-1];
        cout << endl;
    }
    cout << endl;
    
    // Write message, yorp, and player info
    if (msg != "")
        cout << msg << endl;
    cout << "There are " << yorpCount() << " yorps remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player!" << endl;
    else if (m_player->isDead())
        cout << "The player is dead." << endl;
}

void Arena::placeWallAt(int r, int c)
{
    checkPos(r, c, "Arena::placeWallAt");
    m_wallGrid[r-1][c-1] = true;
}

bool Arena::addYorp(int r, int c, char color)
{
    if (hasWallAt(r, c))
        return false;
    if (m_player != nullptr  &&  m_player->row() == r  &&  m_player->col() == c)
        return false;
    if (color != 'R'  &&  color != 'Y'  &&  color != 'B')
        return false;
    if (m_nYorps == MAXYORPS)
        return false;
    m_yorps[m_nYorps] = new Yorp(this, r, c, color);
    m_nYorps++;
    return true;
}

bool Arena::addPlayer(int r, int c)
{
    if (m_player != nullptr  ||  hasWallAt(r, c))
        return false;
    if (numberOfYorpsAt(r, c) > 0)
        return false;
    m_player = new Player(this, r, c);
    return true;
}

string Arena::moveYorps(char color, int dir)
{
    // Yorps of the indicated color will follow that color with probability 1/2
    bool willFollow = (randInt(0, 1) == 0);
    int i;
    // Move all yorps
    int nYorpsOriginally = m_nYorps;
    
    // DONE:  Move each yorp.  Force yorps of the indicated color to move
    //        in the indicated direction if willFollow is true.  If
    //        willFollow is false, or if the yorp is of a different color,
    //        it just moves.  Mark the player as dead necessary.  Release
    //        any dead dynamically allocated yorps.
    
   for (i = 0; i < m_nYorps; i++)
    {
        if (willFollow == true && m_yorps[i]->color() == color)
            m_yorps[i]->forceMove(dir);
        
        else
            m_yorps[i]->move();

        if (m_player != nullptr && m_player->row() ==  m_yorps[i]->row() && m_player->col() ==  m_yorps[i]->col())
            m_player->setDead();
        
        if (m_yorps[i]->isDead())
        {
            delete m_yorps[i];
            m_yorps[i] = m_yorps[m_nYorps-1];
            m_nYorps--;
        }
    }
    
    if (m_nYorps < nYorpsOriginally)
        return "Some yorps have been destroyed.";
    else
        return "No yorps were destroyed.";
}

void Arena::checkPos(int r, int c, string functionName) const
{
    if (r < 1  ||  r > m_rows  ||  c < 1  || c > m_cols)
    {
        cout << "***** " << "Invalid arena position (" << r << ","
        << c << ") in call to " << functionName << endl;
        exit(1);
    }
}

///////////////////////////////////////////////////////////////////////////
//  Game implementation
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nYorps)
{
    if (nYorps < 0  ||  nYorps > MAXYORPS)
    {
        cout << "***** Game created with invalid number of yorps:  "
        << nYorps << endl;
        exit(1);
    }
    int nEmpty = rows * cols - nYorps - 1;  // 1 for Player
    if (nEmpty < 0)
    {
        cout << "***** Game created with a " << rows << " by "
        << cols << " arena, which is too small too hold a player and "
        << nYorps << " yorps!" << endl;
        exit(1);
    }
    
    // Create arena
    m_arena = new Arena(rows, cols);
    
    // Add some walls in WALL_DENSITY of the empty spots
    assert(WALL_DENSITY >= 0  &&  WALL_DENSITY <= 1);
    int nWalls = static_cast<int>(WALL_DENSITY * nEmpty);
    while (nWalls > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        if (m_arena->hasWallAt(r, c))
            continue;
        m_arena->placeWallAt(r, c);
        nWalls--;
    }
    
    // Add player
    int rPlayer;
    int cPlayer;
    do
    {
        rPlayer = randInt(1, rows);
        cPlayer = randInt(1, cols);
    } while (m_arena->hasWallAt(rPlayer, cPlayer));
    m_arena->addPlayer(rPlayer, cPlayer);
    
    // Populate with yorps
    while (nYorps > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        if (m_arena->hasWallAt(r, c)  ||  (r == rPlayer && c == cPlayer))
            continue;
        const char colors[MAXCOLORS] = { 'R', 'Y', 'B' };
        m_arena->addYorp(r, c, colors[randInt(1, MAXCOLORS)-1]);
        nYorps--;
    }
}

Game::~Game()
{
    delete m_arena;
}

string Game::takePlayerTurn()
{
    for (;;)
    {
        cout << "Your move (n/e/s/w/x or nothing): ";
        string playerMove;
        getline(cin, playerMove);
        
        Player* player = m_arena->player();
        int dir;
        
        if (playerMove.size() == 0)
        {
            if (recommendMove(*m_arena, player->row(), player->col(), dir))
                return player->move(dir);
            else
                return player->stand();
        }
        else if (playerMove.size() == 1)
        {
            if (tolower(playerMove[0]) == 'x')
                return player->stand();
            else
            {
                dir = decodeDirection(tolower(playerMove[0]));
                if (dir != -1)
                    return player->move(dir);
            }
        }
        cout << "Player move must be nothing, or 1 character n/e/s/w/x." << endl;
    }
}

string Game::takeYorpsTurn()
{
    for (;;)
    {
        cout << "Color thrown and direction (e.g., Rn or bw): ";
        string colorAndDir;
        getline(cin, colorAndDir);
        if (colorAndDir.size() != 2)
        {
            cout << "You must specify a color followed by a direction." << endl;
            continue;
        }
        char color = toupper(colorAndDir[0]);
        if (color != 'R'  &&  color != 'Y'  &&  color != 'B')
        {
            cout << "Color must be upper or lower R, Y, or B." << endl;
            continue;
        }
        int dir = decodeDirection(tolower(colorAndDir[1]));
        if (dir != -1)
            return m_arena->moveYorps(color, dir);
        cout << "Direction must be n, e, s, or w." << endl;
    }
}

void Game::play()
{
    m_arena->display("");
    Player* player = m_arena->player();
    if (player == nullptr)
        return;
    while ( ! player->isDead()  &&  m_arena->yorpCount() > 0)
    {
        string msg = takePlayerTurn();
        m_arena->display(msg);
        if (player->isDead())
            break;
        msg = takeYorpsTurn();
        m_arena->display(msg);
    }
    if (player->isDead())
        cout << "You lose." << endl;
    else
        cout << "You win." << endl;
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir)
{
    switch (dir)
    {
        case 'n':  return NORTH;
        case 'e':  return EAST;
        case 's':  return SOUTH;
        case 'w':  return WEST;
    }
    return -1;  // bad argument passed in!
}

// Return a random int from min to max, inclusive
int randInt(int min, int max)
{
    if (max < min)
        swap(max, min);
    static random_device rd;
    static default_random_engine generator(rd());
    uniform_int_distribution<> distro(min, max);
    return distro(generator);
}

// Return false without changing anything if moving one step from (r,c)
// in the indicated direction would hit a wall or run off the edge of the
// arena.  Otherwise, update r and c to the position resulting from the
// move and return true.
bool attemptMove(const Arena& a, int dir, int& r, int& c)
{
    // DONE:  Implement this function.
    // Delete the following line and replace it with the correct code.
    if (dir == NORTH)
    {
        if (r == 1 || a.hasWallAt(r-1, c) == true)
            return false;
        else
            r--;
    }
    else if (dir == EAST)
    {
        if (c == a.cols() || a.hasWallAt(r, c+1) == true)
            return false;
        else
            c++;
    }
    else if (dir == SOUTH)
    {
        if (r == a.rows() || a.hasWallAt(r+1, c) == true)
            return false;
        else
            r++;
    }
    else if (dir == WEST)
    {
        if (c == 1 || a.hasWallAt(r, c-1) == true)
            return false;
        else
            c--;
    }
    return true;
}

// Recommend a move for a player at (r,c):  A false return means the
// recommendation is that the player should stand; otherwise, bestDir is
// set to the recommended direction to move.
int yorpsAround(const Arena& a, int r, int c)
{
    int count = 0;
    if (a.numberOfYorpsAt(r, c+1) > 0)
        count++;
    if (a.numberOfYorpsAt(r+1, c) > 0)
        count++;
    if (a.numberOfYorpsAt(r, c-1) > 0)
        count++;
    if (a.numberOfYorpsAt(r-1, c) > 0)
        count++;
    
 
 
    return count;
}

bool recommendMove(const Arena& a, int r, int c, int& bestDir)
{
   
    // DONE:  replace this implementation:
    // Delete the following line and replace it with the correct code.
    
    int n = yorpsAround(a, r-1, c);
    if (a.numberOfYorpsAt(r-1, c) > 0)
        n += 4; // do not move if there is a yorp at that position
    int e = yorpsAround(a, r, c+1);
    if (a.numberOfYorpsAt(r, c+1) > 0)
        e += 4;
    int s = yorpsAround(a, r+1, c);
    if (a.numberOfYorpsAt(r+1, c) > 0)
        s += 4;
    int w = yorpsAround(a, r, c-1);
    if (a.numberOfYorpsAt(r, c-1) > 0)
        w += 4;
    
    if (r == 1) // do not attempt to move if at edge
    {
        if (c == 1 || c == a.cols())    // do not attempt to move if at corner
            n += 2;
        else
            n++;
        
    }
    else
    {
        if (a.hasWallAt(r-1, c))    // do not attempt to move if there is a wall at the position
            n++;
    }
    if (r == a.rows())
    {
        if (c == 1 || c == a.cols())
            s += 2;
        else
            s++;
    }
    else
    {
        if (a.hasWallAt(r+1, c))
            s++;
    }
    if (c == 1)
    {
        if (r == 1 || r == a.rows())
            w += 2;
        else
            w++;
        
    }
    else
    {
        if (a.hasWallAt(r, c-1))
            w++;
    }
    if (c == a.cols())
    {
        if (r == 1 || r == a.rows())
            e += 2;
        else
            e++;
    }
    else
    {
        if (a.hasWallAt(r, c+1))
            e++;
    }
    
    int yorpsAt[4] = {n, e, s, w};  // array with number of yorps at positions corresponding to each direction
    
    int min = 3;
    int pos = 0;
    
    if (n > 3 && e > 3 && s > 3 && w > 3)
        return false;
    
    for (int i = 0; i < 4; i++)
    {
        if (yorpsAt[i] <= min)
        {
            min = yorpsAt[i];
            pos = i;    // sets pos to direction with least number of yorps
        }
    }
 
    if (yorpsAround(a, r, c) >  min)
    {
        bestDir = pos;
        return true;
    }
    
    return false;

    
    // Your replacement implementation should do something intelligent.
    // For example, if you're standing next to four zurts, and moving
    // north would put you next to two zurts, but moving east would put
    // you next to none, moving east is a safer choice than standing or
    // moving north.
}

///////////////////////////////////////////////////////////////////////////
// main()
///////////////////////////////////////////////////////////////////////////

void doBasicTests();

int main()
{
//  doBasicTests(); // Remove this line after completing test.
 // return 0;       // Remove this line after completing test.
    // Create a game
    // Use this instead to create a mini-game:
   // Game g(3, 5, 2);
   Game g(10, 12, 50);
    // Play the game
    g.play();
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANY CODE BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++/g31 UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _MSC_VER  //  Microsoft Visual C++

#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                               &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Microsoft Visual C++, so assume UNIX interface

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen()  // will just write a newline in an Xcode output window
{
    static const char* term = getenv("TERM");
    if (term == nullptr  ||  strcmp(term, "dumb") == 0)
        cout << endl;
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif

/* #include <type_traits>
#include <cassert>

#define CHECKTYPE(c, f, r, a)  \
static_assert(std::is_same<decltype(&c::f), r (c::*)a>::value, \
"FAILED: You changed the type of " #c "::" #f);  \
[[gnu::unused]] r (c::* xxx##c##_##f) a = &c::f

void thisFunctionWillNeverBeCalled()
{
    // If the student deleted or changed the interfaces to the public
    // functions, this won't compile.  (This uses magic beyond the scope
    // of CS 31.)
    
    Yorp y(static_cast<Arena*>(0), 1, 1, 'R');
    CHECKTYPE(Yorp, row, int, () const);
    CHECKTYPE(Yorp, col, int, () const);
    CHECKTYPE(Yorp, color, char, () const);
    CHECKTYPE(Yorp, isDead, bool, () const);
    CHECKTYPE(Yorp, forceMove, void, (int));
    CHECKTYPE(Yorp, move, void, ());
    
    Player p(static_cast<Arena*>(0), 1, 1);
    CHECKTYPE(Player, row, int, () const);
    CHECKTYPE(Player, col, int, () const);
    CHECKTYPE(Player, isDead, bool, () const);
    CHECKTYPE(Player, stand, string, ());
    CHECKTYPE(Player, move, string, (int));
    CHECKTYPE(Player, setDead, void, ());
    
    Arena a(1, 1);
    CHECKTYPE(Arena, rows, int, () const);
    CHECKTYPE(Arena, cols, int, () const);
    CHECKTYPE(Arena, player, Player*, () const);
    CHECKTYPE(Arena, yorpCount, int, () const);
    CHECKTYPE(Arena, hasWallAt, bool, (int,int) const);
    CHECKTYPE(Arena, numberOfYorpsAt, int, (int,int) const);
    CHECKTYPE(Arena, display, void, (string) const);
    CHECKTYPE(Arena, placeWallAt, void, (int,int));
    CHECKTYPE(Arena, addYorp, bool, (int,int,char));
    CHECKTYPE(Arena, addPlayer, bool, (int,int));
    CHECKTYPE(Arena, moveYorps, string, (char,int));
    
    Game g(1,1,1);
    CHECKTYPE(Game, play, void, ());
}

void doBasicTests()
{
    {
        Arena a(10, 20);
        a.addPlayer(2, 5);
        Player* pp = a.player();
        assert(pp->row() == 2  &&  pp->col() == 5  && ! pp->isDead());
        assert(pp->move(NORTH) == "Player moved north.");
        assert(pp->row() == 1  &&  pp->col() == 5  && ! pp->isDead());
        assert(pp->move(NORTH) == "Player couldn't move; player stands.");
        assert(pp->row() == 1  &&  pp->col() == 5  && ! pp->isDead());
        pp->setDead();
        assert(pp->row() == 1  &&  pp->col() == 5  && pp->isDead());
    }
    {
        Arena a(10, 20);
        a.placeWallAt(1, 4);
        a.placeWallAt(1, 5);
        a.placeWallAt(3, 4);
        a.placeWallAt(3, 5);
        a.placeWallAt(2, 3);
        a.placeWallAt(2, 6);
        a.addYorp(2, 4, 'R');
        a.addPlayer(7, 7);
        assert(a.yorpCount() == 1  &&  a.numberOfYorpsAt(2, 4) == 1);
        for (int k = 0; k < 100  &&  a.numberOfYorpsAt(2, 4) == 1; k++)
            a.moveYorps('R', EAST);
        assert(a.numberOfYorpsAt(2, 4) == 0 && a.numberOfYorpsAt(2, 5) == 1);
        for (int k = 0; k < 100  &&  a.yorpCount() == 1; k++)
            a.moveYorps('Y', EAST);
        assert(a.yorpCount() == 1);
        assert(a.numberOfYorpsAt(2, 4) == 1 || a.numberOfYorpsAt(2, 5) == 1);
        for (int k = 0; k < 100  &&  a.yorpCount() == 1; k++)
            a.moveYorps('R', EAST);
        assert(a.yorpCount() == 0);
        assert(a.numberOfYorpsAt(2, 4) == 0 && a.numberOfYorpsAt(2, 5) == 0);
        for (int k = 0; k < MAXYORPS/4; k++)
        {
            a.addYorp(6, 7, 'B');
            a.addYorp(8, 7, 'B');
            a.addYorp(7, 6, 'B');
            a.addYorp(7, 8, 'B');
        }
        assert(! a.player()->isDead());
        a.moveYorps('Y', NORTH);
        assert(a.player()->isDead());
    }
    {
        Arena a(1, 3);
        a.addPlayer(1, 1);
        a.placeWallAt(1, 2);
        int k;
        cout << a.yorpCount() << endl;
        for (k = 0; k < MAXYORPS/2; k++)
        {
            assert(a.addYorp(1, 3, 'Y'));
            assert(a.addYorp(1, 3, 'B'));
        }
        for (k = 0; k < 100  &&  a.yorpCount() > MAXYORPS/2; k++)
        {
            a.moveYorps('B', SOUTH);
        }
        assert(k < 100);

        while (a.yorpCount() < MAXYORPS)
            assert(a.addYorp(1, 3, 'R'));
        assert(!a.addYorp(1, 3, 'R'));
        for (k = 0; k < 100  &&  a.yorpCount() > 0; k++)
        {
            a.moveYorps('R', WEST);
            a.moveYorps('Y', WEST);
            a.moveYorps('B', WEST);
        }
        assert(k < 100);
       assert(a.numberOfYorpsAt(1, 3) == 0);
    }
    cout << "Passed all basic tests" << endl;
    exit(0);
} */
