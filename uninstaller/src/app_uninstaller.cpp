#include "app_uninstaller.hpp"

#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <iostream>
#include <iostream>

#include "plist.h"

using boost::system::error_code;
using boost::format;

namespace algo = boost::algorithm;

namespace uninstaller
{
app_uninstaller::app_uninstaller( const std::string &app_name )
    : m_app_name( app_name )
{
    if( !fs::is_directory( m_app_name ) )
        throw std::runtime_error(
            ( format( "Directory %1% does not exist" ) % m_app_name ).str() );
}

app_uninstaller::~app_uninstaller()
{
}

objects_list app_uninstaller::uninstall( const objects_list &objs )
{
    objects_list undeleted;

    for( auto obj : objs )
    {
        try
        {
            fs::remove_all( obj );
        }
        catch( fs::filesystem_error &er )
        {
            std::cerr << er.what() << std::endl;
            undeleted.push_back( obj );
        }
    }

    return undeleted;
}

objects_list app_uninstaller::dry_run()
{
    auto     to_delete = objects_list( {m_app_name} );
    fs::path app_path( m_app_name );
    auto     pl = plist( ( app_path /= "Contents/Info.plist" ).string() );

    auto app_name = algo::to_lower_copy( pl.get_value( "CFBundleName" ) );
    auto app_id   = algo::to_lower_copy( pl.get_value( "CFBundleIdentifier" ) );
    auto search_dirs = std::vector<std::string>(
        {"Library/Application Support", "Library/Caches",
         "Library/Saved Application State", "Library/Preferences",
         "Library/Caches/com.crashlytics.data"} );

    static const char *home = getenv( "HOME" );
    std::string app_path_name( m_app_name.begin() + m_app_name.rfind( "/" ) + 1,
                               m_app_name.begin() + m_app_name.rfind( "." ) );
    algo::to_lower( app_path_name );

    for( auto dir : search_dirs )
    {
        for( auto it : fs::directory_iterator( fs::absolute( dir, home ) ) )
        {
            auto name    = algo::to_lower_copy( it.path().filename().string() );
            bool matches = name.find( app_name ) != std::string::npos ||
                           name.find( app_id ) != std::string::npos ||
                           name.find( app_path_name ) != std::string::npos;
            if( matches )
            {
                to_delete.push_back( it.path().string() );
            }
        }
    }

    return to_delete;
}
}
