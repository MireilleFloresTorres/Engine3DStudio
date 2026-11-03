#pragma once
#include "Engine/Prerequisites.h"
#include "Engine/MeshComponent.h"

/**
 * @brief Declaración anticipada de la clase Device 
 * Y las clase DeviceContext, que se utilizan para la gestión 
 * de recursos gráficos y el contexto de renderizado en DirectX 11
 */
class Device;
class DeviceContext;

/**
 * @class Buffer
 * @brief Gestiona la creación, actualización, uso 
 * y liberación de búferes de Direct3D 11
 */
class
Buffer {
public:
    
    //Constrcutor y destructor de la clase 
    Buffer() = default;
    ~Buffer() = default;

    /**
     * @brief Inicializa un búfer a partir de los datos de una malla.
     * @param device Dispositivo utilizado para crear el búfer.
     * @param mesh Malla que proporciona los datos iniciales.
     * @param bindFlag Tipo de uso del búfer dentro de la canalización gráfica.
     * @return HRESULT que indica si la operación se realizó correctamente.
     */
    HRESULT
    init(Device& device, const MeshComponent& mesh, unsigned int bindFlag);

    /**
   * @brief Inicializa un búfer con un tamaño específico.
   * @param device Dispositivo utilizado para crear el búfer.
   * @param ByteWidth Tamaño del búfer en bytes.
   * @return HRESULT que indica si la operación se realizó correctamente.
   */
    HRESULT
    init(Device& device, unsigned int ByteWidth);


    /**
    * @brief Actualiza los datos de un recurso de Direct3D 11.
    * @param deviceContext Contexto utilizado para realizar la actualización.
    * @param pDstResource Recurso de destino que recibirá los datos.
    * @param DstSubresource Índice del subrecurso que se actualizará.
    * @param pDstBox Región del recurso que se actualizará, o nullptr para indicar la región completa.
    * @param pSrcData Puntero a los datos de origen.
    * @param SrcRowPitch Cantidad de bytes que ocupa cada fila de los datos de origen.
    * @param SrcDepthPitch Cantidad de bytes que ocupa cada sección de profundidad de los datos de origen.
    */
    void
    update(DeviceContext& deviceContext,
            ID3D11Resource* pDstResource,
            unsigned int    DstSubresource,
            const D3D11_BOX* pDstBox,
            const void* pSrcData,
            unsigned int    SrcRowPitch,
            unsigned int    SrcDepthPitch);

    /**
    * @brief Configura el búfer para su uso durante el renderizado.
    * @param deviceContext Contexto utilizado para configurar los recursos gráficos.
    * @param StartSlot Posición inicial donde se enlazará el búfer.
    * @param NumBuffers Cantidad de búferes que se enlazarán.
    * @param setPixelShader Indica si el búfer se configurará para el sombreador de píxeles.
    * @param format Formato de los datos, o DXGI_FORMAT_UNKNOWN para utilizar el formato predeterminado.
    */
    void
    render(DeviceContext& deviceContext,
            unsigned int   StartSlot,
            unsigned int   NumBuffers,
            bool           setPixelShader = false,
            DXGI_FORMAT    format = DXGI_FORMAT_UNKNOWN);

    //Libera los recursos
    void
    destroy();

    /**
    * @brief Crea un búfer de Direct3D 11.
    * @param device Dispositivo utilizado para crear el búfer.
    * @param desc Descripción que especifica las características del búfer.
    * @param initData Datos iniciales del búfer, o nullptr si no se proporcionan.
    * @return HRESULT que indica si la creación fue exitosa.
    */
    HRESULT
    createBuffer(Device& device,
            D3D11_BUFFER_DESC& desc,
            D3D11_SUBRESOURCE_DATA* initData);

    //Se obtiene el búfer y  se devuelve al puntero del búfer
    ID3D11Buffer* getBuffer() const { return m_buffer; }

public:
    //Puntero al búfer administrado por la clase 
    ID3D11Buffer* m_buffer = nullptr;
private:
    
    unsigned int m_stride = 0; //Tamaño en bytes de cada elemento del búfer

    unsigned int m_offset = 0; //Desplazamiento en bytes desde el inicio 

	unsigned int m_bindFlag = 0;//Indoca el tipo de uso del búfer dentro de la canalización gráfica
};