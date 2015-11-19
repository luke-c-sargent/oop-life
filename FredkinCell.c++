#include <iostream>
#include "FredkinCell.h"

using namespace std;

FredkinCell::FredkinCell(bool living): 
	age(0){
  alive = living; 
  living_neighbors=0;}

int FredkinCell::act(){
//cout << "here" << endl;
    //rules:
    //1)a dead cell becomes a live cell, if 1 or 3 neighbors are alive
    int delta=0;
    if(!alive){
        if(living_neighbors==1 || living_neighbors==3){
            alive=true;
            delta = 1;
        }
    //2)a live cell becomes a dead cell, if 0, 2, or 4 neighbors are alive
    }else{
        if(living_neighbors%2 == 0 && living_neighbors < 5){ // if its even and < 5
            alive=false;
            age=0;
            delta = -1;
        }else{
            ++age;}
    }
    //reset living neighbors value for next pass
    living_neighbors=0;
    return delta;
}
void FredkinCell::living(Locale l){
  living_neighbors += (l.n + l.e + l.s + l.w);
}

void FredkinCell::print_cell() {
  if (alive){
    if(age<10)
        cout << age;
    else
        cout << "+";
  }
  else
    cout << '-';
}

bool FredkinCell::heterogeneous_grid_act(){
//cout << "in hetero act" << endl;
  //possibly:

 // if age = ...
  // delete this;
  //  if(age==2)
//        delete this;
//        return true;
//    }else act();
  //return false;
  // this = new ConwayCell(...)?
  return (age == 2);
}

FredkinCell* FredkinCell::operator->() {
  return this;
}
