#pragma once
#include <Puzzle.h>

class Solver{
    public:
    Solver(Puzzle* puzzle): _puzzle(puzzle){
        _guessCount.assign(_puzzle->getSizeFull(),0);
    }   

    void solve()
    {
        std::cout<<"Solver Start"<<std::endl;
        std::cout<<std::endl;

        int idx = 0;
        int guessIdx = 0;
        int x,y;
        idx2Cord(idx, x, y);

        int counter = 0;
        while(true)
        {
            _puzzle->updatexy(x,y);
            std::vector<int> feasibleList = _puzzle->getFeasible(x,y);
            guessIdx = _guessCount[idx];       

            if(feasibleList.size()<= guessIdx)
            {
                _guessCount[idx] = 0;
                _puzzle->setValue(x,y,0);

                idx = idx - 1;

                if(idx<0)
                {
                    std::cout<<"Solver End with "<<counter<<" iterations"<<std::endl;
                    std::cout<<"Puzzle Infeasible"<<std::endl;
                    return;
                }

                idx2Cord(idx, x, y);  
                _puzzle->setValue(x,y,0);
                _guessCount[idx]++;
                guessIdx = _guessCount[idx]; 
            }
            else
            {
                _puzzle->setValue(x,y,feasibleList[guessIdx]);
                idx++;
                idx2Cord(idx, x, y);      
            }  

            if(idx >= _puzzle->getSizeFull())
            {
                std::cout<<"Solver End with "<<counter<<" iterations"<<std::endl;
                return;
            }
            counter++;
        }
        
    }

    private:
    Puzzle* _puzzle;
    std::vector<int> _guessCount;

    void idx2Cord(int idx, int &x, int &y)
    {
        x = idx / _puzzle->getSize();
        y = idx % _puzzle->getSize();
    }

    void cord2Idx(int &idx, int x, int y)
    {
        idx = x + _puzzle->getSize()*y;
    }
};