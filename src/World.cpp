#include "World.h"
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <math.h>

float backFace[] = {
    0.0f,
    0.0f,
    0.0f,
    1.0f,
    0.0f,
    0.0f,
    1.0f,
    1.0f,
    0.0f,
    1.0f,
    1.0f,
    0.0f,
    0.0f,
    1.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
};

float frontFace[] = {
    0.0f,
    0.0f,
    1.0f,
    1.0f,
    0.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    0.0f,
    1.0f,
    1.0f,
    0.0f,
    0.0f,
    1.0f,
};

float leftFace[] = {
    0.0f,
    1.0f,
    1.0f,
    0.0f,
    1.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    1.0f,
    0.0f,
    1.0f,
    1.0f,
};

float rightFace[] = {
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    0.0f,
    1.0f,
    0.0f,
    0.0f,
    1.0f,
    0.0f,
    0.0f,
    1.0f,
    0.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
};

float bottomFace[] = {
    0.0f,
    0.0f,
    0.0f,
    1.0f,
    0.0f,
    0.0f,
    1.0f,
    0.0f,
    1.0f,
    1.0f,
    0.0f,
    1.0f,
    0.0f,
    0.0f,
    1.0f,
    0.0f,
    0.0f,
    0.0f,
};

float topFace[] = {
    0.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 0.0f};

int vertices_count = 6;

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

bool World::isEmpty(int x, int y, int z) const
{
    if (x < 0 || x >= resolution || y < 0 || y >= resolution || z < 0 || z >= resolution)
    {
        return true;
    }
    return !cells[coordToIndex(x, y, z)];
}

void World::addFace(std::vector<float> &mesh, float face[], int x, int y, int z) const
{
    for (int v = 0; v < vertices_count; v++)
    {
        mesh.push_back(face[3 * v] + x);
        mesh.push_back(face[3 * v + 1] + y);
        mesh.push_back(face[3 * v + 2] + z);
    }
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
                    if (isEmpty(x, y, z - 1))
                    {
                        addFace(mesh, backFace, x, y, z);
                    }
                    if (isEmpty(x, y, z + 1))
                    {
                        addFace(mesh, frontFace, x, y, z);
                    }
                    if (isEmpty(x - 1, y, z))
                    {
                        addFace(mesh, leftFace, x, y, z);
                    }
                    if (isEmpty(x + 1, y, z))
                    {
                        addFace(mesh, rightFace, x, y, z);
                    }
                    if (isEmpty(x, y - 1, z))
                    {
                        addFace(mesh, bottomFace, x, y, z);
                    }
                    if (isEmpty(x, y + 1, z))
                    {
                        addFace(mesh, topFace, x, y, z);
                    }
                }
            }
        }
    }
    return mesh;
}
