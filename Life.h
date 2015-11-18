//#pragma once

#include <vector>
#include <iostream> 
#include <string>
#include "gtest/gtest_prod.h"

#include "Cell.h"
#include "FredkinCell.h"
#include "ConwayCell.h"

using namespace std;

#ifndef LOCALE
#define LOCALE
struct Locale{
    int n,ne,e,se,s,sw,w,nw;
    Locale():n(0),ne(0),e(0),se(0),s(0),sw(0),w(0),nw(0){}
};
#endif
template<typename CellType>
class Life{
	int grid_rows,grid_cols,evolutions,frequency;
	vector<CellType> grid;
  
  public:
	bool is_hetero;

  //constructor
  Life(int rows, int cols) :
    grid(vector<CellType>(rows*cols))
  {
    grid_rows = rows;
    grid_cols = cols;
    cin >> evolutions;
    cin >> frequency;
  cout << grid_rows << " " << grid_cols << " " << evolutions << " " << frequency << endl;
  }

/*
  void populate_grid() {
    if (is_hetero)
      populate_heterogeneous_grid();
    else
      populate_homogeneous_grid();
  }
*/

  void populate_heterogeneous_grid(){
    string line;
    for (int i = 0; i < grid_rows; i++){
      getline(cin, line);
      for (int j = 0; j < grid_cols; j++) {
        char ch = line[j];
        switch (ch) {
          case ('.'):
            at(i,j).abstractcell_ptr = new ConwayCell(false);
            break;
          case('*'):
            at(i,j).abstractcell_ptr = new ConwayCell(true);
            break;
          case('-'):
            at(i,j).abstractcell_ptr = new FredkinCell(false);
            break;
          case('0'):
            at(i,j).abstractcell_ptr = new FredkinCell(true);
            break;
        }
      }
    }
  }

  void populate_homogeneous_grid(){
    string line;
    for (int i = 0; i < grid_rows; i++){
      getline(cin, line);
      for (int j = 0; j < grid_cols; j++) {
        if (line[j] == '0' || line[j] == '*')
          at(i,j).alive = true;
      }
    }
  }

  CellType& at(int rows, int cols) {
    int n = convert(rows, cols);
    return grid[n];
  }

  CellType& at(int n) {
    return grid[n];
  }

  int convert(int rows, int cols) {
    return rows*grid_cols+cols;
  }

  pair<int, int> convert(int i) {
    return make_pair((i/grid_cols), (i-(i/grid_cols)*grid_cols));
  }
 
  void print_grid() {
  cout << endl;
    for (int i = 0; i < grid_rows; i++){
      for (int j = 0; j < grid_cols; j++) {
        at(i,j)->print_cell();
      }
      cout << endl;
    }
    cout << endl;
  }
  
  void step(int steps=1){
    int _x,_y;
    _x=_y=0;
    for(int i=0; i < grid.size(); ++i){//going through the cells,
        if(at(i)->alive){//if the cell is alive
            _x=grid.size()%grid_cols; // get coords
            _y=grid.size()/grid_cols;
            Locale l; //get local info
            if(i>=grid_cols){ // if its not a top row, can check northern values
                l.n=at(i-grid_cols)->alive; //north = one row up
                if(_x) // if x is not 0, can go backwards
                    l.nw=at(i-grid_cols-1)->alive;
                else if( _x < ( grid_cols -1) )// if its not a eastmost cell
                    l.ne=at(i-grid_cols+1)->alive;
            }
            if(_y != grid_rows - 1){ // if its not a bottom row, can check southern values
                l.s=at(i+grid_cols)->alive; // south = one row down
                if(_x)
                    l.sw=at(i+grid_cols-1)->alive;
                else if( _x < ( grid_cols -1) )
                    l.se=at(i+1+grid_cols)->alive;
            }
            if(_x)
                l.w=at(i-1)->alive;// west = one back
            if(_x < grid_cols)
                l.e=at(i+1)->alive; // east = one forward
            at(i)->living(l);
            _x=_y=0;// reset values
        }
    }
  }
  
  //FRIEND TESTS
	FRIEND_TEST(LifeFixture, Life_Constructor_1);
};
