#pragma once
	struct Vector4D
	{
		union
		{
			struct
			{
				float x, y, z, w;
			};
			struct
			{
				float r, g, b, a;
			};
			struct
			{
				unsigned long ulx, uly, ulz, ulw;
			};
			float v[4];
		};
	};
	struct Matrix4D
	{
		union
		{
			struct
			{
				float m00, m01, m02, m03;
				float m10, m11, m12, m13;
				float m20, m21, m22, m23;
				float m30, m31, m32, m33;
			};
			float m[4][4];
			Vector4D vec[4];
			float v[16];
		};
	};
	Vector4D Create(float x, float y, float z, float w);
	Matrix4D operator*(Matrix4D& A, Matrix4D &B);
	Vector4D operator*(Matrix4D& A, Vector4D& V);
	Vector4D operator*(Vector4D& V, Matrix4D& A);
	Vector4D operator*(Vector4D& A, Vector4D& B);
	Vector4D operator-(Vector4D& A, Vector4D &B);
	Vector4D operator+(Vector4D& A, Vector4D &B);
	Vector4D operator*(Vector4D& A, float s);
	Matrix4D Zero();
	float Dot(Vector4D& A, Vector4D& B);
	float Magnity(Vector4D& A);
	Vector4D Normalize(Vector4D& A);
	Matrix4D Identity();
	Matrix4D Transpose(Matrix4D& M);
	Matrix4D FastInverse(Matrix4D& M);
	Matrix4D Translation(float dx, float dy, float dz);
	Matrix4D RotationXRH(float theta);
	Matrix4D RotationYRH(float theta);
	Matrix4D RotationZRH(float theta);
	Matrix4D RotationXLH(float theta);
	Matrix4D RotationYLH(float theta);
	Matrix4D RotationZLH(float theta);
	Matrix4D Scaling(float sx, float sy, float sz);
	Vector4D Cross3(Vector4D&A, Vector4D &B);
	Matrix4D LookAtRH(Vector4D& EyePos, Vector4D& Target, Vector4D& Up);
	Matrix4D LookAtLH(Vector4D& EyePos, Vector4D& Target, Vector4D& Up);
	Matrix4D OrthoRH(float width, float height, float zNear, float zFar);
	Matrix4D OrthoLH(float width, float height, float zNear, float zFar);
	Matrix4D PerspectiveFOVRH(float FOVY, float ratio, float zNear, float zFar);
	Matrix4D PerspectiveFOVLH(float FOVY, float ratio, float zNear, float zFar);
	Vector4D TransformNormalLH(const Vector4D &v, const Matrix4D &mat);
	Vector4D TransformNormalRH(const Vector4D &v, const Matrix4D &mat);
	float Inverse(Matrix4D & M, Matrix4D & R);
	float Deg2Rad(float Angle);
class Matrix{
public:
	Matrix4D myMatrix;
	Matrix4D &operator= (float* A);
	Matrix4D &operator= (Matrix4D* otherMat);
};
