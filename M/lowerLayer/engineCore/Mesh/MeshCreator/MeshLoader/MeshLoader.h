#pragma once
#include "../../meshStructure/ModelData/ModelData.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/cimport.h>

class MeshLoader
{
public:
    MeshLoader();
    ~MeshLoader();

    bool Load(
        const wchar_t* filename,
        std::vector<ResMesh>& meshes,
        std::vector<ResMaterial>& materials);

private:
    const aiScene* m_pScene = nullptr;   // シーンデータ.

    void ParseMesh(ResMesh& dstMesh, const aiMesh* pSrcMesh);
    void ParseMaterial(ResMaterial& dstMaterial, const aiMaterial* pSrcMaterial);
    std::wstring Convert(const aiString& path);
    std::string ToUTF8(const std::wstring& value);

};

inline bool LoadMesh
(
    const wchar_t* filename,
    std::vector<ResMesh>& meshes,
    std::vector<ResMaterial>& materials
)
{
    MeshLoader loader;
    return loader.Load(filename, meshes, materials);
}
