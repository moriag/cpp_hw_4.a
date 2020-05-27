#include "Board.hpp"
#include "FootSoldier.hpp"
#include "FootCommander.hpp"
#include "Paramedic.hpp"
#include "Sniper.hpp"
#include "SniperCommander.hpp"
#include "ParamedicCommander.hpp"
#include "doctest.h"
#include <iostream>

using namespace WarGame;
Board board{2,2};
TEST_CASE("moves"){
    SUBCASE("init"){
        CHECK_NOTHROW((board[{0,1}] = new FootSoldier(1)));
        CHECK_NOTHROW((board[{0,0}] = new FootSoldier(2)));
    }
    
    SUBCASE("move soldier and throw for wrong player"){
    
        CHECK_THROWS((board.move(2, {0,1}, Board::MoveDIR::Up)));
        CHECK_NOTHROW((board.move(1, {0,1}, Board::MoveDIR::Up)));//11r
    
        CHECK_THROWS((board.move(1, {0,0}, Board::MoveDIR::Right)));
        CHECK_NOTHROW((board.move(2, {0,0}, Board::MoveDIR::Right)));//01l

        CHECK_THROWS((board.move(2, {1,1}, Board::MoveDIR::Left)));
        CHECK_NOTHROW((board.move(1, {1,1}, Board::MoveDIR::Left)));//10r
        
        CHECK_THROWS((board.move(1, {0,1}, Board::MoveDIR::Up)));
        CHECK_NOTHROW((board.move(2, {0,1}, Board::MoveDIR::Up)));//11l
    
        CHECK_THROWS((board.move(2, {1,0}, Board::MoveDIR::Down)));
        CHECK_NOTHROW((board.move(1, {1,0}, Board::MoveDIR::Down)));//00r

        CHECK_THROWS((board.move(1, {1,1}, Board::MoveDIR::Left)));
        CHECK_NOTHROW((board.move(2, {1,1}, Board::MoveDIR::Left)));//10l

        CHECK_THROWS((board.move(2, {0,0}, Board::MoveDIR::Right)));
        CHECK_NOTHROW((board.move(1, {0,0}, Board::MoveDIR::Right)));//01r
    
        CHECK_THROWS((board.move(1, {1,0}, Board::MoveDIR::Down)));
        CHECK_NOTHROW((board.move(2, {1,0}, Board::MoveDIR::Down)));//00l
    }
    
    SUBCASE("throw for empty place"){
        CHECK_THROWS((board.move(1, {1,0}, Board::MoveDIR::Up)));
        CHECK_THROWS((board.move(2, {1,0}, Board::MoveDIR::Up)));
        CHECK_THROWS((board.move(1, {1,0}, Board::MoveDIR::Down)));
        CHECK_THROWS((board.move(2, {1,0}, Board::MoveDIR::Down)));
        CHECK_THROWS((board.move(1, {1,0}, Board::MoveDIR::Left)));
        CHECK_THROWS((board.move(2, {1,0}, Board::MoveDIR::Left)));
        CHECK_THROWS((board.move(1, {1,0}, Board::MoveDIR::Right)));
        CHECK_THROWS((board.move(2, {1,0}, Board::MoveDIR::Right)));
    
        CHECK_THROWS((board.move(1, {1,1}, Board::MoveDIR::Up)));
        CHECK_THROWS((board.move(2, {1,1}, Board::MoveDIR::Up)));
        CHECK_THROWS((board.move(1, {1,1}, Board::MoveDIR::Down)));
        CHECK_THROWS((board.move(2, {1,1}, Board::MoveDIR::Down)));
        CHECK_THROWS((board.move(1, {1,1}, Board::MoveDIR::Left)));
        CHECK_THROWS((board.move(2, {1,1}, Board::MoveDIR::Left)));
        CHECK_THROWS((board.move(1, {1,1}, Board::MoveDIR::Right)));
        CHECK_THROWS((board.move(2, {1,1}, Board::MoveDIR::Right)));
    }
}
TEST_CASE("FootSoldier life, damege, remove when dead"){
    CHECK(board.has_soldiers(1));
    CHECK(board.has_soldiers(2));
    
    CHECK_NOTHROW(board.move(1, {0,1}, Board::MoveDIR::Up));
    
    CHECK_FALSE(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));
}

