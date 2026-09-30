#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <Windows.h>

/**
 * @brief Gestiona la creación y control de una ventana de Windows
 * Aquí se crea, muestra, destruye y procesa los mensajes de la ventana
 * Ademas se registra la clase de la ventana
 */
class
	Window final {
public:

	//Crea una instancia de la ventana 
	Window() = default;

	//destruye la ventana y libera los recursos
	~Window();

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	/**
	 * @brief Registra la clase y crea la ventana.
	 *
	 * @param instance Instancia de la aplicación.
	 * @param tittle Título de la ventana.
	 * @param clientWidth Ancho del área de cliente.
	 * @param clientHeight Alto del área de cliente.
	 * @return true si la ventana fue creada correctamente.
	 */
	bool
		Create(HINSTANCE instance, const wchar_t* tittle,
			UINT clientWidth, UINT clientHeight) noexcept;

	//muestra la ventana con showCommand
	void
		Show(int showCommand) noexcept;

	//destruye la ventana
	void
		Destroy() noexcept;

	//Devuelve false cuando se recibe WM_QUIT.
	bool
		ProcessMessages() noexcept;

	//ibtiene el identificador de la ventana 
	HWND
		GetHandle() const noexcept;

	//para saber si la ventana está minimizada
	bool
		IsMinimized() const noexcept;

private:

	/**
	 * @brief Procesa los mensajes enviados a la ventana.
	 *
	 * @param handle Identificador de la ventana.
	 * @param message Mensaje recibido.
	 * @param aParam Parámetro adicional del mensaje.
	 * @param lParam Parámetro adicional del mensaje.
	 * @return Resultado del procesamiento del mensaje.
	 */
	static LRESULT CALLBACK
		WindowProcedure(HWND handle, UINT message,
			WPARAM aParam, LPARAM lParam);

	static constexpr const wchar_t* ClassName =
		L"SpiderEngineWindow";

	HINSTANCE m_instance = nullptr;
	HWND m_handle = nullptr;
	bool m_classRegistered = false;
};