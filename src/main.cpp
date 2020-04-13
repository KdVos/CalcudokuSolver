#include <iostream>
#include <Square.h>
#include <Puzzle.h>
#include <Row.h>
#include <Solver.h>
#include <Block.h>

int main()
{
    Puzzle puzzle(5);
    puzzle.print();

    std::vector<int> xs = {0,1,0};
    std::vector<int> ys = {0,0,1};
    int constraint = 12;
    puzzle.addBlock(xs,ys,constraint,1);

    xs = {1,1};
    ys = {1,2};
    constraint = 1;
    puzzle.addBlock(xs,ys,constraint,2);

    xs = {0,0,0,1,1};
    ys = {2,3,4,3,4};
    constraint = 13;
    puzzle.addBlock(xs,ys,constraint,1);

    xs = {2,2,3};
    ys = {0,1,0};
    constraint = 9;
    puzzle.addBlock(xs,ys,constraint,1);

    xs = {2,2,3};
    ys = {2,3,3};
    constraint = 45;
    puzzle.addBlock(xs,ys,constraint,3);    

    xs = {2,3};
    ys = {4,4};
    constraint = 10;
    puzzle.addBlock(xs,ys,constraint,3);

    xs = {4,4};
    ys = {0,1};
    constraint = 3;
    puzzle.addBlock(xs,ys,constraint,4);

    xs = {3,3,4,4,4};
    ys = {1,2,2,3,4};
    constraint = 14;
    puzzle.addBlock(xs,ys,constraint,1);

    
    Solver solver(&puzzle);
    solver.solve();

    puzzle.printfull();
    
    return 0;
}