#pragma once

#include<vector>

class Square{

public:
    Square(){
        _value = 0;
        _set = false;
        _memberOfBlock = -1;
    }

    Square(const Square &other)
    {
        _value = other._value;
        _set = other._set;
        _memberOfBlock = other._memberOfBlock;
    }

    int getValue(){
        return _value;
    }

    void setConstraintBlock(int N){
        _memberOfBlock = N;
    }

    int getConstraintBlock(){
        return _memberOfBlock;
    }

    bool isSet(){
        return _set;
    }

    void setValue(int Value){
        _value = Value;
    }

    void setFeasible(std::vector<int> feasibleSet)
    {
        _feasibleSet = feasibleSet;
    }

    std::vector<int> getFeasible()
    {
        return _feasibleSet;
    }

    void printFeasible()
    {
        std::cout<<"Feasible Set:"<<std::endl;

        for(int i = 0; i<_feasibleSet.size(); i++)
        {
            std::cout<<_feasibleSet[i]<<",";
        }
        std::cout<<std::endl;
    }

    private:
        int _value;
        bool _set;
        int _memberOfBlock;
        std::vector<int> _feasibleSet;
};