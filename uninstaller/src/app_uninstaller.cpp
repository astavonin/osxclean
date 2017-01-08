#include "app_uninstaller.hpp"

#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <iostream>

#include "plist.h"

using boost::format;
using boost::algorithm::to_lower_copy;

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

void app_uninstaller::uninstall()
{
}

std::vector<object> app_uninstaller::dry_run()
{
    auto to_delete =
        std::vector<object>( {object{object_type::application, m_app_name}} );
    auto pl =
        plist( ( fs::path( m_app_name ) /= "Contents/Info.plist" ).string() );

    auto app_name    = to_lower_copy( pl.get_value( "CFBundleName" ) );
    auto app_id      = to_lower_copy( pl.get_value( "CFBundleIdentifier" ) );
    auto search_dirs = std::vector<std::string>(
        {"Library/Application Support", "Library/Caches",
         "Library/Saved Application State", "Library/Preferences",
         "Library/Caches/com.crashlytics.data"} );

    static const char *home = getenv( "HOME" );
    for( auto dir : search_dirs )
    {
        for( auto it : fs::directory_iterator( fs::absolute( dir, home ) ) )
        {
            auto name    = to_lower_copy( it.path().filename().string() );
            bool matches = name.find( app_name ) != std::string::npos ||
                           name.find( app_id ) != std::string::npos;
            if( matches )
            {
                to_delete.push_back(
                    object{object_type::directory, it.path()} );
            }
        }
    }

    return to_delete;
}
}
