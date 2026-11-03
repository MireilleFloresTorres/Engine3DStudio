#pragma once
#include "Engine/Prerequisites.h"

/**
 * @class Device
 * @brief Gestiona el dispositivo de Direct3D 11 y la creación de recursos gráficos.
 */
class
Device {
public: 

	//Constrcutor y destrcutor de la clase Device
	Device() = default; 
	~Device(); 

	//Inicializa el dispositivo de Direct3D 11
	//y crea un contexto de dispositivo
	void
	init();

	//Libera los recursos 
	void
	destroy();

	/**
	 * @brief Obtiene el puntero al dispositivo de Direct3D 11.
	 * @return Puntero al dispositivo gráfico.
	 */
	ID3D11Device*
	getDevice() const noexcept
	{
		return m_device;
	}

	/**
	 * @brief Obtiene la dirección del puntero al dispositivo.
	 * @return Dirección del puntero al dispositivo de Direct3D 11.
	 */
	ID3D11Device**
	getDeviceAddress() noexcept
	{
		return &m_device;
	}

	/**
	 * @brief Crea una vista de renderizado a partir de un recurso.
	 * @param pResource Recurso que se utilizará para crear la vista.
	 * @param pDesc Descripción de la vista de renderizado.
	 * @param ppRTView Puntero donde se almacenará la vista creada.
	 * @return HRESULT que indica si la operación se realizó correctamente.
	 */
	HRESULT 
	CreateRenderTargetView( ID3D11Resource* pResource,
							const D3D11_RENDER_TARGET_VIEW_DESC* pDesc,
							ID3D11RenderTargetView** ppRTView);

	/**
	 * @brief Crea una textura bidimensional.
	 * @param pDesc Descripción de las características de la textura.
	 * @param pInitialData Datos iniciales de la textura, o nullptr si no se proporcionan.
	 * @param ppTexture2D Dirección donde se almacenará el puntero a la textura creada.
	 * @return HRESULT que indica si la operación se realizó correctamente.
	 */
	HRESULT  
	CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc,
		_In_reads_opt_(_Inexpressible_(pDesc->MipLevels* pDesc->ArraySize))  
					const D3D11_SUBRESOURCE_DATA* pInitialData,
					ID3D11Texture2D** ppTexture2D);

	/**
	 * @brief Crea un sombreador de vértices.
	 * @param pShaderBytecode Código compilado del sombreador.
	 * @param BytecodeLength Tamaño del código compilado en bytes.
	 * @param pClassLinkage Enlace de clases utilizado por el sombreador, o nullptr si no se necesita.
	 * @param ppVertexShader Dirección donde se almacenará el puntero al sombreador creado.
	 * @return HRESULT que indica si la operación se realizó correctamente.
	 */
	HRESULT
	CreateVertexShader(const void* pShaderBytecode,
					   unsigned int BytecodeLength,
					   ID3D11ClassLinkage* pClassLinkage,
					   ID3D11VertexShader** ppVertexShader);

	/**
	 * @brief Crea un sombreador de píxeles.
	 * @param pShaderBytecode Código compilado del sombreador.
	 * @param BytecodeLength Tamaño del código compilado en bytes.
	 * @param pClassLinkage Enlace de clases utilizado por el sombreador, o nullptr si no se necesita.
	 * @param ppPixelShader Dirección donde se almacenará el puntero al sombreador creado.
	 * @return HRESULT que indica si la operación se realizó correctamente.
	 */
	HRESULT
	CreatePixelShader(const void* pShaderBytecode,
					  unsigned int BytecodeLength,
					  ID3D11ClassLinkage* pClassLinkage,
					  ID3D11PixelShader** ppPixelShader);

	/**
	 * @brief Crea un diseño de entrada.
	 * @param pInputElementDescs Descripciones de los elementos de entrada.
	 * @param NumElements Número de elementos de entrada.
	 * @param pShaderBytecodeWithInputSignature Código compilado del sombreador con firma de entrada.
	 * @param BytecodeLength Tamaño del código compilado en bytes.
	 * @param ppInputLayout Dirección donde se almacenará el diseño de entrada creado.
	 * @return HRESULT que indica si la operación se realizó correctamente.
	 */
	HRESULT
	CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
					  unsigned int NumElements,
					  const void* pShaderBytecodeWithInputSignature,
					  unsigned int BytecodeLength,
					  ID3D11InputLayout** ppInputLayout);

	/**
	 * @brief Crea un búfer de Direct3D 11.
	 * @param pDesc Descripción de las características del búfer.
	 * @param pInitialData Datos iniciales del búfer, o nullptr si no se proporcionan.
	 * @param ppBuffer Dirección donde se almacenará el puntero al búfer creado.
	 * @return HRESULT que indica si la operación se realizó correctamente.
	 */
	HRESULT
	CreateBuffer(	const D3D11_BUFFER_DESC* pDesc,
					const D3D11_SUBRESOURCE_DATA* pInitialData,
					ID3D11Buffer** ppBuffer);

	/**
	 * @brief Crea un estado de rasterización.
	 * @param pRasterizerDesc Descripción de la configuración de rasterización.
	 * @param ppRasterizerState Dirección donde se almacenará el puntero al estado creado.
	 * @return HRESULT que indica si la operación se realizó correctamente.
	 */
	HRESULT
	CreateRasterizerState(const D3D11_RASTERIZER_DESC* pRasterizerDesc,
							ID3D11RasterizerState** ppRasterizerState);

	/**
	 * @brief Crea una vista de búfer de profundidad y plantilla.
	 * @param pResource Recurso que se utilizará para la vista.
	 * @param pDesc Descripción de la vista de profundidad y plantilla.
	 * @param ppDepthStencilView Dirección donde se almacenará el puntero a la vista creada.
	 * @return HRESULT que indica si la operación se realizó correctamente.
	 */
	HRESULT
	CreateDepthStencilView(ID3D11Resource* pResource,
						   D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc,
						   ID3D11DepthStencilView** ppDepthStencilView);

	private:

		//Puntero al dispositivo de Direct3D 11
		ID3D11Device* m_device = nullptr;

		//Nivel de características del dispositivo, se establece en D3D_FEATURE_LEVEL_11_0
		D3D_FEATURE_LEVEL featureLevels = D3D_FEATURE_LEVEL_11_0;
};
