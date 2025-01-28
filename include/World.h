#ifndef WORLD_H
#define WORLD_H

#include <vector>

class World
{
private:
    int resolution;
    std::vector<bool> cells;
    std::vector<bool> prevCells;

    int countNeighbors(int i) const;
    int mod(int n) const { return (n + resolution) % resolution; }
    int coordToIndex(int x, int y, int z) const { return (x * resolution * resolution + y * resolution + z); }
    bool isEmpty(int x, int y, int z) const;
    void addFace(std::vector<float> &mesh, float face[], int x, int y, int z) const;

public:
    World(int res);
    void noise();
    void step();
    std::vector<float> genMesh() const;

    int getRes() const { return resolution; }
};

#endif