#include "Scene1.h"

Scene1::Scene1(ID3D11Device* device, ID3D11DeviceContext* deviceContext) : Scene("First s") {

	//float aspect_ratio = 1.3333f;
	float aspect_ratio = 1.7777f;
	float hfov = 65.0f;
	float vfov = hfov / aspect_ratio;

	m_camera = std::make_unique<CameraClass>();
	m_camera->SetPosition(-25.0f, 1.5f, -25.0f);
	m_camera->Pitch(DirectX::XM_PI / 4.0f);
	m_camera->SetLens(DirectX::XMConvertToRadians(hfov), aspect_ratio, 0.1f, 1000.0f);
	m_camera->UpdateViewMatrix();

	std::wstring skyTexture = L"10.dds";
	m_sky = std::make_unique<Sky>(device, deviceContext, skyTexture, m_camera.get());

	//TextureClass& boxTexture = TextureHolder::GetTexture("stone01.tga");
	//m_box = std::make_unique<BoxObj>(device, deviceContext, &boxTexture, m_camera.get());

	m_planetTrans = DirectX::XMFLOAT3(0.0f, 100.0f, 100.0f);
	m_planetScale = 50.0f;
	DirectX::XMStoreFloat4x4(&m_platetMatrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixScaling(m_planetScale, m_planetScale, m_planetScale),  DirectX::XMMatrixMultiply(DirectX::XMMatrixIdentity(), DirectX::XMMatrixTranslation(m_planetTrans.x, m_planetTrans.y, m_planetTrans.z))));
	m_planet = std::make_unique<Planet>(device, deviceContext, m_camera.get(), &m_platetMatrix);

	DirectX::XMStoreFloat4x4(&m_cloudsMatrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixIdentity(), DirectX::XMMatrixTranslation(0.0f, 5.0f, 5.0f)));
	m_clouds = std::make_unique<Clouds>(device, deviceContext, m_camera.get(), &m_cloudsMatrix);

	DirectX::XMStoreFloat4x4(&m_moonMatrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixIdentity(), DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f)));
	m_moon = std::make_unique<MoonCrate>(device, deviceContext, m_camera.get(), &m_moonMatrix);


	m_shipTrans = DirectX::XMFLOAT3(10.0f, 10.0f, -60.0f);
	m_shipScale = 10.0f;
	DirectX::XMStoreFloat4x4(&m_shipMatrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixScaling(m_shipScale, m_shipScale, m_shipScale), DirectX::XMMatrixMultiply(DirectX::XMMatrixRotationY(DirectX::XM_PI), DirectX::XMMatrixTranslation(m_shipTrans.x, m_shipTrans.y, m_shipTrans.z))));
	//DirectX::XMStoreFloat4x4(&m_shipMatrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixIdentity(), DirectX::XMMatrixTranslation(0.0f, 10.0f, 0.0f)));
	m_ship = std::make_unique<Ship>(device, deviceContext, m_camera.get(), &m_shipMatrix);

	//float dist = 3.0f;
	//DirectX::XMVECTOR forwardXM = m_camera->GetLook();
	//DirectX::XMVECTOR posXM = DirectX::XMVectorAdd(DirectX::XMVectorScale(forwardXM, dist), m_camera->GetPosition());
	//DirectX::XMStoreFloat3(&m_c1Trans, posXM);
	m_c1Trans = DirectX::XMFLOAT3(-20.0f, 0.0f, -22.0f);
	m_c1Scale = 1.0f;
	DirectX::XMStoreFloat4x4(&m_c1Matrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixScaling(m_c1Scale, m_c1Scale, m_c1Scale), DirectX::XMMatrixTranslation(m_c1Trans.x, m_c1Trans.y, m_c1Trans.z)));
	//DirectX::XMStoreFloat4x4(&m_c1Matrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMMatrixIdentity(), DirectX::XMMatrixRotationZ(DirectX::XM_PI)), DirectX::XMMatrixTranslation(-25.0f, 1.5f, -24.0f)));
	//DirectX::XMStoreFloat4x4(&m_c1Matrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixIdentity(), DirectX::XMMatrixTranslation(-25.0f, 1.5f, -24.0f)));
	//DirectX::XMStoreFloat4x4(&m_shipMatrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixIdentity(), DirectX::XMMatrixTranslation(0.0f, 10.0f, 0.0f)));
	m_c1 = std::make_unique<C1>(device, deviceContext, m_camera.get(), &m_c1Matrix);

	m_c2Trans = DirectX::XMFLOAT3(-12.0f, 0.0f, -22.0f);
	m_c2Scale = 1.0f;
	DirectX::XMStoreFloat4x4(&m_c2Matrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixScaling(m_c2Scale, m_c2Scale, m_c2Scale), DirectX::XMMatrixTranslation(m_c2Trans.x, m_c2Trans.y, m_c2Trans.z)));
	m_c2 = std::make_unique<C2>(device, deviceContext, m_camera.get(), &m_c2Matrix);

	m_c3Trans = DirectX::XMFLOAT3(-6.0f, 0.0f, -22.0f);
	m_c3Scale = 1.0f;
	DirectX::XMStoreFloat4x4(&m_c3Matrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixScaling(m_c3Scale, m_c3Scale, m_c3Scale), DirectX::XMMatrixTranslation(m_c3Trans.x, m_c3Trans.y, m_c3Trans.z)));
	m_c3 = std::make_unique<C3>(device, deviceContext, m_camera.get(), &m_c3Matrix);
}

