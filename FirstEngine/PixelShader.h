#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include <string>
#include <fstream>

#include "Bindable.h"
#include "memoryUtility.h"

class PixelShader : public Bindable {
public:
	PixelShader(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const std::wstring& path);
	void Bind(ID3D11Device* device, ID3D11DeviceContext* deviceContext) override;
	ID3DBlob* GetBytecode() const;

protected:
	Microsoft::WRL::ComPtr<ID3DBlob> pBytecodeBlob;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;

	void OutputShaderErrorMessage(ID3D10Blob* errorMessage);
};