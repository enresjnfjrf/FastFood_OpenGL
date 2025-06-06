#pragma once

#include "Mesh.h"
#include "Shader.h"
#include <vector>
#include <string>

class Model
{
private:
	std::vector<Texture> textures_loaded;
	std::vector<Mesh> meshes;
	std::string directory;
	bool gammaCorrection;

	void loadModel(std::string const& path, bool isUV_flipped);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTexture(aiMaterial* mat, aiTextureType type, std::string typeName);

public:
	Model(std::string path, bool isUV_flipped = true, bool gamma = false);
	void Draw(Shader* shader);
};

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);
