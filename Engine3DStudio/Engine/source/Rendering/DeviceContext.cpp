#include "Rendering/DeviceContext.h"

/**
 * @brief Libera los recursos del contexto al destruir el objeto.
 */
DeviceContext::~DeviceContext()
{
	destroy();
}

/**
 * @brief Libera el contexto de Direct3D y sus recursos asociados.
 */
void
DeviceContext::destroy() {
	if (m_deviceContext) {
		m_deviceContext->ClearState();
		m_deviceContext->Release();
		SafeRelease(m_deviceContext);
	}
}

/**
 * @brief Obtiene una referencia al contexto de Direct3D.
 * @return Referencia al contexto inicializado.
 */
ID3D11DeviceContext&
DeviceContext::requireContext() const noexcept
{
	if (!m_deviceContext) {
		ERROR("DeviceContext", "RequireContext", "Device context is not initialized.");
	}

	return *m_deviceContext;
}

/**
 * @brief Limpia un objetivo de renderizado con un color específico.
 * @param pRenderTargetView Vista del objetivo de renderizado.
 * @param colorRGBA Arreglo con los componentes del color RGBA.
 */
void
DeviceContext::ClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView,
	const float colorRGBA[4]) noexcept {
	if (!pRenderTargetView || !colorRGBA) {
		ERROR("DeviceContext", "ClearRenderTargetView", "Invalid render target view or color parameters.");
		return;
	}

	requireContext().ClearRenderTargetView(pRenderTargetView, colorRGBA);
}

/**
 * @brief Limpia el búfer de profundidad y el búfer de plantilla.
 * @param pDepthStencilView Vista del búfer de profundidad y plantilla.
 */
void
DeviceContext::ClearDepthStencilView(ID3D11DepthStencilView* pDepthStencilView,
	unsigned int clearFlags,
	float depth,
	unsigned int stencil) noexcept {
	if (!pDepthStencilView) {
		ERROR("DeviceContext", "ClearDepthStencilView", "Invalid depth-stencil view parameter.");
		return;
	}

	requireContext().ClearDepthStencilView(pDepthStencilView, clearFlags, depth, stencil);
}

/**
 * @brief Establece los objetivos de renderizado y el búfer de profundidad.
 * @param numViews Cantidad de objetivos de renderizado.
 * @param ppRenderTargetViews Arreglo de vistas de los objetivos de renderizado.
 * @param pDepthStencilView Vista del búfer de profundidad y plantilla.
 */
void
DeviceContext::OMSetRenderTargets(unsigned int numViews,
	ID3D11RenderTargetView* const* ppRenderTargetViews,
	ID3D11DepthStencilView* pDepthStencilView) noexcept {
	if (!ppRenderTargetViews || numViews == 0) {
		ERROR("DeviceContext", "OMSetRenderTargets", "Invalid render target view parameters.");
		return;
	}

	requireContext().OMSetRenderTargets(numViews, ppRenderTargetViews, pDepthStencilView);
}

/**
 * @brief Establece las áreas de visualización utilizadas durante el renderizado.
 * @param numViewports Cantidad de áreas de visualización.
 * @param pViewports Arreglo con las configuraciones de las áreas de visualización.
 */
void
DeviceContext::RSSetViewports(unsigned int numViewports,
	const D3D11_VIEWPORT* pViewports) noexcept {
	if (!pViewports || numViewports == 0) {
		ERROR("DeviceContext", "RSSetViewports", "Invalid viewport parameters.");
		return;
	}
	requireContext().RSSetViewports(numViewports, pViewports);
}

/**
 * @brief Establece los recursos de textura que utilizará el shader de píxeles.
 * @param StartSlot Posición inicial de los recursos.
 * @param NumViews Cantidad de vistas de recursos.
 * @param ppShaderResourceViews Arreglo de vistas de recursos del shader.
 */
void
DeviceContext::PSSetShaderResources(unsigned int StartSlot,
	unsigned int NumViews,
	ID3D11ShaderResourceView* const* ppShaderResourceViews) {
	if (!ppShaderResourceViews || NumViews == 0) {
		ERROR("DeviceContext", "PSSetShaderResources", "Invalid shader resource view parameters.");
		return;
	}
	requireContext().PSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

/**
 * @brief Establece el estado de rasterización utilizado durante el renderizado.
 * @param pRasterizerState Estado de rasterización que se aplicará.
 */
void
DeviceContext::RSSetState(ID3D11RasterizerState* pRasterizerState) noexcept {
	if (!pRasterizerState) {
		ERROR("DeviceContext", "RSSetState", "Invalid rasterizer state parameter.");
		return;
	}
	requireContext().RSSetState(pRasterizerState);
}

/**
 * @brief Establece la distribución de los datos de entrada de los vértices.
 * @param pInputLayout Formato de entrada que se utilizará.
 */
void
DeviceContext::IASetInputLayout(ID3D11InputLayout* pInputLayout) noexcept {
	if (!pInputLayout) {
		ERROR("DeviceContext", "IASetInputLayout", "Invalid input layout parameter.");
		return;
	}
	requireContext().IASetInputLayout(pInputLayout);
}

/**
 * @brief Establece el tipo de primitivas que se utilizarán para dibujar.
 * @param topology Tipo de topología de las primitivas.
 */
void
DeviceContext::IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY topology) noexcept {
	requireContext().IASetPrimitiveTopology(topology);
}

