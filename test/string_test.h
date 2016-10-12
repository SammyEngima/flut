#pragma once
#include "flut/system/types.hpp"
#include "flut/string_tools.hpp"
#include "flut/system/test_framework.hpp"
#include "flut/system/path.hpp"

namespace flut
{
	void string_test()
	{
		string s = "Test 0.123 24";
		string a;
		double d;
		int i;
		scan_str( s, a, d, i );
		FLUT_TEST( a == "Test" );
		FLUT_TEST( d == 0.123 );
		FLUT_TEST( i == 24 );

		auto vs = split_str( s, " " );
		FLUT_TEST( vs[ 0 ] == "Test" );
		FLUT_TEST( vs[ 1 ] == "0.123" );
		FLUT_TEST( vs[ 2 ] == "24" );

		path p( "X:/appel/taart.txt" );
		FLUT_TEST( p.empty() == false );
		FLUT_TEST( p.extension() == "txt" );
		FLUT_TEST( p.replace_extension( "new_ext" ).str() == "X:/appel/taart.new_ext" );
		FLUT_TEST( p.filename() == "taart.new_ext");
		FLUT_TEST( p.stem() == "taart");
		FLUT_TEST( path( "foo/bar.txt" ).stem() == "bar" );
		FLUT_TEST( path( "foo/.bar" ).stem() == "" );
		FLUT_TEST( p.replace_filename( "new" ) == "X:/appel/new" );
		FLUT_TEST( path( "X:/test" ) / "bla" == "X:/test/bla" );
		FLUT_TEST( path( "X:/test/" ) / "bla" == "X:/test/bla" );
		FLUT_TEST( path( "X:\\test\\bla" ).make_preferred() == "X:/test/bla" );
	}
}