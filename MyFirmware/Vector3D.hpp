#pragma once
class Vector3D
{
public:
	long X;
	long Y;
	long Z;
	Vector3D() {};
	Vector3D(long x, long y, long z = 0) {
		X = x;
		Y = y;
		Z = z;
	};
	Vector3D* Add(Vector3D p) {
		this->X += p.X;
		this->Y += p.Y;
		this->Z += p.Z;
		return this;
	};

};






