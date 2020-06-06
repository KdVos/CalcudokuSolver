#pragma once

#include<vector>

class Square{

public:
    Square(){
        _value = 0;
        _memberOfBlock = -1;
    }

    Square(const Square &other)
    {
        _value = other._value;
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
        return (_value >0);
    }

    void setValue(int Value){
        if(!_persistent){
            _value = Value;
        }
    }

    void setFeasible(std::vector<int> feasibleSet)
    {
        _feasibleSet = feasibleSet;
    }

    std::vector<int> getFeasible()
    {
        if(!_persistent){
            return _feasibleSet;
        }
        else
        {
            return {_value};
        }
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

    void setValuePersistent(int Value)
    {
        setValue(Value);
        _persistent = true;
    }


    bool isPersistent()
    {
        return _persistent;
    }

    private:
        int _value;
        int _memberOfBlock;
        bool _persistent = false;
        std::vector<int> _feasibleSet;
};