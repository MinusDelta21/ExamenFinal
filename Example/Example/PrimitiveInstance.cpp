#include "PrimitiveInstance.h"
#include "Matrix4D.h"
#define Pi 3.141592
void PrimitiveInst::TranslateAbsolute(float x, float y, float z){
	//Matrix4DTranslation(&Position, x, y, z);
	Position = Translation(x, y, z);
}

void PrimitiveInst::RotateXAbsolute(float ang) {
	ang = ang*Pi / 180;
	//Matrix4DRotationX(&RotationX,D3DXToRadian(ang));
	RotationX = RotationXRH(ang);

}

void PrimitiveInst::RotateYAbsolute(float ang) {
	ang = ang*Pi / 180;
	//Matrix4DRotationY(&RotationY, D3DXToRadian(ang));
	RotationY = RotationYRH(ang);
}

void PrimitiveInst::RotateZAbsolute(float ang) {
	ang = ang*Pi / 180;
	//Matrix4DRotationZ(&RotationZ, D3DXToRadian(ang));
	RotationZ = RotationZRH(ang);
}

void PrimitiveInst::ScaleAbsolute(float sc) {
	//Matrix4DScaling(&Scale,sc,sc,sc);
	Scale = Scaling(sc, sc, sc);
}

void PrimitiveInst::TranslateRelative(float x, float y, float z) {
	Matrix4D tmp;
	//Matrix4DTranslation(&tmp, x, y, z);
	tmp = Translation(x, y, z);
	Position = tmp;
}

void PrimitiveInst::RotateXRelative(float ang) {
	ang = ang*Pi / 180;
	Matrix4D tmp;
	//Matrix4DRotationX(&tmp, D3DXToRadian(ang));
	tmp = RotationXRH(ang);
	RotationX = tmp;
}

void PrimitiveInst::RotateYRelative(float ang) {
	ang = ang*Pi / 180;
	Matrix4D tmp;
	//Matrix4DRotationY(&tmp, D3DXToRadian(ang));
	tmp = RotationYRH(ang);
	RotationY = tmp;
	}

void PrimitiveInst::RotateZRelative(float ang) {
	ang = ang*Pi / 180;
	Matrix4D tmp;
	//Matrix4DRotationZ(&tmp, D3DXToRadian(ang));
	tmp = RotationZRH(ang);
	RotationX = tmp;
}

void PrimitiveInst::ScaleRelative(float sc) {
	Matrix4D tmp;
	tmp = Scaling(sc,sc,sc);
	Scale = tmp;
}

void PrimitiveInst::Update() {
	Final = Scale*RotationX*RotationY*RotationZ*Position;
}

void PrimitiveInst::Draw(){
	pBase->Draw(&Final.m[0][0],&(*pViewProj).m[0][0]);
}
