#pragma once

#include "flut/system/types.hpp"
#include <limits>

namespace flut
{
	/// constants
	template< typename T > struct num_const
	{
		static constexpr T pi() { return T( 3.14159265358979 ); }
		static T half_pi() { return T( 0.5 ) * T( 3.14159265358979 ); }
		static T two_pi() { return T( 2 ) * T( 3.14159265358979 ); }
		static T epsilon() { return std::numeric_limits< T >::epsilon(); }
		static T relaxed_epsilon() { return T( 4 * std::numeric_limits< T >::epsilon() ); }
		static T one() { return T( 1 ); }
		static T zero() { return T( 0 ); }
		static T max() { return std::numeric_limits<T>::max(); }
		static T min() { return std::numeric_limits<T>::min(); }
		static T lowest() { return std::numeric_limits<T>::lowest(); }
		static T nan() { return std::numeric_limits<T>::quiet_NaN(); }
		static constexpr T rare() { return std::numeric_limits<T>::is_signed ? std::numeric_limits<T>::lowest() : std::numeric_limits<T>::max(); }
	};

	typedef num_const< int > num_const_i;
	typedef num_const< float > num_const_f;
	typedef num_const< double > num_const_d;

	const real_t real_pi = num_const< real_t >::pi();
	const float float_pi = num_const< float >::pi();
	const double double_pi = num_const< double >::pi();

	namespace math
	{
		/// convert rad to deg
		template< typename T > T rad_to_deg( T rad_value ) { return ( T( 180 ) / num_const<T>::pi() ) * rad_value; }

		/// convert deg to rad
		template< typename T > T deg_to_rad( T deg_value ) { return ( num_const<T>::pi() / T( 180 ) ) * deg_value; }

		/// compare floating point variables using relaxed_epsilon
		template< typename T > bool equals( T v1, T v2, T e = num_const<T>::relaxed_epsilon() ) { return std::abs( v1 - v2 ) <= std::abs( v1 ) * e; }

		/// inverse of v (1 / v)
		template< typename T > T inv( T v ) { return T(1) / v; }

		/// inverse of sqrt
		template< typename T > T invsqrt( T v ) { return T(1) / sqrt( v ); }

		/// sqrt based on sign: if v >= 0 sqrt( v ) else -sqrt( -v )
		template< typename T > T signed_sqrt( T v ) { return v >= T(0) ? sqrt( v ) : -sqrt( -v ); }

		/// squared
		template< typename T > T squared( T v ) { return v * v; }

		/// cubed
		template< typename T > T cubed( T v ) { return v * v * v; }

		/// sign of v: 1 or -1
		template< typename T > T sign( T v ) { return v >= T(0) ? T(1) : T(-1); }

		/// set if smaller
		template< typename T > T& set_if_smaller( T& value, const T& other ) { if ( other < value ) value = other; return value; }

		/// set if bigger
		template< typename T > T& set_if_bigger( T& value, const T& other ) { if ( other > value ) value = other; return value; }

		/// check if an integer value is a power of two
		template< typename T > bool is_power_of_two( T v ) { return v != 0 && !( v & ( v - 1 ) ); }

		/// check if an integer value is odd / even
		template< typename T > bool is_even( T v ) { return ( v & 1 ) == 0; }
		template< typename T > bool is_odd( T v ) { return ( v & 1 ) == 1; }

		/// clamp a value so that it is between min and max
		template< typename T > T& clamp( T& v, const T& min, const T& max )
		{ if ( v < min ) v = min; else if ( v > max ) v = max; return v; } // TODO: use efficient instructions

		/// return clamped value that is between min and max
		template< typename T > T clamped( T v, const T& min, const T& max )
		{ return clamp( v, min, max ); }

		/// limit transform function
		template< typename T > T limit_transfer( T x, T limit ) { return limit - limit * limit / ( x + limit ); }

		/// clamp with smooth boundary transformation
		template< typename T > T soft_clamp( T& v, const T& min, const T& max, const T& boundary ) {
			auto r = boundary * ( max - min );
			if ( v > max - r ) v = max - r + limit_transfer( v - max + r, r );
			else if ( v < min + r )	v = min + r - limit_transfer( min + r - v, r );
			return v;
		}

		template< typename T > T soft_clamped( T v, const T& min, const T& max, const T& boundary )
		{ return soft_clamp( v, min, max, boundary ); }


		/// check a value is within a range
		template< typename T > bool is_between( T v, T min, T max ) { return ( v >= min && v <= max ); }

		/// square wave, period = 2, min = -1, max = 1
		template< typename T > T square_wave( T v ) { return fmod( v, T(2) ) < T(1) ? T(1) : T(-1); }
	}
}
