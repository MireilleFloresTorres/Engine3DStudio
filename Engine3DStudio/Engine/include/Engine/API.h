#pragma once

/**
 * @brief Controla la exportación e importación de elementos de la DLL.
 */
#if defined(_WIN32) 

#if defined(ENGINE_BUILD_DLL)
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif
#else

 /**
  * @brief Define ENGINE_API para plataformas que no utilizan la
  *        configuración de DLL de Windows.
  */
#define ENGINE_API
#endif