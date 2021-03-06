#pragma once

#include <functional>
#include <memory>
#include "system/assert.hpp"
#include "system/platform.hpp"
#include "flat_map.hpp"

// need for demangling with GCC
#ifndef FLUT_COMP_MSVC
#	include <cxxabi.h>
#endif

namespace flut
{
	template< typename T, class ...Args >
	class factory
	{
	public:
		typedef std::function< std::unique_ptr< T >( Args... ) > create_func_t;

		// register class
		template< typename U > void register_class( const std::string& name = clean_type_name<U>() )
		{ func_map_[ name ] = []( Args... args ) { return std::unique_ptr< T >( new U( args... ) ); }; }

		// access function
		const create_func_t& operator[]( const string& type ) const
		{ auto it = func_map_.find( type ); flut_error_if( it == func_map_.end(), "Unregistered type: " + type ); return it->second; }

		// create instance
		std::unique_ptr< T > create( const std::string& type, Args... args ) const { return ( *this )[ type ]( args... ); }

		// try create instance
		std::unique_ptr< T > try_create( const std::string& type, Args... args ) const
		{ auto it = func_map_.find( type ); return it != func_map_.end() ? it->second( args... ) : nullptr; }

		// create instance
		std::unique_ptr< T > operator()( const std::string& type, Args... args ) const { return create( type, args... ); }

		bool empty() const { return func_map_.empty(); }
		bool has_type( const string& type ) const { return func_map_.find( type ) != func_map_.end(); }

	private:
		flut::flat_map< std::string, create_func_t > func_map_;
	};
}
