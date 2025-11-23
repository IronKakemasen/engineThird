#include "M.h"

void M::DrawMTriangle(VertexData& left_, VertexData& top_, VertexData& right_,
	Vector4 color_, int texHandle_, DrawMode drawMode_, BlendMode blendMode_, CullMode cullMode_,
	Transform& trans_, UVTransform& uvTrans_, Matrix4& vpMat_)
{
	exclusiveDraw->DrawMobileTriangle(left_, top_, right_,
		color_, texHandle_, drawMode_, blendMode_, cullMode_,
		trans_, uvTrans_, vpMat_);
}


M* M::GetInstance()
{
	static M m;
	return &m;
}

int M::GetTexIndex(TextureTag tag_)
{
	return resourceContainer.GetTextureIndex(tag_);
}

void M::Init(TextureDataManager* textureDataManager_, ExclusiveDraw* exclusiveDraw_)
{
	if (initOnlyOnce)
	{
		resourceContainer.Init(textureDataManager_);
		exclusiveDraw = exclusiveDraw_;
	}

	initOnlyOnce = false;
}
