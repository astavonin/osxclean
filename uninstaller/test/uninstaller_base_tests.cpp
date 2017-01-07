#include <uninstaller.h>

#include <boost/exception/all.hpp>
#include <boost/test/unit_test.hpp>

using namespace uninstaller;

BOOST_AUTO_TEST_SUITE( UninstallerBaseTests )

BOOST_AUTO_TEST_CASE( uninstaller_create )
{
    BOOST_CHECK_THROW( create_uninstaller( "com.apple.pkg.iTunesX",
                                           filter_type::pkg_id, false ),
                       std::invalid_argument );

    auto uninst = create_uninstaller( "/Applications/Calculator.app",
                                      filter_type::app_path_name, false );
    BOOST_TEST( uninst.get() );
}

BOOST_AUTO_TEST_SUITE_END()
