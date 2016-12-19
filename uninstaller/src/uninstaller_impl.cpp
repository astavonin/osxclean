#include "uninstaller_impl.hpp"

namespace uninstaller
{
std::unique_ptr<uninstaller> create_uninstaller( const std::string &filter,
                                                 filter_type        type,
                                                 bool               isRegexp )
{
    return std::make_unique<uninstaller_impl>();
}

uninstaller_impl::uninstaller_impl()
{
}

uninstaller_impl::~uninstaller_impl()
{
}

void uninstaller_impl::uninstall()
{
}

std::vector<object> uninstaller_impl::do_dry_run()
{
    return std::vector<object>();
}
}
