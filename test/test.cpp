#include "test.h"
#include "math_test.h"
#include "buffer_test.h"
#include "flut/prop_node.hpp"
#include "flut/system_tools.hpp"
#include "prop_node_test.h"
#include "flut/stopwatch.hpp"
#include "flut/system/test_framework.hpp"
#include "string_test.h"
#include "flut/dictionary.hpp"
#include "flut/system/log_sink.hpp"
#include "factory_test.h"
#include "container_test.h"
#include "timer_test.h"
#include "flut/system/profiler.hpp"

using flut::string;

int main( int argc, char* argv[] )
{
	flut::log::stream_sink str( flut::log::info_level, std::cout );
	flut::log::add_sink( &str );

	try
	{
		flut_logvar2( flut::num_const<double>::epsilon(), flut::num_const<double>::relaxed_epsilon() );
		flut_logvar2( flut::num_const<float>::epsilon(), flut::num_const<float>::relaxed_epsilon() );

		str.set_log_level( flut::log::trace_level );

		flut::timer_test();
#ifdef FLUT_USE_PROFILER
		flut::profile_test();
#endif

		flut::stopwatch sw;

		flut::container_test();
		sw.add_measure( "container" );

		flut::factory_test();
		sw.add_measure( "factory" );

		flut::prop_node_test();
		sw.add_measure( "prop_node" );

		flut::string_test();
		sw.add_measure( "string" );

		flut::buffer_test();
		sw.add_measure( "buffer" );

		flut::math::optional_test();
		flut::math::clamp_test();
		flut::math::linear_regression_test();
		flut::math::math_test();
		flut::math::function_test();
		flut::math::angle_test();
		flut::math::vec_quat_test();
		sw.add_measure( "math" );

		auto pn = sw.get_report();
		flut::log::info( pn );
	}
	catch ( std::exception& e )
	{
		std::cout << e.what();				
	}

	return flut::test_framework::get_instance().report();
}
