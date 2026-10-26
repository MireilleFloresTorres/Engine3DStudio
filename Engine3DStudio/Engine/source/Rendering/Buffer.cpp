#include "Rendering/Buffer.h"
#include "Rendering/Device.h"
#include "Rendering/DeviceContext.h"

HRESULT
Buffer::init(Device& device, const MeshComponent& mesh, unsigned int bindFlag) {
	if (!device.getDevice()) {
		ERROR("Buffer", "init", "Device is null");
		return E_POINTER;
	}
	if ((bindFlag & D3D11_BIND_VERTEX_BUFFER) && mesh.m_vertex.empty()) {
		ERROR("Buffer", "init", "Vertex buffer is empty");
		return E_INVALIDARG;
	}
	if ((bindFlag & D3D11_BIND_INDEX_BUFFER) && mesh.m_index.empty()) {
		ERROR("Buffer", "init", "Index buffer is empty");
		return E_INVALIDARG;
	}

	D3D11_BUFFER_DESC desc = {};
	D3D11_SUBRESOURCE_DATA data = {};

	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.CPUAccessFlags = 0;
	m_bindFlag = (D3D11_BIND_FLAG)bindFlag;

	if (bindFlag & D3D11_BIND_VERTEX_BUFFER) {
		if (mesh.m_vertex.size() == 0) {

		}
		else {
			m_stride = sizeof(Vertex);
			desc.ByteWidth = m_stride * static_cast<unsigned int>(mesh.m_vertex.size());
			data.pSysMem = mesh.m_vertex.data();
		}
	}
	else if (bindFlag & D3D11_BIND_INDEX_BUFFER) {
		m_stride = sizeof(unsigned int); 
		desc.ByteWidth = m_stride * static_cast<unsigned int>(mesh.m_index.size()); 
		desc.BindFlags = (D3D11_BIND_FLAG)bindFlag; 
		data.pSysMem = mesh.m_index.data(); 
	}
	return createBuffer(device, desc, &data); 
}
