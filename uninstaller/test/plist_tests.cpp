#include <plist.h>

#include <boost/exception/all.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( PlistTests )

BOOST_AUTO_TEST_CASE( plist_load )
{
    uninstaller::plist pl( "./test_data/Info.plist" );
    BOOST_REQUIRE_EQUAL( pl.get_value( "CFBundleIdentifier" ),
                         "com.valvesoftware.steam" );

    BOOST_CHECK_THROW( uninstaller::plist( "./wrong_path.plist" ),
                       std::runtime_error );
}

BOOST_AUTO_TEST_SUITE_END()
