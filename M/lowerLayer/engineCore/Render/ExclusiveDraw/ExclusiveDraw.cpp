#include "ExclusiveDraw.h"
#include "../../PSO/allPipelineSet.h"
#include "../../Mesh/allMesh/allMesh.h"
#include "../../Buffer/gpuResources/Data/ShaderBufferData/ShaderBufferData.h"
#include "../../Essential/BarrierControl/BarrierControl.h"

void ExclusiveDraw::ResetDrawIndexes()
{
	allMesh->ResetDrawIndexes();
}

void ExclusiveDraw::Init(AllPipelineSet* allPipelineSet_, AllMesh* allMesh_, ShaderBufferData* shaderBufferData_)
{
	allMesh = allMesh_;
	allPipelineSet = allPipelineSet_;
	shaderBufferData = shaderBufferData_;
}

void ExclusiveDraw::DrawMobileQuad(VertexData& leftTop_, VertexData& rightTop_, VertexData& rightBottom_, VertexData& leftBottom_,
	Vector4 color_, int texHandle_, DrawMode drawMode_, BlendMode blendMode_, CullMode cullMode_, int shaderSet_,
	Transform& trans_, UVTransform& uvTrans_, Matrix4& vpMat_)
{
	auto* quadMesh = allMesh->Getter_QuadMesh();

	quadMesh->DetectOverDrawing();

	if (drawMode_ == kSolid)
	{
		int i = quadMesh->cur_drawIndex;

		//使用する三角形のマップインデックス
		uint32_t const usingIndex_index = i * quadMesh->indexCnt;
		uint32_t const usingVertex_index = i * quadMesh->vertexCnt;

		VertexData vData[4] =
		{
			leftBottom_,leftTop_,rightBottom_,rightTop_
		};

		uint32_t indices[6] = { 0,1,2,2,1,3 };

		float const i255 = CommonV::inv_255;
		Vector4 color = { color_.x * i255,color_.y * i255,color_.z * i255,color_.w * i255 };

		//< データの入力 >
		//[ インデックス ]
		std::memcpy(&quadMesh->indexMap[usingIndex_index], indices, sizeof(uint32_t) * quadMesh->indexCnt);
		
		//[ 頂点 ]
		std::memcpy(&quadMesh->vertexMap[usingVertex_index], vData, sizeof(VertexData) * quadMesh->vertexCnt);
		
		//[ 行列 ]
		Matrix4 wMat = trans_.GetWorldMatrix();
		Matrix4 wvp = wMat.Multiply(vpMat_);
		*quadMesh->worldMatrixBuffer[i].matrix.buffMap = wMat;
		*quadMesh->wvpMatrixBuffer[i].matrix.buffMap = wvp;

		//[ マテリアル ]
		//色
		Matrix4 uvMat = uvTrans_.GetUVMat();
		quadMesh->materialBuffer[i].material.buffMap->color = color;
		quadMesh->materialBuffer[i].material.buffMap->uvTransform = uvMat;

		//< データの転送 >
		auto* src_pipeline = allPipelineSet->Getter_pipelineSet(shaderSet_, blendMode_, cullMode_);
		auto* cList = src_pipeline->Getter_CommandList();

		cList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		src_pipeline->SetGraphicsRootSignature();
		src_pipeline->SetPipelineState();

		//VBV
		cList->IASetVertexBuffers(0, 1, quadMesh->Getter_VertexBufferView());

		//IBV
		cList->IASetIndexBuffer(quadMesh->Getter_IndexBufferView());

		cList->SetGraphicsRootDescriptorTable(0, shaderBufferData->gpuHandleContainer[texHandle_]);

		//Cバッファの場所を指定
		src_pipeline->SetConstantBufferViews(
			quadMesh->worldMatrixBuffer[i].matrix.GetVirtualGPUAddress(),
			quadMesh->wvpMatrixBuffer[i].matrix.GetVirtualGPUAddress(),
			quadMesh->materialBuffer[i].material.GetVirtualGPUAddress());

		//描画(DrawCall)。6インデックスで一つのインスタンス
		cList->DrawIndexedInstanced(quadMesh->indexCnt, 1, static_cast<UINT>(usingIndex_index), static_cast<UINT>(usingVertex_index), 0);


		//次の描画用にインクリメント
		quadMesh->cur_drawIndex++;
	}
}

