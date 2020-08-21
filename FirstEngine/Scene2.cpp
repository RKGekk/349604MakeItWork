#include "Scene2.h"

Scene2::Scene2(ID3D11Device* device, ID3D11DeviceContext* deviceContext) : Scene("Second s") {

	//float aspect_ratio = 1.3333f;
	float aspect_ratio = 1.7777f;
	float hfov = 65.0f;
	float vfov = hfov / aspect_ratio;

	m_camera = std::make_unique<CameraClass>();
	m_camera->SetPosition(-2.0f, 0.0f, -1.0f);
	m_camera->Pitch(-DirectX::XM_PI / 16.0f);
	m_camera->RotateY(DirectX::XM_PI / 2.0f);
	m_camera->SetLens(DirectX::XMConvertToRadians(hfov), aspect_ratio, 0.1f, 1000.0f);
	m_camera->UpdateViewMatrix();

	DirectX::XMStoreFloat4x4(&m_cryoRoomMatrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixIdentity(), DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f)));
	m_cryoRoom = std::make_unique<CryoRoom>(device, deviceContext, m_camera.get(), &m_cryoRoomMatrix);

	DirectX::XMStoreFloat4x4(&m_cryoCapsuleMatrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixIdentity(), DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f)));
	m_cryoCapsule = std::make_unique<CryoCapsule>(device, deviceContext, m_camera.get(), &m_cryoCapsuleMatrix);

	m_radioCameraTrans = DirectX::XMFLOAT3(-9.5f, 0.0f, -38.0f);
	m_radioCameraScale = 3.0f;
	//DirectX::XMStoreFloat4x4(&m_radioCameraMatrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixIdentity(), DirectX::XMMatrixTranslation(m_radioCameraTrans.x, m_radioCameraTrans.y, m_radioCameraTrans.z)));
	DirectX::XMStoreFloat4x4(&m_radioCameraMatrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMMatrixScaling(m_radioCameraScale, m_radioCameraScale, m_radioCameraScale), DirectX::XMMatrixRotationX(DirectX::XM_PIDIV2)), DirectX::XMMatrixTranslation(m_radioCameraTrans.x, m_radioCameraTrans.y, m_radioCameraTrans.z)));
	m_radioCamera = std::make_unique<RadioCamera>(device, deviceContext, m_camera.get(), &m_radioCameraMatrix);

	m_spikeCameraTrans = DirectX::XMFLOAT3(-10.0f, 0.0f, -62.0f);
	m_spikeCameraScale = 0.8f;
	DirectX::XMStoreFloat4x4(&m_spikeCameraMatrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMMatrixScaling(m_spikeCameraScale, m_spikeCameraScale, m_spikeCameraScale), DirectX::XMMatrixRotationY(DirectX::XM_PIDIV2)), DirectX::XMMatrixTranslation(m_spikeCameraTrans.x, m_spikeCameraTrans.y, m_spikeCameraTrans.z)));
	m_spikeCamera = std::make_unique<SpikeCamera>(device, deviceContext, m_camera.get(), &m_spikeCameraMatrix);

	m_bridgeTrans = DirectX::XMFLOAT3(-9.0f, -1.4f, -58.0f);
	m_bridgeScale = 12.0f;
	DirectX::XMStoreFloat4x4(&m_bridgeMatrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMMatrixScaling(m_bridgeScale, m_bridgeScale, m_bridgeScale), DirectX::XMMatrixRotationX(DirectX::XM_PI)), DirectX::XMMatrixRotationY(DirectX::XM_PIDIV2 + DirectX::XM_PI / 18.0f)), DirectX::XMMatrixTranslation(m_bridgeTrans.x, m_bridgeTrans.y, m_bridgeTrans.z)));
	m_bridge = std::make_unique<Bridge>(device, deviceContext, m_camera.get(), &m_bridgeMatrix);

	m_ringTrans = DirectX::XMFLOAT3(-9.0f, 0.0f, -62.0f);
	m_ring1Scale = 4.0f;
	DirectX::XMStoreFloat4x4(&m_ring1Matrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMMatrixScaling(m_ring1Scale, m_ring1Scale, m_ring1Scale), DirectX::XMMatrixRotationX(DirectX::XM_PIDIV2)), DirectX::XMMatrixTranslation(m_ringTrans.x, m_ringTrans.y, m_ringTrans.z)));
	//DirectX::XMStoreFloat4x4(&m_ring1Matrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMMatrixScaling(m_ring1Scale, m_ring1Scale, m_ring1Scale), DirectX::XMMatrixRotationX(DirectX::XM_PI)), DirectX::XMMatrixRotationY(DirectX::XM_PIDIV2 + DirectX::XM_PI / 16.0f)), DirectX::XMMatrixTranslation(m_ring1Trans.x, m_ring1Trans.y, m_ring1Trans.z)));
	m_ring1 = std::make_unique<Ring>(device, deviceContext, m_camera.get(), &m_ring1Matrix);
	m_ring2Scale = m_ring1Scale * 0.9f;
	DirectX::XMStoreFloat4x4(&m_ring2Matrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMMatrixScaling(m_ring2Scale, m_ring2Scale, m_ring2Scale), DirectX::XMMatrixRotationX(DirectX::XM_PIDIV2)), DirectX::XMMatrixTranslation(m_ringTrans.x, m_ringTrans.y, m_ringTrans.z)));
	//DirectX::XMStoreFloat4x4(&m_ring1Matrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMMatrixScaling(m_ring1Scale, m_ring1Scale, m_ring1Scale), DirectX::XMMatrixRotationX(DirectX::XM_PI)), DirectX::XMMatrixRotationY(DirectX::XM_PIDIV2 + DirectX::XM_PI / 16.0f)), DirectX::XMMatrixTranslation(m_ring1Trans.x, m_ring1Trans.y, m_ring1Trans.z)));
	m_ring2 = std::make_unique<Ring>(device, deviceContext, m_camera.get(), &m_ring2Matrix);
	m_ring3Scale = m_ring1Scale;
	DirectX::XMStoreFloat4x4(&m_ring3Matrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMMatrixScaling(m_ring3Scale, m_ring3Scale, m_ring3Scale), DirectX::XMMatrixRotationX(DirectX::XM_PIDIV2)), DirectX::XMMatrixTranslation(m_ringTrans.x, m_ringTrans.y, m_ringTrans.z)));
	m_ring3 = std::make_unique<SpikeRing>(device, deviceContext, m_camera.get(), &m_ring3Matrix);

	m_sphereTrans = DirectX::XMFLOAT3(-9.0f, 0.0f, -62.0f);
	m_sphereScale = 3.0f;
	DirectX::XMStoreFloat4x4(&m_sphereMatrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMMatrixScaling(m_sphereScale, m_sphereScale, m_sphereScale), DirectX::XMMatrixRotationY(DirectX::XM_PIDIV2)), DirectX::XMMatrixTranslation(m_sphereTrans.x, m_sphereTrans.y, m_sphereTrans.z)));
	m_sphere = std::make_unique<Sphere>(device, deviceContext, m_camera.get(), &m_sphereMatrix);
}

