#pragma once

#include <Windows.h>
#include <memory>

#include "D3DClass.h"
#include "EngineOptions.h"
#include "TextureHolder.h"
#include "TextureShaderClass.h"
#include "CameraClass.h"
#include "GameTimer.h"
#include "ModelClass.h"
#include "GDIPlusManager.h"
#include "Scene1.h"
#include "Scene2.h"

class GraphicsClass {
public:
	GraphicsClass(const EngineOptions& options);
	GraphicsClass(const GraphicsClass&) = delete;
	GraphicsClass& operator=(const GraphicsClass&) = delete;
	~GraphicsClass();

	bool Initialize(const EngineOptions& options, HWND hwnd);
	void Shutdown();

	void OnResize(const EngineOptions& options);

	void Update(InputClass& kbd, Mouse& mouse, const GameTimer&);
	bool Frame();
	void DrawIndexed(int count);

	float AspectRatio() const;

	std::shared_ptr<D3DClass>			GetD3D();
	std::shared_ptr<TextureHolder>		GetTexture();
	std::shared_ptr<CameraClass>		GetCamera();

	int GetWidth();
	int GetHeight();

private:
	bool Render();

	GDIPlusManager								gdipMan;

	std::shared_ptr<D3DClass>					m_Direct3D;
	std::shared_ptr<TextureHolder>				m_TextureHolder;

	std::unique_ptr<Scene1>						m_Scene1;
	std::unique_ptr<Scene2>						m_Scene2;
	int											m_sceneNumber;

	int											mClientWidth;
	int											mClientHeight;
};