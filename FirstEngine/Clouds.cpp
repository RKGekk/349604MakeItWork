#include "Clouds.h"

Clouds::Clouds(ID3D11Device* device, ID3D11DeviceContext* deviceContext, CameraClass* cam, DirectX::XMFLOAT4X4* world) : Drawable(world), m_camera(cam) {

	float cloudsRadius = 1.01f;

	GeometryGenerator::MeshData sphere;
	GeometryGenerator geoGen;
	geoGen.CreateSphere(cloudsRadius, 30, 30, sphere);

	std::vector<Vertex> verts(sphere.Vertices.size());
	for (size_t i = 0; i < sphere.Vertices.size(); i++) {
		verts[i].pos = DirectX::XMFLOAT4(sphere.Vertices[i].Position.x, sphere.Vertices[i].Position.y, sphere.Vertices[i].Position.z, 1.0f);
		verts[i].n = DirectX::XMFLOAT3(sphere.Vertices[i].Normal.x, sphere.Vertices[i].Normal.y, sphere.Vertices[i].Normal.z);
		verts[i].t = DirectX::XMFLOAT2(sphere.Vertices[i].TexC.x, sphere.Vertices[i].TexC.y);
		verts[i].tg = DirectX::XMFLOAT3(sphere.Vertices[i].TangentU.x, sphere.Vertices[i].TangentU.y, sphere.Vertices[i].TangentU.z);
	}

	std::vector<USHORT> indices16;
	indices16.assign(sphere.Indices.begin(), sphere.Indices.end());

	IndexedTriangleList model(
		std::move(verts),
		std::move(indices16)
	);

	std::unique_ptr<VertexBuffer> vb = std::make_unique<VertexBuffer>(device, deviceContext, model.vertices);
	AddBind(std::move(vb));

	std::unique_ptr<IndexBuffer> ibuf = std::make_unique<IndexBuffer>(device, deviceContext, model.indices);
	AddIndexBuffer(std::move(ibuf));

	auto pvs = std::make_unique<VertexShader>(device, deviceContext, L"AlphaPhongTextureVertexShader.fx");
	ID3DBlob* pvsbc = pvs->GetBytecode();
	AddBind(std::move(pvs));

	auto pps = std::make_unique<PixelShader>(device, deviceContext, L"AlphaPhongTexturePixelShader.fx");
	ID3DBlob* ppsbc = pps->GetBytecode();
	AddBind(std::move(pps));

	std::unique_ptr<ShaderResource> srv0 = std::make_unique<ShaderResource>(device, deviceContext, TextureHolder::GetTexture("2k_earth_clouds.bmp").GetTexture());
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

	D3D11_BLEND_DESC transparentDesc = { 0 };
	transparentDesc.AlphaToCoverageEnable = false;
	transparentDesc.IndependentBlendEnable = false;

	transparentDesc.RenderTarget[0].BlendEnable = true;
	transparentDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	transparentDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	transparentDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	transparentDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	transparentDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	transparentDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	transparentDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	std::unique_ptr<BlendState> blendState = std::make_unique<BlendState>(device, deviceContext, transparentDesc);
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

	cbPerFrame lt;
	DirectionalLight dl;
	dl.Ambient = DirectX::XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	dl.Diffuse = DirectX::XMFLOAT4(0.9f, 0.9f, 0.9f, 1.0f);
	dl.Specular = DirectX::XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	dl.Direction = DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f);
	dl.Pad = 1.0f;
	lt.dirLight = dl;
	lt.eyePos = m_camera->GetPosition3f();

	std::unique_ptr<PixelConstantBufferPF> cbps = std::make_unique<PixelConstantBufferPF>(device, deviceContext, lt);
	m_cbps = cbps.get();
	AddBind(std::move(cbps));
}

void Clouds::Update(ID3D11Device* device, ID3D11DeviceContext* deviceContext, float dt, float tt) {

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
	dl.Direction = DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f);
	lt.dirLight = dl;
	lt.eyePos = m_camera->GetPosition3f();
	m_cbps->Update(device, deviceContext, lt);
}