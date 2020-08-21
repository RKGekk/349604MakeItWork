#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include <vector>
#include <memory>
#include <string>

#include "memoryUtility.h"

#include "Drawable.h"
#include "TextureClass.h"
#include "cbPerObject.h"
#include "cbPerFrame.h"

#include "Vertex.h"
#include "IndexedTriangleList.h"
#include "TextureHolder.h"

#include "PixelConstantBufferPO.h"
#include "VertexConstantBufferPO.h"
#include "PixelConstantBufferPF.h"
#include "VertexConstantBufferPF.h"
#include "IndexBuffer.h"
#include "InputLayout.h"
#include "PixelShader.h"
#include "Topology.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "ShaderResource.h"
#include "CameraClass.h"
#include "DDSTextureLoader.h"
#include "GeometryGenerator.h"
#include "DepthStencilState.h"
#include "RasterizerState.h"
#include "SamplerState.h"
#include "BlendState.h"

class Ship : public Drawable {
public:
	Ship(ID3D11Device* device, ID3D11DeviceContext* deviceContext, CameraClass* cam, DirectX::XMFLOAT4X4* world);
	void Update(ID3D11Device* device, ID3D11DeviceContext* deviceContext, float dt, float tt) override;

private:

	VertexConstantBufferPO* m_cbvs;
	PixelConstantBufferPF* m_cbps;
	CameraClass* m_camera;
};