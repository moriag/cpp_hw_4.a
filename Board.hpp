/**
 * Header file for the board of the war game.
 * 
 * You can copy this file to a new file called Board.hpp, and extend it as you like.
 * 
 * @author Oz Levi 
 * @author Erel Segal-Halevi
 * @since  2020-05
 */

#include <string>
#include <vector>
#include <stdexcept>
#include "Soldier.hpp"


namespace WarGame {

class Board {
  private:
    std::vector<std::vector<Soldier*>> board;
    uint size_player1;
    uint size_player2;
  public:
    enum MoveDIR { Up, Down, Right, Left };
    
    Board(uint numRows, uint numCols) : 
      board(numRows, std::vector<Soldier*>(numCols, nullptr)) {}
    ~Board(){}
    Soldier*& operator[](std::pair<int,int> location);
    Soldier* operator[](std::pair<int,int> location) const;
    void move(uint player_number, std::pair<int,int> source, MoveDIR direction);
    bool has_soldiers(uint player_number) const;
    
};

}
