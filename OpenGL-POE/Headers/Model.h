#pragma once
#include <string>
#include <sstream>
#include <vector>

#include <GL/glew.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Transform.h"
GLint TextureFromFile( const char *path, std::string directory );

class Model
{
public:
    /*  Functions   */
    // Constructor, expects a filepath to a 3D model.
    Model( const std::string& path );
    Transform transform;
    // Draws the model, and thus all its meshes
    void Draw( Shader& shader, Camera& camera);

private:
    /*  Model Data  */
    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<Texture> textures_loaded;	// Stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    
    /*  Functions   */
    // Loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    void loadModel(const std::string& path );

    void processNode( aiNode* node, const aiScene* scene );

    Mesh processMesh(aiMesh* mesh);

};

