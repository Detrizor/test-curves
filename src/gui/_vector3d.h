#pragma once
#include <limits>

constexpr float EPS_S = .0000001f;
constexpr float EPS = .0000100f;
constexpr float EPS_L = .0010000f;

constexpr float PI = 3.1415926535897932384626433832795f;
constexpr float PI_MUL_2 = 6.2831853071795864769252867665590f;
constexpr float PI_MUL_3 = 9.4247779607693797153879301498385f;
constexpr float PI_MUL_4 = 12.566370614359172953850573533118f;
constexpr float PI_MUL_6 = 18.849555921538759430775860299677f;
constexpr float PI_MUL_8 = 25.132741228718345907701147066236f;
constexpr float PI_DIV_2 = 1.5707963267948966192313216916398f;
constexpr float PI_DIV_3 = 1.0471975511965977461542144610932f;
constexpr float PI_DIV_4 = 0.7853981633974483096156608458199f;
constexpr float PI_DIV_6 = 0.5235987755982988730771072305466f;
constexpr float PI_DIV_8 = 0.3926990816987241548078304229099f;

// Inline call
#ifndef IC
#define IC __forceinline
#endif

IC float _abs(float x) { return fabsf(x); }
IC float _sqrt(float x) { return sqrtf(x); }
IC float _sin(float x) { return sinf(x); }
IC float _cos(float x) { return cosf(x); }
IC bool fis_zero(float val, float cmp = EPS_S) { return _abs(val) < cmp; }

template <class T>
struct _vector3
{
public:
    typedef T TYPE;
    typedef _vector3<T> Self;
    typedef Self& SelfRef;
    typedef const Self& SelfCRef;
public:
    T x, y, z;

    // access operators
    IC T& operator[] (int i) { return *((T*)this + i); }
    IC T& operator[] (int i) const { return *((T*)this + i); }

    IC SelfRef set(T _x, T _y, T _z) { x = _x; y = _y; z = _z; return *this; };
    IC SelfRef set(const _vector3<float>& v) { x = T(v.x); y = T(v.y); z = T(v.z); return *this; };
    IC SelfRef set(const _vector3<double>& v) { x = T(v.x); y = T(v.y); z = T(v.z); return *this; };
    IC SelfRef set(float* p) { x = p[0]; y = p[1]; z = p[2]; return *this; };
    IC SelfRef set(double* p) { x = p[0]; y = p[1]; z = p[2]; return *this; };

    IC SelfRef add(const Self& v) { x += v.x; y += v.y; z += v.z; return *this; };
    IC SelfRef add(T s) { x += s; y += s; z += s; return *this; };
    IC SelfRef add(const Self& a, const Self& v) { x = a.x + v.x; y = a.y + v.y; z = a.z + v.z; return *this; };
    IC SelfRef add(const Self& a, T s) { x = a.x + s; y = a.y + s; z = a.z + s; return *this; };

    IC SelfRef sub(const Self& v) { x -= v.x; y -= v.y; z -= v.z; return *this; };
    IC SelfRef sub(T s) { x -= s; y -= s; z -= s; return *this; };
    IC SelfRef sub(const Self& a, const Self& v) { x = a.x - v.x; y = a.y - v.y; z = a.z - v.z; return *this; };
    IC SelfRef sub(const Self& a, T s) { x = a.x - s; y = a.y - s; z = a.z - s; return *this; };

    IC SelfRef mul(const Self& v) { x *= v.x; y *= v.y; z *= v.z; return *this; };
    IC SelfRef mul(T s) { x *= s; y *= s; z *= s; return *this; };
    IC SelfRef mul(const Self& a, const Self& v) { x = a.x*v.x; y = a.y*v.y; z = a.z*v.z; return *this; };
    IC SelfRef mul(const Self& a, T s) { x = a.x*s; y = a.y*s; z = a.z*s; return *this; };

    IC SelfRef div(const Self& v) { x /= v.x; y /= v.y; z /= v.z; return *this; };
    IC SelfRef div(T s) { x /= s; y /= s; z /= s; return *this; };
    IC SelfRef div(const Self& a, const Self& v) { x = a.x / v.x; y = a.y / v.y; z = a.z / v.z; return *this; };
    IC SelfRef div(const Self& a, T s) { x = a.x / s; y = a.y / s; z = a.z / s; return *this; };

    IC SelfRef invert() { x = -x; y = -y; z = -z; return *this; }
    IC SelfRef invert(const Self& a) { x = -a.x; y = -a.y; z = -a.z; return *this; }

