#pragma once
class Vector3D
{
  public:
	float_t X;
	float_t Y;
	float_t Z;

	Vector3D() {
		X = 0; Y = 0; Z = 0;
	};

	Vector3D(float_t x, float_t y = 0, float_t z = 0) {
		X = x; Y = y; Z = z;
	};

	Vector3D(const Vector3D &v) {//copy ctor
		X = v.X; Y = v.Y; Z = v.Z;
	};

	Vector3D operator+(Vector3D v) {
		return Vector3D(X + v.X, Y + v.Y, Z + v.Z);
	}

	Vector3D operator-(Vector3D v) {
		return Vector3D(X - v.X, Y - v.Y, Z - v.Z);
	}

	float_t GetLength() {
		return sqrtf(powf(X, 2) + powf(Y, 2) + powf(Z, 2));
	};

	// float_t GetLengthSquared()
	// {
	// 	return powf(X, 2) + powf(Y, 2) + powf(Z, 2);
	// };

	Vector3D Inverse() { //todo change Negate
		X *= -1; Y *= -1; Z *= -1;
		return *this;
	};

	Vector3D Add(float_t x = 0, float_t y = 0, float_t z = 0) {
		return Add(Vector3D(x, y, z));
	};

	Vector3D Add(Vector3D p) {
		this->X += p.X; //todo is it need by this-> ???
		this->Y += p.Y;
		this->Z += p.Z;
		return *this;
	};

	Vector3D Subtract(float_t x = 0, float_t y = 0, float_t z = 0) {
		return Subtract(Vector3D(x, y, z));
	};

	Vector3D Subtract(Vector3D p) {
		this->X -= p.X; //todo is it need by this-> ???
		this->Y -= p.Y;
		this->Z -= p.Z;
		return *this;
	};

	float_t AbsMaxCoord() {
		float_t max = fabsf(X);
		if (max < fabsf(Y))
			max = fabsf(Y);
		if (max < fabsf(Z))
			max = fabsf(Z);
		return max;
	};

	// void Normalize()
	// Negate()

	// float_t GetLengthXY()
	// {
	// 	return sqrtf(powf(X, 2) + powf(Y, 2));
	// };

	// float_t GetLengthXZ()
	// {
	// 	return sqrtf(powf(X, 2) + powf(Z, 2));
	// };

	// float_t GetLengthYZ()
	// {
	// 	return sqrtf(powf(Y, 2) + powf(Z, 2));
	// };
};
