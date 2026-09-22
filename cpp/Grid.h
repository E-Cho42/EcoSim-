#ifndef GRID_H
#define GRID_H

#include <vector>

class Grid{
    public:
    //defult construtor and distructor 
    Grid();
    ~Grid(); 

    //constructor
    Grid(int size, int time_step);

    //stepfunction
    void step();

    //get_grid
    std::vector<std::vector<float>> get_grid() const;

    //set_cell
    void set_cell(int x, int y, float value);

    private:
    //_grid
    std::vector<std::vector<float>> _grid;
    //size
    int _size;
    //timestep
    int _time_step; 



};


#endif