#pragma once

#include "Bindable.h"
#include "ConstantBufferPerFrame.h"
#include "cbPerFrame.h"
#include "memoryUtility.h"

class VertexConstantBufferPF : public ConstantBufferPerFrame {
public:

	VertexConstantBufferPF(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const cbPerFrame& consts);

	void Bind(ID3D11Device* device, ID3D11DeviceContext* deviceContext) override;
};