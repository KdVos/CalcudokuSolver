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
        else if (_type == 2)
        {
            minusUpdate();
        }
        else if (_type == 3)
        {
            multiUpdate();
        }
        else
        {
            divUpdate();
        }
        
    }

    void divUpdate()
    {

        int currentProduct = 1;
        int numUnSet = 0;

        for(int i = 0; i<_listOfSquares.size(); i++)
        {
            int value = _listOfSquares[i]->getValue();

            if(value > 0){
                currentProduct*= value;
            }
            
            if(!_listOfSquares[i]->isSet())
            {
                numUnSet++;
            }
        }

        _feasibleList.resize(0);

        if(numUnSet>1)
        {
            for(int i = 1; i<= _puzzleSize; i++)
            {

                _feasibleList.push_back(i);
            }
        }
        else
        {
           for(int i = 1; i<= _puzzleSize; i++)
            {
                if(i * _constraint == currentProduct)
                {
                    _feasibleList.push_back(i);
                }
                else if (i % _constraint == 0 && i / _constraint == currentProduct)
                {
                    _feasibleList.push_back(i);
                }
            }
        }
    }

    void multiUpdate(){
        int currentProduct = 1;
        int numUnSet = 0;

        for(int i = 0; i<_listOfSquares.size(); i++)
        {
            int value = _listOfSquares[i]->getValue();

            if(value > 0){
                currentProduct*= value;
            }
            
            if(!_listOfSquares[i]->isSet())
            {
                numUnSet++;
            }
        }
        _feasibleList.resize(0);

        if(numUnSet>1)
        {
            int remConstraint = _constraint/currentProduct;
            for(int i = 1; i<= _puzzleSize; i++)
            {
                if(remConstraint % i == 0)
                {
                    _feasibleList.push_back(i);
                }
            }
        }
        else
        {
           int remConstraint = _constraint/currentProduct;
           for(int i = 1; i<= _puzzleSize; i++)
            {
                if(remConstraint % i == 0 && remConstraint / i == 1)
                {
                    _feasibleList.push_back(i);
                }
            }
        }
    }

    void minusUpdate(){
         int currentSum = 0;
         int numUnSet = 0;

        for(int i = 0; i<_listOfSquares.size(); i++)
        {
            currentSum+=_listOfSquares[i]->getValue();
            
            if(!_listOfSquares[i]->isSet())
            {
                numUnSet++;
            }

        }

        _feasibleList.resize(0);

        if(numUnSet>1)
        {
            for(int i = 1; i<= _puzzleSize; i++)
            {
                _feasibleList.push_back(i);
            }
        }
        else
        {
            for(int i = 1; i<= _puzzleSize; i++)
            {
            if(i==(currentSum+_constraint) || i==(currentSum-_constraint))
            {
                _feasibleList.push_back(i);
            }
            }
        }

    }

    void sumUpdate(){
         int currentSum = 0;
         int numUnSet = 0;

        for(int i = 0; i<_listOfSquares.size(); i++)
        {
            currentSum+=_listOfSquares[i]->getValue();
            
            if(!_listOfSquares[i]->isSet())
            {
                numUnSet++;
            }

        }

        _feasibleList.resize(0);

        if(numUnSet>1)
        {
            for(int i = 1; i<= _puzzleSize; i++)
            {
            if(i<=(_constraint-currentSum))
            {
                _feasibleList.push_back(i);
            }
            }
        }
        else
        {
            for(int i = 1; i<= _puzzleSize; i++)
            {
            if(i==(_constraint-currentSum))
            {
                _feasibleList.push_back(i);
            }
            }
        }
        
        
    }

    std::vector<int> getFeasibleSet(){
        update();
        return _feasibleList;
    }

    int getConstraint(){

        if (_type == 1)
        {
            int sum = 0;
            for(int i  = 0; i<_listOfSquares.size(); i++)
            {
                sum += _listOfSquares[i]->getValue();
            }
            return sum;
        }
        else if (_type == 2)
        {   int num1 = _listOfSquares[0]->getValue();
            int num2 = _listOfSquares[1]->getValue();
            return abs(num1 - num2);
        }
        else if (_type == 3)
        {
            int product = 1;
            for(int i  = 0; i<_listOfSquares.size(); i++)
            {
                int value = _listOfSquares[i]->getValue();
                if (value > 0){
                  product *= value;  
                }
                
            }
            return product;
        }
        else
        {
            int num1 = _listOfSquares[0]->getValue();
            int num2 = _listOfSquares[1]->getValue();

            if (num1 > num2)
            {
                return num1 / num2;
            }
            else
            {
                return num2 / num1;
            }
            
        }
        
       
    }

    int get_constraint(){
        return _constraint;
    }

    private:
    std::vector<Square*> _listOfSquares;
    std::vector<int> _feasibleList;
    int _type;
    int _puzzleSize;
    int _size;
    int _constraint;
};