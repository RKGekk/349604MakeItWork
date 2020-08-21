#include "PixelConstantBufferPO.h"

PixelConstantBufferPO::PixelConstantBufferPO(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const cbPerObject& consts) : ConstantBufferPerObject(device, deviceContext, consts) {}

void PixelConstantBufferPO::Bind(ID3D11Device* device, ID3D11DeviceContext* deviceContext) {

	deviceContext->PSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());
}