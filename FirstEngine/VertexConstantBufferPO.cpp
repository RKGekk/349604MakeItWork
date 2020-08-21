#include "VertexConstantBufferPO.h"

VertexConstantBufferPO::VertexConstantBufferPO(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const cbPerObject& consts) : ConstantBufferPerObject(device, deviceContext, consts) {
}

void VertexConstantBufferPO::Bind(ID3D11Device* device, ID3D11DeviceContext* deviceContext) {

	deviceContext->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());
}