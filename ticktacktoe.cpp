
#include "ticktacktoe.hpp"
#include "util.hpp"

#include <codecvt>
#include <locale>

#define LOOP_FIELD for(int i=0; i<9; i++)

const std::wstring HORIZONTAL =  L"━";
const std::wstring VERTICAL =  L"┃";
const std::wstring VERTICAL_RIGHT =  L"┣";
const std::wstring VERTICAL_LEFT =  L"┫";
const std::wstring HORIZONTAL_DOWN =  L"┳";
const std::wstring HORIZONTAL_UP =  L"┻";
const std::wstring CORNER_M =  L"╋";
const std::wstring CORNER_LT =  L"┏";
const std::wstring CORNER_LB =  L"┗";
const std::wstring CORNER_RT =  L"┓";
const std::wstring CORNER_RB =  L"┛";

std::string wide_to_utf8(const std::wstring& wstr) {
    std::string utf8str;
    for (wchar_t wc : wstr) {
        if (wc <= 0x7F) {
            utf8str.push_back(static_cast<char>(wc));
        } else if (wc <= 0x7FF) {
            utf8str.push_back(static_cast<char>(0xC0 | ((wc >> 6) & 0x1F)));
            utf8str.push_back(static_cast<char>(0x80 | (wc & 0x3F)));
        } else if (wc <= 0xFFFF) {
            utf8str.push_back(static_cast<char>(0xE0 | ((wc >> 12) & 0x0F)));
            utf8str.push_back(static_cast<char>(0x80 | ((wc >> 6) & 0x3F)));
            utf8str.push_back(static_cast<char>(0x80 | (wc & 0x3F)));
        } else if (wc <= 0x10FFFF) {
            utf8str.push_back(static_cast<char>(0xF0 | ((wc >> 18) & 0x07)));
            utf8str.push_back(static_cast<char>(0x80 | ((wc >> 12) & 0x3F)));
            utf8str.push_back(static_cast<char>(0x80 | ((wc >> 6) & 0x3F)));
            utf8str.push_back(static_cast<char>(0x80 | (wc & 0x3F)));
        } else {
            throw std::runtime_error("Invalid Unicode character");
        }
    }
    return utf8str;
}

Game::Game()
{
    LOOP_FIELD
        field[i] = NEUTRAL;

    possibleMoves = {0, 1, 2, 3 ,4, 5 ,6, 7, 8};

    history = std::vector<int>();
}

const std::vector<int> &Game::getMoves()
{
    return possibleMoves;
}

STATUS Game::getStatus()
{
    constexpr int winnerMasks[] = {
        0b111000000,
        0b000111000,
        0b000000111,
        0b100100100,
        0b010010010,
        0b001001001,
        0b100010001,
        0b001010100
    };

    int crossMask = 0;
    int circleMask = 0;

    LOOP_FIELD
    {
        if(field[i] == CROSS)
            crossMask |= 1;
        else if(field[i] == CIRCLE)
            circleMask |= 1;

        if(i < 8)
        {
            crossMask <<= 1;
            circleMask <<= 1;
        }
    }

    for(int i=0; i<8; i++)
        if(winnerMasks[i] == (winnerMasks[i] & crossMask))
            return CROSS;
        else if(winnerMasks[i] == (winnerMasks[i] & circleMask))
            return CIRCLE;
    
    return NEUTRAL;
}

STATUS Game::getTurn()
{
    return (history.size() % 2 == 0) ? CROSS : CIRCLE;
}

void Game::makeMove(int m)
{
    auto it = std::find(possibleMoves.begin(), possibleMoves.end(), m);
    possibleMoves.erase(it);

    field[m] = getTurn();

    history.push_back(m);
}

void Game::undoMove()
{
    int m = history.back();
    history.pop_back();

    field[m] = NEUTRAL;

    possibleMoves.push_back(m);
}

std::ostream &operator<<(std::ostream &os, STATUS s)
{
    switch (s)
    {
    case CROSS:
        os << 'x';
        break;
    case CIRCLE:
        os << 'o';
        break;
    default:
        os << ' ';
        break;
    }

    return os;
}

std::ostream &operator<<(std::ostream &os, Game &g)
{
    os << wide_to_utf8(CORNER_LT) << wide_to_utf8(HORIZONTAL) << wide_to_utf8(HORIZONTAL_DOWN) << wide_to_utf8(HORIZONTAL) << wide_to_utf8(HORIZONTAL_DOWN) << wide_to_utf8(HORIZONTAL) << wide_to_utf8(CORNER_RT) << std::endl;
    
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            os << wide_to_utf8(VERTICAL);

            if(g.field[3*i+j] != NEUTRAL)
                os << (STATUS) g.field[3*i + j];
            else
                os << MAGENTA << (3*i + j) << RESET_COLOR;
        }
        
        os << wide_to_utf8(VERTICAL) << std::endl;

        if(i < 2)
            os << wide_to_utf8(VERTICAL_RIGHT) << wide_to_utf8(HORIZONTAL) << wide_to_utf8(CORNER_M) << wide_to_utf8(HORIZONTAL) << wide_to_utf8(CORNER_M) << wide_to_utf8(HORIZONTAL) << wide_to_utf8(VERTICAL_LEFT) << std::endl;
    }

    os << wide_to_utf8(CORNER_LB) << wide_to_utf8(HORIZONTAL) << wide_to_utf8(HORIZONTAL_UP) << wide_to_utf8(HORIZONTAL) << wide_to_utf8(HORIZONTAL_UP) << wide_to_utf8(HORIZONTAL) << wide_to_utf8(CORNER_RB);

    return os;
}
