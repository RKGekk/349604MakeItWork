#pragma once

#include "Bindable.h"
#include "ConstantBufferPerObject.h"
#include "cbPerObject.h"
#include "memoryUtility.h"

class VertexConstantBufferPO : public ConstantBufferPerObject {
public:

	VertexConstantBufferPO(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const cbPerObject& consts);

	void Bind(ID3D11Device* device, ID3D11DeviceContext* deviceContext) override;
};