#include <libA.h>
#include <algorithm>
#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

int main( int argc, char *argv[] )
{
    try
    {
        po::options_description desc( "Options" );
        desc.add_options()( "help", "Show help message" )(
            "size", po::value<size_t>(), "Default buffer size" );

        po::variables_map vm;
        po::store( po::parse_command_line( argc, argv, desc ), vm );
        po::notify( vm );

        if( vm.count( "help" ) || !vm.count( "size" ) )
        {
            std::cout << desc << "\n";
            return 1;
        }

    }
    catch( const po::error &ex )
    {
        std::cerr << ex.what() << '\n';
    }

    return 0;
}
