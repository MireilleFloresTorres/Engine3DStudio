#include "Rendering/Device.h"

HRESULT
Device::CreateRenderTargetView(ID3D11Resource* pResource,
	const D3D11_RENDER_TARGET_VIEW_DESC* pDesc,
	ID3D11RenderTargetView** ppRTView) {

	if (ppRTView == nullptr) {
		ERROR("Device", "CreateRenderTargetView", "Output Pointer is null.");
		return E_POINTER;
	}

	*ppRTView = nullptr;

	if (device == nullptr || pResource == nullptr) {
		ERROR("Device", "CreateRenderTargetView", "Device o Resource Pointer is null.");
		return E_INVALIDARG;
	}

	HRESULT result = m_device->CreateRenderTargetView(pResource, pDesc, ppRTView);

	if (FAILED(result)) {
		ERROR("Device",
			  "CreateRenderTargetView",
			  ("fAILED TO CREATE RENDER TARGET VIEW. HRESULT: " + std::to_string(result)).c_str());
		return result;
	}

	MESSAGE("Device", "CreateRenderTargetView", "SUCCES");
	return result; 
}
