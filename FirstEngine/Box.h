#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include <vector>
#include <memory>

#include "Drawable.h"
#include "TextureClass.h"
#include "cbPerObject.h"

#include "Vertex.h"
#include "IndexedTriangleList.h"

#include "PixelConstantBufferPO.h"
#include "VertexConstantBufferPO.h"
#include "IndexBuffer.h"
#include "InputLayout.h"
#include "PixelShader.h"
#include "Topology.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "ShaderResource.h"
#include "CameraClass.h"
#include "DepthStencilState.h"
#include "RasterizerState.h"
#include "BlendState.h"

class Box : public Drawable {
public:
	Box(ID3D11Device* device, ID3D11DeviceContext* deviceContext, TextureClass* texture, CameraClass* cam);
	void Update(ID3D11Device* device, ID3D11DeviceContext* deviceContext, float dt, float tt) override;

private:

	VertexConstantBufferPO*	m_cbvs;
	CameraClass*			m_camera;
};