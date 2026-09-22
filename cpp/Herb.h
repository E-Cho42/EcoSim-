#ifndef HERB_H
#define HERB_H

#include <vector>
#include "Grid.h"

class Herb{
    public:
    //defult construtor and distructor 
    Herb();
    ~Herb();

    //constructor
    Herb(int x_pos, int y_pos, int id, int size);

    //step function
    void step(Grid& _grid);

    //get stuff 
    int get_x() const;
    int get_y() const;
    float get_energy() const;
    bool is_alive() const;
    int get_id() const;


    private:
    //inits
    int x_pos, y_pos;
    float energy;
    bool alive; 
    int id; 
    int size; 

    
};

#endif