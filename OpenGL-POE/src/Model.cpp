#include "../Headers/Model.h"
//  DE VRIES, J. (n.d.). LearnOpenGL - Model. [online] learnopengl.com.
//  Available at: https://learnopengl.com/Model-Loading/Model
//  [Accessed 15 Nov. 2023].

Model::Model(const std::string& path)
{
    transform.m_parent = nullptr;
    this->loadModel( path );
}

void Model::Draw(Shader& shader, Camera& camera)
{
    for ( GLuint i = 0; i < this->meshes.size( ); i++ )
    {
        shader.Activate();
        shader.setMat4("model", transform.getModelMatrix());
        this->meshes[i].Draw( shader, camera );
    }
}

void Model::loadModel(const std::string& path)
{
    // Read file via ASSIMP
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile( path, aiProcess_Triangulate | aiProcess_FlipUVs );
        
    // Check for errors
    if( !scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode ) // if is Not Zero
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString( ) << std::endl;
        return;
    }
    // Retrieve the directory path of the filepath
    this->directory = path.substr( 0, path.find_last_of( '/' ) );
        
    // Process ASSIMP's root node recursively
    this->processNode( scene->mRootNode, scene );
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    // Process each mesh located at the current node
    for ( GLuint i = 0; i < node->mNumMeshes; i++ )
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            
        this->meshes.push_back( this->processMesh( mesh) );
    }
    for ( GLuint i = 0; i < node->mNumChildren; i++ )
    {
        this->processNode( node->mChildren[i], scene );
    }
}

Mesh Model::processMesh(aiMesh* mesh)
{
    // Data to fill
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    Texture texture;
        
    for ( GLuint i = 0; i < mesh->mNumVertices; i++ )
    {
        Vertex vertex{};
        glm::vec3 vector; // We declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
            
        // Positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        
        if (mesh->HasNormals())
        {
            // Normals
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;  
        }
        
        // Texture Coordinates
        if( mesh->mTextureCoords[0] ) // Does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
        {
            vertex.TexCoords = glm::vec2( 0.0f, 0.0f );
        }
            
        vertices.push_back( vertex );
    }
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);        
    }

    texture = Texture("Textures/brick.png", "", 0);
    // Return a mesh object created from the extracted mesh data
    return Mesh(vertices, indices, texture);
}

