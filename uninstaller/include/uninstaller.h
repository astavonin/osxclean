#pragma once

#include <boost/filesystem.hpp>
#include <string>
#include <vector>

namespace fs = boost::filesystem;

namespace uninstaller
{
enum class object_type
{
    file,
    directory,
    package,
    application
};

struct object
{
    object_type type;
    fs::path    name;
};

class uninstaller
{
public:
    virtual ~uninstaller()
    {
    }

    virtual void                uninstall() = 0;
    virtual std::vector<object> dry_run()   = 0;
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
