#pragma once

#include "flut/system/types.hpp"
#include "system/assert.hpp"
#include <numeric>

namespace flut
{
	template< typename C > typename C::iterator find( C& cont, typename C::value_type& e )
	{ return std::find( std::begin( cont ), std::end( cont ), e ); }

	template< typename C, typename P > typename C::const_iterator find( const C& cont, typename C::value_type& e )
	{ return std::find( std::begin( cont ), std::end( cont ), e ); }

	template< typename C, typename P > typename C::iterator find_if( C& cont, P pred )
	{ return std::find_if( std::begin( cont ), std::end( cont ), pred ); }

	template< typename C, typename P > typename C::const_iterator find_if( const C& cont, const P pred )
	{ return std::find_if( std::cbegin( cont ), std::cend( cont ), pred ); }

	template< typename C > typename C::iterator min_element( C& cont )
	{ return std::min_element( std::begin( cont ), std::end( cont ) ); }

	template< typename C > typename C::const_iterator min_element( const C& cont )
	{ return std::min_element( std::cbegin( cont ), std::cend( cont ) ); }

	template< typename C > typename C::iterator max_element( C& cont )
	{ return std::max_element( std::begin( cont ), std::end( cont ) ); }

	template< typename C > typename C::const_iterator max_element( const C& cont )
	{ return std::max_element( std::cbegin( cont ), std::cend( cont ) ); }

	template< typename C > typename C::value_type average( const C& cont )
	{ return std::accumulate( std::cbegin( cont ), std::cend( cont ), C::value_type( 0 ) ) / C::value_type( cont.size() ); }

	template< typename T > T median( const vector< T >& vec ) {
		auto s = vec.size();
		flut_assert( s > 0 );
		auto sorted_vec = vec;
		std::sort( sorted_vec.begin(), sorted_vec.end() );
		if ( s % 2 == 1 ) return sorted_vec[ s / 2 ];
		else return ( sorted_vec[ s / 2 ] + sorted_vec[ s / 2 - 1 ] ) / T(2);
	}

	template< typename T > index_t find_index( const vector< T >& vec, const T& val ) {
		auto it = std::find( vec.begin(), vec.end(), val );
		if ( it == vec.end() ) return no_index;
		else return it - vec.begin();
	}

	template< typename T > index_t back_index( const vector< T >& vec )
	{ flut_assert( vec.size() > 0 ) return vec.size() - 1; }

	template< typename It, typename Pr > struct view_if {
		view_if( It first, It last, Pr pred ) : first_( first ), last_( last ), pred_( pred ) {}
		struct iterator {
			iterator( const view_if& cv, It pos ) : cv_( cv ), pos_( pos ) { next_match(); }
			void next_match() { while ( pos_ != cv_.last_ && !cv_.pred_( *pos_ ) ) ++pos_; }
			iterator& operator++() { ++pos_; next_match(); return *this; }
			iterator operator++( int ) { auto keepit = *this; ++pos_; next_match(); return keepit; }
			bool operator==( const iterator& other ) { return pos_ == other.pos_; }
			bool operator!=( const iterator& other ) { return pos_ != other.pos_; }
			typename It::value_type operator*() const { return *pos_; }
			const view_if& cv_;
			It pos_;
		};
		iterator begin() const { return iterator( *this, first_ ); }
		iterator end() const { return iterator( *this, last_ ); }
		It first_, last_;
		Pr pred_;
	};

	template< typename T > std::ostream& operator<<( std::ostream& str, const vector< T >& vec )
	{
		for ( auto it = vec.begin(); it != vec.end(); ++it ) {
			if ( it != vec.begin() ) str << "\t";
			str << *it;
		}
		return str;
	}

	template< typename It, typename Pr > view_if< It, Pr > make_view_if( It first, It last, Pr pred ) {
		return view_if< It, Pr >( first, last, pred );
	}

	template< typename C, typename Pr > view_if< typename C::iterator, Pr > make_view_if( C& cont, Pr pred ) {
		return view_if< typename C::iterator, Pr >( cont.begin(), cont.end(), pred );
	}
}
