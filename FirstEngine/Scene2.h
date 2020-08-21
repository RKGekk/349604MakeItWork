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
#include "CryoRoom.h"
#include "CryoCapsule.h"
#include "RadioCamera.h"
#include "SpikeCamera.h"
#include "Bridge.h"
#include "Ring.h"
#include "SpikeRing.h"
#include "Sphere.h"

class Scene2 : Scene {

public:
	Scene2(ID3D11Device* device, ID3D11DeviceContext* deviceContext);

	virtual void Update(ID3D11Device* device, ID3D11DeviceContext* deviceContext, InputClass& kbd, Mouse& mouse, float dt, float tt) override;
	virtual void Draw(ID3D11Device* device, ID3D11DeviceContext* deviceContext) override;

private:

	std::unique_ptr<CryoRoom>		m_cryoRoom;
	DirectX::XMFLOAT4X4				m_cryoRoomMatrix;
	std::unique_ptr<CryoCapsule>	m_cryoCapsule;
	DirectX::XMFLOAT4X4				m_cryoCapsuleMatrix;

	std::unique_ptr<RadioCamera>	m_radioCamera;
	DirectX::XMFLOAT4X4				m_radioCameraMatrix;
	float							m_radioCameraScale;
	DirectX::XMFLOAT3				m_radioCameraTrans;

	std::unique_ptr<SpikeCamera>	m_spikeCamera;
	DirectX::XMFLOAT4X4				m_spikeCameraMatrix;
	float							m_spikeCameraScale;
	DirectX::XMFLOAT3				m_spikeCameraTrans;

	std::unique_ptr<Bridge>			m_bridge;
	DirectX::XMFLOAT4X4				m_bridgeMatrix;
	float							m_bridgeScale;
	DirectX::XMFLOAT3				m_bridgeTrans;

	std::unique_ptr<Ring>			m_ring1;
	DirectX::XMFLOAT4X4				m_ring1Matrix;
	float							m_ring1Scale;
	std::unique_ptr<Ring>			m_ring2;
	DirectX::XMFLOAT4X4				m_ring2Matrix;
	float							m_ring2Scale;
	DirectX::XMFLOAT3				m_ringTrans;
	std::unique_ptr<SpikeRing>		m_ring3;
	DirectX::XMFLOAT4X4				m_ring3Matrix;
	float							m_ring3Scale;

	std::unique_ptr<Sphere>			m_sphere;
	DirectX::XMFLOAT4X4				m_sphereMatrix;
	float							m_sphereScale;
	DirectX::XMFLOAT3				m_sphereTrans;
	
	std::unique_ptr<CameraClass>	m_camera;

	Mouse::MouseTracker				m_MouseTracker;
};
