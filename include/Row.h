#pragma once

#include <Square.h>
#include <vector>
#include <iostream>

class Row{
    public:
    Row() = default;

    void addSquare(Square* sqrptr){
        _listOfSquares.push_back(sqrptr);
        _size = _listOfSquares.size();
        update();
    }

    void update(){
        _presenceList.assign(_size,false);
        _feasibleList.resize(0);

        for (int i = 0; i<_listOfSquares.size();i++)
        {
            int value = _listOfSquares[i]->getValue();
            if(value>0)
            {
                _presenceList[value-1] = true;
            }
        }

        for (int i = 0; i<_presenceList.size();i++)
        {
            if(!_presenceList[i])
            {
                _feasibleList.push_back(i+1);
            }
        }


    }

    std::vector<int> getFeasibleSet(){
        update();
        return _feasibleList;
    }

    void printFeasibleSet(){
        for (int i = 0; i<_feasibleList.size(); i++)
        {
            std::cout<<_feasibleList[i]<<",";
        }
        std::cout<<std::endl;
        for (int i = 0; i<_presenceList.size(); i++)
        {
            std::cout<<_presenceList[i]<<",";
        }
        std::cout<<std::endl;
    }

    void printRow(){
        for(int i = 0; i<_listOfSquares.size(); i++)
        {
            std::cout<<_listOfSquares[i]->getValue()<<"..";
        }
        std::cout<<std::endl;
    }

    private:
    std::vector<Square*> _listOfSquares;
    std::vector<bool> _presenceList;
    std::vector<int> _feasibleList;

    int _size;

};
