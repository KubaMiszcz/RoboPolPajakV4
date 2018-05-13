#pragma once
class Vector3D
{
public:
	int32_t X;
	int32_t Y;
	int32_t Z;
	Vector3D() {
		X = 0; 		Y = 0; 		Z = 0;
	};
	Vector3D(int32_t x, int32_t y, int32_t z = 0) {
		X = x;		Y = y;		Z = z;
	};
	Vector3D(const Vector3D& v) { //copy ctor
		X = v.X;		Y = v.Y;		Z = v.Z;
	}
	Vector3D* Add(Vector3D p) {
		this->X += p.X;
		this->Y += p.Y;
		this->Z += p.Z;
		return this;
	};

};






