#pragma once
#include "../../meshStructure/Vertex/Vertex.h"
#include <vector>
#include <string>

struct ResMaterial
{
    Vector3 diffuse;   
    Vector3 specular;
    float alpha{};
    float shininess{};
    std::wstring diffuseMap;    
    std::wstring specularMap; 
    std::wstring shininessMap; 
    std::wstring normalMap;   
};

struct ResMesh
{
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
    uint32_t materialId;   //!< マテリアル番号です.
};

