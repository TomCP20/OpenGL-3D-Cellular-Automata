#include "World.h"
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <math.h>

float vertices[] = {
    0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f,

    0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f,

    0.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 1.0f,

    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f,

    0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 0.0f,

    0.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 0.0f};
int vertices_count = 36;

int World::countNeighbors(int i) const
{
    int x = floor(i / (resolution * resolution));
    int y = floor((i % (resolution * resolution)) / resolution);
    int z = i % (resolution);
    int neighbors = 0;
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            for (int dz = -1; dz <= 1; dz++)
            {
                if (dx == 0 && dy == 0 && dz == 0)
                {
                    continue;
                }
                int neighbori = coordToIndex(mod(x + dx), mod(y + dy), mod(z + dz));
                if (prevCells[neighbori])
                {
                    neighbors++;
                }
            }
        }
    }
    return neighbors;
}

World::World(int res)
{
    resolution = res;
    cells = std::vector<bool>(res * res * res, false);
    prevCells = std::vector<bool>(res * res * res, false);
}

void World::noise()
{
    for (int i = 0; i < cells.size(); i++)
    {
        cells[i] = rand() % 4 == 0;
    }
}

void World::step()
{
    std::swap(cells, prevCells);
    for (int i = 0; i < prevCells.size(); i++)
    {
        int neighbors = countNeighbors(i);
        if (prevCells[i])
        {
            cells[i] = 5 <= neighbors && neighbors <= 7;
        }
        else
        {
            cells[i] = 6 <= neighbors && neighbors <= 6;
        }
    }
}

std::vector<float> World::genMesh() const
{
    std::vector<float> mesh;
    for (int x = 0; x < resolution; x++)
    {
        for (int y = 0; y < resolution; y++)
        {
            for (int z = 0; z < resolution; z++)
            {
                int i = coordToIndex(x, y, z);
                if (cells[i])
                {
                    for (int v = 0; v < vertices_count; v++)
                    {
                        mesh.push_back(vertices[3 * v] + x);
                        mesh.push_back(vertices[3 * v + 1] + y);
                        mesh.push_back(vertices[3 * v + 2] + z);
                    }
                }
            }
        }
    }
    return mesh;
}
