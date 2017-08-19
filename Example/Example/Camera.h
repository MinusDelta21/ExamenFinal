#pragma once
#include "Matrix4D.h"
class CCamera
{
public:
	CCamera();

	void	Init(Vector4D position, float fov, float ratio, float np, float fp, bool lf = true);
	void	CreatePojection();

	void	SetLookAt(Vector4D v);

	void	MoveForward(float dt);
	void	MoveBackward(float dt);
	void	StrafeLeft(float dt);
	void	StrafeRight(float dt);

	void	MoveYaw(float f);
	void	MovePitch(float f);
	void	MoveRoll(float f);

	void	Update(float dt);
	void	Reset();

	void	SetFov(float f);
	void	SetRatio(float r);
	void	SetPlanes(float n, float f);

	float		Fov;
	float		AspectRatio;
	float		NPlane;
	float		FPlane;

	float		Yaw;
	float		Pitch;
	float		Roll;

	float		MaxRoll;
	float		MaxPitch;
	float		MaxYaw;

	float		Speed;
	float		Friction;

	bool		LeftHanded;

	Vector4D	Eye;
	Vector4D	Look;
	Vector4D	Right;
	Vector4D	Up;

	Vector4D	Velocity;

	Matrix4D	Position;
	Matrix4D	RotX;
	Matrix4D	RotY;
	Matrix4D	RotZ;

	Matrix4D	View;
	Matrix4D	Projection;
	Matrix4D	VP;

	static const	Vector4D	LookConstCameraSpace;
	static const	Vector4D	RightConstCameraSpace;
	static const	Vector4D	UpConstCameraSpace;
};

