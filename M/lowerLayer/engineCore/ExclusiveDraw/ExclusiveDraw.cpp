#include "ExclusiveDraw.h"
#include "../allPipelineSet/allPipelineSet.h"
#include "../allMesh/allMesh.h"
#include "../gpuResources/shaderBuffer/shaderBuffer.h"
#include "../BarrierControl/BarrierControl.h"

void ExclusiveDraw::ResetDrawIndex()
{
	auto* triangleMesh = allMesh->Getter_TriangleMesh();

	triangleMesh->DrawIndexReset();
}

void ExclusiveDraw::Init(AllPipelineSet* allPipelineSet_, AllMesh* allMesh_, std::vector<ShaderBuffer >* shaderBufferData_)
{
	allMesh = allMesh_;
	allPipelineSet = allPipelineSet_;
	shaderBufferData = shaderBufferData_;
}

void ExclusiveDraw::DrawMobileTriangle(VertexData& left_, VertexData& top_, VertexData& right_,
	Vector4 color_, int texHandle_, DrawMode drawMode_, BlendMode blendMode_ , CullMode cullMode_,
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

		float const i255 = V_Common::inv_255;
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
		auto* src_pipeline = allPipelineSet->Getter_pipelineSet(0, blendMode_, cullMode_);
		auto* cList = src_pipeline->Getter_CommandList();

		cList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		src_pipeline->SetGraphicsRootSignature();
		src_pipeline->SetPipelineState();

		//VBV
		cList->IASetVertexBuffers(0, 1, triangleMesh->Getter_VertexBufferView());

		cList->SetGraphicsRootDescriptorTable(0, (*shaderBufferData)[texHandle_].handleGPU);
		
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
