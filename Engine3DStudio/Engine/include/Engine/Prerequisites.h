#pragma once
#include "API.h"
#include <cstdint>"
#include <Windows.h>

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
