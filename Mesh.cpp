/**
 * Mesh.cpp
 */

#include "ArtemisBase.hpp"

ArtemisBase::Mesh::Mesh() {
	_numVertices = 0;
	_vertices = NULL;
	_normals = NULL;
	_texCoords = NULL;
}

ArtemisBase::Mesh::~Mesh() {
	if (_vertices != NULL)
		delete [] _vertices;
	_vertices = NULL;
	if (_normals != NULL)
		delete [] _normals;
	_normals = NULL;
	if (_texCoords != NULL)
		delete[] _texCoords;
	_texCoords = NULL;
}

bool ArtemisBase::Mesh::loadCube(float size) {
	// Loads vertices defining size x size x size tetrahedral, where size is the length of one side
	clear();
	size = size / 2.0f;
	
	// Set up each corner vertex
	ArtemisBase::Vertex vert0 = ArtemisBase::Vertex(-size, size, size);
	ArtemisBase::Vertex vert1 = ArtemisBase::Vertex(size, size, size);
	ArtemisBase::Vertex vert2 = ArtemisBase::Vertex(size, -size, size);
	ArtemisBase::Vertex vert3 = ArtemisBase::Vertex(-size, -size, size);
	ArtemisBase::Vertex vert4 = ArtemisBase::Vertex(size, size, -size);
	ArtemisBase::Vertex vert5 = ArtemisBase::Vertex(-size, size, -size);
	ArtemisBase::Vertex vert6 = ArtemisBase::Vertex(-size, -size, -size);
	ArtemisBase::Vertex vert7 = ArtemisBase::Vertex(size, -size, -size);
	
	// Create vertex arrays
	_numVertices = 36;
	_vertices = new ArtemisBase::Vertex[_numVertices];
	_vertices[0] = vert0; _vertices[1] = vert2; _vertices[2] = vert1; // Front face
	_vertices[3] = vert0; _vertices[4] = vert3; _vertices[5] = vert2;
	_vertices[6] = vert1; _vertices[7] = vert7; _vertices[8] = vert4; // Right face
	_vertices[9] = vert1; _vertices[10] = vert2; _vertices[11] = vert7;
	_vertices[12] = vert4; _vertices[13] = vert6; _vertices[14] = vert5; // Back face
	_vertices[15] = vert4; _vertices[16] = vert7; _vertices[17] = vert6;
	_vertices[18] = vert5; _vertices[19] = vert3; _vertices[20] = vert0; // Left face
	_vertices[21] = vert5; _vertices[22] = vert6; _vertices[23] = vert3;
	_vertices[24] = vert0; _vertices[25] = vert4; _vertices[26] = vert5; // Top face
	_vertices[27] = vert0; _vertices[28] = vert1; _vertices[29] = vert4;
	_vertices[30] = vert2; _vertices[31] = vert6; _vertices[32] = vert7; // Bottom face
	_vertices[33] = vert2; _vertices[34] = vert3; _vertices[35] = vert6;

	// Create texture coordinates
	_texCoords = new ArtemisBase::TexCoord[_numVertices];
	for (int i = 0; i < _numVertices; i++) {
		int offset = i % 6;
		switch(offset) {
			case 0:
				_texCoords[i].u = 0.0f;
				_texCoords[i].v = 1.0f;
				break;
			case 1:
				_texCoords[i].u = 1.0f;
				_texCoords[i].v = 0.0f;
				break;
			case 2:
				_texCoords[i].u = 1.0f;
				_texCoords[i].v = 1.0f;
				break;
			case 3:
				_texCoords[i].u = 0.0f;
				_texCoords[i].v = 1.0f;
				break;
			case 4:
				_texCoords[i].u = 0.0f;
				_texCoords[i].v = 0.0f;
				break;
			case 5:
				_texCoords[i].u = 1.0f;
				_texCoords[i].v = 0.0f;
				break;
			default:
				_texCoords[i].u = 0.0f;
				_texCoords[i].v = 0.0f;
		}
	}

	refreshNormals();
	return true;
}

bool ArtemisBase::Mesh::loadTetra(float size) {
	// Loads vertices defining size x size x size cube, where size is the length of one side.
	clear();
	float L = size / sqrt(3.0f);
	float l = 2 * size / 3;
	
	// Set up each corner vertex
	ArtemisBase::Vertex vert0 = ArtemisBase::Vertex(0.0f, l, 0.0f);
	ArtemisBase::Vertex vert1 = ArtemisBase::Vertex(size / 2, -l / 2, -L / 2);
	ArtemisBase::Vertex vert2 = ArtemisBase::Vertex(0.0f, -l / 2, L);
	ArtemisBase::Vertex vert3 = ArtemisBase::Vertex(-size / 2, -l / 2, -L / 2);
	
	// Create vertex arrays
	_numVertices = 12;
	_vertices = new ArtemisBase::Vertex[_numVertices];
	_vertices[0] = vert0; _vertices[1] = vert2; _vertices[2] = vert1; // Right face
	_vertices[3] = vert0; _vertices[4] = vert1; _vertices[5] = vert3; // Back face
	_vertices[6] = vert0; _vertices[7] = vert3; _vertices[8] = vert2; // Left face
	_vertices[9] = vert1; _vertices[10] = vert2; _vertices[11] = vert3; // Bottom face

	refreshNormals();
	return true;
}

