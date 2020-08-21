#pragma once

#include <d3d11.h>
#include <wrl.h>

#include "Bindable.h"
#include "memoryUtility.h"

class SamplerState : public Bindable {
public:
	SamplerState(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	SamplerState(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const D3D11_SAMPLER_DESC& samplerDesc);
	void Bind(ID3D11Device* device, ID3D11DeviceContext* deviceContext) override;
protected:
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_sampleState;
};