/**
 * Small library of mathematical data types and operations
 * 
 * Header File
 * 
 * C 2018 Braxton Salyer
 **/

#ifndef _MATH
#define _MATH

#include <math.h>
#include <iostream>

#define _USE_MATH_DEFINES

namespace fusion { namespace core { namespace math {

    class vec2{

        public:
            float m_x;
            float m_y;

            //constructors
            vec2();
            vec2(const float &x, const float &y);

            //functions to do what they say. used inside the operators
            vec2& add(const vec2 &in);
            vec2& subtract(const vec2 &in);
            vec2& multiply(const vec2 &in);
            vec2& divide(const vec2 &in);

            //operator overloads
            friend vec2 operator+(vec2 left, const vec2& right);
            vec2 operator+=(const vec2& right);
            friend vec2 operator-(vec2 left, const vec2& right);
            vec2 operator-=(const vec2& right);
            friend vec2 operator*(vec2 left, const vec2& right);
            vec2 operator*=(const vec2& right);
            friend vec2 operator/(vec2 left, const vec2& right);
            vec2 operator/=(const vec2& right);
            vec2& operator=(const vec2& right);
            bool operator==(const vec2& right);
            bool operator!=(const vec2& right);

            friend std::ostream& operator<<(std::ostream& stream, const vec2& vector) {
                stream << "vec2: (" << vector.m_x << ", " << vector.m_y << ")";
                return stream;
            }

    };

    class vec3 {

        public:
            float m_x;
            float m_y;
            float m_z;

            //constructors
            vec3();
            vec3(const float &x, const float &y, const float &z);

            //functions to do what they say. used inside the operators
            vec3& add(const vec3 &in);
            vec3& subtract(const vec3 &in);
            vec3& multiply(const vec3 &in);
            vec3& divide(const vec3 &in);

            //operator overloads
            friend vec3 operator+(vec3 left, const vec3& right);
            vec3 operator+=(const vec3& right);
            friend vec3 operator-(vec3 left, const vec3& right);
            vec3 operator-=(const vec3& right);
            friend vec3 operator*(vec3 left, const vec3& right);
            vec3 operator*=(const vec3& right);
            friend vec3 operator/(vec3 left, const vec3& right);
            vec3 operator/=(const vec3& right);
            vec3& operator=(const vec3& right);
            bool operator==(const vec3& right);
            bool operator!=(const vec3& right);

            friend std::ostream& operator<<(std::ostream& stream, const vec3& vector) {
                stream << "vec3: (" << vector.m_x << ", " << vector.m_y << ", " << vector.m_z << ")";
                return stream;
            }

    };

    class vec4 {

        public:
            float m_x;
            float m_y;
            float m_z;
            float m_w;

            //constructors
            vec4() = default;
            vec4(const float &x, const float &y, const float &z, const float &w);

            //functions to do what they say. used inside the operators
            vec4& add(const vec4 &in);
            vec4& subtract(const vec4 &in);
            vec4& multiply(const vec4 &in);
            vec4& divide(const vec4 &in);

            //operator overloads
            friend vec4 operator+(vec4 left, const vec4& right);
            vec4 operator+=(const vec4& right);
            friend vec4 operator-(vec4 left, const vec4& right);
            vec4 operator-=(const vec4& right);
            friend vec4 operator*(vec4 left, const vec4& right);
            vec4 operator*=(const vec4& right);
            friend vec4 operator/(vec4 left, const vec4& right);
            vec4 operator/=(const vec4& right);
            vec4& operator=(const vec4& right);
            bool operator==(const vec4& right);
            bool operator!=(const vec4& right);

            friend std::ostream& operator<<(std::ostream& stream, const vec4& vector) {
                stream << "vec4: (" << vector.m_x << ", " << vector.m_y << ", " << vector.m_z <<
                        ", " << vector.m_w << ")";
                return stream;
            }
    };

    class mat4 {

        public:
            //constructors
            mat4();
            mat4(float diagonal);

            union {
                float elements[4 * 4];
                vec4 columns[4];
            };

            //create the identity matrix
            static mat4 identity();

            //create an orthographic transform matrix
            static mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
            
            //create a perspective transform matrix
            static mat4 perspective(float fov, float aspectRatio, float near, float far);

            //create a translation transform matrix
            static mat4 translation(const vec3& translation);

            //create a rotational transform matrix
            static mat4 rotation(float angle, const vec3& axis);

            //create a scale transform matrix
            static mat4 scale(const vec3& scale);

            //functions to do what they say. used inside the operators
            //also operator overloads
            mat4 multiply(const mat4& right);
            friend mat4 operator*(const mat4 left, const mat4& right);
            mat4 operator*=(const mat4& right);

            vec3 multiply(const vec3& right) const;
            friend vec3 operator*(const mat4& left, const vec3& right);

            vec4 multiply(const vec4& right) const;
            friend vec4 operator*(const mat4& left, const vec4& right);

            mat4 operator=(const mat4& right);


    };
}}}

#endif
