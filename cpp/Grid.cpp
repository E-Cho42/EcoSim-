#include "Grid.h"
#include <random>




// default constructor

Grid::Grid(){
    _size = 100; 
    _time_step = 0; 

    // inside your parameterized constructor
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0f, 0.4f);

    _grid.resize(_size, std::vector<float>(_size));
    for (int i = 0; i < _size; i++){
        for (int j = 0; j < _size; j++){
            _grid[i][j] = dist(gen);
        }
    }
};

// destructor
Grid::~Grid(){
    // nothing to manually clean up 
}

// non default constructor
Grid::Grid(int size, int time_step){
    _size = size;
    _time_step = time_step;
    // inside your parameterized constructor
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0f, 0.4f);

    _grid.resize(_size, std::vector<float>(_size));
    for (int i = 0; i < _size; i++){
        for (int j = 0; j < _size; j++){
            _grid[i][j] = dist(gen);
        }
    }

};

//get_grid function 
std::vector<std::vector<float>> Grid::get_grid() const{
    return _grid; 

};

// growth logic 
void Grid::step(){
    float carrying_capacity = 1.0f;
    float growth_rate = .04f; 
    float dt = 1.0f; 

    for(int i = 0; i < _size; i++){
        for (int j = 0; j < _size; j++){
            float old_value = _grid[i][j];
            float new_value = old_value + growth_rate * old_value * (1-old_value/carrying_capacity) * dt;
            _grid[i][j] = new_value;
        }

    }

};

void Grid::set_cell(int x, int y, float value){
    _grid[x][y] = value;
}