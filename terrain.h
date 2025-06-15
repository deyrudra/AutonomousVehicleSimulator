// terrain.h
#pragma once
unsigned int createTerrainVAO(int width, int depth, float scale, std::vector<float>& outVertices, std::vector<unsigned int>& outIndices);

unsigned int createFlatTerrainVAO(int width, int depth, float scale, std::vector<float>& outVertices, std::vector<unsigned int>& outIndices);