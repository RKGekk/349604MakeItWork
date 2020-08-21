#include "VertexShader.h"

VertexShader::VertexShader(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const std::wstring& path) {

	// Initialize the pointers this function will use to null.
	Microsoft::WRL::ComPtr<ID3D10Blob> vertexErrorMessage;

	std::wstring fileExtension = path.substr(path.find_last_of(L".") + 1);
	std::transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(), ::toupper);

	if (fileExtension == L"FX") {

		HRESULT result = D3DCompileFromFile(
			path.c_str(),
			NULL,
			NULL,
			"TextureVertexShader",
			"vs_5_0",
			D3D10_SHADER_ENABLE_STRICTNESS,
			0,
			pBytecodeBlob.GetAddressOf(),
			vertexErrorMessage.GetAddressOf()
		);
		if (FAILED(result)) {
			// If the shader failed to compile it should have writen something to the error message.
			if (vertexErrorMessage) {
				OutputShaderErrorMessage(vertexErrorMessage.Get());
			}
			// If there was nothing in the error message then it simply could not find the shader file itself.
			else {
				ThrowIfFailed(result);
			}
		}
	}

	if (fileExtension == L"CSO") {
		ThrowIfFailed(
			D3DReadFileToBlob(path.c_str(), &pBytecodeBlob)
		);
	}

	ThrowIfFailed(
		device->CreateVertexShader(pBytecodeBlob->GetBufferPointer(), pBytecodeBlob->GetBufferSize(), nullptr, pVertexShader.GetAddressOf())
	);
}

void VertexShader::OutputShaderErrorMessage(ID3D10Blob* errorMessage) {
	char* compileErrors;
	unsigned long long bufferSize, i;
	std::ofstream fout;

	// Get a pointer to the error message text buffer.
	compileErrors = (char*)(errorMessage->GetBufferPointer());

	// Get the length of the message.
	bufferSize = errorMessage->GetBufferSize();

	// Open a file to write the error message to.
	fout.open("shader-error.txt");

	// Write out the error message.
	for (i = 0; i < bufferSize; i++) {
		fout << compileErrors[i];
	}

	// Close the file.
	fout.close();

	// Release the error message.
	errorMessage->Release();
	errorMessage = 0;

	// Pop a message up on the screen to notify the user to check the text file for compile errors.
	//MessageBox(hwnd, L"Error compiling shader.  Check shader-error.txt for message.", shaderFilename, MB_OK);

	return;
}

void VertexShader::Bind(ID3D11Device* device, ID3D11DeviceContext* deviceContext) {
	deviceContext->VSSetShader(pVertexShader.Get(), nullptr, 0u);
}

ID3DBlob* VertexShader::GetBytecode() const {
	return pBytecodeBlob.Get();
}
