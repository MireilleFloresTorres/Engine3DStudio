#pragma once
#include "Engine/Prerequisites.h"

class
DeviceContext
{
public:
	DeviceContext() = default;
	~DeviceContext();

	void
	init();

	void
	destroy();

	ID3D11DeviceContext*
		getDeviceContext() const noexcept
	{
		return m_deviceContext;
	}

	ID3D11DeviceContext**
		getDeviceContextAddress() noexcept
	{
		return &m_deviceContext;
	}

	ID3D11DeviceContext&
		requireContext() const noexcept;


	void 
	RSSetViewports( unsigned int NumViewports,
					const D3D11_VIEWPORT* pViewports) noexcept;

	void
	OMSetRenderTargets( unsigned int NumViews,
						ID3D11RenderTargetView* const* ppRenderTargetViews,
						ID3D11DepthStencilView* pDepthStencilView) noexcept;
	void 
	ClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView,
						  const float ColorRGBA[4]) noexcept;

	void 
	ClearDepthStencilView(ID3D11DepthStencilView* pDepthStencilView,
						  unsigned int ClearFlags,
						  float Depth,
						  unsigned int Stencil) noexcept;
	void 
	UpdateSubresource(ID3D11Resource* pDstResource,
					  unsigned int DstSubresource,
					  const D3D11_BOX* pDstBox,
					  const void* pSrcData,
					  unsigned int SrcRowPitch,
					  unsigned int SrcDepthPitch) noexcept;

	void 
	IASetVertexBuffers(unsigned int StartSlot,
					   unsigned int NumBuffers,
					   ID3D11Buffer* const* ppVertexBuffers,
					   const UINT* pStrides,
					   const UINT* pOffsets) noexcept;
	void 
	IASetIndexBuffer(ID3D11Buffer* pIndexBuffer,
					 DXGI_FORMAT Format,
					 unsigned int Offset) noexcept;

	void
	IASetInputLayout(ID3D11InputLayout* pInputLayout) noexcept;

	void 
	IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology) noexcept;

	void
	RSSetState(ID3D11RasterizerState* pRasterizerState) noexcept;

	void
	VSSetShader(ID3D11VertexShader* pVertexShader,
				ID3D11ClassInstance* const* ppClassInstances = nullptr,
				unsigned int NumClassInstances = 0) noexcept;

	void
	VSSetConstantBuffers(unsigned int StartSlot,
						 unsigned int NumBuffers,
						 ID3D11Buffer* const* ppConstantBuffers) noexcept;

	void
	PSSetShader(ID3D11PixelShader* pPixelShader,
				ID3D11ClassInstance* const* ppClassInstances = nullptr,
				unsigned int NumClassInstances = 0) noexcept;
	void
	PSSetShaderResources(unsigned int StartSlot,
						 unsigned int NumViews,
						 ID3D11ShaderResourceView* const* ppShaderResourceViews);

	void
	DrawIndexed(unsigned int indexCount,
	unsigned int startIndexLocation = 0,
	int baseVertexLocation = 0) noexcept;

private: 
	ID3D11DeviceContext* m_deviceContext = nullptr;
};