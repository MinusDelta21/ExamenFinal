#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "MeshGl.h"
#include "Matrix4D.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

void MeshGL::SetDocName(char* docname) {
	docName = docname;
}

void MeshGL::Create() {
	//Textures
	//"Textures/BatmanArmoured_Body_D.tga"
	string path = "Textures/BatmanArmoured_Body_D.tga";
	int x = 0, y = 0, channels = 0;
	unsigned char *buffer = stbi_load(path.c_str(), &x, &y, &channels, 4);
	shaderID = glCreateProgram();
	glGenTextures(1, &TexID);
	glBindTexture(GL_TEXTURE_2D, TexID);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)(buffer));
	glGenerateMipmap(GL_TEXTURE_2D);
	unsigned int glFiltering = 0;
	unsigned int glWrap = 0;

	glFiltering = GL_LINEAR_MIPMAP_LINEAR;
	glWrap = GL_CLAMP_TO_EDGE;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, glFiltering);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, glFiltering);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, glWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, glWrap);

	int Max = 1;
	glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &Max);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, Max);
	
	char *vsSourceP = file2string("VS_Mesh.glsl");
	char *fsSourceP = file2string("FS_Mesh.glsl");

	GLuint vshader_id = createShader(GL_VERTEX_SHADER, vsSourceP);
	GLuint fshader_id = createShader(GL_FRAGMENT_SHADER, fsSourceP);

	glAttachShader(shaderID, vshader_id);
	glAttachShader(shaderID, fshader_id);

	glLinkProgram(shaderID);
	glUseProgram(shaderID);

	vertexAttribLoc = glGetAttribLocation(shaderID, "Vertex");
	normalAttribLoc = glGetAttribLocation(shaderID, "Normal");
	uvAttribLoc = glGetAttribLocation(shaderID, "UV");

	matWorldViewProjUniformLoc = glGetUniformLocation(shaderID, "WVP");
	matWorldUniformLoc = glGetUniformLocation(shaderID, "World");
	DiffuseLoc = glGetUniformLocation(shaderID, "Diffuse");

	//Textures


	//Read X File
	string line;
	ifstream myfile;
	int numNormals, numTex;
	Matrix FTMr;
	Mesh *myMesh;
	myfile.open(docName);
	if (myfile.is_open())
	{
		if (myfile.is_open()) {
			while (getline(myfile, line)) {
				char c_temp;
				if (line == "xof 0303txt 0032") cout << line << endl;
				int PosM = line.find("FrameTransformMatrix relative {");
				int PosV = line.find("Mesh mesh");
				int PosN = line.find("MeshNormals normals");
				int PosT = line.find("MeshTextureCoords tc");

				if (PosM != -1) {
					myfile >> FTMr.myMatrix.v[0] >> c_temp >> FTMr.myMatrix.v[1] >> c_temp >> FTMr.myMatrix.v[2] >> c_temp >> FTMr.myMatrix.v[3] >> c_temp >> FTMr.myMatrix.v[4] >> c_temp
						>> FTMr.myMatrix.v[5] >> c_temp >> FTMr.myMatrix.v[6] >> c_temp >> FTMr.myMatrix.v[7] >> c_temp >> FTMr.myMatrix.v[8] >> c_temp >> FTMr.myMatrix.v[9] >> c_temp
						>> FTMr.myMatrix.v[10] >> c_temp >> FTMr.myMatrix.v[11] >> c_temp >> FTMr.myMatrix.v[12] >> c_temp >> FTMr.myMatrix.v[13] >> c_temp >> FTMr.myMatrix.v[14] >> c_temp
						>> FTMr.myMatrix.v[15] >> c_temp >> c_temp;
				}
				
				if (PosV != -1) {
					myMesh = new Mesh;
					getline(myfile, line);
					myMesh->num_Vertices = stoi(line);
					cout << "Vertices: " << myMesh->num_Vertices << endl;
					//Separar vertices
					myMesh->vertices = new MeshVertex[myMesh->num_Vertices];
					for (int i = 0; i < myMesh->num_Vertices; i++) {
						myfile >> myMesh->vertices[i].x >> c_temp >> myMesh->vertices[i].y >> c_temp >> myMesh->vertices[i].z >> c_temp >> c_temp;
						myMesh->vertices[i].w = 1;
					}
					myfile >> myMesh->num_Indices >> c_temp;
					//n_Indices = myMesh->num_Indices;
					cout << "Indices: " << myMesh->num_Indices << endl;
					myMesh->indices = new unsigned short[myMesh->num_Indices * 3];
					for (int i = 0; i < myMesh->num_Indices; i++) {
						float aux;
						myfile >> aux >> c_temp;
						for (int j = 0; j < aux; j++) {
							myfile >> myMesh->indices[(i * 3) + j] >> c_temp;
						}
						myfile >> c_temp;
					}
				}
				if (PosN != -1) {
					getline(myfile, line);
					numNormals = stoi(line);
					cout << "Normals: " << numNormals << endl;
					//Separar vertices
					for (int i = 0; i < numNormals; i++) {
						myfile >> myMesh->vertices[i].nx >> c_temp >> myMesh->vertices[i].ny >> c_temp >> myMesh->vertices[i].nz >> c_temp >> c_temp;
						myMesh->vertices[i].nw = 1;
					}

				}
				if (PosT != -1) {
					getline(myfile, line);
					numTex = stoi(line);
					cout << "Texture: " << numTex << endl;
					//Separar vertices
					for (int i = 0; i < numTex; i++) {
						myfile >> myMesh->vertices[i].u >> c_temp >> myMesh->vertices[i].v >> c_temp >> c_temp;
					}
				Meshes.push_back(myMesh);
				}
			}
			myfile.close();
		}
		else cout << "Unable to open file";
	}
	for (int i = 0; i < Meshes.size(); i++) {
		cout << Meshes[i]->vertices->u << ", " << Meshes[i]->vertices->v << endl;
	}
	Info.resize(Meshes.size());
	for (int i = 0; i < Meshes.size(); i++) {
			Info[i].num_Vertices = Meshes[i]->num_Vertices;
			Info[i].num_Indices = Meshes[i]->num_Indices;

			glGenBuffers(1, &Info[i].VB);
			glBindBuffer(GL_ARRAY_BUFFER, Info[i].VB);
			glBufferData(GL_ARRAY_BUFFER, Meshes[i]->num_Vertices * sizeof(MeshVertex), Meshes[i]->vertices, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);


			glGenBuffers(1, &Info[i].IB);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Info[i].IB);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, Meshes[i]->num_Indices * 3 * sizeof(unsigned short), Meshes[i]->indices, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		
	}
	transform.myMatrix = Identity();
}

