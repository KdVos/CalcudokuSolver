#include <iostream>
#include <bits/stdc++.h> 
#include <chrono> 
#include <fstream>

#include <json.hpp>

#include <Square.h>
#include <Puzzle.h>
#include <Row.h>
#include <Solver.h>
#include <Block.h>

int main()
{

    std::fstream i("VK_11-4.json");
    nlohmann::json puzzlefile =  nlohmann::json::parse(i);


    auto puzzleInformation = puzzlefile["Puzzle"];
    int puzzleSize = puzzleInformation["Size"];

    Puzzle puzzle(puzzleSize);
    // puzzle.print();

    std::vector<int> xs = {0,1,2};
    std::vector<int> ys = {0,0,0};
    int constraint = 8;
    puzzle.addBlock(xs,ys,constraint,1);

    xs = {0,0,0};
    ys = {1,2,3};
    constraint = 14;
    puzzle.addBlock(xs,ys,constraint,1);

    xs = {1,1};
    ys = {1,2};
    constraint = 3;
    puzzle.addBlock(xs,ys,constraint,4);

    xs = {1,2};
    ys = {2,2};
    constraint = 4;
    puzzle.addBlock(xs,ys,constraint,2);

    xs = {1,2,0,1,0,1};
    ys = {3,3,4,4,5,5};
    constraint = 24;
    puzzle.addBlock(xs,ys,constraint,1);

    xs = {2,2};
    ys = {4,5};
    constraint = 2;
    puzzle.addBlock(xs,ys,constraint,3);

    xs = {3,4,5,3,3,3,3};
    ys = {0,0,0,1,2,3,4};
    constraint = 28;
    puzzle.addBlock(xs,ys,constraint,1);

    xs = {4,5};
    ys = {1,1};
    constraint = 5;
    puzzle.addBlock(xs,ys,constraint,4);

    xs = {4,5};
    ys = {2,2};
    constraint = 2;
    puzzle.addBlock(xs,ys,constraint,4);

    xs = {4,4};
    ys = {3,4};
    constraint = 8;
    puzzle.addBlock(xs,ys,constraint,1);

    xs = {5,5,5,4,3};
    ys = {3,4,5,5,5};
    constraint = 15;
    puzzle.addBlock(xs,ys,constraint,1);
    
    auto start = std::chrono::high_resolution_clock::now(); 
    std::ios_base::sync_with_stdio(false); 

    Solver solver(&puzzle);
    solver.solve();

    auto end = std::chrono::high_resolution_clock::now(); 
    double time_taken =  
    std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count(); 
  
    time_taken *= 1e-9; 
    std::cout<<"Took "<<time_taken<<" Seconds"<<std::endl;

    puzzle.print();
    
    return 0;
}