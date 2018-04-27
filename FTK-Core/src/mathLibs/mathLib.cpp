/**
 * Small library of mathematical data types and operations
 * 
 * Implementation File
 * 
 * C 2018 Braxton Salyer
 **/

#include "mathLib.h"
#include <string.h>

namespace ftk { namespace core { namespace math {

#ifndef _VEC2
#define _VEC2
    vec2::vec2() {
        m_x = 0.0f;
        m_y = 0.0f;
    }

    vec2::vec2(const float &x, const float &y) {
        m_x = x;
        m_y = y;
    }

    vec2& vec2::add(const vec2 &in) {
        m_x += in.m_x;
        m_y += in.m_y;

        return *this;
    }

    vec2& vec2::subtract(const vec2 &in) {
        m_x -= in.m_x;
        m_y -= in.m_y;

        return *this;
    }

    vec2& vec2::multiply(const vec2 &in) {
        m_x *= in.m_x;
        m_y *= in.m_y;

        return *this;
    }

    vec2& vec2::divide(const vec2 &in) {
        m_x /= in.m_x;
        m_y /= in.m_y;

        return *this;
    }

    vec2 operator+(vec2 left, const vec2& right) {
        return left.add(right);
    }

    vec2 vec2::operator+=(const vec2& right) {
        return add(right);
    }

    vec2 operator-(vec2 left, const vec2& right) {
        return left.subtract(right);
    }

    vec2 vec2::operator-=(const vec2& right) {
        return subtract(right);
    }

    vec2 operator*(vec2 left, const vec2& right) {
        return left.multiply(right);
    }

    vec2 vec2::operator*=(const vec2& right) {
        return multiply(right);
    }

    vec2 operator/(vec2&left, const vec2& right) {
        return left.divide(right);
    }

    vec2 operator/=(vec2 left, const vec2& right) {
        return left.divide(right);
    }

    vec2& vec2::operator=(const vec2& right) {
        m_x = right.m_x;
        m_y = right.m_y;

        return *this;
    }

    bool vec2::operator==(const vec2& right) {
        if ((m_x - right.m_x < 0.00001f) && (m_y - right.m_y < 0.00001f)) {
            return true;
        } else return false;
    }

    bool vec2::operator!= (const vec2& right) {
        return !(*this == right);
    }

    bool vec2::operator<(const vec2& right) {
        return (m_x < right.m_x && m_y < right.m_y);
    }

    bool vec2::operator<=(const vec2& right) {
        return (*this < right || *this == right);
    }

    bool vec2::operator>(const vec2& right) {
        return (m_x > right.m_x && m_y > right.m_y);
    }

    bool vec2::operator>=(const vec2& right) {
        return (*this > right || *this == right);
    }

    vec2 vec2::operator+(const vec3& right) {
        vec2 vec(m_x, m_y);
        vec.m_x += right.m_x;
        vec.m_y += right.m_y;

        return vec;
    }

    vec2 vec2::operator+=(const vec3& right) {
        return *this = *this + right;
    }

    vec2 vec2::operator-(const vec3& right) {
        vec2 vec(m_x, m_y);
        vec.m_x -= right.m_x;
        vec.m_y -= right.m_y;

        return vec;
    }

    vec2 vec2::operator-=(const vec3& right) {
        return *this = *this - right;
    }

    vec2 vec2::operator*(const vec3& right) {
        vec2 vec(m_x, m_y);
        vec.m_x *= right.m_x;
        vec.m_y *= right.m_y;

        return vec;
    }

    vec2 vec2::operator*=(const vec3& right) {
        return *this = *this * right;
    }

    vec2 vec2::operator/(const vec3& right) {
        vec2 vec(m_x, m_y);
        vec.m_x /= right.m_x;
        vec.m_y /= right.m_y;

        return vec;
    }

    vec2 vec2::operator/=(const vec3& right) {
        return *this = *this / right;
    }

#endif

#ifndef _VEC3
#define _VEC3
    vec3::vec3() {
       m_x = 0.0f;
       m_y = 0.0f;
       m_z = 0.0f;
    }

