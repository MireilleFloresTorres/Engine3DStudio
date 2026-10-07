#pragma once
#include <Engine/Prerequisites.h>

class
Device {
public: 
	Device() = default; 
	~Device(); 

	void
	init();

	void
	desctroy();

	HRESULT 
	CreateRenderTargetView( ID3D11Resource* pResource,
							const D3D11_RENDER_TARGET_VIEW_DESC* pDesc,
							ID3D11RenderTargetView** ppRTView);

	HRESULT  
	CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc,
		_In_reads_opt_(_Inexpressible_(pDesc->MipLevels* pDesc->ArraySize))  
					const D3D11_SUBRESOURCE_DATA* pInitialData,
					ID3D11Texture2D** ppTexture2D);

	HRESULT
	CreateVertexShader(_In_reads_(BytecodeLength)  const void* pShaderBytecode,
						SIZE_T BytecodeLength,
						ID3D11ClassLinkage* pClassLinkage,
						ID3D11VertexShader** ppVertexShader);

	HRESULT 
	CreatePixelShader( _In_reads_(BytecodeLength)  const void* pShaderBytecode,
						SIZE_T BytecodeLength,
						ID3D11ClassLinkage* pClassLinkage,
						ID3D11PixelShader** ppPixelShader);

	HRESULT
	CreateInputLayout(
	_In_reads_(NumElements)  const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
	_In_range_(0, D3D11_IA_VERTEX_INPUT_STRUCTURE_ELEMENT_COUNT)  UINT NumElements,
	_In_reads_(BytecodeLength)  const void* pShaderBytecodeWithInputSignature,
	SIZE_T BytecodeLength,
	ID3D11InputLayout** ppInputLayout);

	HRESULT
	CreateBuffer(	const D3D11_BUFFER_DESC* pDesc,
					const D3D11_SUBRESOURCE_DATA* pInitialData,
					ID3D11Buffer** ppBuffer);

	HRESULT
	CreateRasterizerState(const D3D11_RASTERIZER_DESC* pRasterizerDesc,
							ID3D11RasterizerState** ppRasterizerState);

	HRESULT 
	CreateDepthStencilView(ID3D11Resource* pResource,
							const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc,
							ID3D11DepthStencilView** ppDepthStencilView);

	private:
		ID3D11Device* m_device = nullptr;
		D3D_FEATURE_LEVEL featureLevels = D3D_FEATURE_LEVEL_11_0;
};