/**
 * @brief Establece los búferes que contienen los datos de los vértices.
 * @param startSlot Posición inicial de los búferes.
 * @param numBuffers Cantidad de búferes de vértices.
 * @param ppVertexBuffers Arreglo de búferes de vértices.
 * @param pStrides Arreglo con el tamaño de cada vértice.
 * @param pOffsets Arreglo con los desplazamientos iniciales de los datos.
 */
void
DeviceContext::IASetVertexBuffers(unsigned int startSlot,
	unsigned int numBuffers,
	ID3D11Buffer* const* ppVertexBuffers,
	const unsigned int* pStrides,
	const unsigned int* pOffsets) noexcept {
	if (!ppVertexBuffers || numBuffers == 0) {
		ERROR("DeviceContext", "IASetVertexBuffers", "Invalid vertex buffer parameters.");
		return;
	}

	requireContext().IASetVertexBuffers(startSlot, numBuffers, ppVertexBuffers, pStrides, pOffsets);
}

/**
 * @brief Establece el búfer que contiene los índices de los vértices.
 */
void
DeviceContext::IASetIndexBuffer(ID3D11Buffer* pIndexBuffer,
	DXGI_FORMAT format,
	unsigned int offset) noexcept {
	if (!pIndexBuffer) {
		ERROR("DeviceContext", "IASetIndexBuffer", "Invalid index buffer parameter.");
		return;
	}

	requireContext().IASetIndexBuffer(pIndexBuffer, format, offset);
}

/**
 * @brief Establece el shader de vértices que se utilizará..
 */
void
DeviceContext::VSSetShader(ID3D11VertexShader* pVertexShader,
	ID3D11ClassInstance* const* ppClassInstances,
	unsigned int numClassInstances) noexcept {
	if (!pVertexShader) {
		ERROR("DeviceContext", "VSSetShader", "Invalid vertex shader parameter.");
		return;
	}
	requireContext().VSSetShader(pVertexShader, ppClassInstances, numClassInstances);
}

/**
 * @brief Establece el shader de píxeles que se utilizará.
 * @param pPixelShader Shader de píxeles.
 */
void
DeviceContext::PSSetShader(ID3D11PixelShader* pPixelShader,
	ID3D11ClassInstance* const* ppClassInstances,
	unsigned int numClassInstances) noexcept {
	if (!pPixelShader) {
		ERROR("DeviceContext", "PSSetShader", "Invalid pixel shader parameter.");
		return;
	}
	requireContext().PSSetShader(pPixelShader, ppClassInstances, numClassInstances);
}

/**
 * @brief Establece los búferes constantes utilizados por el shader de vértices.
 * @param startSlot Posición inicial de los búferes.
 * @param numBuffers Cantidad de búferes constantes.
 * @param ppConstantBuffers Arreglo de búferes constantes.
 */
void
DeviceContext::VSSetConstantBuffers(unsigned int startSlot,
	unsigned int numBuffers,
	ID3D11Buffer* const* ppConstantBuffers) noexcept {
	if (!ppConstantBuffers || numBuffers == 0) {
		ERROR("DeviceContext", "VSSetConstantBuffers", "Invalid constant buffer parameters.");
		return;
	}

	requireContext().VSSetConstantBuffers(startSlot, numBuffers, ppConstantBuffers);
}

/**
 * @brief Actualiza los datos almacenados en un recurso de Direct3D.
 */
void
DeviceContext::UpdateSubresource(ID3D11Resource* pDstResource,
	unsigned int dstSubresource,
	const D3D11_BOX* pDstBox,
	const void* pSrcData,
	unsigned int srcRowPitch,
	unsigned int srcDepthPitch) noexcept {
	if (!pDstResource || !pSrcData) {
		ERROR("DeviceContext", "UpdateSubresource", "Invalid destination resource or source data parameters.");
		return;
	}

	requireContext().UpdateSubresource(pDstResource, dstSubresource, pDstBox, pSrcData, srcRowPitch, srcDepthPitch);
}

/**
 * @brief Ejecuta el dibujo de primitivas mediante índices.
 * @param indexCount Cantidad de índices que se utilizarán.
 * @param startIndexLocation Posición inicial de los índices.
 * @param baseVertexLocation Desplazamiento aplicado a los índices de vértices.
 */
void
DeviceContext::DrawIndexed(unsigned int indexCount,
	unsigned int startIndexLocation,
	int baseVertexLocation) noexcept {
	if (indexCount == 0) {
		ERROR("DeviceContext", "DrawIndexed", "Index count must be greater than zero.");
		return;
	}

	requireContext().DrawIndexed(indexCount, startIndexLocation, baseVertexLocation);
}