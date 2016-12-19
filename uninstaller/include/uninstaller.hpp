#pragma once

#include <string>
#include <vector>

namespace uninstaller
{
enum class object_type
{
    file,
    package,
    application
};

struct object
{
    object_type type;
    std::string name;
};

class uninstaller
{
public:
    virtual ~uninstaller(){}

    virtual void                uninstall() = 0;
    virtual std::vector<object> do_dry_run() = 0;
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
