#pragma once
#include "API.h"
#include <cstdint>"
#include <Windows.h>

/**
 * @brief Funciones principales para controlar el motor.
 */
extern "C" {

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
