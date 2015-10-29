#pragma once

#include "quat_type.hpp"

namespace flut
{
	namespace math
	{
		/** Quaternion multiplication. */
		template< typename T > quat_<T> operator*( const quat_<T>& q1, const quat_<T>& q2 );

		/** Vector multiplication. */
		template< typename T > vec3_<T> operator*( const quat_<T>& q, const vec3_<T>& v )
		{
			vec3_<T> qv( q.x, q.y, q.z );
			vec3_<T> uv = cross_product( qv, v );
			vec3_<T> uuv = cross_product( qv, uv );
			uv *= T( 2 ) * q.w;
			uuv *= T( 2 );
			return v + uv + uuv;
		}

		/** Negation (conjugate). */
		template< typename T > quat_<T> operator-( const quat_<T>& q );

		/** Normalize. */
		template< typename T > quat_<T>& normalize( const quat_<T>& q );

		/** Get Normalized. */
		template< typename T > quat_<T> normalized( const quat_<T>& q );

		/** Get quaternion using an axis and an angle. */
		//template< typename T > quat_<T> quat_from_axes( const vec3_<T>& axis, const Radian& angle );

		/** Get quaternion using three axis vectors. */
		template< typename T > quat_<T> make_from_axes( const vec3_<T>& x, const vec3_<T>& y, const vec3_<T>& z );

		/** Get quaternion using Euler angles. */
		//template< typename T > quat<T> quat_from_euler( const Radian& xAngle, const Radian& yAngle, const Radian& zAngle, EulerOrder eulerOrder = EULER_ORDER_XYZ );

		/** Get quaternion to represent the rotation from source to target vector. */
		template< typename T > quat_<T> quat_from_directions( const vec3_<T>& source, const vec3_<T>& target );

		/** Get quaternion to represent the rotation from source to target quaternion. */
		template< typename T > quat_<T> quat_from_quats( const quat_<T>& source, const quat_<T>& target );

		/** Get quaternion from rotation vector. */
		template< typename T > quat_<T> quat_from_rotation_vector( const vec3_<T>& v );
	}
}
