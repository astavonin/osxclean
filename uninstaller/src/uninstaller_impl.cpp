#include <iostream>
#include <uninstaller.h>

#include "app_uninstaller.hpp"

namespace uninstaller
{

uninstaller_base::uninstaller_base()
{
}

uninstaller_base::~uninstaller_base()
{
}

objects_list uninstaller_base::uninstall( const objects_list &objs )
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

std::unique_ptr<uninstaller>
create_uninstaller( const std::string &filter, filter_type type, bool isRegexp )
{
    if( type != filter_type::app_path_name )
        throw std::invalid_argument( "Unsupported uninstaller" );

    return std::make_unique<app_uninstaller>( filter );
}
}
