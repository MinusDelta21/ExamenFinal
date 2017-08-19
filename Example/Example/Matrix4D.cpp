#include "Matrix4D.h"

#include "Matrix4D.h"
#include <string.h>
#include <math.h>

//Metodos de la clase
Matrix4D &Matrix::operator= (float* A){
	for (int i = 0; i < 16; i++) {
		this->myMatrix.v[i] = A[i];
	}
	return this->myMatrix;
}
Matrix4D &Matrix::operator= (Matrix4D* otherMat) {
	for (int i = 0; i < 16; i++) {
		this->myMatrix.v[i] = otherMat->v[i];
	}
	return this->myMatrix;
}

Matrix4D Zero()
{
	Matrix4D Z;
	memset(&Z, 0, sizeof(Matrix4D));
	return Z;
}

Matrix4D operator*(Matrix4D & A, Matrix4D & B)
{
	Matrix4D R = Zero();
	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++)
			for (int k = 0; k < 4; k++)
				R.m[j][i] += A.m[j][k] * B.m[k][i];
	return R;
}

Vector4D operator*(Matrix4D & A, Vector4D & V)
{
	Vector4D R = { 0, 0, 0, 0 };
	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++)
			R.v[j] += A.m[j][i] * V.v[i];
	return R;
}

Vector4D operator*(Vector4D & V, Matrix4D & A)
{
	Vector4D R = { 0, 0, 0, 0 };
	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++)
			R.v[j] += A.m[i][j] * V.v[i];
	return R;
}

Vector4D operator*(Vector4D & A, Vector4D & B)
{
	Vector4D R = { A.x*B.x, A.y*B.y, A.z*B.z, A.w*B.w };
	return R;
}

Vector4D operator-(Vector4D & A, Vector4D & B)
{
	Vector4D R = { A.x - B.x, A.y - B.y, A.z - B.z, A.w - B.w };
	return R;
}

Vector4D operator+(Vector4D& A, Vector4D& B)
{
	Vector4D R = { A.x + B.x, A.y + B.y, A.z + B.z, A.w + B.w };
	return R;
}

Vector4D operator*(Vector4D& A, float s)
{
	Vector4D R = { A.x*s, A.y*s, A.z*s, A.w*s };
	return R;
}

float Dot(Vector4D & A, Vector4D & B)
{
	return  A.x*B.x + A.y*B.y + A.z*B.z + A.w*B.w;
}

float Magnity(Vector4D & A)
{
	return sqrtf(Dot(A, A));
}

Vector4D Normalize(Vector4D & A)
{
	float inv = 1.0f / Magnity(A);
	Vector4D R = { A.x*inv, A.y*inv, A.z*inv, A.w*inv };
	return R;
}

Matrix4D Identity()
{
	Matrix4D I;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			I.m[j][i] = (i == j) ? 1.0f : 0.0f;
	return I;
}

Matrix4D Transpose(Matrix4D & M)
{
	Matrix4D R;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			R.m[i][j] = M.m[j][i];
	return R;

}

Matrix4D FastInverse(Matrix4D & M)
{
	Matrix4D R;
	Vector4D InvPos;
	R = Transpose(M);
	InvPos = R.vec[3];
	R.m03 = -Dot(R.vec[0], InvPos);
	R.m13 = -Dot(R.vec[1], InvPos);
	R.m23 = -Dot(R.vec[2], InvPos);
	R.vec[3].x = 0;
	R.vec[3].y = 0;
	R.vec[3].z = 0;
	return R;
}


Matrix4D Translation(float dx, float dy, float dz)
{
	Matrix4D T = Identity();
	T.m30 = dx;
	T.m31 = dy;
	T.m32 = dz;
	return T;
}

Matrix4D RotationXRH(float theta)
{
	Matrix4D R = Identity();
	R.m22 = R.m11 = cosf(theta);
	R.m12 = -sinf(theta);
	R.m21 = -R.m12;
	return R;
}

