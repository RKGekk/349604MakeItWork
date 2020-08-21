#include "VertexConstantBufferPF.h"

VertexConstantBufferPF::VertexConstantBufferPF(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const cbPerFrame& consts) : ConstantBufferPerFrame(device, deviceContext, consts) {}

void VertexConstantBufferPF::Bind(ID3D11Device* device, ID3D11DeviceContext* deviceContext) {

	deviceContext->VSSetConstantBuffers(1u, 1u, pConstantBuffer.GetAddressOf());
}