    IC SelfRef min_(const Self& v1, const Self& v2) { x = _min(v1.x, v2.x); y = _min(v1.y, v2.y); z = _min(v1.z, v2.z); return *this; }
    IC SelfRef min_(const Self& v) { x = _min(x, v.x); y = _min(y, v.y); z = _min(z, v.z); return *this; }
    IC SelfRef max_(const Self& v1, const Self& v2) { x = _max(v1.x, v2.x); y = _max(v1.y, v2.y); z = _max(v1.z, v2.z); return *this; }
    IC SelfRef max_(const Self& v) { x = _max(x, v.x); y = _max(y, v.y); z = _max(z, v.z); return *this; }

    IC SelfRef abs(const Self& v) { x = _abs(v.x); y = _abs(v.y); z = _abs(v.z); return *this; }
    IC bool similar(const Self& v, T E = EPS_L) const { return _abs(x - v.x) < E && _abs(y - v.y) < E && _abs(z - v.z) < E; };

    IC SelfRef set_length(T l)
    {
        mul(l / magnitude());
        return *this;
    }

    // Align vector3 by axis (!y)
    IC SelfRef align()
    {
        y = 0;
        if (_abs(z) >= _abs(x)) { z /= _abs(z ? z : 1); x = 0; }
        else { x /= _abs(x); z = 0; }
        return *this;
    }

    // Squeeze
    IC SelfRef squeeze(T Epsilon)
    {
        if (_abs(x) < Epsilon) x = 0;
        if (_abs(y) < Epsilon) y = 0;
        if (_abs(z) < Epsilon) z = 0;
        return *this;
    }

    // Clamp vector3
    IC SelfRef clamp(const Self& min, const Self& max)
    {
        ::clamp(x, min.x, max.x);
        ::clamp(y, min.y, max.y);
        ::clamp(z, min.z, max.z);
        return *this;
    }

    IC SelfRef clamp(const Self& _v)
    {
        Self v;
        v.x = _abs(_v.x);
        v.y = _abs(_v.y);
        v.z = _abs(_v.z);
        ::clamp(x, -v.x, v.x);
        ::clamp(y, -v.y, v.y);
        ::clamp(z, -v.z, v.z);
        return *this;
    }

    // Interpolate vectors (inertion)
    IC SelfRef inertion(const Self& p, T v)
    {
        T inv = 1.f - v;
        x = v*x + inv*p.x;
        y = v*y + inv*p.y;
        z = v*z + inv*p.z;
        return *this;
    }
    IC SelfRef average(const Self& p)
    {
        x = (x + p.x)*0.5f;
        y = (y + p.y)*0.5f;
        z = (z + p.z)*0.5f;
        return *this;
    }
    IC SelfRef average(const Self& p1, const Self& p2)
    {
        x = (p1.x + p2.x)*0.5f;
        y = (p1.y + p2.y)*0.5f;
        z = (p1.z + p2.z)*0.5f;
        return *this;
    }
    IC SelfRef lerp(const Self& p1, const Self& p2, T t)
    {
        T invt = 1.f - t;
        x = p1.x*invt + p2.x*t;
        y = p1.y*invt + p2.y*t;
        z = p1.z*invt + p2.z*t;
        return *this;
    }

    // Direct vector3 from point P by dir D with length M
    IC SelfRef mad(const Self& d, T m)
    {
        x += d.x*m;
        y += d.y*m;
        z += d.z*m;
        return *this;
    }
    IC SelfRef mad(const Self& p, const Self& d, T m)
    {
        x = p.x + d.x*m;
        y = p.y + d.y*m;
        z = p.z + d.z*m;
        return *this;
    }
    IC SelfRef mad(const Self& d, const Self& s)
    {
        x += d.x*s.x;
        y += d.y*s.y;
        z += d.z*s.z;
        return *this;
    }
    IC SelfRef mad(const Self& p, const Self& d, const Self& s)
    {
        x = p.x + d.x*s.x;
        y = p.y + d.y*s.y;
        z = p.z + d.z*s.z;
        return *this;
    }

    // SQ magnitude
    IC T square_magnitude(void) const
    {
        return x*x + y*y + z*z;
    }
    // magnitude
    IC T magnitude(void) const
    {
        return _sqrt(square_magnitude());
    }

    // Normalize
    IC T normalize_magn(void)
    {
        T len = magnitude();
        T inv_len = T(1) / len;
        x *= inv_len;
        y *= inv_len;
        z *= inv_len;
        return len;
    }

    IC SelfRef normalize(void)
    {
        T mag = _sqrt(T(1) / (x*x + y*y + z*z));
        x *= mag;
        y *= mag;
        z *= mag;
        return *this;
    }

