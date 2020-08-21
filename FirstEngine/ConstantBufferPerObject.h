#pragma once

#include <d3d11.h>
#include <wrl.h>

#include "Bindable.h"
#include "cbPerObject.h"
#include "memoryUtility.h"

class ConstantBufferPerObject : public Bindable {
public:

	ConstantBufferPerObject(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const cbPerObject& consts);
	ConstantBufferPerObject(ID3D11Device* device, ID3D11DeviceContext* deviceContext);

	void Update(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const cbPerObject& consts);

protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer;
};