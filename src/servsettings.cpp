#include "servsettings.h"

namespace SETTING {
    static ServSettings* sett = nullptr;
}

ServSettings *ServSettings::get_instanse()
{
    if(SETTING::sett==nullptr) SETTING::sett = new ServSettings();
    return SETTING::sett;
}

void ServSettings::parse_args(int argc, char *argv[])
{

}

bool ServSettings::is_init()
{
    return this->is_init_arg;
}

const Settings &ServSettings::get_settings()
{
    return this->m_set;
}

ServSettings::ServSettings(int argc, char *argv[])
{
    parse_args(argc, argv);
}