    vec3::vec3(const float &x, const float &y, const float &z) {
       m_x = x;
       m_y = y;
       m_z = z;
    }

    vec3& vec3::add(const vec3 &in) {
       m_x += in.m_x;
       m_y += in.m_y;
       m_z += in.m_z;

       return *this;
    }

    vec3& vec3::subtract(const vec3 &in) {
       m_x -= in.m_x;
       m_y -= in.m_y;
       m_z -= in.m_z;

       return *this;
    }

    vec3& vec3::multiply(const vec3 &in) {
       m_x *= in.m_x;
       m_y *= in.m_y;
       m_z *= in.m_z;

       return *this;
    }

    vec3& vec3::divide(const vec3 &in) {
       m_x /= in.m_x;
       m_y /= in.m_y;
       m_z /= in.m_z;

       return *this;
    }

    vec3 operator+(vec3 left, const vec3& right) {
       return left.add(right);
    }

    vec3 vec3::operator+=(const vec3& right) {
       return add(right);
    }

    vec3 operator-(vec3 left, const vec3& right) {
       return left.subtract(right);
    }

    vec3 vec3::operator-=(const vec3& right) {
       return subtract(right);
    }

    vec3 operator*(vec3 left, const vec3& right) {
       return left.multiply(right);
    }

    vec3 vec3::operator*=(const vec3& right) {
       return multiply(right);
    }

    vec3 operator/(vec3 left, const vec3& right) {
       return left.divide(right);
    }

    vec3 operator/=(vec3 left, const vec3& right) {
       return left.divide(right);
    }

    vec3& vec3::operator=(const vec3& right) {
        m_x = right.m_x;
        m_y = right.m_y;
        m_z = right.m_z;

        return *this;
    }

    bool vec3::operator==(const vec3& right) {
        if ((m_x - right.m_x < 0.00001f) && (m_y - right.m_y < 0.00001f) && ( m_z - right.m_z < 0.00001f)) {
            return true;
        } else return false;
    }

    bool vec3::operator!= (const vec3& right) {
        return !(*this == right);
    }

    bool vec3::operator<(const vec3& right) {
        return (m_x < right.m_x && m_y < right.m_y && m_z < right.m_z);
    }

    bool vec3::operator<=(const vec3& right) {
        return (*this < right || *this == right);
    }

    bool vec3::operator>(const vec3& right) {
        return (m_x > right.m_x && m_y > right.m_y && m_z > right.m_z);
    }

    bool vec3::operator>=(const vec3& right) {
        return (*this > right || *this == right);
    }

    vec3 vec3::operator+(const vec2& right) {
        vec3 vec(m_x, m_y, m_z);
        vec.m_x += right.m_x;
        vec.m_y += right.m_y;
        
        return vec;
    }

    vec3 vec3::operator+=(const vec2& right) {
        return *this = *this + right;
    }

    vec3 vec3::operator-(const vec2& right) {
        vec3 vec(m_x, m_y, m_z);
        vec.m_x -= right.m_x;
        vec.m_y -= right.m_y;

        return vec;
    }

    vec3 vec3::operator-=(const vec2& right) {
        return *this = *this - right;
    }

    vec3 vec3::operator*(const vec2& right) {
        vec3 vec(m_x, m_y, m_z);
        vec.m_x *= right.m_x;
        vec.m_y *= right.m_y;

        return vec;
    }

    vec3 vec3::operator*=(const vec2& right) {
        return *this = *this * right;
    }

    vec3 vec3::operator/(const vec2& right) {
        vec3 vec(m_x, m_y, m_z);
        vec.m_x /= right.m_x;
        vec.m_y /= right.m_y;

        return vec;
    }

    vec3 vec3::operator/=(const vec2& right) {
        return *this = *this / right;
    }
    
#endif

#ifndef _VEC4
#define _VEC4

