#include "uninstaller_impl.hpp"
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

namespace uninstaller
{
std::unique_ptr<uninstaller> create_uninstaller( const std::string &filter,
                                                 filter_type        type,
                                                 bool               isRegexp )
{
    return std::make_unique<uninstaller_impl>( filter, type, isRegexp );
}

uninstaller_impl::uninstaller_impl( const std::string &filter, filter_type type,
                                    bool isRegexp )
{
}

uninstaller_impl::~uninstaller_impl()
{
}

void uninstaller_impl::uninstall()
{
}

std::vector<object> uninstaller_impl::dry_run()
{
    return std::vector<object>();
}
}
