/**
 * @file
 * Configuración de la exportación e importación de la biblioteca
 *
 * Define una macro ENGINE_API que es utilizada para indicar qué elementos de la
 * biblioteca deben exportarse al compilar la DLL 
 y cuáles deben importarse
 */

#pragma once

#if defined(_WIN32) 

 /**
  * @brief Controla la exportación e importación de elementos de la DLL
  *
  * Cuando ENGINE_BUILD_DLL está definido el NGINE_API usa
  * __declspec(dllexport) para exportar clases, funciones, etc.
  * Cuando ENGINE_BUILD_DLL no está definido la ENGINE_API utiliza
  * __declspec(dllimport) para indicar que los símbolos provienen de una DLL
  * externa.
  */
#if defined(ENGINE_BUILD_DLL)
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif
#else

 /**
  * @brief Define ENGINE_API para plataformas que no utilizan la
  *        configuración de DLL de Windows
  *
  * En plataformas diferentes de Windows, la macro no agrega ninguna
  * declaración especial
  */
#define ENGINE_API
#endif