TEST_CASE("sniper"){
    Board board{2,2};
    CHECK_NOTHROW((board[{1,1}] = new Sniper(1)));
    CHECK_NOTHROW((board[{0,0}] = new Sniper(2)));
    
    CHECK_NOTHROW((board.move(1, {1,1}, Board::MoveDIR::Left)));
    CHECK_THROWS((board.move(2, {0,0}, Board::MoveDIR::Right)));
    
    CHECK(board.has_soldiers(1));
    CHECK(board.has_soldiers(2));
    
    CHECK_NOTHROW(board.move(1, {1,0}, Board::MoveDIR::Down));
    
    CHECK_FALSE(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));
}

TEST_CASE("Paramedic, Sniper aim"){
    Board board{2,6};
    CHECK_NOTHROW((board[{1,5}] = new Paramedic(2)));
    CHECK_NOTHROW((board[{1,4}] = new Paramedic(2)));
    CHECK_NOTHROW((board[{1,0}] = new Sniper(1)));
    CHECK_NOTHROW((board[{1,1}] = new FootSoldier(1)));

    CHECK_NOTHROW((board.move(1, {1,1}, Board::MoveDIR::Down)));//foot
    CHECK_NOTHROW((board.move(2, {1,4}, Board::MoveDIR::Down)));

    CHECK_NOTHROW((board.move(1, {1,0}, Board::MoveDIR::Down)));//sniper
    CHECK_NOTHROW((board.move(2, {0,4}, Board::MoveDIR::Up)));
    CHECK_NOTHROW((board.move(1, {0,0}, Board::MoveDIR::Up)));//sniper
    CHECK_NOTHROW((board.move(2, {1,4}, Board::MoveDIR::Down)));
    CHECK_NOTHROW((board.move(1, {1,0}, Board::MoveDIR::Down)));//sniper
    CHECK_NOTHROW((board.move(2, {0,4}, Board::MoveDIR::Up)));
    CHECK_NOTHROW((board.move(1, {0,0}, Board::MoveDIR::Up)));//sniper
    CHECK_NOTHROW((board.move(2, {1,4}, Board::MoveDIR::Down)));

    CHECK_NOTHROW((board.move(1, {1,0}, Board::MoveDIR::Down)));//sniper
    CHECK_NOTHROW((board.move(2, {0,4}, Board::MoveDIR::Left)));
    CHECK_NOTHROW((board.move(1, {0,0}, Board::MoveDIR::Up)));//sniper
    
    CHECK_THROWS((board.move(2, {1,5}, Board::MoveDIR::Down)));//dead paramedic

    CHECK_NOTHROW((board.move(2, {0,3}, Board::MoveDIR::Up)));
    CHECK_NOTHROW((board.move(1, {1,0}, Board::MoveDIR::Down)));//sniper
    CHECK_NOTHROW((board.move(2, {1,3}, Board::MoveDIR::Down)));
    CHECK_NOTHROW((board.move(1, {0,0}, Board::MoveDIR::Up)));//sniper
    
    CHECK_FALSE(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));
}
TEST_CASE("FootSoldier aim"){
    Board board{3,25};
    
    CHECK_NOTHROW((board[{0,0}] = new FootSoldier(1)));
    CHECK_NOTHROW((board[{0,24}] = new FootSoldier(1)));
    CHECK_NOTHROW((board[{0,1}] = new FootSoldier(2)));
    CHECK_NOTHROW((board[{2,10}] = new FootSoldier(2)));



    CHECK_NOTHROW((board.move(1, {0,0}, Board::MoveDIR::Up)));
    CHECK_NOTHROW((board.move(2, {2,10}, Board::MoveDIR::Left)));

    CHECK_NOTHROW((board.move(1, {1,0}, Board::MoveDIR::Down)));
    CHECK_NOTHROW((board.move(2, {2,9}, Board::MoveDIR::Left)));

    CHECK_NOTHROW((board.move(1, {0,0}, Board::MoveDIR::Up)));
    CHECK_NOTHROW((board.move(2, {2,8}, Board::MoveDIR::Left)));

    CHECK_NOTHROW((board.move(1, {1,0}, Board::MoveDIR::Down)));
    CHECK_NOTHROW((board.move(2, {2,7}, Board::MoveDIR::Left)));

    CHECK_NOTHROW((board.move(1, {0,0}, Board::MoveDIR::Up)));
    CHECK_NOTHROW((board.move(2, {2,6}, Board::MoveDIR::Left)));

    CHECK_NOTHROW((board.move(1, {1,0}, Board::MoveDIR::Down)));
    CHECK_NOTHROW((board.move(2, {2,5}, Board::MoveDIR::Left)));

    CHECK_NOTHROW((board.move(1, {0,0}, Board::MoveDIR::Up)));
    CHECK_NOTHROW((board.move(2, {2,4}, Board::MoveDIR::Left)));

    CHECK_NOTHROW((board.move(1, {1,0}, Board::MoveDIR::Down)));
    CHECK_NOTHROW((board.move(2, {2,3}, Board::MoveDIR::Left)));

    CHECK_NOTHROW((board.move(1, {0,0}, Board::MoveDIR::Up)));
    CHECK_NOTHROW((board.move(2, {0,1}, Board::MoveDIR::Right)));

    CHECK_NOTHROW((board.move(1, {1,0}, Board::MoveDIR::Up)));
    CHECK_NOTHROW((board.move(2, {0,2}, Board::MoveDIR::Left)));
    
    CHECK_THROWS((board.move(1, {0,2}, Board::MoveDIR::Down)));//dead soldier
    CHECK_NOTHROW((board.move(1, {0,24}, Board::MoveDIR::Left)));

    CHECK_THROWS((board.move(2, {0,2}, Board::MoveDIR::Right)));//dead soldier
    CHECK_NOTHROW((board.move(2, {2,2}, Board::MoveDIR::Left)));
}

