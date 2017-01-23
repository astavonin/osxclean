#include <app_uninstaller.hpp>

#include <boost/exception/all.hpp>
#include <boost/format.hpp>
#include <boost/test/unit_test.hpp>
#include <fstream>
#include <iostream>
#include <prettyprint.hpp>
#include <vector>

using namespace uninstaller;
using boost::format;

BOOST_AUTO_TEST_SUITE( AppUninstallerTests )

BOOST_AUTO_TEST_CASE( invalid_app_name )
{
    BOOST_CHECK_THROW( app_uninstaller( "/Applications/NoSuchApp.app" ),
                       std::runtime_error );
}

objects_list build_objects_list( const objects_list  with_full_path,
                                 const objects_list &objs )
{
    static const std::string home( getenv( "HOME" ) );
    objects_list             res( with_full_path );

    for( auto obj : objs ) res.push_back( home + "/" + obj );
    std::sort( res.begin(), res.end() );

    return res;
}

BOOST_AUTO_TEST_CASE( viber_test )
{
    objects_list expected( build_objects_list(
        {"/Applications/Viber.app"},
        {"Library/Application Support/ViberPC",
         "Library/Caches/com.crashlytics.data/com.viber.osx",
         "Library/Saved Application State/com.viber.osx.savedState",
         "Library/Caches/com.viber.osx",
         "Library/Preferences/com.viber.osx.plist",
         "Library/Application Support/com.viber.osx"} ) );

    app_uninstaller un( "/Applications/Viber.app" );
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

BOOST_AUTO_TEST_CASE( vlc_test )
{
    objects_list expected( build_objects_list(
        {"/Applications/VLC.app"},
        {"Library/Application Support/VLC", "Library/Caches/org.videolan.vlc",
         "Library/Preferences/org.videolan.vlc",
         "Library/Preferences/org.videolan.vlc.plist",
         "Library/Saved Application State/org.videolan.vlc.savedState",
         "Library/Application Support/org.videolan.vlc"} ) );

    app_uninstaller un( "/Applications/VLC.app" );
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

BOOST_AUTO_TEST_CASE( remove_test )
{
    BOOST_REQUIRE( fs::create_directory( "dir1" ) );
    BOOST_REQUIRE( fs::create_directory( "dir1/subdir1" ) );
    BOOST_REQUIRE( fs::create_directory( "dir2" ) );

    {
        std::ofstream f( "dir1/test.txt" );
        BOOST_REQUIRE( f.is_open() );
        f << "some data";
    }
    {
        std::ofstream f( "dir2/test.txt" );
        BOOST_REQUIRE( f.is_open() );
        f << "some data";
    }
    fs::permissions( "dir2/test.txt", fs::remove_perms | fs::owner_write |
                                          fs::group_write | fs::others_write );

    objects_list    to_delete( {"dir1", "dir2"} );
    app_uninstaller un( "/Applications/VLC.app" );  // any name is Ok here
    auto            access_errors = un.uninstall( to_delete );

    BOOST_CHECK( access_errors.size() == 0 );
}

BOOST_AUTO_TEST_SUITE_END()
