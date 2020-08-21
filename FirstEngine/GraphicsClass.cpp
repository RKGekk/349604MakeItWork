#include "GraphicsClass.h"

#include "memoryUtility.h"

GraphicsClass::GraphicsClass(const EngineOptions& options) {
	m_Direct3D		= nullptr;
	m_TextureHolder	= nullptr;
}

GraphicsClass::~GraphicsClass() {}

bool GraphicsClass::Initialize(const EngineOptions& options, HWND hwnd) {
	bool result;

	mClientWidth = options.m_screenWidth;
	mClientHeight = options.m_screenHeight;

	// Create the Direct3D object.
	m_Direct3D = std::shared_ptr<D3DClass>(new D3DClass);
	if (!m_Direct3D) {
		return false;
	}

	// Initialize the Direct3D object.
	result = m_Direct3D->Initialize(options, hwnd);
	if (!result) {
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	m_TextureHolder = std::shared_ptr<TextureHolder>(new TextureHolder);
	if (!m_TextureHolder) {
		return false;
	}

	// Initialize the texture holder object.
	std::vector<std::string> textures{ "stone01.tga", "stone02.tga", "2k_earth_daymap.bmp", "2k_earth_specular_map.bmp", "2k_earth_normal_map.bmp", "D.bmp", "2k_earth_clouds.bmp", "greasy-metal-pan1-albedo.bmp", "greasy-metal-pan1-normal.bmp", "vented-metal-panel1_albedo.bmp", "vented-metal-panel1_normal-ogl.bmp", "metal-ventilation1-albedo.bmp", "metal-ventilation1-normal-ogl.bmp" };
	result = m_TextureHolder->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), textures);
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the textures.", L"Error", MB_OK);
		return false;
	}

	m_Scene1 = std::make_unique<Scene1>(GetD3D()->GetDevice(), GetD3D()->GetDeviceContext());
	m_Scene2 = std::make_unique<Scene2>(GetD3D()->GetDevice(), GetD3D()->GetDeviceContext());

	m_sceneNumber = 1;

	return true;
}

void GraphicsClass::Shutdown() {

	// Release the Direct3D object.
	if (m_Direct3D) {
		m_Direct3D->Shutdown();
	}

	return;
}

void GraphicsClass::OnResize(const EngineOptions& options) {

	mClientWidth = options.m_screenWidth;
	mClientHeight = options.m_screenHeight;

	m_Direct3D->OnResize(options);
}

void GraphicsClass::Update(InputClass& kbd, Mouse& mouse, const GameTimer& gt) {

	if(gt.TotalTime() <= 50.0f ) {
		m_sceneNumber = 1;
	}
	else {
		m_sceneNumber = 2;
	}

	if (m_sceneNumber == 1) {
		m_Scene1->Update(GetD3D()->GetDevice(), GetD3D()->GetDeviceContext(), kbd, mouse, gt.DeltaTime(), gt.TotalTime());
	}
	else {
		m_Scene2->Update(GetD3D()->GetDevice(), GetD3D()->GetDeviceContext(), kbd, mouse, gt.DeltaTime(), gt.TotalTime());
	}
}

bool GraphicsClass::Frame() {
	bool result;

	// Render the graphics scene.
	result = Render();
	if (!result) {
		return false;
	}

	return true;
}

void GraphicsClass::DrawIndexed(int count) {

	m_Direct3D->GetDeviceContext()->DrawIndexed(count, 0u, 0u);
}

float GraphicsClass::AspectRatio() const {
	return static_cast<float>(mClientWidth) / mClientHeight;
}

std::shared_ptr<D3DClass> GraphicsClass::GetD3D() {
	return m_Direct3D;
}

std::shared_ptr<TextureHolder> GraphicsClass::GetTexture() {
	return m_TextureHolder;
}

int GraphicsClass::GetWidth() {
	return mClientWidth;
}

int GraphicsClass::GetHeight() {
	return mClientHeight;
}

bool GraphicsClass::Render() {
	
	// Clear the buffers to begin the scene.
	//m_Direct3D->BeginScene(0.5f, 0.5f, 0.5f, 1.0f);
	m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	bool result;

	if (m_sceneNumber == 1) {
		m_Scene1->Draw(GetD3D()->GetDevice(), GetD3D()->GetDeviceContext());
	}
	else {
		m_Scene2->Draw(GetD3D()->GetDevice(), GetD3D()->GetDeviceContext());
	}

	// Present the rendered scene to the screen.
	m_Direct3D->EndScene();

	return true;
}