void MeshGL::Transform(float *t) {
	transform = t;
}

void MeshGL::Draw(float *t, float *vp) {
	glUseProgram(shaderID);

	if (t)
		transform = t;

	Matrix VP;
	VP = vp;
	Matrix WVP;
	WVP.myMatrix = transform.myMatrix*VP.myMatrix;
	glUniformMatrix4fv(matWorldUniformLoc, 1, GL_FALSE, &transform.myMatrix.m[0][0]);
	glUniformMatrix4fv(matWorldViewProjUniformLoc, 1, GL_FALSE, &WVP.myMatrix.m[0][0]);
	for (int i = 0; i < Meshes.size(); i++) {
		glBindBuffer(GL_ARRAY_BUFFER, Info[i].VB);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Info[i].IB);
		glEnableVertexAttribArray(vertexAttribLoc);
		if (normalAttribLoc != -1)
		glEnableVertexAttribArray(normalAttribLoc);

		if (uvAttribLoc != -1)
			glEnableVertexAttribArray(uvAttribLoc);
		
		glVertexAttribPointer(vertexAttribLoc, 4, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), BUFFER_OFFSET(0));
		if (normalAttribLoc != -1)
			glVertexAttribPointer(normalAttribLoc, 4, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), BUFFER_OFFSET(16));

		if (uvAttribLoc != -1)
			glVertexAttribPointer(uvAttribLoc, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), BUFFER_OFFSET(32));
		
		//Agregue esto
		//if (DiffuseLoc != -1) {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, TexID);
			glUniform1i(DiffuseLoc, 0);
	//	}
		glDrawElements(GL_TRIANGLES, Info[i].num_Indices * 3, GL_UNSIGNED_SHORT, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glDisableVertexAttribArray(vertexAttribLoc);
		if (normalAttribLoc != -1)
			glDisableVertexAttribArray(normalAttribLoc);

		if (uvAttribLoc != -1) {
			glDisableVertexAttribArray(uvAttribLoc);
		}
	}
	glUseProgram(0);
}

void MeshGL::Destroy() {
	glDeleteProgram(shaderID);
}