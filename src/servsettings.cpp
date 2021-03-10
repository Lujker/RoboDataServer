#include "servsettings.h"

ServSettings &ServSettings::get_instanse()
{
    static ServSettings sett;
    return sett;
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

ServSettings::~ServSettings()
{}
