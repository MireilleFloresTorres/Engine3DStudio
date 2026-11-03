#include "Rendering/Texture2D.h"
#include "Rendering/Device.h"
#include "Rendering/DeviceContext.h"

//Libera los recursos de la textura al destruir el objeto
Texture2D::~Texture2D() noexcept {
    destroy();
}

/**
 * @brief Inicializa una textura desde un archivo de imagen.
 * @param device Dispositivo de Direct3D.
 * @param fullPath Ruta del archivo.
 * @param texture Textura que se inicializará.
 * @return Resultado de la operación.
 */
HRESULT
Texture2D::InitTextureFromImage(Device& device,
    const std::string& fullPath,
    Texture2D& texture) {
    return S_OK;
}

/**
 * @brief Crea una textura con dimensiones y formato específicos.
 */
HRESULT Texture2D::init(Device& device,
    const std::string& textureName,
    ExtensionType extensionType) {
    if (!device.getDevice()) {
        ERROR("Texture", "init", "Device is null.");
        return E_POINTER;
    }
    if (textureName.empty()) {
        ERROR("Texture", "init", "Texture name cannot be empty.");
        return E_INVALIDARG;
    }

    HRESULT hr = S_OK;

    switch (extensionType) {
    case DDS:
        break;
    case PNG: {
        m_textureName = textureName + ".png";
        hr = InitTextureFromImage(device, m_textureName, *this);
        break;
    }
    case JPG: {
        m_textureName = textureName + ".jpg";
        hr = InitTextureFromImage(device, m_textureName, *this);
        break;
    }
    default:
        ERROR("Texture", "init", "Unsupported extension type");
        return E_INVALIDARG;
    }

    return hr;
}


HRESULT Texture2D::init(Device& device,
    unsigned int width,
    unsigned int height,
    DXGI_FORMAT Format,
    unsigned int BindFlags,
    unsigned int sampleCount,
    unsigned int qualityLevels) {
    if (!device.getDevice()) {
        ERROR("Texture", "init", "Device is null.");
        return E_POINTER;
    }
    if (width == 0 || height == 0) {
        ERROR("Texture", "init", "Width and height must be greater than 0.");
        return E_INVALIDARG;
    }

    D3D11_TEXTURE2D_DESC desc;
    memset(&desc, 0, sizeof(desc));
    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = Format;
    desc.SampleDesc.Count = sampleCount;
    desc.SampleDesc.Quality = qualityLevels;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = BindFlags;
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = 0;

    HRESULT hr = device.CreateTexture2D(&desc, nullptr, &m_texture);

    if (FAILED(hr)) {
        ERROR("Texture", "init",
            ("Failed to create texture with specified params. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }

    return S_OK;
}

/**
 * @brief Vincula la textura al shader de píxeles.
 */
void
Texture2D::render(DeviceContext& deviceContext,
    unsigned int StartSlot,
    unsigned int NumViews) {
    if (!deviceContext.getDeviceContext()) {
        ERROR("Texture", "render", "Device Context is null.");
        return;
    }

    if (m_textureFromImg) {
        deviceContext.PSSetShaderResources(StartSlot, NumViews, &m_textureFromImg);
    }
}

// Libera los recursos utilizados por la textura
void
Texture2D::destroy() {
    if (m_texture != nullptr) {
        SAFE_RELEASE(m_texture);
    }
    if (m_textureFromImg != nullptr) {
        SAFE_RELEASE(m_textureFromImg);
    }


}