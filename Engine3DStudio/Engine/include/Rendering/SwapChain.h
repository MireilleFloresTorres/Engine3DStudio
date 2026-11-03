#pragma once
#include "Engine/Prerequisites.h"

//Declaraciones anticipadas de las clases que se utilizan en SwapChain.h	
class Window;
class Device; 
class Texture2D; 

/**
 * @class SwapChain
 * @brief Gestiona la cadena de intercambio utilizada para presentar imágenes en pantalla.
 */
class
SwapChain {
public: 

	//Constrcutor y desttructor de la clase 
	SwapChain() = default; 
	~SwapChain(); 

	/**
	 * @brief Deshabilita el constructor de copia.
	 */
	SwapChain(const SwapChain&) = delete; 

	/**
	 * @brief Deshabilita el operador de asignación por movimiento.
	 */
	SwapChain& operator= (SwapChain&&) = delete; 

	/**
	 * @brief Inicializa la cadena de intercambio.
	 * @param device Dispositivo gráfico utilizado para crear la cadena.
	 * @param window Ventana donde se presentarán las imágenes.
	 * @param width Ancho de la cadena de intercambio en píxeles.
	 * @param height Alto de la cadena de intercambio en píxeles.
	 * @return HRESULT que indica si la inicialización se realizó correctamente.
	 */
	HRESULT
	init(Device device, Window window,
		 unsigned int width, unsigned int height); 

	//Destruye la cadena de intercambio y libera los recursos asociados
	void
	destroy(); 

	/**
	 * @brief Presenta el contenido renderizado en pantalla.
	 * @param syncInterval Intervalo de sincronización vertical utilizado al presentar la imagen.
	 * @param flag Indicadores adicionales para la presentación.
	 * @return HRESULT que indica si la operación se realizó correctamente.
	 */
	HRESULT
	Present(unsigned int syncInterval = 1,
			unsigned int flag = 0);

	/**
	 * @brief Obtiene un búfer de la cadena de intercambio.
	 * @param bufferIndex Índice del búfer que se desea obtener.
	 * @param backBuffer Objeto Texture2D que recibirá el búfer obtenido.
	 * @return HRESULT que indica si la operación se realizó correctamente.
	 */
	HRESULT
	GetBuffer(unsigned int bufferIndex,
			  Texture2D backBuffer);

	/**
	 * @brief Cambia el tamaño de los búferes de la cadena de intercambio.
	 * @param width Nuevo ancho de los búferes en píxeles.
	 * @param height Nuevo alto de los búferes en píxeles.
	 * @return HRESULT que indica si la operación se realizó correctamente.
	 */
	HRESULT
	ResizeBuffers(unsigned int width,
				  unsigned int height);

	/**
	 * @brief Obtiene el puntero a la cadena de intercambio.
	 * @return Puntero al objeto IDXGISwapChain.
	 */
	IDXGISwapChain*
		getSwapChain() { return m_swapChain; }

private: 

	//Puntero a la cadena de intercambio de DirectX
	IDXGISwapChain* m_swapChain = nullptr; 
};