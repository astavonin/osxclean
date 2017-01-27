#include "pkg_uninstaller.hpp"
#include <array>
#include <boost/format.hpp>
#include <cstdio>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

using boost::format;

namespace uninstaller
{

std::string exec( const char *cmd )
{
    std::array<char, 128> buffer;
    std::string           result;
    std::shared_ptr<FILE> pipe( popen( cmd, "r" ), pclose );
    if( !pipe )
        throw std::runtime_error( "popen() failed!" );
    while( !feof( pipe.get() ) )
    {
        if( fgets( buffer.data(), 128, pipe.get() ) != NULL )
            result += buffer.data();
    }
    return result;
}

void pkg_uninstaller::load_pkg_info( const std::string pkg_name )
{
    auto              cmd  = format( "pkgutil --pkg-info %1% 2>&1" ) % pkg_name;
    auto              resp = exec( cmd.str().c_str() );
    std::stringstream ss( resp );
    std::string       l, loc, vol;

    static const std::string loc_mask( "location: " );
    static const std::string vol_mask( "volume: " );

    while( std::getline( ss, l, '\n' ) )
    {
        if( l.find( "No receipt for" ) != std::string::npos )
        {
            throw std::runtime_error(
                ( format( "Invalid package name %1%" ) % pkg_name ).str() );
        }

        if( auto pos = l.find( loc_mask ) != std::string::npos )
        {
            loc.assign( l, pos + loc_mask.length() - 1, std::string::npos );
            continue;
        }
        if( auto pos = l.find( vol_mask ) != std::string::npos )
        {
            vol.assign( l, pos + vol_mask.length() - 1, std::string::npos );
            continue;
        }
    }
    if( vol == loc )
        m_pkg_location = vol;
    else
        m_pkg_location = vol + loc;
}

pkg_uninstaller::pkg_uninstaller( const std::string &pkg_name, bool is_regexp )
    : m_pkg_name( pkg_name )
{
    load_pkg_info( pkg_name );
}

pkg_uninstaller::~pkg_uninstaller()
{
}

objects_list pkg_uninstaller::uninstall( const objects_list &objs )
{
    return objects_list{};
}

objects_list pkg_uninstaller::dry_run()
{
    auto              cmd  = format( "pkgutil --files %1% 2>&1" ) % m_pkg_name;
    auto              resp = exec( cmd.str().c_str() );
    std::stringstream ss( resp );
    std::string       l;
    objects_list      objs{};

    while( std::getline( ss, l, '\n' ) )
    {
        fs::path p{m_pkg_location / l};
        objs.push_back( p.string() );
    }

    return objs;
}
}
