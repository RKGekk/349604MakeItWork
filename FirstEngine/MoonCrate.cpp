#include "MoonCrate.h"

MoonCrate::MoonCrate(ID3D11Device* device, ID3D11DeviceContext* deviceContext, CameraClass* cam, DirectX::XMFLOAT4X4* world) : Drawable(world), m_camera(cam) {

	IndexedTriangleList model = IndexedTriangleList::LoadUVNormals("MoonCrate.obj");

	std::unique_ptr<VertexBuffer> vb = std::make_unique<VertexBuffer>(device, deviceContext, model.vertices);
	AddBind(std::move(vb));

	std::unique_ptr<IndexBuffer> ibuf = std::make_unique<IndexBuffer>(device, deviceContext, model.indices);
	AddIndexBuffer(std::move(ibuf));

	auto pvs = std::make_unique<VertexShader>(device, deviceContext, L"BasicNormalMapVertexShader.fx");
	ID3DBlob* pvsbc = pvs->GetBytecode();
	AddBind(std::move(pvs));

	auto pps = std::make_unique<PixelShader>(device, deviceContext, L"BasicNormalMapPixelShader.fx");
	ID3DBlob* ppsbc = pps->GetBytecode();
	AddBind(std::move(pps));

	std::unique_ptr<ShaderResource> srv0 = std::make_unique<ShaderResource>(device, deviceContext, TextureHolder::GetTexture("D.bmp").GetTexture());
	AddBind(std::move(srv0));

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
	DirectX::XMStoreFloat4x4(&mt.worldMatrix, DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(m_worldMatrix)));
	mt.viewMatrix = m_camera->GetViewMatrix4x4T();
	mt.projectionMatrix = m_camera->GetProjectionMatix4x4T();
	// Inverse-transpose is just applied to normals.  So zero out 
	// translation row so that it doesn't get into our inverse-transpose
	// calculation--we don't want the inverse-transpose of the translation.
	DirectX::XMMATRIX A = DirectX::XMLoadFloat4x4(m_worldMatrix);
	A.r[3] = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	DirectX::XMVECTOR det = DirectX::XMMatrixDeterminant(A);
	DirectX::XMStoreFloat4x4(&mt.worldInvTranspose, DirectX::XMMatrixInverse(&det, A));

	std::unique_ptr<VertexConstantBufferPO> cbvs = std::make_unique<VertexConstantBufferPO>(device, deviceContext, mt);
	m_cbvs = cbvs.get();
	AddBind(std::move(cbvs));

	std::unique_ptr<PixelConstantBufferPO> cbps0 = std::make_unique<PixelConstantBufferPO>(device, deviceContext, mt);
	m_cbps0 = cbps0.get();
	AddBind(std::move(cbps0));

	cbPerFrame lt;
	DirectionalLight dl;
	dl.Ambient = DirectX::XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	dl.Diffuse = DirectX::XMFLOAT4(0.9f, 0.9f, 0.9f, 1.0f);
	dl.Specular = DirectX::XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	dl.Direction = DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f);
	dl.Pad = 1.0f;
	lt.dirLight = dl;
	lt.eyePos = m_camera->GetPosition3f();

	std::unique_ptr<PixelConstantBufferPF> cbps1 = std::make_unique<PixelConstantBufferPF>(device, deviceContext, lt);
	m_cbps1 = cbps1.get();
	AddBind(std::move(cbps1));
}

void MoonCrate::Update(ID3D11Device* device, ID3D11DeviceContext* deviceContext, float dt, float tt) {

	cbPerObject mt;
	DirectX::XMStoreFloat4x4(&mt.worldMatrix, DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(m_worldMatrix)));
	mt.viewMatrix = m_camera->GetViewMatrix4x4T();
	mt.projectionMatrix = m_camera->GetProjectionMatix4x4T();
	// Inverse-transpose is just applied to normals.  So zero out 
	// translation row so that it doesn't get into our inverse-transpose
	// calculation--we don't want the inverse-transpose of the translation.
	DirectX::XMMATRIX A = DirectX::XMLoadFloat4x4(m_worldMatrix);
	A.r[3] = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	DirectX::XMVECTOR det = DirectX::XMMatrixDeterminant(A);
	DirectX::XMStoreFloat4x4(&mt.worldInvTranspose, DirectX::XMMatrixInverse(&det, A));
	m_cbvs->Update(device, deviceContext, mt);

	cbPerFrame lt;
	DirectionalLight dl;
	dl.Ambient = DirectX::XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	dl.Diffuse = DirectX::XMFLOAT4(0.9f, 0.9f, 0.9f, 1.0f);
	dl.Specular = DirectX::XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);

	//DirectX::XMFLOAT3 dir3f = DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f);
	//DirectX::XMVECTOR dir = DirectX::XMLoadFloat3(&dir3f);
	//DirectX::XMVECTOR rdir = DirectX::XMVector3Transform(dir, DirectX::XMMatrixRotationY(tt));
	//DirectX::XMStoreFloat3(&dir3f, rdir);

	//dl.Direction = dir3f;
	dl.Direction = DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f);
	lt.dirLight = dl;
	lt.eyePos = m_camera->GetPosition3f();
	m_cbps1->Update(device, deviceContext, lt);
}