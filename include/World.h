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
    void updateMesh();
    bool isEmpty(int x, int y, int z) const;
    void addFace(float face[], int x, int y, int z);

public:
    std::vector<float> mesh;

    World(int res);
    void noise();
    void step();

    int getRes() const { return resolution; }
};

#endif