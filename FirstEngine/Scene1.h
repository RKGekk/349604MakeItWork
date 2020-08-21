#pragma once

#include <string>
#include <memory>
#include <d3d11.h>

#include "Scene.h"
#include "Sky.h"
#include "BoxObj.h"
#include "CameraClass.h"
#include "TextureHolder.h"
#include "TextureClass.h"
#include "Planet.h"
#include "MoonCrate.h"
#include "Ship.h"
#include "Clouds.h"
#include "C1.h"
#include "C2.h"
#include "C3.h"

class Scene1 : Scene {

public:
	Scene1(ID3D11Device* device, ID3D11DeviceContext* deviceContext);

	virtual void Update(ID3D11Device* device, ID3D11DeviceContext* deviceContext, InputClass& kbd, Mouse& mouse, float dt, float tt) override;
	virtual void Draw(ID3D11Device* device, ID3D11DeviceContext* deviceContext) override;

private:
	std::unique_ptr<Sky>			m_sky;
	//std::unique_ptr<BoxObj>			m_box;

	std::unique_ptr<Planet>			m_planet;
	DirectX::XMFLOAT4X4				m_platetMatrix;
	std::unique_ptr<Clouds>			m_clouds;
	DirectX::XMFLOAT4X4				m_cloudsMatrix;
	DirectX::XMFLOAT3				m_planetTrans;
	float							m_planetScale;

	std::unique_ptr<MoonCrate>		m_moon;
	DirectX::XMFLOAT4X4				m_moonMatrix;

	std::unique_ptr<Ship>			m_ship;
	DirectX::XMFLOAT4X4				m_shipMatrix;
	DirectX::XMFLOAT3				m_shipTrans;
	float							m_shipScale;

	std::unique_ptr<C1>				m_c1;
	DirectX::XMFLOAT4X4				m_c1Matrix;
	DirectX::XMFLOAT3				m_c1Trans;
	float							m_c1Scale;

	std::unique_ptr<C2>				m_c2;
	DirectX::XMFLOAT4X4				m_c2Matrix;
	DirectX::XMFLOAT3				m_c2Trans;
	float							m_c2Scale;

	std::unique_ptr<C3>				m_c3;
	DirectX::XMFLOAT4X4				m_c3Matrix;
	DirectX::XMFLOAT3				m_c3Trans;
	float							m_c3Scale;

	std::unique_ptr<CameraClass>	m_camera;

	Mouse::MouseTracker				m_MouseTracker;
};