#pragma once

#include <vector>
#include <iostream>

#include <Square.h>
#include <Row.h>
#include <Block.h>

class Puzzle{

    public:
    Puzzle(int n){
        _listofSquares.resize(n*n);
        _size = n;

        populateCollumns();
        populateRows();
    }

    void addBlock(std::vector<int> xs, std::vector<int> ys, int value, int type){
        Block block;
        block.setConstraint(value,type,_size);
        
        for (int i = 0; i<xs.size(); i++)
        {
            int xi = xs[i];
            int yi = ys[i];
            Square* si = getSquare(xi,yi);
            si->setConstraintBlock(_listofBlocks.size());

            block.addSquare(si);
        }
        _listofBlocks.push_back(block);
    }

    int getValue(int x,int y){
        return getSquare(x,y)->getValue();
    }

    void setValue(int x, int y,int v){
        getSquare(x,y)->setValue(v);
        updatexy(x,y);
    }

    std::vector<int> getFeasible(int x, int y){
        return getSquare(x,y)->getFeasible();
    }

    void printFeasiblexy(int x, int y){
        std::cout<<"Square ("<<x<<","<<y<<")"<<std::endl;
        getSquare(x,y)->printFeasible();
    }

    void print(){
        for(int y = 0; y<_size; y++)
        {
            for (int x = 0; x<_size; x++)
            {
                std::cout<<getValue(x,y);
            }
            std::cout<<std::endl;
        }
    }

    void printfull(){
        print();
        for (int i=0; i<_listofBlocks.size(); i++)
        {
            std::cout<<"Block "<<i<<", "<<_listofBlocks[i].getConstraint()<<std::endl;
        }
    }

    void update(){
        for (int x = 0; x<_size; x++)
        {
            for (int y = 0; y<_size; y++)
            {
               updatexy(x,y);
            }
        }
    }

    void updatexy(int x,int y){
        _listofRows[y].update();
        _listofCollumns[x].update();
         std::vector<int> feasibleRow = _listofRows[y].getFeasibleSet();
         std::vector<int> feasibleCol = _listofCollumns[x].getFeasibleSet();
         std::vector<int> feasibleSet = compareLists(feasibleRow,feasibleCol);

         int activeBlock = getSquare(x,y)->getConstraintBlock();


         if(activeBlock>-1)
         {
            std::vector<int> feasibleBlock = _listofBlocks[activeBlock].getFeasibleSet();        
            feasibleSet = compareLists(feasibleSet,feasibleBlock);
         }
         else
         {
            
         }
        
         getSquare(x,y)->setFeasible(feasibleSet);
    }

    int getSize(){
        return _size;
    }

    int getSizeFull(){
        return _listofSquares.size();
    }
    private:

    std::vector<int> compareLists( std::vector<int> A,  std::vector<int> B){
        std::vector<int> C;

        for(int i = 0; i<A.size(); i++)
        {
            for (int j=0; j<B.size(); j++)
            {
                if(A[i] == B[j])
                {
                    C.push_back(A[i]);
                    break;
                }
            }
        }
        return C;
    }

    void populateRows(){
        _listofRows.resize(_size);
        for (int x = 0; x<_size; x++)
        {
            for (int y = 0; y<_size; y++)
            {
                Square* sqrptr = getSquare(x,y);
                _listofRows[y].addSquare(sqrptr);
            }
        }
    }

     void populateCollumns(){
        _listofCollumns.resize(_size);
        for (int x = 0; x<_size; x++)
        {
            for (int y = 0; y<_size; y++)
            {
                Square* sqrptr = getSquare(x,y);
                _listofCollumns[x].addSquare(sqrptr);
            }
        }
    }

    Square* getSquare(int x, int y){
            int idx = x + _size*y;
            return &_listofSquares[idx];
    }

    std::vector<Square> _listofSquares;
    std::vector<Row> _listofRows;
    std::vector<Row> _listofCollumns;
    std::vector<Block> _listofBlocks;
    int _size;

};