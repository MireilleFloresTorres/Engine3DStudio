#pragma once

#include "API.h"
#include <cstdint>
#include <Windows.h>

/**
 * @brief Inicializa el motor
 * es hwnd Ventana donde se ejecutará el motor
 * @return true si la inicialización fue exitosa
 */
extern "C" {
	ENGINE_API bool
		Engine_Initialize(HWND hwnd, int width, int height) noexcept;

	/**
	 * @brief Actualiza el estado del motor.
	 */
	ENGINE_API void
		Engine_Update() noexcept;

	/**
	 * @brief Renderiza el contenido del motor.
	 */
	ENGINE_API void
		Engine_Render() noexcept;

	/**
	 * @brief Libera los recursos del motor.
	 */
	ENGINE_API void
		Engine_Shutdown() noexcept;

}

class ENGINE_API
	Engine final {
public:

	Engine() noexcept;

	/**
	 * @brief Construye una instancia del motor.
	 */
	~Engine() noexcept;

	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	Engine(const Engine&&) = delete;
	Engine& operator=(Engine&&) = delete;

	/**
	 * @brief Inicializa el motor.
	 * @param nativeWindow Ventana donde se ejecutará el motor
	 * @return true si la inicialización fue correcta 
	 */
	bool Initialize(
		void* nativeWindow,
		std::uint32_t width,
		std::uint32_t height
	) noexcept;

	/**
	 * @brief Renderiza el contenido del motor.
	 */
	void Render() noexcept;

	/**
	 * @brief Libera los recursos del motor.
	 */
	void Shutdown() noexcept;

private:
	struct Implementation;
	Implementation* m_implementation = nullptr;
};