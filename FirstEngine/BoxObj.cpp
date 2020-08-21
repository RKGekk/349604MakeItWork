#include "BoxObj.h"

BoxObj::BoxObj(ID3D11Device* device, ID3D11DeviceContext* deviceContext, TextureClass* texture, CameraClass* cam) : m_camera(cam) {

	IndexedTriangleList model = IndexedTriangleList::LoadUVNormals("box1.obj");

	std::unique_ptr<VertexBuffer> vb = std::make_unique<VertexBuffer>(device, deviceContext, model.vertices);
	AddBind(std::move(vb));

	std::unique_ptr<IndexBuffer> ibuf = std::make_unique<IndexBuffer>(device, deviceContext, model.indices);
	AddIndexBuffer(std::move(ibuf));

	auto pvs = std::make_unique<VertexShader>(device, deviceContext, L"BasicTextureVertexShader.fx");
	ID3DBlob* pvsbc = pvs->GetBytecode();
	AddBind(std::move(pvs));

	auto pps = std::make_unique<PixelShader>(device, deviceContext, L"BasicTexturePixelShader.fx");
	ID3DBlob* ppsbc = pps->GetBytecode();
	AddBind(std::move(pps));

	std::unique_ptr<ShaderResource> srv = std::make_unique<ShaderResource>(device, deviceContext, texture->GetTexture());
	AddBind(std::move(srv));

	std::unique_ptr<InputLayout> inputLayout = std::make_unique<InputLayout>(device, deviceContext, pvsbc);
	AddBind(std::move(inputLayout));

	std::unique_ptr<Topology> topology = std::make_unique<Topology>(device, deviceContext, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	AddBind(std::move(topology));

	std::unique_ptr<SamplerState> samplerState = std::make_unique<SamplerState>(device, deviceContext);
	AddBind(std::move(samplerState));

	std::unique_ptr<DepthStencilState> depthStencilState = std::make_unique<DepthStencilState>(device, deviceContext);
	AddBind(std::move(depthStencilState));

	std::unique_ptr<RasterizerState> rasterizerState = std::make_unique<RasterizerState>(device, deviceContext);
	AddBind(std::move(rasterizerState));

	std::unique_ptr<BlendState> blendState = std::make_unique<BlendState>(device, deviceContext);
	AddBind(std::move(blendState));

	cbPerObject mt;
	DirectX::XMStoreFloat4x4(&mt.worldMatrix, DirectX::XMMatrixIdentity());
	mt.viewMatrix = m_camera->GetViewMatrix4x4T();
	mt.projectionMatrix = m_camera->GetProjectionMatix4x4T();

	std::unique_ptr<VertexConstantBufferPO> cbvs = std::make_unique<VertexConstantBufferPO>(device, deviceContext, mt);
	m_cbvs = cbvs.get();
	AddBind(std::move(cbvs));
}

void BoxObj::Update(ID3D11Device* device, ID3D11DeviceContext* deviceContext, float dt, float tt) {

	cbPerObject mt;
	DirectX::XMStoreFloat4x4(&mt.worldMatrix, DirectX::XMMatrixIdentity());
	mt.viewMatrix = m_camera->GetViewMatrix4x4T();
	mt.projectionMatrix = m_camera->GetProjectionMatix4x4T();
	m_cbvs->Update(device, deviceContext, mt);
}
