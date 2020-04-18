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

int main(int argc, char* argv[])
{
    std::string filename;

    if (argc>1)
    {
        filename = argv[1];
    }
    else
    {
        filename = "../puzzles/puzzle.json";    
    }
    
    std::cout<<"Reading (and parsing) json puzzle file:"<<filename<<std::endl;
    std::fstream i(filename);
    nlohmann::json puzzlefile =  nlohmann::json::parse(i);


    auto puzzleInformation = puzzlefile["Puzzle"];
    int puzzleSize = puzzleInformation["Size"];
	 std::string type = puzzleInformation["Type"];
	
	 std::cout<<"Start Solving "<<puzzleSize<<"x"<<puzzleSize<<" " <<type<<std::endl;
    Puzzle puzzle(puzzleSize);

    for (const auto &block : puzzlefile.at("Blocks"))
    {
        std::vector<int> xs(0);
        std::vector<int> ys(0);
        for(const auto &p : block.at("Coordinates"))
        {
            int x = p[0];
            int y = p[1];

            xs.push_back(x);
            ys.push_back(y);
        }
        puzzle.addBlock(xs,ys,block["Constraint"],block["Type"]);
    }
    puzzle.setPersistent(4,4,5);

    puzzle.print();
   
    auto start = std::chrono::high_resolution_clock::now(); 
    std::ios_base::sync_with_stdio(false); 

    Solver solver(&puzzle);
    solver.solve();

    auto end = std::chrono::high_resolution_clock::now(); 
    double time_taken =  
    std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count(); 
  
    time_taken *= 1e-9; 
    std::cout<<"Took "<<time_taken<<" Seconds"<<std::endl;

    puzzle.printfull();
    
    return 0;
}