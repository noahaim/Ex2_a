#include "doctest.h"
#include "Board.hpp"
#include "Direction.hpp"
using ariel::Direction;

//function that return ramdo direction
ariel::Direction randomDirection()
{
    int ans=random()%2;//random number 0/1
    if(ans==1)
        return Direction::Horizontal;
    return Direction::Vertical;
}

//function that return random number 
uint randomNumber(int low,int top)
{
    return (uint)(rand()%(top+1-low)+low);

}

TEST_CASE("check post+read function")
{
    ariel::Board board;
    //check read of empty places
    CHECK(board.read(9,11,Direction::Horizontal,3) == "___");
    CHECK(board.read(30,20,Direction::Vertical,5) == "_____");
    CHECK(board.read(1,11,Direction::Horizontal,3) == "___");
    CHECK(board.read(100,3,Direction::Horizontal,3) == "___");
    CHECK(board.read(14,123,Direction::Horizontal,3) == "___");

    //check post+read Horizontal
    board.post(1,2, Direction::Horizontal, "abcd");
    CHECK(board.read(1,2,Direction::Horizontal,4) == "abcd");
    board.post(10,20, Direction::Horizontal, "1234");
    CHECK(board.read(10,20,Direction::Horizontal,4) == "1234");
    board.post(100,200,Direction::Horizontal,"efgh");
    CHECK(board.read(100,200,Direction::Horizontal,4) == "efgh");
    

    //check post+read Vertical
    board.post(30,20, Direction::Vertical, "acd");
    CHECK(board.read(30,20,Direction::Vertical,3) == "abc");
    board.post(1,50,Direction::Vertical,"efg");
    CHECK(board.read(1,50,Direction::Vertical,3) == "efg");
    board.post(100,2,Direction::Vertical,"hi my name is noa");
    CHECK(board.read(100,2,Direction::Vertical,17) == "hi my name is noa");

    //check read of string len 0
    CHECK(board.read(9,11,Direction::Horizontal,0) == "");
    CHECK(board.read(1,19,Direction::Vertical,0) == "");

    //check read of place with ad+empty places
    CHECK(board.read(100,2,Direction::Vertical,19) == "hi my name is noa__");
    CHECK(board.read(100,199,Direction::Horizontal,5) == "_efgh");
    CHECK(board.read(0,50,Direction::Vertical,6) == "_efg__");
    }
TEST_CASE("check that the function post writes above what is written")
{
    ariel::Board board;
    /*
    ace
    bdf
    */
    board.post(0,0, Direction::Vertical, "ab");
    board.post(0,1, Direction::Vertical, "cd");
    board.post(0,2, Direction::Vertical, "ef");
    board.post(0,0, Direction::Horizontal, "noa");
    /*
    noa
    bdf
    */
    CHECK(board.read(0,0,Direction::Vertical,2) == "nb");
    CHECK(board.read(0,0,Direction::Vertical,2) == "od");
    CHECK(board.read(0,0,Direction::Vertical,2) == "af");
    //check that it writes above all the word
    board.post(10,0, Direction::Horizontal, "hello world");
    CHECK(board.read(10,0, Direction::Horizontal,11)=="hello world");
    board.post(10,0, Direction::Horizontal, "yello 12345");
    CHECK(board.read(10,0, Direction::Horizontal,11)=="yello 12345");
    //check that it writes above the beggin of the word
     board.post(10,0, Direction::Horizontal, "abcde");
     CHECK(board.read(10,0, Direction::Horizontal,11)=="abcde 12345");
    //check that it writes above the middle of the word
     board.post(10,3, Direction::Horizontal, "noa");
     CHECK(board.read(10,0, Direction::Horizontal,11)=="abcnoa12345");
    //check that it writes above the end of the word
    board.post(10,9, Direction::Horizontal, "hi");
     CHECK(board.read(10,0, Direction::Horizontal,11)=="abcnoa123hi");
}
TEST_CASE("check post of emty ad")
{
    ariel::Board board;
    board.post(0,0, Direction::Vertical, "");
    board.post(100,20, Direction::Vertical, "");
    board.post(145,302, Direction::Vertical, "");
    CHECK(board.read(0,0,Direction::Vertical,1) == "_");
    CHECK(board.read(100,20,Direction::Vertical,1) == "_");
    CHECK(board.read(145,302,Direction::Vertical,1) == "_");
}
TEST_CASE("check post and read of random places")
{
    ariel::Board board;
    uint randomLine;
    uint randomCloumn;
    for(int i=0;i<20;i++)
    {
        randomLine=randomNumber(i*10,100+i*10);
        randomCloumn=randomNumber(i*10,100+i*10);
        Direction direction=randomDirection();
        board.post(randomLine,randomCloumn,direction, "dasdkakda");
        CHECK(board.read(randomLine,randomCloumn,direction,9)=="dasdkakda");
    }
}