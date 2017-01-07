#include "plist.h"
#import <Foundation/Foundation.h>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>

namespace fs = boost::filesystem;
using boost::format;

namespace uninstaller
{
plist::plist( const std::string &path )
{
    if( !fs::exists( path ) )
        throw std::runtime_error(
            ( format( "File %1% does not exist" ) % path ).str() );

    NSString *    path_int = [NSString stringWithUTF8String:path.c_str()];
    NSDictionary *dict = [NSDictionary dictionaryWithContentsOfFile:path_int];
    for( id key in [dict allKeys] )
    {
        NSString *tmpStr =
            [NSString stringWithFormat:@"%@", [dict valueForKey:key]];

        // it'll drop all complex data structures like sub-array or
        // sub-dictionaries but it's not a case here.
        m_nodes[[key UTF8String]] = [tmpStr UTF8String];
        [tmpStr release];
    }
    [path_int release];
}
}