void Scene2::Update(ID3D11Device* device, ID3D11DeviceContext* deviceContext, InputClass& kbd, Mouse& mouse, float dt, float tt) {

	tt -= 50.0f;

	//m_camera->SetPosition(2.0f * DirectX::XMScalarCos(tt), 5.0f * DirectX::XMScalarSin(tt), -5.0f * DirectX::XMScalarCos(tt));
	//m_camera->Pitch(dt);
	//m_camera->RotateY(dt);

	//DirectX::XMStoreFloat4x4(&m_platetMatrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixIdentity(), DirectX::XMMatrixTranslation(0.0f, DirectX::XMScalarCos(tt), 0.0f)));
	//DirectX::XMStoreFloat4x4(&m_platetMatrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixIdentity(), DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f)));

	float fSpeed = 4.0f;

	if (kbd.IsKeyDown(16)) {
		fSpeed = 16.0f;
	}
	if (kbd.IsKeyDown('W')) {
		m_camera->Walk(fSpeed * dt);
	}
	if (kbd.IsKeyDown('A')) {
		m_camera->Strafe(fSpeed * -dt);
	}
	if (kbd.IsKeyDown('S')) {
		m_camera->Walk(fSpeed * -dt);
	}
	if (kbd.IsKeyDown('D')) {
		m_camera->Strafe(fSpeed * dt);
	}

	while (!mouse.IsEmpty()) {
		const auto e = mouse.Read();
		switch (e.GetType()) {
			case Mouse::Event::Type::LPress:
			m_MouseTracker.Engage(e.GetPosX(), e.GetPosY());
			break;
			case Mouse::Event::Type::LRelease:
			m_MouseTracker.Release();
			break;
			case Mouse::Event::Type::Move:
			if (m_MouseTracker.Engaged()) {
				const auto delta = m_MouseTracker.Move(e.GetPosX(), e.GetPosY());
				m_camera->Pitch(1.0f * (((float)delta.y) * 0.5f * DirectX::XM_PI) / 180.0f);
				m_camera->RotateY(1.0f * (((float)delta.x) * 0.5f * DirectX::XM_PI) / 180.0f);
			}
			break;
		}
	}

	DirectX::XMStoreFloat4x4(&m_radioCameraMatrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMMatrixScaling(m_radioCameraScale, m_radioCameraScale, m_radioCameraScale), DirectX::XMMatrixRotationY(tt * 0.25f)), DirectX::XMMatrixRotationX(DirectX::XM_PIDIV2)), DirectX::XMMatrixTranslation(m_radioCameraTrans.x, m_radioCameraTrans.y, m_radioCameraTrans.z)));
	//DirectX::XMStoreFloat4x4(&m_radioCameraMatrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixScaling(m_radioCameraScale, m_radioCameraScale, m_radioCameraScale), DirectX::XMMatrixMultiply(DirectX::XMMatrixRotationY(tt * 0.25f), DirectX::XMMatrixTranslation(m_radioCameraTrans.x, m_radioCameraTrans.y, m_radioCameraTrans.z))));

	DirectX::XMStoreFloat4x4(&m_ring1Matrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMMatrixTranslation(0.0f, -0.125f, 0.0f), DirectX::XMMatrixScaling(m_ring1Scale, m_ring1Scale, m_ring1Scale)), DirectX::XMMatrixRotationX(DirectX::XM_PIDIV2)), DirectX::XMMatrixRotationY(tt * 0.25f)), DirectX::XMMatrixTranslation(m_ringTrans.x, m_ringTrans.y, m_ringTrans.z)));
	DirectX::XMStoreFloat4x4(&m_ring3Matrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMMatrixIdentity(), DirectX::XMMatrixScaling(m_ring3Scale, m_ring3Scale, m_ring3Scale)), DirectX::XMMatrixRotationX(DirectX::XM_PIDIV2)), DirectX::XMMatrixRotationY(tt * 0.25f)), DirectX::XMMatrixTranslation(m_ringTrans.x, m_ringTrans.y, m_ringTrans.z)));
	DirectX::XMStoreFloat4x4(&m_ring2Matrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMMatrixTranslation(0.0f, -0.125f, 0.0f), DirectX::XMMatrixScaling(m_ring2Scale, m_ring2Scale, m_ring2Scale)), DirectX::XMMatrixRotationX(DirectX::XM_PIDIV2)), DirectX::XMMatrixRotationX(tt * 0.25f)), DirectX::XMMatrixTranslation(m_ringTrans.x, m_ringTrans.y, m_ringTrans.z)));
	//DirectX::XMStoreFloat4x4(&m_ring1Matrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMMatrixIdentity(), DirectX::XMMatrixScaling(m_ring1Scale, m_ring1Scale, m_ring1Scale)), DirectX::XMMatrixRotationX(DirectX::XM_PIDIV2)), DirectX::XMMatrixRotationY(tt * 0.25f)), DirectX::XMMatrixTranslation(m_ringTrans.x, m_ringTrans.y, m_ringTrans.z)));
	//DirectX::XMStoreFloat4x4(&m_ring3Matrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMMatrixIdentity(), DirectX::XMMatrixScaling(m_ring1Scale, m_ring1Scale, m_ring1Scale)), DirectX::XMMatrixRotationX(DirectX::XM_PIDIV2)), DirectX::XMMatrixRotationY(tt * 0.25f)), DirectX::XMMatrixTranslation(m_ringTrans.x, m_ringTrans.y, m_ringTrans.z)));
	//DirectX::XMStoreFloat4x4(&m_ring2Matrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMMatrixIdentity(), DirectX::XMMatrixScaling(m_ring2Scale, m_ring2Scale, m_ring2Scale)), DirectX::XMMatrixRotationX(DirectX::XM_PIDIV2)), DirectX::XMMatrixRotationX(tt * 0.25f)), DirectX::XMMatrixTranslation(m_ringTrans.x, m_ringTrans.y, m_ringTrans.z)));
	//DirectX::XMStoreFloat4x4(&m_ring2Matrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMMatrixScaling(m_ring2Scale, m_ring2Scale, m_ring2Scale), DirectX::XMMatrixRotationZ(DirectX::XM_PIDIV2)), DirectX::XMMatrixRotationY(tt * 0.25f)), DirectX::XMMatrixRotationZ(tt * 0.25f)), DirectX::XMMatrixTranslation(m_ringTrans.x, m_ringTrans.y, m_ringTrans.z)));


	if (tt >= 0.0f && tt < 7.0f) {
		DirectX::XMFLOAT3 pos = m_camera->GetPosition3f();
		m_camera->SetPosition(pos.x - dt, pos.y, pos.z);
	}
	if (tt >= 7.0f && tt < 9.0f) {
		m_camera->RotateY(dt * DirectX::XM_PIDIV4);
	}
	if (tt >= 7.0f && tt < 12.0f) {
		DirectX::XMFLOAT3 pos = m_camera->GetPosition3f();
		m_camera->SetPosition(pos.x, pos.y, pos.z - dt * 10.0f);
	}

	m_camera->UpdateViewMatrix();
	m_cryoRoom->Update(device, deviceContext, dt, tt);
	m_cryoCapsule->Update(device, deviceContext, dt, tt);
	m_radioCamera->Update(device, deviceContext, dt, tt);
	m_spikeCamera->Update(device, deviceContext, dt, tt);
	m_bridge->Update(device, deviceContext, dt, tt);
	m_ring1->Update(device, deviceContext, dt, tt);
	m_ring2->Update(device, deviceContext, dt, tt);
	m_ring3->Update(device, deviceContext, dt, tt);
	m_sphere->Update(device, deviceContext, dt, tt);
}

void Scene2::Draw(ID3D11Device* device, ID3D11DeviceContext* deviceContext) {

	m_cryoRoom->Draw(device, deviceContext);
	m_cryoCapsule->Draw(device, deviceContext);
	m_radioCamera->Draw(device, deviceContext);
	m_spikeCamera->Draw(device, deviceContext);
	m_bridge->Draw(device, deviceContext);
	m_ring1->Draw(device, deviceContext);
	m_ring2->Draw(device, deviceContext);
	m_ring3->Draw(device, deviceContext);
	m_sphere->Draw(device, deviceContext);
}