void ExclusiveDraw::DrawMobileTriangle(VertexData& left_, VertexData& top_, VertexData& right_,
	Vector4 color_, int texHandle_, DrawMode drawMode_, BlendMode blendMode_ , CullMode cullMode_, int shaderSet_,
	Transform& trans_, UVTransform& uvTrans_, Matrix4& vpMat_)
{
	if (drawMode_ == kSolid)
	{
		auto* triangleMesh = allMesh->Getter_TriangleMesh();

		triangleMesh->DetectOverDrawing();

		//使用する三角形のマップインデックス
		uint16_t i = triangleMesh->cur_drawIndex;
		uint32_t usingVertex_index = i * triangleMesh->vertexCnt;

		VertexData vData[3] =
		{
			left_,top_,right_
		};

		float const i255 = CommonV::inv_255;
		Vector4 color = { color_.x * i255,color_.y * i255,color_.z * i255,color_.w * i255 };

		//< データのコピー>
		//[ 頂点 ]
		std::memcpy(&triangleMesh->vertexMap[usingVertex_index], vData, sizeof(VertexData) * triangleMesh->vertexCnt);
		
		//[ 行列 ]
		Matrix4 wMat = trans_.GetWorldMatrix();
		Matrix4 wvp = wMat.Multiply(vpMat_);
		*triangleMesh->worldMatrixBuffer[i].matrix.buffMap = wMat;
		*triangleMesh->wvpMatrixBuffer[i].matrix.buffMap = wvp;
		
		//[ マテリアル ]
		//色
		Matrix4 uvMat = uvTrans_.GetUVMat();
		triangleMesh->materialBuffer[i].material.buffMap->color = color;
		triangleMesh->materialBuffer[i].material.buffMap->uvTransform = uvMat;

		//< データの転送 >
		//< 描画 >
		auto* src_pipeline = allPipelineSet->Getter_pipelineSet(shaderSet_, blendMode_, cullMode_);
		auto* cList = src_pipeline->Getter_CommandList();

		cList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		src_pipeline->SetGraphicsRootSignature();
		src_pipeline->SetPipelineState();

		//VBV
		cList->IASetVertexBuffers(0, 1, triangleMesh->Getter_VertexBufferView());

		cList->SetGraphicsRootDescriptorTable(0, shaderBufferData->gpuHandleContainer[texHandle_]);
		
		//Cバッファの場所を指定
		src_pipeline->SetConstantBufferViews(
			triangleMesh->worldMatrixBuffer[i].matrix.GetVirtualGPUAddress(),
			triangleMesh->wvpMatrixBuffer[i].matrix.GetVirtualGPUAddress(),
			triangleMesh->materialBuffer[i].material.GetVirtualGPUAddress());

		//描画(DrawCall)。3インデックスで一つのインスタンス
		cList->DrawInstanced(triangleMesh->vertexCnt, 1, static_cast<UINT>(usingVertex_index), 0);
		//次の三角形描画用にインクリメント
		triangleMesh->cur_drawIndex++;
	}

}

void ExclusiveDraw::DrawInstancingParticle2D(int numParticles_,Vector4 color_, int texHandle_, 
	BlendMode blendMode_, CullMode cullMode_, int shaderSet_,
	std::vector<Transform> trans_, UVTransform* uvTrans_, Matrix4* vpMat_)
{
	auto* pMesh = allMesh->Getter_TestParticleMesh();
	pMesh->DetectOverDrawing(numParticles_);

	//PSO
	auto* src_pipeline = allPipelineSet->Getter_pipelineSet(shaderSet_, blendMode_, cullMode_);
	auto* cList = src_pipeline->Getter_CommandList();
	
	cList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	src_pipeline->SetGraphicsRootSignature();
	src_pipeline->SetPipelineState();

	//VBV
	cList->IASetVertexBuffers(0, 1, pMesh->Getter_VertexBufferView());
	//IBV
	cList->IASetIndexBuffer(pMesh->Getter_IndexBufferView());

	//行列データの入力
	for (int i = 0; i < numParticles_; ++i)
	{
		pMesh->transformMatrixStructuredBuffer.matrix.buffMap[i].world = trans_[i].GetWorldMatrix();
		pMesh->transformMatrixStructuredBuffer.matrix.buffMap[i].wvp =
			pMesh->transformMatrixStructuredBuffer.matrix.buffMap[i].world.Multiply(*vpMat_);
	}

	//Material
	float const i255 = CommonV::inv_255;
	Vector4 color = { color_.x * i255,color_.y * i255,color_.z * i255,color_.w * i255 };
	pMesh->materialBuffer.material.buffMap->color = color;
	pMesh->materialBuffer.material.buffMap->uvTransform = uvTrans_->GetUVMat();

	//トランスフォーム
	cList->SetGraphicsRootDescriptorTable(0, shaderBufferData->gpuHandleContainer[pMesh->srvIndex]);
	//テクスチャ
	cList->SetGraphicsRootDescriptorTable(1, shaderBufferData->gpuHandleContainer[texHandle_]);
	//Cバッファの場所を指定
	cList->SetGraphicsRootConstantBufferView(2, pMesh->materialBuffer.material.GetVirtualGPUAddress());

	//DrawCall
	cList->DrawIndexedInstanced(pMesh->indexCnt, numParticles_, 0, 0,0);
}

