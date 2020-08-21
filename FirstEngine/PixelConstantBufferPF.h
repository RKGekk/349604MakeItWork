#pragma once

#include <d3d11.h>
#include <wrl.h>

#include "Bindable.h"
#include "ConstantBufferPerFrame.h"
#include "cbPerFrame.h"
#include "memoryUtility.h"

class PixelConstantBufferPF : public ConstantBufferPerFrame {
public:

	PixelConstantBufferPF(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const cbPerFrame& consts);

	void Bind(ID3D11Device* device, ID3D11DeviceContext* deviceContext) override;
};