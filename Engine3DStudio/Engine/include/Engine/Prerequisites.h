#pragma once
#include "API.h"
#include <cstdint>
#include <Windows.h>
#include <DirectXMath.h>
#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <sstream>
#include <cstddef>
#include <chrono>
#include <new>


/**
   * @brief Libera un recurso COM y establece su puntero en nullptr
   */
template<typename T>
void SafeRelease(T*& object) noexcept
{
	if (object != nullptr)
	{
		object->Release();
		object = nullptr;
	}
}


HWND window = nullptr;

std::uint32_t width = 0;

std::int32_t height = 0;

ID3D11Device* device = nullptr;

ID3D11DeviceContext* context = nullptr;

IDXGISwapChain* swapChain = nullptr;

ID3D11RenderTargetView* renderTarget = nullptr;

ID3D11Texture2D* depthStencilBuffer = nullptr;

ID3D11DepthStencilView* depthStencilView = nullptr;

ID3D11Buffer* vertexBuffer = nullptr;

ID3D11Buffer* indexBuffer = nullptr;

ID3D11Buffer* transformBuffer = nullptr;

ID3D11RasterizerState* rasterizerState = nullptr;

std::chrono::steady_clock::time_point startTime{};

ID3D11VertexShader* vertexShader = nullptr;
ID3D11PixelShader* pixelShader = nullptr;

ID3D11InputLayout* inputLayout = nullptr;

/**
 * @brief Libera un recurso COM y establece su puntero en nullptr
 */
#define SAFE_RELEASE(x) if(x != nullptr) x->Release(); x = nullptr;

 /**
  * @brief Registra un mensaje sobre la creación de un recurso
  */
#define MESSAGE( classObj, method, state )   \
{                                            \
   std::wostringstream os_;                  \
   os_ << classObj << "::" << method << " : " << "[CREATION OF RESOURCE " << ": " << state << "] \n"; \
   OutputDebugStringW( os_.str().c_str() );  \
}

  /**
   * @brief Registra un mensaje de error en la salida de depuración
   */
#define ERROR(classObj, method, errorMSG)                     \
{                                                             \
    try {                                                     \
        std::wostringstream os_;                              \
        os_ << L"ERROR : " << classObj << L"::" << method     \
            << L" : " << errorMSG << L"\n";                   \
        OutputDebugStringW(os_.str().c_str());                \
    } catch (...) {                                           \
        OutputDebugStringW(L"Failed to log error message.\n");\
    }                                                         \
}

/**
 * @brief Funciones principales para controlar el motor.
 */
extern "C" {

	/**
	 * @brief Inicializa el motor
	 *
	 * @param nativeWindow Ventana donde se ejecutará el motor.
	 * @param width Ancho de la ventana
	 * @param height Alto de la ventana
	 * @return true si la inicialización fue correcta y false lo contrario
	 */
	ENGINE_API bool
		engine_Initialize(HWND hwnd, int width, int height) noexcept;

	/**
	 * @brief Renderiza el contenido del motor
	 */
	ENGINE_API void
		Engine_Render() noexcept;

	/**
	 * @brief Actualiza el estado
	 */
	ENGINE_API void
		Engine_Update() noexcept;

	/**
	 * @brief Libera los recursos
	 */
	ENGINE_API void
		Engine_Shutdown() noexcept;
}