TEST_CASE("FootCommander"){
    Board board{3,25};
    int i;
    for(i=1;i<=10;i++){
        board[{2,i}] = new FootSoldier(1);
    }
    for(i=3;i<=10;i++){
        board[{0,i}] = new FootSoldier(1);
    }
    CHECK_NOTHROW((board[{0,2}] = new FootCommander(1)));
    CHECK_NOTHROW((board[{0,0}] = new FootSoldier(2)));
    CHECK_NOTHROW((board[{2,0}] = new FootSoldier(2)));
    CHECK_NOTHROW((board[{0,24}] = new FootSoldier(2)));
    CHECK_NOTHROW((board.move(1, {0,2}, Board::MoveDIR::Left)));
    CHECK_THROWS((board.move(2, {0,0}, Board::MoveDIR::Up)));//dead
    CHECK_THROWS((board.move(2, {2,0}, Board::MoveDIR::Down)));//dead
    CHECK_NOTHROW((board.move(1, {0,24}, Board::MoveDIR::Right)));//not dead
}
TEST_CASE("FootCommander"){
    Board board{1,6};
    board[{0,2}] = new Sniper(1);
    board[{0,3}] = new Sniper(1);
    CHECK_NOTHROW((board[{0,4}] = new SniperCommander(1)));
    CHECK_NOTHROW((board[{0,0}] = new Paramedic(2)));
    CHECK_NOTHROW((board.move(1, {0,3}, Board::MoveDIR::Right)));
    CHECK_THROWS((board.move(2, {0,0}, Board::MoveDIR::Right)));//dead
}
TEST_CASE("ParamedicCommander"){
    Board board{1,30};
    int i;
    for(i=4;i<=10;i++){
        board[{0,i}] = new FootSoldier(1);
    }
    CHECK_NOTHROW((board[{0,11}] = new FootCommander(1)));
    CHECK_NOTHROW((board[{0,0}] = new Paramedic(2)));
    CHECK_NOTHROW((board[{0,29}] = new ParamedicCommander(2)));
    CHECK_NOTHROW((board[{0,1}] = new FootSoldier(2)));
    CHECK_NOTHROW((board.move(1, {0,11}, Board::MoveDIR::Right)));
    CHECK_NOTHROW((board.move(2, {0,29}, Board::MoveDIR::Left)));
    CHECK_NOTHROW((board.move(1, {0,12}, Board::MoveDIR::Right)));
    CHECK_NOTHROW((board.move(2, {0,1}, Board::MoveDIR::Right)));//not dead
}
TEST_CASE("throw for overlap"){
    Board board{3,3};
    board[{1,1}] = new FootSoldier(1);
    board[{1,0}] = new FootSoldier(2);
    board[{0,1}] = new FootSoldier(2);
    board[{2,1}] = new FootSoldier(2);
    board[{1,2}] = new FootSoldier(2);
    CHECK_THROWS((board.move(1, {1,1}, Board::MoveDIR::Up)));
    CHECK_THROWS((board.move(1, {1,1}, Board::MoveDIR::Down)));
    CHECK_THROWS((board.move(1, {1,1}, Board::MoveDIR::Left)));
    CHECK_THROWS((board.move(1, {1,1}, Board::MoveDIR::Right)));
}