#pragma once
class Vector3D
{
public:
	float_t X;
	float_t Y;
	float_t Z;

	Vector3D() {
		X = 0; 		Y = 0; 		Z = 0;
	};

	Vector3D(float_t x, float_t y, float_t z = 0) {
		X = x;		Y = y;		Z = z;
	};

	Vector3D(const Vector3D& v) { //copy ctor
		X = v.X;		Y = v.Y;		Z = v.Z;
	}

	Vector3D Add(Vector3D p) {
		this->X += p.X;
		this->Y += p.Y;
		this->Z += p.Z;
		return *this;
	};

	Vector3D Subtract(Vector3D p) {
		this->X -= p.X;
		this->Y -= p.Y;
		this->Z -= p.Z;
		return *this;
	};

};






