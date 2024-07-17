#pragma once
#include <math.h>

namespace Tmpl8 {

	class Vector2
	{

	public:
		union { struct { float x, y; }; float cell[2]; };
		Vector2() {}
		Vector2(float v) : x(v), y(v) {}
		Vector2(float x, float y) : x(x), y(y) {}
		Vector2 operator - () const { return Vector2(-x, -y); }
		Vector2 operator + (const Vector2& addOperand) const { return Vector2(x + addOperand.x, y + addOperand.y); }
		Vector2 operator - (const Vector2& operand) const { return Vector2(x - operand.x, y - operand.y); }
		Vector2 operator * (const Vector2& operand) const { return Vector2(x * operand.x, y * operand.y); }
		Vector2 operator * (float operand) const { return Vector2(x * operand, y * operand); }
		void operator -= (const Vector2& a) { x -= a.x; y -= a.y; }
		void operator += (const Vector2& a) { x += a.x; y += a.y; }
		void operator *= (const Vector2& a) { x *= a.x; y *= a.y; }
		void operator *= (float a) { x *= a; y *= a; }
		float& operator [] (const int idx) { return cell[idx]; }
		float length() { return sqrtf(x * x + y * y); }
		float sqrLentgh() { return x * x + y * y; }
		Vector2 normalized() { float r = 1.0f / length(); return Vector2(x * r, y * r); }
		void normalize() { float r = 1.0f / length(); x *= r; y *= r; }
		static Vector2 normalize(Vector2 v) { return v.normalized(); }
		float dot(const Vector2& operand) const { return x * operand.x + y * operand.y; }
		
		static bool doesSegmentsIntersectTimed(Vector2 A1, Vector2 A2, Vector2 B1, Vector2 B2, float& ipx, float& ipy) {
			float denominatorX = B2.x - B1.x - (A2.x - A1.x);
			float numeratorX = A1.x - B1.x;
			bool n0nx = near0(numeratorX), n0dx = near0(denominatorX);
			if (n0dx && !n0nx)
				return false;
			float denominatorY = B2.y - B1.y - (A2.y - A1.y);
			float numeratorY = A1.y - B1.y;
			bool n0ny = near0(numeratorY), n0dy = near0(denominatorY);
			if (n0dy && !n0ny)
				return false;
			float tx, ty;
			tx = (A1.x - B1.x) / (B2.x - B1.x - (A2.x - A1.x));
			ty = (A1.y - B1.y) / (B2.y - B1.y - (A2.y - A1.y));
			bool result;
			if ((tx >= 0.0f) && (tx <= 1.0f) && (near0(tx - ty)))
			{
				result = true;
				float ipx = A1.x + tx * (A2.x - A1.x),
					ipy = A1.y + ty * (A2.y - A1.y);
			}
			else {
				result = false;
			}
			return result;
		}
		static bool near0(float val) {
			const float eps = 1.0e-8f;
			return (fabs(val) < eps);
		}
		static bool nearPoint(Vector2 A, Vector2 B) {
			return near0(A.x - B.x) && near0(A.y - B.y);
		}
		static float surface(Vector2 A, Vector2 B, Vector2 C) {
			return (A.x * (B.y - C.y) +
				B.x * (C.y - A.y) +
				C.x * (A.y - B.y)
				) / 2.0f;
		}
		static bool doesSegmentsIntersect(Vector2 A1, Vector2 A2, Vector2 B1, Vector2 B2) {
			if (nearPoint(A1, A2)) {
				if (nearPoint(B1, B2)) {
					return nearPoint(A1, B1);
				}
			}
			float sA1A2B1 = surface(A1, A2, B1),
				sA1A2B2 = surface(A1, A2, B2),
				sB1B2A1 = surface(B1, B2, A1),
				sB1B2A2 = surface(B1, B2, A2);
			return (sA1A2B1 * sA1A2B2 <= 0.0f) && (sB1B2A1 * sB1B2A2 <= 0.0f);
		}

		static void clipSegment(Vector2 A, Vector2 B, float r, float& x, float& y)
		{
			float R = float(sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y)));
			if (R <= r)
			{
				x = A.x;
				y = A.y;
			}
			else {
				x = (B.x - A.x) * (R - r);
				y = (B.y - A.y) * (R - r);
			}
		}
	};





}