Matrix4D RotationYRH(float theta)
{
	Matrix4D R = Identity();
	R.m00 = R.m22 = cosf(theta);
	R.m20 = -sinf(theta);
	R.m02 = -R.m20;
	return R;
}

Matrix4D RotationZRH(float theta)
{
	Matrix4D R = Identity();
	R.m11 = R.m00 = cosf(theta);
	R.m01 = -sinf(theta);
	R.m10 = -R.m01;
	return R;
}

Matrix4D RotationXLH(float theta)
{
	Matrix4D R = Identity();
	R.m22 = R.m11 = cosf(theta);
	R.m12 = sinf(theta);
	R.m21 = -R.m12;
	return R;
}

Matrix4D RotationYLH(float theta)
{
	Matrix4D R = Identity();
	R.m00 = R.m22 = cosf(theta);
	R.m20 = sinf(theta);
	R.m02 = -R.m20;
	return R;
}

Matrix4D RotationZLH(float theta)
{
	Matrix4D R = Identity();
	R.m11 = R.m00 = cosf(theta);
	R.m01 = sinf(theta);
	R.m10 = -R.m01;
	return R;
}

Matrix4D Scaling(float sx, float sy, float sz)
{
	Matrix4D S = Identity();
	S.m00 = sx;
	S.m11 = sy;
	S.m22 = sz;
	return S;
}

Vector4D Cross3(Vector4D & A, Vector4D & B)
{
	Vector4D R;
	R.x = A.y*B.z - A.z*B.y;
	R.y = A.z*B.x - A.x*B.z;
	R.z = A.x*B.y - A.y*B.x;
	R.w = 0;
	return R;
}

Matrix4D LookAtRH(Vector4D & EyePos, Vector4D & Target, Vector4D & Up)
{
	Vector4D xDir, yDir, zDir;
	zDir = Normalize(EyePos - Target);
	xDir = Normalize(Cross3(Up, zDir));
	yDir = Cross3(zDir, xDir);
	Matrix4D View = { xDir.x,				yDir.x,				zDir.x,		 0,
		xDir.y,				yDir.y,				zDir.y,		 0,
		xDir.z,				yDir.z,				zDir.z,		 0,
		-Dot(xDir,EyePos), -Dot(yDir, EyePos), -Dot(zDir, EyePos), 1 };
	return View;
}

Matrix4D LookAtLH(Vector4D & EyePos, Vector4D & Target, Vector4D & Up)
{
	Vector4D xDir, yDir, zDir;
	zDir = Normalize(Target - EyePos);
	xDir = Normalize(Cross3(Up, zDir));
	yDir = Cross3(zDir, xDir);
	Matrix4D View = { xDir.x,			yDir.x,				zDir.x,		   0,
		xDir.y,			yDir.y,				zDir.y,		   0,
		xDir.z,			yDir.z,				zDir.z,		   0,
		-Dot(xDir,EyePos), -Dot(yDir, EyePos), -Dot(zDir, EyePos), 1 };
	return View;
}

Matrix4D OrthoRH(float width, float height, float zNear, float zFar)
{
	Matrix4D O = { 2 / width,	    0,				 0,			    0,
		0,		2 / height,			 0,			    0,
		0,		    0,		  1 / (zNear - zFar),   0,
		0,		    0,		zNear / (zNear - zFar),	1 };
	return O;
}

Matrix4D OrthoLH(float width, float height, float zNear, float zFar)
{
	Matrix4D O = { 2 / width,		0,				  0,		    0,
		0,		2 / height,			  0,		    0,
		0,			0,		  1 / (zFar - zNear),   0,
		0,			0,		zNear / (zNear - zFar),	1 };
	return O;
}

Matrix4D PerspectiveFOVRH(float FOVY, float ratio, float zNear, float zFar)
{
	float x, y;
	float h = cos(FOVY / 2) / sin(FOVY / 2);
	float w = h/ratio;
	Matrix4D P = { w,	0,				 0,				 0,
		0,	h,				 0,				 0,
		0,	0,	   zFar / (zNear - zFar),   -1,
		0,	0,	zNear*zFar / (zNear - zFar), 0 };
	return P;
}

