#pragma once

#include <d3d11.h>
#include <wrl.h>

#include "Bindable.h"
#include "ConstantBufferPerObject.h"
#include "cbPerObject.h"
#include "memoryUtility.h"

class PixelConstantBufferPO : public ConstantBufferPerObject {
public:

	PixelConstantBufferPO(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const cbPerObject& consts);

	void Bind(ID3D11Device* device, ID3D11DeviceContext* deviceContext) override;
};