#pragma once

#include <d3d11.h>
#include <wrl.h>

#include "Bindable.h"
#include "cbPerFrame.h"
#include "memoryUtility.h"

class ConstantBufferPerFrame : public Bindable {
public:

	ConstantBufferPerFrame(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const cbPerFrame& consts);
	ConstantBufferPerFrame(ID3D11Device* device, ID3D11DeviceContext* deviceContext);

	void Update(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const cbPerFrame& consts);

protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer;
};