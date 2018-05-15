#pragma once
class Vector3D
{
public:
	int16_t X;
	int16_t Y;
	int16_t Z;

	Vector3D() {
		X = 0; 		Y = 0; 		Z = 0;
	};

	Vector3D(int16_t x, int16_t y, int16_t z = 0) {
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