    vec4::vec4(const float &x, const float &y, const float &z, const float &w) {
       m_x = x;
       m_y = y;
       m_z = z;
       m_w = w;

    }

    vec4& vec4::add(const vec4 &in) {
       m_x += in.m_x;
       m_y += in.m_y;
       m_z += in.m_z;
       m_w += in.m_w;

       return *this;
    }

    vec4& vec4::subtract(const vec4 &in) {
       m_x -= in.m_x;
       m_y -= in.m_y;
       m_z -= in.m_z;
       m_w -= in.m_w;

       return *this;
    }

    vec4& vec4::multiply(const vec4 &in) {
       m_x *= in.m_x;
       m_y *= in.m_y;
       m_z *= in.m_z;
       m_w *= in.m_w;

       return *this;
    }

    vec4& vec4::divide(const vec4 &in) {
       m_x /= in.m_x;
       m_y /= in.m_y;
       m_z /= in.m_z;
       m_w /= in.m_w;

       return *this;
    }

    vec4 operator+(vec4 left, const vec4& right) {
       return left.add(right);
    }

    vec4 vec4::operator+=(const vec4& right) {
       return add(right);
    }

    vec4 operator-(vec4 left, const vec4& right) {
       return left.subtract(right);
    }

    vec4 vec4::operator-=(const vec4& right) {
       return subtract(right);
    }

    vec4 operator*(vec4 left, const vec4& right) {
       return left.multiply(right);
    }

    vec4 vec4::operator*=(const vec4& right) {
       return multiply(right);
    }

    vec4 operator/(vec4 left, const vec4& right) {
       return left.divide(right);
    }

    vec4 operator/=(vec4 left, const vec4& right) {
       return left.divide(right);
    }

    vec4& vec4::operator=(const vec4& right) {
        m_x = right.m_x;
        m_y = right.m_y;
        m_z = right.m_z;
        m_w = right.m_w;

        return *this;
    }

    bool vec4::operator==(const vec4& right) {
        if ((m_x - right.m_x < 0.00001f) && (m_y - right.m_y < 0.00001f) &&
            (m_z - right.m_z < 0.00001f) && (m_w - right.m_w < 0.00001f)) {
            return true;
        } else return false;
    }

    bool vec4::operator!= (const vec4& right) {
        return !(*this == right);
    }
#endif

#ifndef _MAT4
#define _MAT4
    mat4::mat4() {

        for(int i = 0; i < 4 * 4; i ++) {
            elements[i] = 0.0f;
        }
    }

    mat4::mat4(float diagonal) {
        for(int i = 0; i < 4 * 4; i ++) {
            elements[i] = 0.0f;
        }

        elements[0 + 0 * 4] = diagonal;
        elements[1 + 1 * 4] = diagonal;
        elements[2 + 2 * 4] = diagonal;
        elements[3 + 3 * 4] = diagonal;
    }

    mat4 mat4::identity() {
        return mat4(1.0f);
    }

    mat4 mat4::multiply(const mat4& right) {

		float data[16];

        for(int y = 0; y < 4; ++y) {
            for (int x = 0; x < 4; ++x) {

                float sum = 0.0f;
                for(int e = 0; e < 4; ++e) {
                    sum += elements[x + e * 4] * right.elements[e + y * 4];
                }
                data[x + y * 4] = sum;
            }
        }

        memcpy(elements, data, 16 * sizeof(float));

        return *this;
    }

    mat4 operator*(mat4 left, const mat4& right) {
        return left.multiply(right);
    }

    mat4 mat4::operator*=(const mat4& right) {
        return multiply(right);
    }

	vec3 mat4::multiply(const vec3& right) const {

        return vec3(
            columns[0].m_x * right.m_x + columns[1].m_x * right.m_y + columns[2].m_x * right.m_z + columns[3].m_x,
            columns[0].m_y * right.m_x + columns[1].m_y * right.m_y + columns[2].m_y * right.m_z + columns[3].m_y,
            columns[0].m_z * right.m_x + columns[1].m_z * right.m_y + columns[2].m_z * right.m_z + columns[3].m_z
        );
    }

