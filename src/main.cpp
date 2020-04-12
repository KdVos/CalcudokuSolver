#include <iostream>
#include <Square.h>
#include <Puzzle.h>
#include <Row.h>
#include <Solver.h>
#include <Block.h>

int main()
{
    Puzzle puzzle(4);
    puzzle.print();

    std::vector<int> xs = {0,0,0};
    std::vector<int> ys = {0,1,2};
    int constraint = 7;
    puzzle.addBlock(xs,ys,constraint,1);

    xs = {1,2,3};
    ys = {0,0,0};
    constraint = 8;
    puzzle.addBlock(xs,ys,constraint,1);

    xs = {0,1,1};
    ys = {3,3,2};
    constraint = 9;
    puzzle.addBlock(xs,ys,constraint,1);

    xs = {1,2,2};
    ys = {1,1,2};
    constraint = 8;
    puzzle.addBlock(xs,ys,constraint,1);

    xs = {3,3};
    ys = {1,2};
    constraint = 1;
    puzzle.addBlock(xs,ys,constraint,2);    

     xs = {2,3};
    ys = {3,3};
    constraint = 3;
    puzzle.addBlock(xs,ys,constraint,2);

    
    Solver solver(&puzzle);
    solver.solve();

    puzzle.printfull();
    
    return 0;
}