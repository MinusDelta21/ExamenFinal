#ifndef UAD_MESH_GL_H
#define UAD_MESH_GL_H

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <d3dx9math.h>
#include "Matrix4D.h"
#include "PrimitiveBase.h"
#include "UtilsGL.h"
#include <string>
#include <fstream>
#include <vector>
using namespace std;
struct MeshVertex {
	float x, y, z, w;
	float nx, ny, nz, nw;
	float u, v;
};
struct Mesh
{
	MeshVertex			*vertices;
	unsigned short		*indices;
	int num_Vertices;
	int num_Indices;
};

struct Buffers {
	GLuint			VB;
	GLuint			IB;
	int num_Vertices;
	int num_Indices;
};

class MeshGL : public PrimitiveBase {
public:
	MeshGL() : shaderID(0) {}
	void Create();
	void Transform(float *t);
	void Draw(float *t, float *vp);
	void Destroy();
	void SetDocName(char* docname);
	GLuint	shaderID;
	GLint	vertexAttribLoc;
	GLint	normalAttribLoc;
	GLint	uvAttribLoc;
	vector<Mesh*> Meshes;
	GLint  matWorldViewProjUniformLoc;
	GLint  matWorldUniformLoc;
	char* docName;
	vector<Buffers> Info;
	GLuint TexID;
	GLuint TexID_2;
	GLint DiffuseLoc;
	Matrix transform;
};


#endif