/*MIT License

C++ 3D Game Tutorial Series (https://github.com/PardCode/CPP-3D-Game-Tutorial-Series)

Copyright (c) 2019-2022, PardCode

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#pragma once
#include <memory>
#include <iostream>

#include "Vector3D.h"
#include "Vector4D.h"
#include "Math.h"

class Matrix4x4
{
public:
	Matrix4x4()
	{
	}

	void setIdentity()
	{
		::memset(m_mat, 0, sizeof(float) * 16);
		m_mat[0][0] = 1;
		m_mat[1][1] = 1;
		m_mat[2][2] = 1;
		m_mat[3][3] = 1;
	}

	Vector3D getTranslation()
	{
		return Vector3D(m_mat[3][0], m_mat[3][1], m_mat[3][2]);
	}

	Vector3D getRotationDegrees()
	{
		float roll = atan2f(this->m_mat[1][2], this->m_mat[2][2]);
		float c2 = sqrtf(this->m_mat[0][0] * this->m_mat[0][0] + this->m_mat[0][1] * this->m_mat[0][1]);
		float s1 = sinf(roll);
		float c1 = cosf(roll);
		float pitch = atan2f(-this->m_mat[0][2], c2);
		float yaw = atan2f(s1 * this->m_mat[2][0] - c1 * this->m_mat[1][0],
			c1 * this->m_mat[1][1] - s1 * this->m_mat[2][1]);
		return Vector3D(Math::toDegrees(roll), Math::toDegrees(yaw), Math::toDegrees(pitch));
	}

	Vector3D getScale()
	{
		return Vector3D(this->m_mat[0][0], this->m_mat[1][1], this->m_mat[2][2]);
	}

	void setTranslation(const Vector3D& translation)
	{
		setIdentity();
		m_mat[3][0] = translation.X();
		m_mat[3][1] = translation.Y();
		m_mat[3][2] = translation.Z();
	}

	void setScale(const Vector3D& scale)
	{
		setIdentity();
		m_mat[0][0] = scale.X();
		m_mat[1][1] = scale.Y();
		m_mat[2][2] = scale.Z();
	}

	void setRotationX(float x)
	{
		setIdentity();
		m_mat[1][1] = cos(x);
		m_mat[1][2] = sin(x);
		m_mat[2][1] = -sin(x);
		m_mat[2][2] = cos(x);
	}

	void setRotationY(float y)
	{
		setIdentity();
		m_mat[0][0] = cos(y);
		m_mat[0][2] = -sin(y);
		m_mat[2][0] = sin(y);
		m_mat[2][2] = cos(y);
	}

	void setRotationZ(float z)
	{
		setIdentity();
		m_mat[0][0] = cos(z);
		m_mat[0][1] = sin(z);
		m_mat[1][0] = -sin(z);
		m_mat[1][1] = cos(z);
	}

	Vector3D getZDirection()
	{
		return Vector3D(m_mat[2][0], m_mat[2][1], m_mat[2][2]);
	}
	Vector3D getYDirection()
	{
		return Vector3D(m_mat[1][0], m_mat[1][1], m_mat[1][2]);
	}
	Vector3D getXDirection()
	{
		return Vector3D(m_mat[0][0], m_mat[0][1], m_mat[0][2]);
	}

	void printMatrix()
	{
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				std::cout << m_mat[x][y] << " ";
			}
			std::cout << "\n";
		}

		std::cout << std::endl;
	}

	void operator *=(const Matrix4x4& matrix)
	{
		Matrix4x4 out;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				out.m_mat[i][j] =
					m_mat[i][0] * matrix.m_mat[0][j] + m_mat[i][1] * matrix.m_mat[1][j] + 
					m_mat[i][2] * matrix.m_mat[2][j] + m_mat[i][3] * matrix.m_mat[3][j];
			}
		}
		setMatrix(out);
	}

	void setMatrix(const Matrix4x4& matrix)
	{
		::memcpy(this->m_mat, matrix.m_mat, sizeof(float) * 16);
	}

	void setMatrix(float matrix[4][4])
	{
		::memcpy(this->m_mat, matrix, sizeof(float) * 16);
	}

	void setMatrix(float matrix[16])
	{
		float mat[4][4];
		mat[0][0] = matrix[0];
		mat[0][1] = matrix[1];
		mat[0][2] = matrix[2];
		mat[0][3] = matrix[3];

		mat[1][0] = matrix[4];
		mat[1][1] = matrix[5];
		mat[1][2] = matrix[6];
		mat[1][3] = matrix[7];

		mat[2][0] = matrix[8];
		mat[2][1] = matrix[9];
		mat[2][2] = matrix[10];
		mat[2][3] = matrix[11];

		mat[3][0] = matrix[12];
		mat[3][1] = matrix[13];
		mat[3][2] = matrix[14];
		mat[3][3] = matrix[15];
		::memcpy(this->m_mat, mat, sizeof(float) * 16);
	}

	void setOrthoLH(float width,float height,float near_plane, float far_plane)
	{
		setIdentity();
		m_mat[0][0] = 2.0f / width;
		m_mat[1][1] = 2.0f / height;
		m_mat[2][2] = 1.0f / (far_plane - near_plane);
		m_mat[3][2] = -(near_plane / (far_plane - near_plane));
	}

	~Matrix4x4()
	{
	}

	Matrix4x4 multiplyTo(Matrix4x4 matrix)
	{
		Matrix4x4 out;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				out.m_mat[i][j] =
					this->m_mat[i][0] * matrix.m_mat[0][j] + this->m_mat[i][1] * matrix.m_mat[1][j] +
					this->m_mat[i][2] * matrix.m_mat[2][j] + this->m_mat[i][3] * matrix.m_mat[3][j];
			}
		}

		return out;
	}

	float getDeterminant()
	{
		Vector4D minor, v1, v2, v3;
		float det;

		v1 = Vector4D(this->m_mat[0][0], this->m_mat[1][0], this->m_mat[2][0], this->m_mat[3][0]);
		v2 = Vector4D(this->m_mat[0][1], this->m_mat[1][1], this->m_mat[2][1], this->m_mat[3][1]);
		v3 = Vector4D(this->m_mat[0][2], this->m_mat[1][2], this->m_mat[2][2], this->m_mat[3][2]);


		minor.cross(v1, v2, v3);
		det = -(this->m_mat[0][3] * minor.m_x + this->m_mat[1][3] * minor.m_y + this->m_mat[2][3] * minor.m_z +
			this->m_mat[3][3] * minor.m_w);
		return det;
	}

	void inverse()
	{
		int a, i, j;
		Matrix4x4 out;
		Vector4D v, vec[3];
		float det = 0.0f;

		det = this->getDeterminant();
		if (!det) return;
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (j != i)
				{
					a = j;
					if (j > i) a = a - 1;
					vec[a].m_x = (this->m_mat[j][0]);
					vec[a].m_y = (this->m_mat[j][1]);
					vec[a].m_z = (this->m_mat[j][2]);
					vec[a].m_w = (this->m_mat[j][3]);
				}
			}
			v.cross(vec[0], vec[1], vec[2]);

			out.m_mat[0][i] = pow(-1.0f, i) * v.m_x / det;
			out.m_mat[1][i] = pow(-1.0f, i) * v.m_y / det;
			out.m_mat[2][i] = pow(-1.0f, i) * v.m_z / det;
			out.m_mat[3][i] = pow(-1.0f, i) * v.m_w / det;
		}

		this->setMatrix(out);
	}

	void setPerspectiveFovLH(float fov, float aspect, float znear, float zfar)
	{
		float yscale = 1.0f / tan(fov / 2.0f);
		float xscale = yscale / aspect;
		m_mat[0][0] = xscale;
		m_mat[1][1] = yscale;
		m_mat[2][2] = zfar / (zfar - znear);
		m_mat[2][3] = 1.0f;
		m_mat[3][2] = (-znear * zfar) / (zfar - znear);
	}

	float* getMatrix()
	{
		//re-arrange to be compatible with react physics
		/*float matrix4x4[16];
		matrix4x4[0] = matrix[0][0]; matrix4x4[1] = matrix[1][0];
		matrix4x4[2] = matrix[2][0]; matrix4x4[3] = 0.0;
		matrix4x4[4] = matrix[0][1]; matrix4x4[5] = matrix[1][1];
		matrix4x4[6] = matrix[2][1]; matrix4x4[7] = 0.0;
		matrix4x4[8] = matrix[0][2]; matrix4x4[9] = matrix[1][2];
		matrix4x4[10] = matrix[2][2]; matrix4x4[11] = 0.0;
		matrix4x4[12] = matrix[3][0]; matrix4x4[13] = matrix[3][1];
		matrix4x4[14] = matrix[3][2]; matrix4x4[15] = 1.0;

		return matrix4x4;*/

		return *this->m_mat;
	}

public:
	float m_mat[4][4] = {};
};