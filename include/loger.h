#ifndef LOGER_H
#define LOGER_H

#include <memory>
#include <fstream>
#include <iostream>
#include <mutex>
#include <ctime>


enum LOG_TYPE {
    DEB,
    WAR,
    CRIT,
    FAT
};

class Loger
{
public:
    static Loger &getInstanse();

    virtual bool init(const std::string &logFilePath);
    virtual bool writeMessage(const char* mes, LOG_TYPE type=DEB);
    virtual bool writeMessage(const std::string& mes, LOG_TYPE type=DEB);
    virtual bool isInit();

protected:
    virtual bool createLogFile(const std::string &logFilePath);
    virtual bool logFileIsValid(const std::string &logFilePath);

    virtual ~Loger();
    Loger();
    Loger(Loger& ) = delete;
    Loger& operator= (const Loger& ) = delete;

private:
    std::string get_type(const LOG_TYPE& type);

    std::fstream m_out;
    bool m_isInit;
    std::mutex m_mutex;
    //fileDiscriptor
};



#endif // LOGER_H
