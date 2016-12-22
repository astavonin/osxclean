#include "plist.h"
#import <Foundation/Foundation.h>

namespace uninstaller
{
plist::plist( const std::string &path )
{
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
