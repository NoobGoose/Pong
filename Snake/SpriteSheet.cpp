#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(const wchar_t* filename, Graphics* gfx)
{
	//Init:
	this->gfx = gfx;
	bmp = NULL;
	HRESULT hr;

	//WIC factory
	IWICImagingFactory* wicFactory = NULL;
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&wicFactory);
	
	//Decoder
	IWICBitmapDecoder* wicDecoder = NULL;
	hr = wicFactory->CreateDecoderFromFilename(
		filename,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&wicDecoder);

	//Read Frame
	IWICBitmapFrameDecode* wicFrame = NULL;
	hr = wicDecoder->GetFrame(0, &wicFrame);

	//Create converter
	IWICFormatConverter* wicConverter = NULL;
	hr = wicFactory->CreateFormatConverter(&wicConverter);

	//Setup converter
	hr = wicConverter->Initialize(
		wicFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.0,
		WICBitmapPaletteTypeCustom
	);

	//Create D2D1Bitmap
	ID2D1Bitmap* bmp;
	gfx->GetRenderTarget()->CreateBitmapFromWicBitmap(
		wicConverter,
		NULL,
		&bmp
	);

	if (wicFactory)
		wicFactory->Release();
	if (wicDecoder)
		wicDecoder->Release();
	if (wicConverter)
		wicConverter->Release();
	if (wicFrame)
		wicFrame->Release();
}

SpriteSheet::~SpriteSheet()
{

}

void SpriteSheet::Draw()
{
	gfx->GetRenderTarget()->DrawBitmap(

		bmp,
		D2D1::RectF(
		0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height),
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(0.0f, 0.0f,
		bmp->GetSize().width, bmp->GetSize().height)
	);
}