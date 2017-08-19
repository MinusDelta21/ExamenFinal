#include "Camera.h"
#include <math.h>
#include "Matrix4D.h"

const	Vector4D	CCamera::LookConstCameraSpace = Vector4D{ 0.0f, 0.0f, 1.0f,0.0f };
const	Vector4D	CCamera::RightConstCameraSpace = Vector4D{ 1.0f, 0.0f, 0.0f,0.0f };
const	Vector4D	CCamera::UpConstCameraSpace = Vector4D{ 0.0f, 1.0f, 0.0f,0.0f };

CCamera::CCamera() {
	Reset();
}

void	CCamera::Init(Vector4D position, float fov, float ratio, float np, float fp, bool lf) {
	this->Fov = fov;
	this->AspectRatio = ratio;
	this->NPlane = np;
	this->FPlane = fp;
	this->Eye = position;
	this->LeftHanded = lf;
	CreatePojection();
}

void	CCamera::CreatePojection() {
	if (LeftHanded)
		Projection = PerspectiveFOVLH(Fov, AspectRatio, NPlane, FPlane);
	else
		Projection = PerspectiveFOVRH(Fov, AspectRatio, NPlane, FPlane);
}

void	CCamera::SetLookAt(Vector4D v) {
	Look = v - Eye;
	Look = Normalize(Look);
	Pitch = atan2f(-Look.y, -Look.z);
	Yaw = atan2f(-Look.x, Look.z);
	Update(1.0f / 60.0f);
}

void	CCamera::MoveForward(float dt) {
	Velocity.z += Speed * dt;
}

void	CCamera::MoveBackward(float dt) {
	Velocity.z -= Speed * dt;
}

void	CCamera::StrafeLeft(float dt) {
	Velocity.x -= Speed * dt;
}

void	CCamera::StrafeRight(float dt) {
	Velocity.x += Speed * dt;
}

void	CCamera::SetFov(float f) {
	this->Fov = f;
	CreatePojection();
}

void	CCamera::SetRatio(float r) {
	this->AspectRatio = r;
	CreatePojection();
}

void	CCamera::SetPlanes(float n, float f) {
	this->NPlane = n;
	this->FPlane = f;
	CreatePojection();
}

void	CCamera::MoveYaw(float f) {
	if (MaxYaw != 0.0) {
		if ((Yaw + f) > MaxYaw || (Yaw + f) < -MaxYaw)
			return;
	}
	Yaw += f;
}

void	CCamera::MovePitch(float f) {
	if (MaxPitch != 0.0) {
		if ((Pitch + f) > MaxPitch || (Pitch + f) < -MaxPitch)
			return;
	}
	Pitch += f;
}

void	CCamera::MoveRoll(float f) {
	if (MaxRoll != 0.0) {
		if ((Roll + f) > MaxRoll || (Roll + f) < -MaxRoll)
			return;
	}
	Roll += f;
}

void	CCamera::Update(float dt) {
	Matrix4D	X_, Y_, Z_, T_;
	X_ = RotationXLH(-Pitch);
	Y_ = RotationYLH(-Yaw);
	Z_ = RotationZLH(-Roll);
	View = Z_*Y_*X_;

	Matrix4D transpose;
	transpose = Transpose(View);
	Look = TransformNormalLH(LookConstCameraSpace, transpose);
	Up = TransformNormalLH(UpConstCameraSpace, transpose);
	Right = TransformNormalLH(RightConstCameraSpace, transpose);

	Look = Normalize(Look);
	Up = Normalize(Up);
	Right = Normalize(Right);

	Vector4D currentvelocity = Right*Velocity.x + Up*Velocity.y + Look*Velocity.z;
	Velocity = Velocity -Velocity*Friction;
	Eye = Eye + currentvelocity;

	Vector4D TEYE = Eye*-1;
	T_ = Translation(TEYE.x,TEYE.y,TEYE.z);
	View = T_*View;
	VP = View*Projection;
}

void	CCamera::Reset() {
	Eye = Vector4D{ 0.0f, 0.0f, 0.0f, 0.0f };
	Velocity = Vector4D{0.0f, 0.0f, 0.0f,0.0f};
	Fov = Deg2Rad(45.0f);
	NPlane = 0.01f;
	FPlane = 1000.0f;
	AspectRatio = 1.0f;
	Speed = 5000.0;
	Yaw = 0.0f;
	Pitch = 0.0f;
	Roll = 0.0f;
	Friction = 0.1f;
	MaxRoll = 0.0f;
	MaxPitch = Deg2Rad(89.0f);
	MaxYaw = 0.0f;
	LeftHanded = true;
}