Matrix4D PerspectiveFOVLH(float FOVY, float ratio, float zNear, float zFar)
{
	float h = 1 / tan(FOVY / 2);
	float w = h/ratio;
	Matrix4D P = { w,	0,				  0,				0,
		0,	h,				  0,				0,
		0,	0,		zFar / (zFar - zNear),		1,
		0,	0,	-zNear*zFar / (zFar - zNear),	0 };
	return P;
}


float Inverse(Matrix4D & M, Matrix4D & R)
{
	double inv[16], det;
	int i;

	inv[0] = M.v[5] * M.v[10] * M.v[15] -
		M.v[5] * M.v[11] * M.v[14] -
		M.v[9] * M.v[6] * M.v[15] +
		M.v[9] * M.v[7] * M.v[14] +
		M.v[13] * M.v[6] * M.v[11] -
		M.v[13] * M.v[7] * M.v[10];

	inv[4] = -M.v[4] * M.v[10] * M.v[15] +
		M.v[4] * M.v[11] * M.v[14] +
		M.v[8] * M.v[6] * M.v[15] -
		M.v[8] * M.v[7] * M.v[14] -
		M.v[12] * M.v[6] * M.v[11] +
		M.v[12] * M.v[7] * M.v[10];

	inv[8] = M.v[4] * M.v[9] * M.v[15] -
		M.v[4] * M.v[11] * M.v[13] -
		M.v[8] * M.v[5] * M.v[15] +
		M.v[8] * M.v[7] * M.v[13] +
		M.v[12] * M.v[5] * M.v[11] -
		M.v[12] * M.v[7] * M.v[9];

	inv[12] = -M.v[4] * M.v[9] * M.v[14] +
		M.v[4] * M.v[10] * M.v[13] +
		M.v[8] * M.v[5] * M.v[14] -
		M.v[8] * M.v[6] * M.v[13] -
		M.v[12] * M.v[5] * M.v[10] +
		M.v[12] * M.v[6] * M.v[9];

	inv[1] = -M.v[1] * M.v[10] * M.v[15] +
		M.v[1] * M.v[11] * M.v[14] +
		M.v[9] * M.v[2] * M.v[15] -
		M.v[9] * M.v[3] * M.v[14] -
		M.v[13] * M.v[2] * M.v[11] +
		M.v[13] * M.v[3] * M.v[10];

	inv[5] = M.v[0] * M.v[10] * M.v[15] -
		M.v[0] * M.v[11] * M.v[14] -
		M.v[8] * M.v[2] * M.v[15] +
		M.v[8] * M.v[3] * M.v[14] +
		M.v[12] * M.v[2] * M.v[11] -
		M.v[12] * M.v[3] * M.v[10];

	inv[9] = -M.v[0] * M.v[9] * M.v[15] +
		M.v[0] * M.v[11] * M.v[13] +
		M.v[8] * M.v[1] * M.v[15] -
		M.v[8] * M.v[3] * M.v[13] -
		M.v[12] * M.v[1] * M.v[11] +
		M.v[12] * M.v[3] * M.v[9];

	inv[13] = M.v[0] * M.v[9] * M.v[14] -
		M.v[0] * M.v[10] * M.v[13] -
		M.v[8] * M.v[1] * M.v[14] +
		M.v[8] * M.v[2] * M.v[13] +
		M.v[12] * M.v[1] * M.v[10] -
		M.v[12] * M.v[2] * M.v[9];

	inv[2] = M.v[1] * M.v[6] * M.v[15] -
		M.v[1] * M.v[7] * M.v[14] -
		M.v[5] * M.v[2] * M.v[15] +
		M.v[5] * M.v[3] * M.v[14] +
		M.v[13] * M.v[2] * M.v[7] -
		M.v[13] * M.v[3] * M.v[6];

	inv[6] = -M.v[0] * M.v[6] * M.v[15] +
		M.v[0] * M.v[7] * M.v[14] +
		M.v[4] * M.v[2] * M.v[15] -
		M.v[4] * M.v[3] * M.v[14] -
		M.v[12] * M.v[2] * M.v[7] +
		M.v[12] * M.v[3] * M.v[6];

	inv[10] = M.v[0] * M.v[5] * M.v[15] -
		M.v[0] * M.v[7] * M.v[13] -
		M.v[4] * M.v[1] * M.v[15] +
		M.v[4] * M.v[3] * M.v[13] +
		M.v[12] * M.v[1] * M.v[7] -
		M.v[12] * M.v[3] * M.v[5];

	inv[14] = -M.v[0] * M.v[5] * M.v[14] +
		M.v[0] * M.v[6] * M.v[13] +
		M.v[4] * M.v[1] * M.v[14] -
		M.v[4] * M.v[2] * M.v[13] -
		M.v[12] * M.v[1] * M.v[6] +
		M.v[12] * M.v[2] * M.v[5];

	inv[3] = -M.v[1] * M.v[6] * M.v[11] +
		M.v[1] * M.v[7] * M.v[10] +
		M.v[5] * M.v[2] * M.v[11] -
		M.v[5] * M.v[3] * M.v[10] -
		M.v[9] * M.v[2] * M.v[7] +
		M.v[9] * M.v[3] * M.v[6];

	inv[7] = M.v[0] * M.v[6] * M.v[11] -
		M.v[0] * M.v[7] * M.v[10] -
		M.v[4] * M.v[2] * M.v[11] +
		M.v[4] * M.v[3] * M.v[10] +
		M.v[8] * M.v[2] * M.v[7] -
		M.v[8] * M.v[3] * M.v[6];

	inv[11] = -M.v[0] * M.v[5] * M.v[11] +
		M.v[0] * M.v[7] * M.v[9] +
		M.v[4] * M.v[1] * M.v[11] -
		M.v[4] * M.v[3] * M.v[9] -
		M.v[8] * M.v[1] * M.v[7] +
		M.v[8] * M.v[3] * M.v[5];

	inv[15] = M.v[0] * M.v[5] * M.v[10] -
		M.v[0] * M.v[6] * M.v[9] -
		M.v[4] * M.v[1] * M.v[10] +
		M.v[4] * M.v[2] * M.v[9] +
		M.v[8] * M.v[1] * M.v[6] -
		M.v[8] * M.v[2] * M.v[5];

	det = M.v[0] * inv[0] + M.v[1] * inv[4] + M.v[2] * inv[8] + M.v[3] * inv[12];

	if (fabs(det) < 0.0001)
		return 0.0f;

	double invdet = 1.0 / det;

	for (i = 0; i < 16; i++)
		R.v[i] = (float)(inv[i] * invdet);

	return (float)det;
}
Vector4D TransformNormalLH(const Vector4D &v, const Matrix4D &mat) {
	Vector4D vpout;
	vpout.x = v.x*mat.m[0][0] + v.y*mat.m[1][0] + v.z*mat.m[2][0];
	vpout.y = v.x*mat.m[0][1] + v.y*mat.m[1][1] + v.z*mat.m[2][1];
	vpout.z = v.x*mat.m[0][2] + v.y*mat.m[1][2] + v.z*mat.m[2][2];
	vpout.w = 1.0f;
	return vpout;
}
Vector4D TransformNormalRH(const Vector4D &v, const Matrix4D &mat) {
	Vector4D vpout;
	vpout.x = v.x*mat.m[0][0] + v.y*mat.m[0][1] + v.z*mat.m[0][2];
	vpout.y = v.x*mat.m[1][0] + v.y*mat.m[1][1] + v.z*mat.m[1][2];
	vpout.z = v.x*mat.m[2][0] + v.y*mat.m[2][1] + v.z*mat.m[2][2];
	vpout.w = 1.0f;
	return vpout;
}
float Deg2Rad(float Angle) {
	return Angle * (3.141592 / 180);
}
Vector4D Create(float x, float y, float z, float w) {
	Vector4D myVec;
	myVec.x = x;
	myVec.y = y;
	myVec.z = z;
	myVec.w = w;
	return myVec;
}