#include "Box.h"

Box::Box(ID3D11Device* device, ID3D11DeviceContext* deviceContext, TextureClass* texture, CameraClass* cam) : m_camera(cam) {

	constexpr float side = 1.0f / 2.0f;

	std::vector<DirectX::XMFLOAT4> vertices;
	vertices.emplace_back(-side, -side, -side, 1.0f); // 0
	vertices.emplace_back( side, -side, -side, 1.0f); // 1
	vertices.emplace_back(-side,  side, -side, 1.0f); // 2
	vertices.emplace_back( side,  side, -side, 1.0f); // 3
	vertices.emplace_back(-side, -side,  side, 1.0f); // 4
	vertices.emplace_back( side, -side,  side, 1.0f); // 5
	vertices.emplace_back(-side,  side,  side, 1.0f); // 6
	vertices.emplace_back( side,  side,  side, 1.0f); // 7

	std::vector<DirectX::XMFLOAT2> texs;
	texs.emplace_back(0.33f, 0.0f); // 0
	texs.emplace_back(0.66f, 0.0f); // 1
	texs.emplace_back(0.33f, 0.33f); // 2
	texs.emplace_back(0.66f, 0.33f); // 3
	texs.emplace_back(0.33f, 1.0f); // 4
	texs.emplace_back(0.66f, 1.0f); // 5
	texs.emplace_back(0.33f, 0.66f); // 6
	texs.emplace_back(0.66f, 0.66f); // 7

	std::vector<Vertex> verts(vertices.size());
	for (size_t i = 0; i < vertices.size(); i++) {
		verts[i].pos = vertices[i];
		verts[i].t = texs[i];
	}
	
	IndexedTriangleList model (
		std::move(verts),
		{	0,2,1, 2,3,1,
			1,3,5, 3,7,5,
			2,6,3, 3,6,7,
			4,5,7, 4,7,6,
			0,4,2, 2,4,6,
			0,1,4, 1,5,4
		}
	);

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

void Box::Update(ID3D11Device* device, ID3D11DeviceContext* deviceContext, float dt, float tt) {
	
	cbPerObject mt;
	DirectX::XMStoreFloat4x4(&mt.worldMatrix, DirectX::XMMatrixIdentity());
	mt.viewMatrix = m_camera->GetViewMatrix4x4T();
	mt.projectionMatrix = m_camera->GetProjectionMatix4x4T();
	m_cbvs->Update(device, deviceContext, mt);
}