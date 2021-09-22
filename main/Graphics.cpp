#include "Graphics.h"
#include "comdef.h"

Graphics::Graphics()
{
	factory = NULL; 
	DWriteFactory = NULL;
	renderTarget = NULL;
	brush = NULL;
}

Graphics::~Graphics()
{
	if (factory)
		factory->Release();
	if (renderTarget) 
		renderTarget->Release();
	if (brush)
		brush->Release();
}

bool Graphics::Init(HWND windowHandle)
{
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);

	if (res != S_OK) 
		return false;

	RECT rect;
	GetClientRect(windowHandle, &rect);

	res = factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)),
		&renderTarget);

	if (res != S_OK)
		return false;

	res = renderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &brush);

	if (res != S_OK)
		return false;

	//Direct Write
	res = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(DWriteFactory),
		reinterpret_cast<IUnknown**>(&DWriteFactory)
	);

	res = DWriteFactory->CreateTextFormat(
		L"Verdana",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		128,
		L"", //locale
		&textFormat128
	);

		textFormat128->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

		textFormat128->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

	return true;
}

void Graphics::renderCharacters(float x, float y, float r, float g, float b, float a, std::wstring textArg, unsigned int mode)
{

	static const WCHAR sc_helloWorld[] = L"Hello, World!";

	brush->SetColor(D2D1::ColorF(r, g, b, a));

	D2D1_SIZE_F renderTargetSize = renderTarget->GetSize();

	renderTarget->BeginDraw();

	renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	renderTarget->DrawText(
		textArg.data(),
		textArg.length(),
		textFormat128,
		D2D1::RectF(0, 0, renderTargetSize.width, renderTargetSize.height),
		brush
	);

	renderTarget->EndDraw();
}
void Graphics::ClearScreen(float r, float g, float b) 
{
	renderTarget->Clear(D2D1::ColorF(r, g, b));
}
void Graphics::DrawCircle(float x, float y, float radius, float r, float g, float b, float a) 
{
	brush->SetColor(D2D1::ColorF(r, g, b, a));
	renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush, 3.0f);
}

void Graphics::FillCircle(float x, float y, float radius, float r, float g, float b, float a) 
{
	brush->SetColor(D2D1::ColorF(r, g, b, a));
	renderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush);
}

void Graphics::FillRect(float x, float y, float length, float width, float r, float g, float b, float a)
{
	brush->SetColor(D2D1::ColorF(r, g, b, a));
	D2D1_RECT_F rect = D2D1::RectF(x, y, x + length, y + width);
	renderTarget->FillRectangle(rect, brush);
}
