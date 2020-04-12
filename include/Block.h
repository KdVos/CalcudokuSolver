#pragma once
#include <Square.h>

class Block{
    public:
    Block() = default;

   void addSquare(Square* sqrptr){
        _listOfSquares.push_back(sqrptr);
        _size = _listOfSquares.size();
        update();
    }

    void setConstraint(int value, int type, int puzzleSize)
    {
        _constraint = value;
        _type = type;
        _puzzleSize = puzzleSize;
    }

    void update(){
        if(_type == 1)
        {
            sumUpdate();
        }
        else 
        {
            
        }
    }

    void sumUpdate(){
         int currentSum = 0;

        for(int i = 0; i<_listOfSquares.size(); i++)
        {
            currentSum+=_listOfSquares[i]->getValue();
        }

        _feasibleList.resize(0);

        for(int i = 1; i<= _puzzleSize; i++)
        {
            if(i<=(_constraint-currentSum))
            {
                _feasibleList.push_back(i);
            }
        }
    }

    std::vector<int> getFeasibleSet(){
        update();
        return _feasibleList;
    }

    int getConstraint()
    {
        int sum = 0;
        for(int i  = 0; i<_listOfSquares.size(); i++)
        {
            sum += _listOfSquares[i]->getValue();
        }
        return sum;
    }

    private:
    std::vector<Square*> _listOfSquares;
    std::vector<int> _feasibleList;
    int _type;
    int _puzzleSize;
    int _size;
    int _constraint;
};