	vec3 operator*(const mat4& left, const vec3& right) {
        return left.multiply(right);
    }

    vec4 mat4::multiply(const vec4& right) const {

        return vec4(
            columns[0].m_x * right.m_x + columns[1].m_x * right.m_y + columns[2].m_x * right.m_z + columns[3].m_x * right.m_w,
            columns[0].m_y * right.m_x + columns[1].m_y * right.m_y + columns[2].m_y * right.m_z + columns[3].m_y * right.m_w,
            columns[0].m_z * right.m_x + columns[1].m_z * right.m_y + columns[2].m_z * right.m_z + columns[3].m_z * right.m_w,
            columns[0].m_w * right.m_x + columns[1].m_w * right.m_y + columns[2].m_w * right.m_z + columns[3].m_w * right.m_w
        );
    }

	vec4 operator*(const mat4& left, const vec4& right) {
        return left.multiply(right);
    }

    mat4 mat4::orthographic(float left, float right, float bottom, float top, float near, float far) {

        mat4 result(1.0f);

        result.elements[0 + 0 * 4] = 2.0 / (right - left);
        result.elements[1 + 1 * 4] = 2.0 / (top - bottom);
        result.elements[2 + 2 * 4] = 2.0 / (near - far);

        result.elements[0 + 3 * 4] = (left + right) / (left - right);
        result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
        result.elements[2 + 3 * 4] = (far + near) / (far - near);

        return result;
    }

    mat4 mat4::perspective(float fov, float aspectRatio, float near, float far) {

        mat4 result(1.0f);

        float q = 1.0f / tan((0.5f*fov)*(M_PI/180.0f));
        float a = q / aspectRatio;

        float b = (near + far) / ( near - far);
        float c = (2.0f * near * far) / (near - far);

        result.elements[0 + 0 * 4] = a;
        result.elements[1 + 1 * 4] = q;
        result.elements[2 + 2 * 4] = b;
        result.elements[3 + 2 * 4] = -1.0f;
        result.elements[2 + 3 * 4] = c;

        return result;
    }

    mat4 mat4::translation(const vec3& translation) {

        mat4 result(1.0f);

        result.elements[0 + 3 * 4] = translation.m_x;
        result.elements[1 + 3 * 4] = translation.m_y;
        result.elements[2 + 3 * 4] = translation.m_z;

        return result;
    }

    mat4 mat4::rotation(float angle, const vec3& axis) {

        mat4 result(1.0f);

        float r = angle * (M_PI/180.0f);
        float c = cos(r);
        float s = sin(r);
        float omc = 1.0f - c;

        float x = axis.m_x;
        float y = axis.m_y;
        float z = axis.m_z;

        result.elements[0 + 0 * 4] = x * omc + c;
        result.elements[1 + 0 * 4] = y * x * omc + z * s;
        result.elements[2 + 0 * 4] = x * z * omc - y * s;

        result.elements[0 + 1 * 4] = x * y * omc - z * s;
        result.elements[1 + 1 * 4] = y * omc + c;
        result.elements[2 + 1 * 4] = y * z * omc + x * s;

        result.elements[0 + 2 * 4] = x * z * omc + y * s;
        result.elements[1 + 2 * 4] = y * z * omc - x * s;
        result.elements[2 + 2 * 4] = z * omc + c;

        return result;

    }

    mat4 mat4::scale(const vec3& scale) {

        mat4 result(1.0f);

        result.elements[0 + 0 * 4] = scale.m_x;
        result.elements[1 + 1 * 4] = scale.m_y;
        result.elements[2 + 2 * 4] = scale.m_z;

        return result;
    }

    mat4 mat4::operator=(const mat4& right) {

        mat4 result(1.0f);

        for(int i = 0; i < 16; ++i) {
            result.elements[i] = right.elements[i];
        }

        return result;
    }

#endif

}}}
