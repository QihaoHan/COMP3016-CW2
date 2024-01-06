/*
Model class
Used to handle internal logic in.obj files, generally a scene and multiple objects (which have hierarchical relationships between them)
And the meshes of each of these objects (these are stored in the same way in another structure, the corresponding mesh can be found through the mMeshes of the object aiNode []).
Initialization starts with the scene root object mRootNode and goes through all ainOdes with a depth-first search down
*/

#include "Model.h"

Model::Model(std::string path)
{
	loadModel(path);
}

Model::~Model() {}

void Model::Draw(Shader * shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++) {
		meshes[i].Draw(shader);
	}
}

void Model::loadModel(std::string path)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);		//scene, must be const
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "Assimp error." << std::endl;
		return;
	}
	directory = path.substr(0, path.find_last_not_of('\\'));
	std::cout << "Model loaded successfully!" << std::endl;
	std::cout << directory << std::endl;

	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode * node, const aiScene * scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh *curMesh = scene->mMeshes[node->mMeshes[i]];		//To convert to my own Mesh type, including uv values, Normal values, and so on
		meshes.push_back(processMesh(curMesh, scene));
	}

	std::cout << node->mName.data << std::endl;
	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh * mesh, const aiScene * scene)
{
	std::vector<Vertex> tempVertices;
	std::vector<unsigned int> tempIndices;
	std::vector<Texture> tempTexture;
	
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		Vertex tempVertex;
		
		tempVertex.Position.x = mesh->mVertices[i].x;
		tempVertex.Position.y = mesh->mVertices[i].y;
		tempVertex.Position.z = mesh->mVertices[i].z;
		
		tempVertex.Normal.x = mesh->mNormals[i].x;
		tempVertex.Normal.y = mesh->mNormals[i].y;
		tempVertex.Normal.z = mesh->mNormals[i].z;

		if (mesh->mTextureCoords[0]) {
			tempVertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
			tempVertex.TexCoords.y = mesh->mTextureCoords[0][i].y;
		}
		else {
			tempVertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}
		tempVertices.push_back(tempVertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; j++) {
			tempIndices.push_back(mesh->mFaces[i].mIndices[j]);
		}
	}

	return Mesh(tempVertices, tempIndices, {});
}
