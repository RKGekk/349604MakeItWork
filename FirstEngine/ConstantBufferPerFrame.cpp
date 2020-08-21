#include "ConstantBufferPerFrame.h"

ConstantBufferPerFrame::ConstantBufferPerFrame(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const cbPerFrame& consts) {

	D3D11_BUFFER_DESC cbd;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = sizeof(consts);
	cbd.StructureByteStride = 0u;

	D3D11_SUBRESOURCE_DATA csd = {};
	csd.pSysMem = &consts;
	ThrowIfFailed(
		device->CreateBuffer(&cbd, &csd, &pConstantBuffer)
	);
}

ConstantBufferPerFrame::ConstantBufferPerFrame(ID3D11Device* device, ID3D11DeviceContext* deviceContext) {

	D3D11_BUFFER_DESC cbd;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = sizeof(cbPerFrame);
	cbd.StructureByteStride = 0u;
	ThrowIfFailed(
		device->CreateBuffer(&cbd, nullptr, &pConstantBuffer)
	);
}

void ConstantBufferPerFrame::Update(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const cbPerFrame& consts) {

	D3D11_MAPPED_SUBRESOURCE msr;

	ThrowIfFailed(
		deviceContext->Map(pConstantBuffer.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &msr)
	);
	memcpy(msr.pData, &consts, sizeof(consts));
	deviceContext->Unmap(pConstantBuffer.Get(), 0u);
}