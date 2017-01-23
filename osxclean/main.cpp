#include <boost/program_options.hpp>
#include <iostream>
#include <uninstaller.h>

namespace po = boost::program_options;
using namespace uninstaller;

void process_app( const std::string path, bool dry_run )
{
    auto uninst = create_uninstaller( path, filter_type::app_path_name, false );
    if( dry_run )
    {
        auto files    = uninst->dry_run();
        auto del_errs = uninst->uninstall( files );
        if( !del_errs.empty() )
        {
            std::cout << "Unable to delete:"
                      << "\n";
            for( auto f : del_errs )
                std::cout << f << "\n";
        }
    }
    else
    {
        auto files = uninst->dry_run();
        std::cout << "Next files will be removed:"
                  << "\n";
        for( auto f : files )
            std::cout << f << "\n";
    }
}

int main( int argc, char *argv[] )
{
    try
    {
        po::options_description desc( "Options" );
        desc.add_options()( "help", "Show help message" )(
            "dry-run,d",
            "By default. Do not remove files, only report what would be "
            "removed" )( "remove,R",
                         "Remove package/application and all dependencies" )
            //( "type,T", po::value<std::string>(), "Target type: app or pkg" )
            ( "target,t", po::value<std::string>(),
              "Path to application to remove" );

        po::variables_map vm;
        po::store( po::parse_command_line( argc, argv, desc ), vm );
        po::notify( vm );

        if( vm.count( "help" ) || vm.empty() || !vm.count( "target" ) )
        {
            std::cout << desc << "\n";
            return 1;
        }

        process_app( vm["target"].as<std::string>(), vm.count( "remove" ) );
    }
    catch( const std::exception &ex )
    {
        std::cerr << ex.what() << '\n';
    }

    return 0;
}
