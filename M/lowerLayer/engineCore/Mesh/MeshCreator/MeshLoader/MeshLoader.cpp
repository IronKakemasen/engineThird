#include "MeshLoader.h"
#include <assert.h>
#include <Windows.h>

MeshLoader::MeshLoader()
    : m_pScene(nullptr)
{ 
}

MeshLoader::~MeshLoader()
{ 
}

std::string MeshLoader::ToUTF8(const std::wstring& value)
{
    auto length = WideCharToMultiByte(
        CP_UTF8, 0U, value.data(), -1, nullptr, 0, nullptr, nullptr);
    auto buffer = new char[length];

    WideCharToMultiByte(
        CP_UTF8, 0U, value.data(), -1, buffer, length, nullptr, nullptr);

    std::string result(buffer);
    delete[] buffer;
    buffer = nullptr;

    return result;
}

std::wstring MeshLoader::Convert(const aiString& path)
{
    wchar_t temp[256] = {};
    size_t  size;
    mbstowcs_s(&size, temp, path.C_Str(), 256);
    return std::wstring(temp);
}

bool MeshLoader::Load
(
    const wchar_t* filename,
    std::vector<ResMesh>& meshes,
    std::vector<ResMaterial>& materials
)
{
    if (filename == nullptr)
    {
        return false;
    }

    // wchar_t から char型(UTF-8)に変換します.
    auto path = ToUTF8(filename);

    Assimp::Importer importer;
    unsigned int flag = 0;
    flag |= aiProcess_Triangulate;
    flag |= aiProcess_PreTransformVertices;
    flag |= aiProcess_CalcTangentSpace;
    flag |= aiProcess_GenSmoothNormals;
    flag |= aiProcess_GenUVCoords;
    flag |= aiProcess_RemoveRedundantMaterials;
    flag |= aiProcess_OptimizeMeshes;

    // ファイルを読み込み.
    m_pScene = importer.ReadFile(path, flag);

    // チェック.
    if (m_pScene == nullptr)
    {
        return false;
    }

    // メッシュのメモリを確保.
    meshes.clear();
    meshes.resize(m_pScene->mNumMeshes);

    // メッシュデータを変換.
    for (size_t i = 0; i < meshes.size(); ++i)
    {
        const auto pMesh = m_pScene->mMeshes[i];
        ParseMesh(meshes[i], pMesh);
    }

    // マテリアルのメモリを確保.
    materials.clear();
    materials.resize(m_pScene->mNumMaterials);

    // マテリアルデータを変換.
    for (size_t i = 0; i < materials.size(); ++i)
    {
        const auto pMaterial = m_pScene->mMaterials[i];
        ParseMaterial(materials[i], pMaterial);
    }

    // 不要になったのでクリア.
    importer.FreeScene();
    m_pScene = nullptr;

    // 正常終了.
    return true;
}

void MeshLoader::ParseMesh(ResMesh& dstMesh, const aiMesh* pSrcMesh)
{
    // マテリアル番号を設定.
    dstMesh.materialId = pSrcMesh->mMaterialIndex;

    aiVector3D zero3D(0.0f, 0.0f, 0.0f);

    // 頂点データのメモリを確保.
    dstMesh.vertices.resize(pSrcMesh->mNumVertices);

    for (auto i = 0u; i < pSrcMesh->mNumVertices; ++i)
    {
        auto pPosition = &(pSrcMesh->mVertices[i]);
        auto pNormal = &(pSrcMesh->mNormals[i]);
        auto pTexCoord = (pSrcMesh->HasTextureCoords(0)) ? &(pSrcMesh->mTextureCoords[0][i]) : &zero3D;
        auto pTangent = (pSrcMesh->HasTangentsAndBitangents()) ? &(pSrcMesh->mTangents[i]) : &zero3D;

        dstMesh.vertices[i] = Vertex(
            Vector3(pPosition->x, pPosition->y, pPosition->z),
            Vector2(pTexCoord->x, pTexCoord->y),
            Vector3(pNormal->x, pNormal->y, pNormal->z),
            Vector3(pTangent->x, pTangent->y, pTangent->z)
        );
    }

    // 頂点インデックスのメモリを確保.
    dstMesh.indices.resize(pSrcMesh->mNumFaces * 3);

    for (auto i = 0u; i < pSrcMesh->mNumFaces; ++i)
    {
        const auto& face = pSrcMesh->mFaces[i];
        assert(face.mNumIndices == 3);  

        dstMesh.indices[i * 3 + 0] = face.mIndices[0];
        dstMesh.indices[i * 3 + 1] = face.mIndices[1];
        dstMesh.indices[i * 3 + 2] = face.mIndices[2];
    }
}

void MeshLoader::ParseMaterial(ResMaterial& dstMaterial, const aiMaterial* pSrcMaterial)
{
    // 拡散反射成分.
    {
        aiColor3D color(0.0f, 0.0f, 0.0f);

        if (pSrcMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS)
        {
            dstMaterial.diffuse.x = color.r;
            dstMaterial.diffuse.y = color.g;
            dstMaterial.diffuse.z = color.b;
        }
        else
        {
            dstMaterial.diffuse.x = 0.5f;
            dstMaterial.diffuse.y = 0.5f;
            dstMaterial.diffuse.z = 0.5f;
        }
    }

    // 鏡面反射成分.
    {
        aiColor3D color(0.0f, 0.0f, 0.0f);

        if (pSrcMaterial->Get(AI_MATKEY_COLOR_SPECULAR, color) == AI_SUCCESS)
        {
            dstMaterial.specular = { color.r,color.g,color.b };
        }
        else
        {
            dstMaterial.specular = { 0.0f,0.0f,0.0f };
        }
    }

    // 鏡面反射強度.
    {
        auto shininess = 0.0f;
        if (pSrcMaterial->Get(AI_MATKEY_SHININESS, shininess) == AI_SUCCESS)
        {
            dstMaterial.shininess = shininess;
        }
        else
        {
            dstMaterial.shininess = 0.0f;
        }
    }

    // ディフューズマップ.
    {
        aiString path;
        if (pSrcMaterial->Get(AI_MATKEY_TEXTURE_DIFFUSE(0), path) == AI_SUCCESS)
        {
            dstMaterial.diffuseMap = Convert(path);
        }
        else
        {
            dstMaterial.diffuseMap.clear();
        }
    }

    // スペキュラーマップ.
    {
        aiString path;
        if (pSrcMaterial->Get(AI_MATKEY_TEXTURE_SPECULAR(0), path) == AI_SUCCESS)
        {
            dstMaterial.specularMap = Convert(path);
        }
        else
        {
            dstMaterial.specularMap.clear();
        }
    }

    // シャイネスマップ.
    {
        aiString path;
        if (pSrcMaterial->Get(AI_MATKEY_TEXTURE_SHININESS(0), path) == AI_SUCCESS)
        {
            dstMaterial.shininessMap = Convert(path);
        }
        else
        {
            dstMaterial.shininessMap.clear();
        }
    }

    // 法線マップ
    {
        aiString path;
        if (pSrcMaterial->Get(AI_MATKEY_TEXTURE_NORMALS(0), path) == AI_SUCCESS)
        {
            dstMaterial.normalMap = Convert(path);
        }
        else
        {
            if (pSrcMaterial->Get(AI_MATKEY_TEXTURE_HEIGHT(0), path) == AI_SUCCESS)
            {
                dstMaterial.normalMap = Convert(path);
            }
            else
            {
                dstMaterial.normalMap.clear();
            }
        }
    }
}
