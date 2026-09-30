#pragma once

#include "API.h"
#include <cstdint>
#include <Windows.h>

/**
 * @brief Aquí las funciones de la API en el motor
 *
 * Las funciones permiten inicializar, actualizar, renderizar y
 * liberar los recursos del motor desde aplicaciones externas
 */
extern "C" {

	/**
	 * @brief Inicializa el motor
	 *
	 * Configura el motor utilizando la ventana y las dimensiones
	 * proporcionadas
	 *
	 * @param hwnd Identificador de la ventana del motor
	 * @param width Ancho de la ventana
	 * @param height Alto de la ventana
	 * @return true si la inicialización fue correcta yfalse lo contrario
	 */
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

/**
 * @brief Clase principal del motor gráfico
 *
 * Encapsula la inicialización, renderizado y liberación
 *  de los recursos utilizados
 */
class ENGINE_API
	Engine final {
public:

	/**
	 * @brief Construye una instancia del motor.
	 */
	Engine() noexcept;

	/**
	 * @brief Libera los recursos del motor-
	 */
	~Engine() noexcept;

	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	Engine(const Engine&&) = delete;
	Engine& operator=(Engine&&) = delete;

	/**
	 * @brief Inicializa el motor
	 *
	 * @param nativeWindow Ventana donde se ejecutará el motor.
	 * @param width Ancho de la ventana
	 * @param height Alto de la ventana
	 * @return true si la inicialización fue correcta yfalse lo contrario
	 */
	bool
		Initialize(
			void* nativeWindow,
			std::uint32_t width,
			std::uint32_t height
		) noexcept;

	/**
	 * @brief Renderiza el contenido del motor.
	 */
	void
		Render() noexcept;

	/**
	 * @brief Libera los recursos del motor.
	 */
	void
		Shutdown() noexcept;

private:

	/**
	 * @brief Implementación interna del motor
	 *
	 * Contiene los recursos y datos utilizados internamente por el motor
	 */
	struct
		Implementation;

	/**
	 * @brief Puntero a la implementación interna del motor
	 */
	Implementation* m_implementation = nullptr;
};