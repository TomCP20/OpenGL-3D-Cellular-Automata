#ifndef WORLD_H
#define WORLD_H

#include <vector>

class World
{
private:
    int resolution;
    std::vector<bool> cells;

public:
    World(int res);
    void noise();
    std::vector<float> genMesh() const;

    int getRes() const { return resolution; }

};

#endif