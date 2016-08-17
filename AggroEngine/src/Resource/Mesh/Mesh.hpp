#pragma once

#include <memory>
using namespace std;

/**
 * Holds mesh data
 *
 * author: wcrane
 * since: 2014-01-25
**/
class Mesh
{
private:
	unsigned int m_nSizeOfVertices;
	unsigned int m_nSizeOfIndices;

	shared_ptr<float> m_npVertices;
	shared_ptr<float> m_npTexCoords;
	shared_ptr<float> m_npNormals;
	shared_ptr<int> m_npIndices;

public:
	Mesh(int nSizeOfVertices, int nSizeOfIndices, shared_ptr<float> npVertices, shared_ptr<float> npTexCoords, shared_ptr<float> npNormals, shared_ptr<int> npIndices);
	
	unsigned int getSizeOfVerticies();
	unsigned int getSizeOfIndicies();
	shared_ptr<float> getVerticies();
	shared_ptr<float> getTexCoords();
	shared_ptr<float> getNormals();
	shared_ptr<int> getIndicies();
};