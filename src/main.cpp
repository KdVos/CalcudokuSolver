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

    // File I/O
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


    // Construct Problem
    if(type.compare("Calcudoku")==0)
    {
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
    }
    else if (type.compare("Sudoku") == 0)
    {
        int squareSize = puzzleInformation["squareSize"];
        int widthBlocks = puzzleSize/squareSize;

        for (int j = 0; j<widthBlocks; j++)
        {
            for(int i = 0; i<widthBlocks; i++)
            {   
                std::vector<int> xs(0);
                std::vector<int> ys(0);
                for (int y = 0; y<widthBlocks; y++)
                {
                    for(int x = 0; x<widthBlocks; x++)
                    {
                        xs.push_back(x + i*widthBlocks);
                        ys.push_back(y + j*widthBlocks);
                    }
                }            
            puzzle.addBlock(xs,ys,0,5);
            }
        } 
    }

    if(puzzlefile.find("Hints") != puzzlefile.end())
    {
        auto Hints = puzzlefile["Hints"];

        for (const auto &h :Hints["xyv"])
        {
            puzzle.setPersistent(h[0],h[1],h[2]);
        }
    }


    
    puzzle.print();
   
    // Solver
    auto start = std::chrono::high_resolution_clock::now(); 
    std::ios_base::sync_with_stdio(false); 

    Solver solver(&puzzle);
    solver.solve();

    auto end = std::chrono::high_resolution_clock::now(); 
    double time_taken =  
    std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count(); 
  
    time_taken *= 1e-9; 
    std::cout<<"Took "<<time_taken<<" Seconds"<<std::endl;


    //Display Solution
    puzzle.printfull();
    
    return 0;
}