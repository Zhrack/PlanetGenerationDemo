#include "d3dApp.h"
#include "d3dx11Effect.h"
#include "GeometryGenerator.h"
#include "MathHelper.h"
#include "LightHelper.h"
#include "Effects.h"
#include "Vertex.h"
#include "RenderStates.h"
#include "Camera.h"

class PlanetApp : public D3DApp
{
public:
	PlanetApp(HINSTANCE hInstance);
	~PlanetApp();

	bool Init();
	void OnResize();
	void UpdateScene(float dt);
	void DrawScene();

	void OnMouseDown(WPARAM btnState, int x, int y);
	void OnMouseUp(WPARAM btnState, int x, int y);
	void OnMouseMove(WPARAM btnState, int x, int y);

private:
	DirectionalLight mDirLights[3];

	Camera mCam;

	bool mWalkCamMode;

	POINT mLastMousePos;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
	PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	PlanetApp theApp(hInstance);

	if (!theApp.Init())
		return 0;

	return theApp.Run();
}

PlanetApp::PlanetApp(HINSTANCE hInstance)
	: D3DApp(hInstance), mWalkCamMode(false)
{

}

PlanetApp::~PlanetApp()
{
	md3dImmediateContext->ClearState();

	//Effects::DestroyAll();
	//InputLayouts::DestroyAll();
	//RenderStates::DestroyAll();
}

bool PlanetApp::Init()
{
	if (!D3DApp::Init())
		return false;
	return true;
}

void PlanetApp::OnResize()
{
	D3DApp::OnResize();

	mCam.SetLens(0.25f*MathHelper::Pi, AspectRatio(), 1.0f, 3000.0f);
}

void PlanetApp::UpdateScene(float dt)
{

}

void PlanetApp::DrawScene()
{

}

void PlanetApp::OnMouseDown(WPARAM btnState, int x, int y)
{
	mLastMousePos.x = x;
	mLastMousePos.y = y;

	SetCapture(mhMainWnd);
}

void PlanetApp::OnMouseUp(WPARAM btnState, int x, int y)
{
	ReleaseCapture();
}

void PlanetApp::OnMouseMove(WPARAM btnState, int x, int y)
{
	if ((btnState & MK_LBUTTON) != 0)
	{
		// Make each pixel correspond to a quarter of a degree.
		float dx = XMConvertToRadians(0.25f*static_cast<float>(x - mLastMousePos.x));
		float dy = XMConvertToRadians(0.25f*static_cast<float>(y - mLastMousePos.y));

		mCam.Pitch(dy);
		mCam.RotateY(dx);
	}

	mLastMousePos.x = x;
	mLastMousePos.y = y;
}
