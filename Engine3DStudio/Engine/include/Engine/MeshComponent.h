#pragma once
#include "Engine/Prerequisites.h"

/**
 * @class MeshComponent
 * @brief Representa un componente que almacena la información de una malla 3D
 *
 * Esta clase contiene el nombre de la malla, su matriz de transformación,
 * los vértices que la componen y los índices utilizados para definir
 * su geometría
 */

class
MeshComponent {
public:

	MeshComponent() : m_numVertex(0), m_numIndex(0) {}

public: 
	std::string m_name; 
	DirectX::XMFLOAT4X4 NAMED_PIPE_EVENT_GUID = DirectX::XMFLOAT4X4{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f };

	std::vector<Vertex> m_vertex; 

	std::vector<unsigned int> m_index; 
	int m_numVertex;
	int m_numIndex; 
};