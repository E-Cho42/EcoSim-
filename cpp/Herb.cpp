#include "Herb.h"
#include <random>

// default constructor — delegates to the parameterized one with sensible defaults
Herb::Herb() : Herb(0, 0, 0, 10) {
}

Herb::~Herb(){
    // nothing to manually clean up
}

// constructor
Herb::Herb(int x, int y, int _id, int _size){
    x_pos = x;
    y_pos = y;
    energy = 1.0f;
    alive = true;
    id = _id;
    size = _size;
}

// get functions
int Herb::get_x() const{
    return x_pos;
}

int Herb::get_y() const{
    return y_pos;
}

float Herb::get_energy() const{
    return energy;
}

bool Herb::is_alive() const{
    return alive;
}

int Herb::get_id() const{
    return id;
}

// step
void Herb::step(Grid& _grid){
    if(!alive) return;

    std::vector<std::vector<float>> grid = _grid.get_grid();

    // safely read a neighbo
    float lft_cell = (x_pos - 1 >= 0)      ? grid[x_pos - 1][y_pos] : -1.0f;
    float rgt_cell = (x_pos + 1 < size)    ? grid[x_pos + 1][y_pos] : -1.0f;
    float dwn_cell = (y_pos - 1 >= 0)      ? grid[x_pos][y_pos - 1] : -1.0f;
    float up_cell   = (y_pos + 1 < size)   ? grid[x_pos][y_pos + 1] : -1.0f;

    float stsc = 0.0f;
    float vtvc = 0.0f;
    int drc_sts = 0;
    int drc_vtv = 0;

    if(lft_cell >= rgt_cell){
        stsc = lft_cell;
        drc_sts = 0;
    } else {
        stsc = rgt_cell;
        drc_sts = 1;
    }

    if(up_cell >= dwn_cell){
        vtvc = up_cell;
        drc_vtv = 0;
    } else {
        vtvc = dwn_cell;
        drc_vtv = 1;
    }

    if(stsc >= vtvc){
        if(drc_sts == 0){
            if(x_pos != 0){
                x_pos--;
            }
        } else {
            if(x_pos != size - 1){
                x_pos++;
            }
        }
    } else {
        if(drc_vtv == 0){
            if(y_pos != size - 1){
                y_pos++;
            }
        } else {
            if(y_pos != 0){
                y_pos--;
            }
        }
    }

    energy -= 0.3f;

    if(energy <= 0){
        alive = false;
    }

    if(alive){
        energy += grid[x_pos][y_pos];
        _grid.set_cell(x_pos, y_pos, 0.001f);
    }
}