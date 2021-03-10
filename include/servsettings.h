#ifndef SERVSETTINGS_H
#define SERVSETTINGS_H

struct Settings{

};

class ServSettings
{
public:
    static ServSettings *get_instanse();
    void parse_args(int argc, char *argv[]);
    bool is_init();
    const Settings &get_settings();

private:
    ServSettings() = default;
    ServSettings(int argc, char *argv[]);
    ServSettings(ServSettings&)=delete;
    ServSettings(ServSettings&&)=delete;
    ServSettings& operator=(ServSettings&)=delete;
    virtual ~ServSettings();

    Settings m_set;
    bool is_init_arg;
};

#endif // SERVSETTINGS_H