bool ArtemisBase::Mesh::loadSphere(float size, int numFaces) {
	// Loads vertices defining sphere with radius size and the given number of faces
	int nPhi = (int)sqrt(numFaces / 2.0f);
	int nTht = nPhi * 2;
	float phi0, tht0, phi1, tht1;
	ArtemisBase::Vertex vert0, vert1, vert2, vert3;
	_numVertices = 6 * nPhi * nTht;
	_vertices = new ArtemisBase::Vertex[_numVertices];
	_texCoords = new ArtemisBase::TexCoord[_numVertices];
	
	// Create triangles by rotating about sphere
	for (int i = 0; i < nPhi; i++) {
		// Construct vertices for each latitude
		for (int j = 0; j < nTht; j++) {
			// Construct vertices for each longitude, beginning with spherical coordinates
			phi0 = (((float)i) / ((float)nPhi)) * float(M_PI);
			phi1 = (((float)(i+1)) / ((float)nPhi)) * float(M_PI);
			tht0 = (((float)j) / ((float)nTht)) * 2 * float(M_PI);
			tht1 = (((float)(j+1)) / ((float)nTht)) * 2 * float(M_PI);
			//printf("Generating vertices between phi {%f, %f} and tht {%f, %f} (i=%d, j=%d)\n", phi0, phi1, tht0, tht1, i, j);
			
			// Create vertices in cartesian from spherical coordinates
			vert0.set(size * sin(phi0) * cos(tht0), size * cos(phi0), -1 * size * sin(phi0) * sin(tht0));
			vert1.set(size * sin(phi1) * cos(tht0), size * cos(phi1), -1 * size * sin(phi1) * sin(tht0));
			vert2.set(size * sin(phi1) * cos(tht1), size * cos(phi1), -1 * size * sin(phi1) * sin(tht1));
			vert3.set(size * sin(phi0) * cos(tht1), size * cos(phi0), -1 * size * sin(phi0) * sin(tht1));
			//printf("Vertices for this face: 0 {%f, %f, %f}, 1 {%f, %f, %f}, 2 { %f, %f, %f}, 3 {%f, %f, %f}\n", vert0.x, vert0.y, vert0.z, vert1.x, vert1.y, vert1.z, vert2.x, vert2.y, vert2.z, vert3.x, vert3.y, vert3.z);
			
			// Specify triangles
			_vertices[i*nTht*6 + j*6 + 0] = vert0; _vertices[i*nTht*6 + j*6 + 1] = vert2; _vertices[i*nTht*6 + j*6 + 2] = vert1;
			_vertices[i*nTht*6 + j*6 + 3] = vert0; _vertices[i*nTht*6 + j*6 + 4] = vert3; _vertices[i*nTht*6 + j*6 + 5] = vert2;

			// Specify texture coordinate
			_texCoords[i*nTht*6 + j*6 + 0].u = tht0 / (2.0f * float(M_PI));
			_texCoords[i*nTht*6 + j*6 + 0].v = phi0 / float(M_PI);
			_texCoords[i*nTht*6 + j*6 + 1].u = tht1 / (2.0f * float(M_PI));
			_texCoords[i*nTht*6 + j*6 + 1].v = phi1 / float(M_PI);
			_texCoords[i*nTht*6 + j*6 + 2].u = tht0 / (2.0f * float(M_PI));
			_texCoords[i*nTht*6 + j*6 + 2].v = phi1 / float(M_PI);
			_texCoords[i*nTht*6 + j*6 + 3].u = tht0 / (2.0f * float(M_PI));
			_texCoords[i*nTht*6 + j*6 + 3].v = phi0 / float(M_PI);
			_texCoords[i*nTht*6 + j*6 + 4].u = tht1 / (2.0f * float(M_PI));
			_texCoords[i*nTht*6 + j*6 + 4].v = phi0 / float(M_PI);
			_texCoords[i*nTht*6 + j*6 + 5].u = tht1 / (2.0f * float(M_PI));
			_texCoords[i*nTht*6 + j*6 + 5].v = phi1 / float(M_PI);
		}
	}
	refreshNormals();
	return true;
}

void ArtemisBase::Mesh::clear() {
	if (_vertices != NULL)
		delete [] _vertices;
	_vertices = NULL;
	if (_normals != NULL)
		delete [] _normals;
	_normals = NULL;
	if (_texCoords != NULL)
		delete[] _texCoords;
	_texCoords = NULL;
}

void ArtemisBase::Mesh::render() {
	glBegin(GL_TRIANGLES); {
		for(int i = 0; i < _numVertices / 3; i++) {
			glNormal3f(_normals[i].x, _normals[i].y, _normals[i].z);
			if (_texCoords != NULL) {
				glTexCoord2f(_texCoords[3*i].u, _texCoords[3*i].v);
			}
			glVertex3f(_vertices[3*i].x, _vertices[3*i].y, _vertices[3*i].z);
			if (_texCoords != NULL) {
				glTexCoord2f(_texCoords[3*i+1].u, _texCoords[3*i+1].v);
			}
			glVertex3f(_vertices[3*i+1].x, _vertices[3*i+1].y, _vertices[3*i+1].z);
			if (_texCoords != NULL) {
				glTexCoord2f(_texCoords[3*i+2].u, _texCoords[3*i+2].v);
			}
			glVertex3f(_vertices[3*i+2].x, _vertices[3*i+2].y, _vertices[3*i+2].z);
		}
	} glEnd();
}

void ArtemisBase::Mesh::refreshNormals() {
	// Calculate normals
	_normals = new ArtemisBase::Vertex[_numVertices / 3];
	ArtemisBase::Vertex one, two;
	for (int i = 0; i < _numVertices / 3; i++) {
		one = _vertices[3*i+1] - _vertices[3*i];
		two = _vertices[3*i+2] - _vertices[3*i];
		_normals[i] = (two.cross(one)).norm();
	}
}

void ArtemisBase::Mesh::disableTexture() {
	if (_texCoords != NULL) {
		delete[] _texCoords;
		_texCoords = NULL;
	}
}