    // Safe-Normalize
    IC SelfRef normalize_safe(void)
    {
        T magnitude = x*x + y*y + z*z;
        if (magnitude > std::numeric_limits<T>::min())
        {
            magnitude = _sqrt(1 / magnitude);
            x *= magnitude;
            y *= magnitude;
            z *= magnitude;
        }
        return *this;
    }

    // Normalize
    IC SelfRef normalize(const Self& v)
    {
        T mag = _sqrt(1 / (v.x*v.x + v.y*v.y + v.z*v.z));
        x = v.x*mag;
        y = v.y*mag;
        z = v.z*mag;
        return *this;
    }

    // Safe-Normalize
    IC SelfRef normalize_safe(const Self& v)
    {
        T magnitude = v.x*v.x + v.y*v.y + v.z*v.z;
        if (magnitude > std::numeric_limits<T>::min())
        {
            magnitude = _sqrt(1 / magnitude);
            x = v.x*magnitude;
            y = v.y*magnitude;
            z = v.z*magnitude;
        }
        return *this;
    }

    // DotProduct
    IC T dotproduct(const Self& v) const // v1*v2
    {
        return x*v.x + y*v.y + z*v.z;
    }

    // CrossProduct
    IC SelfRef crossproduct(const Self& v1, const Self& v2) // (v1,v2) -> this
    {
        x = v1.y * v2.z - v1.z * v2.y;
        y = v1.z * v2.x - v1.x * v2.z;
        z = v1.x * v2.y - v1.y * v2.x;
        return *this;
    }

    // Distance calculation
    IC T distance_to_xz(const Self& v) const
    {
        return _sqrt((x - v.x)*(x - v.x) + (z - v.z)*(z - v.z));
    }
    IC T distance_to_xz_sqr(const Self& v) const
    {
        return (x - v.x)*(x - v.x) + (z - v.z)*(z - v.z);
    }

    // Distance calculation
    IC T distance_to_sqr(const Self& v) const
    {
        return (x - v.x)*(x - v.x) + (y - v.y)*(y - v.y) + (z - v.z)*(z - v.z);
    }

    // Distance calculation
    IC T distance_to(const Self& v) const
    {
        return _sqrt(distance_to_sqr(v));
    }

    // Barycentric coords
    IC SelfRef from_bary(const Self& V1, const Self& V2, const Self& V3, T u, T v, T w)
    {
        x = V1.x*u + V2.x*v + V3.x*w;
        y = V1.y*u + V2.y*v + V3.y*w;
        z = V1.z*u + V2.z*v + V3.z*w;
        return *this;
    }
    IC SelfRef from_bary(const Self& V1, const Self& V2, const Self& V3, const Self& B)
    {
        from_bary(V1, V2, V3, B.x, B.y, B.z);
        return *this;
    }

    IC SelfRef from_bary4(const Self& V1, const Self& V2, const Self& V3, const Self& V4, T u, T v, T w, T t)
    {
        x = V1.x*u + V2.x*v + V3.x*w + V4.x*t;
        y = V1.y*u + V2.y*v + V3.y*w + V4.y*t;
        z = V1.z*u + V2.z*v + V3.z*w + V4.z*t;
        return *this;
    }

