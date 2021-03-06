#pragma once

#include "flut/system/types.hpp"
#include <iosfwd>
#include <vector>
#include "flut/container_tools.hpp"
#include "buffer/data_header.hpp"

namespace flut
{
	template< typename T, typename L = string >
	class table
	{
	public:
		table( size_t rows = 0, size_t cols = 0 ) : row_labels_( rows ), col_labels_( cols ), data_( rows * cols ) {}
		~table() {}

		index_t add_row( const L& label, const T& default_value = T() ) {
			row_labels_.add( label );
			data_.resize( row_size() * column_size(), default_value );
			return row_size() - 1;
		}

		index_t add_column( const L& label, const T& default_value = T() ) {
			resize( row_size(), column_size() + 1 );
			return col_labels_.set( column_size() - 1, label );
		}

		index_t get_or_add_row( const L& label, const T& default_value = T() ) {
			auto idx = row_labels_.find( label );
			return idx == no_index ? add_row( label, default_value ) : idx;
		}

		index_t get_or_add_column( const L& label, const T& default_value = T() ) {
			auto idx = col_labels_.find( label );
			return idx == no_index ? add_column( label, default_value ) : idx;
		}

		void resize( size_t rows, size_t cols ) {
			flut_error_if( rows < row_size() || cols < column_size(), "tables cannot be shrinked" );

			// reorganize existing data
			data_.resize( row_size() * cols );
			for ( index_t ri = rows; ri-- > 0; )
				for ( index_t ci = cols; ci-- > 0; )
					data_[ cols * ri + ci ] = ( ri < row_size() && ci < column_size() ) ? data_[ column_size() * ri + ci ] : T();
			col_labels_.resize( cols );
			row_labels_.resize( rows );
		}

		size_t row_size() const { return row_labels_.size(); }
		size_t column_size() const { return col_labels_.size(); }

		const data_header< L >& row_labels() const { return row_labels_; }
		const data_header< L >& col_labels() const { return col_labels_; }

		const T& operator()( index_t row, index_t col ) const { flut_assert( row < row_size() && col < column_size() ); return data_[ row * column_size() + col ]; }
		T& operator()( index_t row, index_t col ) { flut_assert( row < row_size() && col < column_size() ); return data_[ row * column_size() + col ]; }

		const T& operator()( const L& row, const L& col ) const { return (*this)( row_index( row ), col_index( col ) ); }
		T& operator()( const L& row, const L& col ) { return (*this)( get_or_add_row( row ), get_or_add_column( col ) ); }

	private:

		data_header< L > row_labels_;
		data_header< L > col_labels_;
		vector< T > data_;
	};

	template< typename T >
	std::ostream& operator<<( std::ostream& str, const table< T >& t ) {
		str << "Row";
		for ( auto& rl : t.col_labels() )
			str << "\t" << rl;
		str << std::endl;

		for ( index_t row = 0; row < t.row_size(); ++row )
		{
			str << t.row_labels()[ row ];
			for ( index_t col = 0; col < t.column_size(); ++col )
				str << "\t" << t( row, col );
			str << std::endl;
		}

		return str;
	}
}
