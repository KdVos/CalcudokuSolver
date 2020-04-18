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

    int getBlock(int x, int y){
        if(x<_size && y<_size){
            return getSquare(x,y)->getConstraintBlock();
        }
        else
        {
            return -1;
        }
    }

    void setValue(int x, int y,int v){
        getSquare(x,y)->setValue(v);
        updatexy(x,y);
    }

    std::vector<int> getFeasible(int x, int y){
        if(x<_size && y<_size){
            return getSquare(x,y)->getFeasible();
        }
        else
        {
            return {-1};
        }
    }

    void printFeasiblexy(int x, int y){
        std::cout<<"Square ("<<x<<","<<y<<")"<<std::endl;
        getSquare(x,y)->printFeasible();
    }

    void print(){
        char ul[]={0x1b,'[','4',';','3','9','m',0};
        std::cout<<ul<<" ";

        for (int x =0; x<_size; x++)
        {
            std::cout<<"    ";
        }

        char normal[]={0x1b,'[','0',';','3','9','m',0};
        std::cout<<normal<<std::endl;

        for(int y = 0; y<_size; y++)
        {
            std::cout<<"|";
            for (int x = 0; x<_size; x++)
            {  
                 if(getBlock(x,y)!=getBlock(x,y+1))
                {
                    char ul[]={0x1b,'[','4',';','3','9','m',0};
                    std::cout<<ul;
                }
                else
                {
                    char normal[]={0x1b,'[','0',';','3','9','m',0};
                    std::cout<<normal;
                }

                if(getValue(x,y)>0){
                    std::cout<<" "<<getValue(x,y)<<" ";
                }
                else
                {
                    std::cout<<" "<<"."<<" ";
                }

                if(getBlock(x,y)!=getBlock(x+1,y))
                {
                    char normal[]={0x1b,'[','0',';','3','9','m',0};
                    std::cout<<normal;
                    std::cout<<"|";
                }
                else
                {
                    std::cout<<" ";
                }
            }
            std::cout<<std::endl;
            char normal[]={0x1b,'[','0',';','3','9','m',0};
            std::cout<<normal;
        }
    }

    void printfull(){
        print();
        for (int i=0; i<_listofBlocks.size(); i++)
        {
            std::cout<<"Block "<<i<<", "<<_listofBlocks[i].getConstraint()<<", "<<_listofBlocks[i].get_constraint()<<std::endl;
        }
    }

    void update(){
        for (int x = 0; x<_size; x++)
        {
            for (int y = 0; y<_size; y++)
            {
                if(!getSquare(x,y)->isSet())
                {
                    updatexy(x,y);
                }
            }
        }
    }

    void updatexy(int x,int y){
         std::vector<int> feasibleRow = _listofRows[y].getFeasibleSet();
         std::vector<int> feasibleCol = _listofCollumns[x].getFeasibleSet();
         std::vector<int> feasibleSet = compareLists(feasibleRow,feasibleCol);

         int activeBlock = getSquare(x,y)->getConstraintBlock();

         if(activeBlock>-1)
         {
            std::vector<int> feasibleBlock = _listofBlocks[activeBlock].getFeasibleSet();        
            feasibleSet = compareLists(feasibleSet,feasibleBlock);
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