#ifndef MODEL_H
#define MODEL_H

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <string>
#include <vector>
#include "Mesh.h"

class Model {
public:
    std::vector<Mesh> meshes;
    Model(const std::string& path);
    void Draw();

private:
    void loadModel(const std::string& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
};

#endif
