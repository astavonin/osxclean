#include <uninstaller.h>

#include "app_uninstaller.hpp"

namespace uninstaller
{
std::unique_ptr<uninstaller> create_uninstaller( const std::string &filter,
                                                 filter_type        type,
                                                 bool               isRegexp )
{
    if( type != filter_type::app_path_name )
        throw std::invalid_argument( "Unsupported uninstaller" );

    return std::make_unique<app_uninstaller>( filter );
}
}
