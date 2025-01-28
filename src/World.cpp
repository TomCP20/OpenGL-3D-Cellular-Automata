#include "World.h"
#include <vector>
#include <stdlib.h>

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

World::World(int res)
{
    resolution = res;
    cells = std::vector<bool>(res * res * res, false);
}

void World::noise()
{
    for (int i = 0; i < cells.size(); i++)
    {
        cells[i] = rand() % 2 == 0;
    }
}

std::vector<float> World::genMesh() const
{
    std::vector<float> mesh;

    for (int y = 0; y < resolution; y++)
    {
        for (int x = 0; x < resolution; x++)
        {
            for (int z = 0; z < resolution; z++)
            {
                int i = z + resolution * x + resolution * resolution * y;
                if (cells[i])
                {
                    for (int v = 0; v < vertices_count; v++)
                    {
                        float vx = vertices[3 * v];
                        float vy = vertices[3 * v + 1];
                        float vz = vertices[3 * v + 2];
                        float nx = ((vx + (float)x) / (float)resolution) * 2 - 1;
                        float ny = ((vy + (float)y) / (float)resolution) * 2 - 1;
                        float nz = ((vz + (float)z) / (float)resolution) * 2 - 1;
                        mesh.push_back(nx);
                        mesh.push_back(ny);
                        mesh.push_back(nz);
                    }
                }
            }
        }
    }
    return mesh;
}
