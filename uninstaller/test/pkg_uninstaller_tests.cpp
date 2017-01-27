#include <boost/test/unit_test.hpp>
#include <pkg_uninstaller.hpp>
#include <prettyprint.hpp>

using namespace uninstaller;

BOOST_AUTO_TEST_SUITE( PkgUninstallerTests )

BOOST_AUTO_TEST_CASE( test_pkg_wrong_pkg_name )
{
    BOOST_CHECK_THROW( pkg_uninstaller( "no_such_pkg" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_BaseSystemResources )
{
    objects_list expected(
        {"/System", "/System/Library", "/System/Library/CoreServices",
         "/System/Library/CoreServices/SystemVersion.plist"} );

    pkg_uninstaller un( "com.apple.pkg.BaseSystemResources" );
    auto            actual = un.dry_run();
    std::sort( actual.begin(), actual.end() );

    objects_list diff;
    std::set_symmetric_difference( expected.begin(), expected.end(),
                                   actual.begin(), actual.end(),
                                   std::back_inserter( diff ) );
    BOOST_CHECK_MESSAGE( diff.size() == 0,
                         "Expected: " << expected << "\nActual: " << actual
                                      << "\nDifference: " << diff );
}

BOOST_AUTO_TEST_SUITE_END()
