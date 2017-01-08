#pragma once

#include <boost/filesystem.hpp>
#include <string>
#include <vector>

namespace fs = boost::filesystem;

namespace uninstaller
{

using objects_list = std::vector<std::string>;

class uninstaller
{
public:
    virtual ~uninstaller()
    {
    }

    virtual objects_list uninstall( const objects_list &objs ) = 0;
    virtual objects_list dry_run()                             = 0;
};

enum class filter_type
{
    pkg_id,
    app_path_name
};

std::unique_ptr<uninstaller> create_uninstaller( const std::string &filter,
                                                 filter_type        type,
                                                 bool               isRegexp );
}