    IC SelfRef mknormal_non_normalized(const Self& p0, const Self& p1, const Self& p2)
    {
        _vector3<T> v01, v12;
        v01.sub(p1, p0);
        v12.sub(p2, p1);
        crossproduct(v01, v12);
        return *this;
    };
    IC SelfRef mknormal(const Self& p0, const Self& p1, const Self& p2)
    {
        mknormal_non_normalized(p0, p1, p2);
        normalize_safe();
        return *this;
    };
    IC SelfRef setHP(T h, T p)
    {
        T _ch = _cos(h), _cp = _cos(p), _sh = _sin(h), _sp = _sin(p);
        x = -_cp*_sh;
        y = _sp;
        z = _cp*_ch;
        return *this;
    }
    IC void getHP(T& h, T& p) const
    {
        float hyp;

        if (fis_zero(x) && fis_zero(z))
        {
            h = 0.0f;
            if (!fis_zero(float(y))) p = (y > 0.0f) ? PI_DIV_2 : -PI_DIV_2;
            else p = 0.0f;
        }
        else
        {
            if (fis_zero(z)) h = (x > 0.0f) ? -PI_DIV_2 : PI_DIV_2;
            else if (z < 0.0f) h = -(atanf(x / z) - PI);
            else h = -atanf(x / z);
            hyp = _sqrt(x*x + z*z);
            if (fis_zero(float(hyp))) p = (y > 0.0f) ? PI_DIV_2 : -PI_DIV_2;
            else p = atanf(y / hyp);
        }
    }
    IC float getH() const
    {
        if (fis_zero(x) && fis_zero(z))
        {
            return 0.0f;
        }
        else
        {
            if (fis_zero(z)) return (x > 0.0f) ? -PI_DIV_2 : PI_DIV_2;
            else if (z < 0.0f) return -(atanf(x / z) - PI);
            else return -atanf(x / z);
        }
    }
    IC float getP() const
    {
        if (fis_zero(x) && fis_zero(z))
        {
            if (!fis_zero(float(y))) return (y > 0.0f) ? PI_DIV_2 : -PI_DIV_2;
            else return 0.0f;
        }
        else
        {
            float hyp = _sqrt(x*x + z*z);
            if (fis_zero(float(hyp))) return (y > 0.0f) ? PI_DIV_2 : -PI_DIV_2;
            else return atanf(y / hyp);
        }
    }
    IC SelfRef reflect(const Self& dir, const Self& norm)
    {
        return mad(dir, norm, -2 * dir.dotproduct(norm));
    }
    IC SelfRef slide(const Self& dir, const Self& norm)
    {
        // non normalized
        return mad(dir, norm, -dir.dotproduct(norm));
    }
    IC static void generate_orthonormal_basis(const _vector3<T>& dir, _vector3<T>& up, _vector3<T>& right)
    {
        T fInvLength;

        if (_abs(dir.x) >= _abs(dir.y))
        {
            // W.x or W.z is the largest magnitude component, swap them
            fInvLength = 1.f / _sqrt(dir.x*dir.x + dir.z*dir.z);
            up.x = -dir.z*fInvLength;
            up.y = 0.0f;
            up.z = +dir.x*fInvLength;
        }
        else
        {
            // W.y or W.z is the largest magnitude component, swap them
            fInvLength = 1.f / _sqrt(dir.y*dir.y + dir.z*dir.z);
            up.x = 0.0f;
            up.y = +dir.z*fInvLength;
            up.z = -dir.y*fInvLength;
        }

        right.crossproduct(up, dir); //. <->
    }
    IC static void generate_orthonormal_basis_normalized(_vector3<T>& dir, _vector3<T>& up, _vector3<T>& right)
    {
        T fInvLength;
        dir.normalize();
        if (fsimilar(dir.y, 1.f, EPS))
        {
            up.set(0.f, 0.f, 1.f);
            fInvLength = 1.f / _sqrt(dir.x*dir.x + dir.y*dir.y);
            // cross (up,dir) and normalize (right)
            right.x = -dir.y * fInvLength;
            right.y = dir.x * fInvLength;
            right.z = 0.f;
            // cross (dir,right)
            up.x = -dir.z * right.y;
            up.y = dir.z * right.x;
            up.z = dir.x * right.y - dir.y * right.x;
        }
        else
        {
            up.set(0.f, 1.f, 0.f);
            fInvLength = 1.f / _sqrt(dir.x*dir.x + dir.z*dir.z);
            // cross (up,dir) and normalize (right)
            right.x = dir.z * fInvLength;
            right.y = 0.f;
            right.z = -dir.x * fInvLength;
            // cross (dir,right)
            up.x = dir.y * right.z;
            up.y = dir.z * right.x - dir.x * right.z;
            up.z = -dir.y * right.x;
        }
    }

	IC SelfRef rotate(float angle, int axis)
	{
		T* dx, *dy;
		switch (axis)
		{
			case 0:
				dx = &z;
				dy = &y;
				break;
			case 1:
				dx = &x;
				dy = &z;
				break;
			case 2:
				dx = &y;
				dy = &x;
				break;
			default:
				return *this;
		}
		T dx_backup = *dx;
		*dx = *dx * cos(angle) + *dy * sin(angle);
		*dy = *dy * cos(angle) - dx_backup * sin(angle);
		return *this;
	}

	IC SelfRef rotate(float angle_x, float angle_y, float angle_z)
	{
		rotate(angle_x, 0);
		rotate(angle_y, 1);
		rotate(angle_z, 2);
		return *this;
	}

	IC SelfRef rotate(const SelfRef angle_vec)
	{
		rotate(angle_vec.x, angle_vec.y, angle_vec.z);
		return *this;
	}

	IC Self rotate_(const SelfRef angle_vec) const
	{
		Self res = *this;
		res.rotate(angle_vec.x, angle_vec.y, angle_vec.z);
		return res;
	}
};

typedef _vector3<float> Fvector;
typedef _vector3<float> Fvector3;
typedef _vector3<double> Dvector;
typedef _vector3<double> Dvector3;
typedef _vector3<int> Ivector;
typedef _vector3<int> Ivector3;

//////////////////////////////////////////////////////////////////////////

constexpr Fvector vZero = { 0.f, 0.f, 0.f };
