#pragma once
#include "Engine/Prerequisites.h"

//Declaraciones anticipadas de las clases que se utilizan en Texture2D.h
class Device; 
class DeviceContext;
class SwapChain; 

/**
 * @class Texture2D
 * @brief Gestiona texturas bidimensionales y recursos de textura de Direct3D 11.
 */
class
Texture2D {
public: 

	//Constructor y destructor de la clase Texture2D
	Texture2D() noexcept = default; 
	~Texture2D() noexcept; 

	//Deshabilita el constructor de copia
	Texture2D(const Texture2D&) = delete; 

	//Deshabilita el operador de aignación por copia
	Texture2D& operator=(const Texture2D&) = delete; 

	//Deshabilita el constructor de movimiento
	Texture2D(Texture2D&&) = delete; 

	//Deshabilita el operador de asignación por movimeinto
	Texture2D& operator= (Texture2D&&) = delete; 

	/**
	 * @brief Inicializa una textura a partir de su nombre y tipo de archivo.
	 * @param device Dispositivo de Direct3D 11 utilizado para crear la textura.
	 * @param textureName Nombre asignado a la textura.
	 * @param extensionType Tipo de extensión del archivo de textura.
	 * @return HRESULT que indica si la inicialización se realizó correctamente.
	 */
	HRESULT
	init(Device& device,
		 const std::string& textureName,
		 ExtensionType extensionType);

	/**
	 * @brief Inicializa una textura con dimensiones y características específicas.
	 * @param device Dispositivo utilizado para crear la textura.
	 * @param Format Formato de los datos de la textura.
	 * @param BindFlags Indicadores que definen cómo se utilizará la textura.
	 * @param sampleCOunt Cantidad de muestras por píxel.
	 * @param qualityLevels Nivel de calidad utilizado para el muestreo múltiple.
	 * @return HRESULT que indica si la inicialización se realizó correctamente.
	 */
	HRESULT
	init(Device& device, 
		unsigned int width, 
		unsigned int height, 
		DXGI_FORMAT Format, 
		unsigned int BindFlags,
		unsigned int sampleCOunt = 1,
		unsigned int qualityLevels = 0);

	/**
	 * @brief Carga una textura desde un archivo de imagen.
	 * @param device Dispositivo utilizado para crear la textura.
	 * @param fullPath Ruta completa del archivo de imagen.
	 * @param texture Objeto Texture2D donde se almacenará el resultado.
	 * @return HRESULT que indica si la operación se realizó correctamente.
	 */
	HRESULT
	InitTextureFromImage(Device& device,
						 const std::string& fullPath,
						 Texture2D& texture);


	/**
	 * @brief Inicializa una textura utilizando otra textura como referencia.
	 * @param Device Dispositivo utilizado para crear o configurar el recurso.
	 * @param textureRef Textura que se utilizará como referencia.
	 * @param format Formato de la textura resultante.
	 * @return HRESULT que indica si la operación se realizó correctamente.
	 */
	HRESULT
	init(Device& Device, Texture2D& textureRef, DXGI_FORMAT format);

	/**
	 * @brief Enlaza la textura para que pueda utilizarse durante el renderizado.
	 * @param deviceContext Contexto del dispositivo utilizado para configurar los recursos gráficos.
	 * @param StartSlot Posición inicial donde se enlazarán las vistas de recursos.
	 * @param NumViews Cantidad de vistas de recursos que se enlazarán.
	 */
	void
	render(DeviceContext& deviceContext, unsigned int StartSlot, unsigned int NumViews);

	//Libera los recursos utilizados por la textura
	void
	destroy();

	/**
	 * @brief Crea un mapa cúbico a partir de seis imágenes.
	 * @param device Dispositivo utilizado para crear el recurso.
	 * @param deviceContext Contexto utilizado para realizar operaciones sobre el recurso.
	 * @param facepaths Arreglo con las rutas de las seis caras del mapa cúbico.
	 * @param generateMips Indica si se deben generar niveles de mipmaps.
	 * @return HRESULT que indica si la operación se realizó correctamente.
	 */
	HRESULT
	CreateCubemap(Device& device,
				  DeviceContext& deviceContext,
				  const std::array<std::string, 6>& facepaths,
				  bool generateMips /*= false*/);

	/**
	 * @brief Crea una vista de recurso del sombreador para una cara del mapa cúbico.
	 * @param device Dispositivo de Direct3D 11 utilizado para crear la vista.
	 * @param cubemapTex Textura que representa el mapa cúbico.
	 * @param format Formato de los datos de la textura.
	 * @param faceIndex Índice de la cara del mapa cúbico.
	 * @param mipLevels Cantidad de niveles de mipmaps que incluirá la vista.
	 * @return Puntero a la vista de recurso creada, o nullptr si no se obtiene una vista válida.
	 */
	ID3D11ShaderResourceView*
	CreateCubemapFaceSRV(ID3D11Device* device,
						 ID3D11Texture2D* cubemapTex,
						 DXGI_FORMAT format,
						 unsigned int faceIndex,
						 unsigned int mipLevels = 1);

	/**
	 * @brief Obtiene el puntero a la textura bidimensional.
	 * Puntero al objeto ID3D11Texture2D.
	 */
	ID3D11Texture2D*
	GetTexture() const noexcept {
		return m_texture; 
	}

	/**
	 * @brief Obtiene la dirección del puntero a la textura bidimensional.
	 * @return Dirección del puntero al objeto ID3D11Texture2D.
	 */
	ID3D11Texture2D**
	GetTextureAddress() noexcept {
		return &m_texture; 
	}

public: 

	//Puntero a la t4extura bidimensional de Direct3D 11
	ID3D11Texture2D* m_texture = nullptr; 

	//Puntero a la vista de recurso del sombreador para la textura
	ID3D11ShaderResourceView* m_textureFromImg = nullptr;

	//Nombre de la textura 
	std::string m_textureName; 
};