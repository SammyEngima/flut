#pragma once

#include "flut/system/types.hpp"
#include "flut/flat_map.hpp"
#include "flut/prop_node.hpp"
#include "par_info.hpp"

#if defined(_MSC_VER)
#	pragma warning( push )
#	pragma warning( disable: 4251 )
#endif

namespace flut
{
	class FLUT_API par_set
	{
	public:
		par_set( const par_info& inf = par_info::empty(), par_vec values = par_vec() ) : info_( inf ), values_( values ) {}

		par_value get( const string& name, par_value mean, par_value std, par_value min, par_value max );
		par_value get( const string& name, const prop_node& prop );

		const par_info& info() const { return info_; }
		size_t size() const { return info_.size(); }

		const par_value& operator[]( index_t i ) const{ return values_[ i ]; }

		void push_prefix( const string& s ) { prefixes_sizes.push_back( prefix_.size() ); prefix_ += s; }
		void pop_prefix() { prefix_.resize( prefixes_sizes.back() ); prefixes_sizes.pop_back(); }
		const string& prefix() { return prefix_; }

		void set_values( const par_vec& values ) { values_ = values_; }

		void set_value( const string& name, par_value value );

	private:
		const par_info& info_;
		par_vec values_;
		flat_map< string, par_value > fixed_values_;
		string prefix_;
		std::vector< size_t > prefixes_sizes;
	};

	FLUT_API std::ostream& operator<<( std::ostream& str, const par_set& ps );
	FLUT_API std::istream& operator>>( std::istream& str, par_set& ps );

	struct scoped_prefix
	{
		scoped_prefix( par_set& ps, const string& prefix ) : ps_( ps ) { ps_.push_prefix( prefix ); }
		operator par_set&( ) { return ps_; }
		~scoped_prefix() { ps_.pop_prefix(); }
	private:
		par_set& ps_;
	};
}

#if defined(_MSC_VER)
#	pragma warning( pop )
#endif