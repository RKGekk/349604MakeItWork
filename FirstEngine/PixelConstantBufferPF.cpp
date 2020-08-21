#include "PixelConstantBufferPF.h"

PixelConstantBufferPF::PixelConstantBufferPF(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const cbPerFrame& consts) : ConstantBufferPerFrame(device, deviceContext, consts) {}

void PixelConstantBufferPF::Bind(ID3D11Device* device, ID3D11DeviceContext* deviceContext) {

	deviceContext->PSSetConstantBuffers(1u, 1u, pConstantBuffer.GetAddressOf());
}