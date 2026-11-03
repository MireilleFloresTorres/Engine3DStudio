#pragma once
#include "Engine/Prerequisites.h"

/**
 * @class DeviceContext
 * @brief Gestiona el contexto de dispositivo de Direct3D 11 para ejecutar operaciones gráficas.
 */
class
DeviceContext
{
public:

	//Constructor y desctructor de la clase 
	DeviceContext() = default;
	~DeviceContext();

	//Se inicializa el contexto
	void
	init();

	//Se liberan los recursos utilizados por el contexto
	void
	destroy();

	/**
	 * @brief Obtiene el puntero al contexto del dispositivo.
	 * @return Puntero al contexto de Direct3D 11.
	 */
	ID3D11DeviceContext*
		getDeviceContext() const noexcept
	{
		return m_deviceContext;
	}

	/**
	 * @brief Obtiene la dirección del puntero al contexto del dispositivo.
	 * @return Dirección del puntero al contexto de Direct3D 11.
	 */
	ID3D11DeviceContext**
		getDeviceContextAddress() noexcept
	{
		return &m_deviceContext;
	}

	/**
	 * @brief Obtiene una referencia al contexto del dispositivo.
	 * @return Referencia al contexto de Direct3D 11.
	 */
	ID3D11DeviceContext&
		requireContext() const noexcept;

	/**
	 * @brief Establece las áreas de visualización utilizadas para renderizar.
	 * @param NumViewports Cantidad de áreas de visualización.
	 * @param pViewports Arreglo con las descripciones de las áreas de visualización.
	 */
	void 
	RSSetViewports( unsigned int NumViewports,
					const D3D11_VIEWPORT* pViewports) noexcept;

	/**
	 * @brief Establece los destinos de renderizado y la vista de profundidad.
	 * @param NumViews Cantidad de vistas de destino de renderizado.
	 * @param ppRenderTargetViews Arreglo de punteros a las vistas de destino.
	 * @param pDepthStencilView Vista del búfer de profundidad y plantilla.
	 */
	void
	OMSetRenderTargets( unsigned int NumViews,
						ID3D11RenderTargetView* const* ppRenderTargetViews,
						ID3D11DepthStencilView* pDepthStencilView) noexcept;

	/**
	 * @brief Limpia un destino de renderizado con un color específico.
	 * @param pRenderTargetView Vista del destino de renderizado que se limpiará.
	 * @param ColorRGBA Arreglo con los componentes de color rojo, verde, azul y alfa.
	 */
	void 
	ClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView,
						  const float ColorRGBA[4]) noexcept;

	/**
	 * @brief Limpia los valores del búfer de profundidad y plantilla.
	 * @param pDepthStencilView Vista del búfer que se limpiará.
	 * @param ClearFlags Indicadores que especifican qué valores se limpiarán.
	 * @param Depth Valor con el que se inicializará la profundidad.
	 * @param Stencil Valor con el que se inicializará la plantilla.
	 */
	void 
	ClearDepthStencilView(ID3D11DepthStencilView* pDepthStencilView,
						  unsigned int ClearFlags,
						  float Depth,
						  unsigned int Stencil) noexcept;

	/**
	 * @brief Actualiza los datos de un recurso de Direct3D 11.
	 * @param pDstResource Recurso de destino que recibirá los datos.
	 * @param DstSubresource Índice del subrecurso que se actualizará.
	 * @param pDstBox Región del recurso que se actualizará, o nullptr para actualizar la región completa.
	 * @param pSrcData Puntero a los datos de origen.
	 * @param SrcRowPitch Cantidad de bytes que ocupa cada fila de los datos de origen.
	 * @param SrcDepthPitch Cantidad de bytes que ocupa cada sección de profundidad de los datos de origen.
	 */
	void 
	UpdateSubresource(ID3D11Resource* pDstResource,
					  unsigned int DstSubresource,
					  const D3D11_BOX* pDstBox,
					  const void* pSrcData,
					  unsigned int SrcRowPitch,
					  unsigned int SrcDepthPitch) noexcept;

	/**
	 * @brief Establece los búferes de vértices que se utilizarán en el renderizado.
	 * @param StartSlot Posición inicial donde se enlazarán los búferes.
	 * @param NumBuffers Cantidad de búferes que se enlazarán.
	 * @param ppVertexBuffers Arreglo de punteros a los búferes de vértices.
	 * @param pStrides Arreglo con el tamaño en bytes de cada vértice.
	 * @param pOffsets Arreglo con los desplazamientos iniciales en bytes de cada búfer.
	 */
	void 
	IASetVertexBuffers(unsigned int StartSlot,
					   unsigned int NumBuffers,
					   ID3D11Buffer* const* ppVertexBuffers,
					   const UINT* pStrides,
					   const UINT* pOffsets) noexcept;

	/**
	 * @brief Establece el búfer de índices que se utilizará para dibujar geometría.
	 * @param pIndexBuffer Puntero al búfer de índices.
	 * @param Format Formato de los índices almacenados.
	 * @param Offset Desplazamiento inicial en bytes dentro del búfer.
	 */
	void 
	IASetIndexBuffer(ID3D11Buffer* pIndexBuffer,
					 DXGI_FORMAT Format,
					 unsigned int Offset) noexcept;
	/**
	 * @brief Establece el diseño de entrada de los datos de los vértices.
	 * @param pInputLayout Puntero al diseño de entrada que se utilizará.
	 */
	void
	IASetInputLayout(ID3D11InputLayout* pInputLayout) noexcept;

	/**
	 * @brief Establece el tipo de primitivas que se utilizarán para dibujar.
	 * @param Topology Tipo de topología de las primitivas.
	 */
	void 
	IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology) noexcept;

	/**
	 * @brief Establece el estado de rasterización.
	 * @param pRasterizerState Estado de rasterización que se aplicará.
	 */
	void
	RSSetState(ID3D11RasterizerState* pRasterizerState) noexcept;

	/**
	 * @brief Establece el sombreador de vértices.
	 * @param pVertexShader Sombreador de vértices que se utilizará.
	 * @param ppClassInstances Arreglo de instancias de clases asociadas al sombreador, o nullptr si no se utilizan.
	 * @param NumClassInstances Cantidad de instancias de clases del arreglo.
	 */
	void
	VSSetShader(ID3D11VertexShader* pVertexShader,
				ID3D11ClassInstance* const* ppClassInstances = nullptr,
				unsigned int NumClassInstances = 0) noexcept;

	/**
	 * @brief Enlaza búferes de constantes al sombreador de vértices.
	 * @param StartSlot Posición inicial donde se enlazarán los búferes.
	 * @param NumBuffers Cantidad de búferes de constantes que se enlazarán.
	 * @param ppConstantBuffers Arreglo de punteros a los búferes de constantes.
	 */
	void
	VSSetConstantBuffers(unsigned int StartSlot,
						 unsigned int NumBuffers,
						 ID3D11Buffer* const* ppConstantBuffers) noexcept;

	/**
	 * @brief Establece el sombreador de píxeles.
	 * @param pPixelShader Sombreador de píxeles que se utilizará.
	 * @param ppClassInstances Arreglo de instancias de clases asociadas al sombreador, o nullptr si no se utilizan.
	 * @param NumClassInstances Cantidad de instancias de clases del arreglo.
	 */
	void
	PSSetShader(ID3D11PixelShader* pPixelShader,
				ID3D11ClassInstance* const* ppClassInstances = nullptr,
				unsigned int NumClassInstances = 0) noexcept;

	/**
	 * @brief Enlaza recursos de textura al sombreador de píxeles.
	 * @param StartSlot Posición inicial donde se enlazarán los recursos.
	 * @param NumViews Cantidad de vistas de recursos que se enlazarán.
	 * @param ppShaderResourceViews Arreglo de punteros a las vistas de recursos del sombreador.
	 */
	void
	PSSetShaderResources(unsigned int StartSlot,
						 unsigned int NumViews,
						 ID3D11ShaderResourceView* const* ppShaderResourceViews);
	/**
	 * @brief Dibuja geometría utilizando un búfer de índices.
	 * @param indexCount Cantidad de índices que se utilizarán para dibujar.
	 * @param startIndexLocation Posición del primer índice que se leerá del búfer.
	 * @param baseVertexLocation Desplazamiento que se aplicará a los índices de vértices.
	 */
	void
	DrawIndexed(unsigned int indexCount,
	unsigned int startIndexLocation = 0,
	int baseVertexLocation = 0) noexcept;

private: 

	//Puntero al contexto del dispositivo de Direct3D 11
	ID3D11DeviceContext* m_deviceContext = nullptr;
};