void Scene1::Update(ID3D11Device* device, ID3D11DeviceContext* deviceContext, InputClass& kbd, Mouse& mouse, float dt, float tt) {

	//m_camera->SetPosition(2.0f * DirectX::XMScalarCos(tt), 5.0f * DirectX::XMScalarSin(tt), -5.0f * DirectX::XMScalarCos(tt));
	//m_camera->Pitch(dt);
	//m_camera->RotateY(dt);

	//DirectX::XMStoreFloat4x4(&m_platetMatrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixIdentity(), DirectX::XMMatrixTranslation(0.0f, DirectX::XMScalarCos(tt), 0.0f)));
	//DirectX::XMStoreFloat4x4(&m_platetMatrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixIdentity(), DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f)));

	float fSpeed = 2.0f;

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

	DirectX::XMStoreFloat4x4(&m_cloudsMatrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixScaling(m_planetScale, m_planetScale, m_planetScale), DirectX::XMMatrixMultiply(DirectX::XMMatrixRotationY(tt * 0.025f), DirectX::XMMatrixTranslation(m_planetTrans.x, m_planetTrans.y, m_planetTrans.z))));


	static float rr = 1.0f;
	if (tt >= 15.0f && tt < 50.0f) {
		m_camera->RotateY((tt / 320.0f) * DirectX::XMScalarCos(tt * 64.0f) * (DirectX::XM_PI / 180.0f));
		m_camera->Walk((tt / 60.0f) * DirectX::XMScalarCos(tt * 64.0f) * (DirectX::XM_PI / 180.0f));
		DirectX::XMFLOAT3 cpos = m_camera->GetPosition3f();
		m_camera->SetPosition(cpos.x, cpos.y + (tt / 20.0f) * (DirectX::XMScalarCos(tt * 64.0f) * (DirectX::XM_PI / 180.0f)), cpos.z);
	}
	rr *= -1.0f; 
	
	if(tt >= 0.0f && tt < 20.0f) {
		m_camera->Strafe(fSpeed * dt);
	}
	
	if (tt >= 22.0f && tt <= 30.0f) {
		m_camera->Pitch(-1.0f * (dt * 8.0f * DirectX::XM_PI) / 180.0f);
	}
	
	if (tt >= 22.0f && tt <= 50.0f) {
		m_shipTrans.z += fSpeed * dt;
		DirectX::XMStoreFloat4x4(&m_shipMatrix, DirectX::XMMatrixMultiply(DirectX::XMMatrixScaling(m_shipScale, m_shipScale, m_shipScale), DirectX::XMMatrixMultiply(DirectX::XMMatrixRotationY(DirectX::XM_PI), DirectX::XMMatrixTranslation(m_shipTrans.x, m_shipTrans.y, m_shipTrans.z))));
	}

	m_camera->UpdateViewMatrix();
	m_sky->Update(device, deviceContext, dt, tt);
	m_planet->Update(device, deviceContext, dt, tt);
	m_clouds->Update(device, deviceContext, dt, tt);
	m_moon->Update(device, deviceContext, dt, tt);
	m_ship->Update(device, deviceContext, dt, tt);
	m_c1->Update(device, deviceContext, dt, tt);
	m_c2->Update(device, deviceContext, dt, tt);
	m_c3->Update(device, deviceContext, dt, tt);
}

void Scene1::Draw(ID3D11Device* device, ID3D11DeviceContext* deviceContext) {

	m_planet->Draw(device, deviceContext);
	m_clouds->Draw(device, deviceContext);
	m_moon->Draw(device, deviceContext);
	m_ship->Draw(device, deviceContext);
	m_sky->Draw(device, deviceContext);
	m_c1->Draw(device, deviceContext);
	m_c2->Draw(device, deviceContext);
	m_c3->Draw(device, deviceContext);
}
