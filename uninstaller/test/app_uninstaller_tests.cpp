#include <app_uninstaller.hpp>

#include <boost/exception/all.hpp>
#include <boost/format.hpp>
#include <boost/test/unit_test.hpp>
#include <vector>

using namespace uninstaller;
using boost::format;

BOOST_AUTO_TEST_SUITE( AppUninstallerTests )

BOOST_AUTO_TEST_CASE( invalid_app_name )
{
    BOOST_CHECK_THROW( app_uninstaller( "/Applications/NoSuchApp.app" ),
                       std::runtime_error );
}

BOOST_AUTO_TEST_CASE( viber_test )
{
    std::vector<std::string> expected{
        "/Applications/Viber.app",
        "Library/Application Support/ViberPC",
        "Library/Caches/com.crashlytics.data/com.viber.osx",
        "Library/Saved Application State/com.viber.osx.savedState",
        "Library/Caches/com.viber.osx",
        "Library/Application Support/com.viber.osx"};

    app_uninstaller un( "/Applications/Viber.app" );
    auto            actual = un.dry_run();

    BOOST_CHECK_EQUAL( expected.size(), actual.size() );

    for( auto e : expected )
    {
        if( std::find_if( actual.begin(), actual.end(), [&]( auto a ) {
                return a.name.string().find( e ) != std::string::npos;
            } ) == actual.end() )
        {
            BOOST_ERROR( format( "Unable to find %1%" ) % e );
        }
    }
}

BOOST_AUTO_TEST_SUITE_END()
