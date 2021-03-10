#include "loger.h"

bool Loger::init(const std::string &logFilePath)
{
    try{
        if(logFilePath==""||logFilePath.empty()){
            std::cout<<"Log file path is empty\n";
            return false;
        }
        if(m_out.is_open()) m_out.close();

        if(logFileIsValid(logFilePath)){
        }
        else{
            if(createLogFile(logFilePath)){
            }
            else{
                std::cout<<"Fail to create log file!\n";
                return m_isInit = false;
            }
        }
        m_out.open(logFilePath,std::ios::app);
        return m_isInit = true;
    }
    catch (const std::exception& exp){
        std::cout<< exp.what();
        return m_isInit = false;
    }
}

Loger &Loger::getInstanse()
{
    static Loger log;
    return log;
}

bool Loger::writeMessage(const char *mes, LOG_TYPE type)
{
    return writeMessage(std::string(mes), type);
}

bool Loger::writeMessage(const std::string &mes, LOG_TYPE type)
{
    try{
        std::string log_msg = "";
        time_t now = time(0);
        std::string dt = "[" + std::string(ctime(&now)); ///текущая дата и время
        dt.at(dt.size()-1)=']'; dt.push_back('\t');
        log_msg = dt + get_type(type) + mes;

        ///Заполенения данными
        std::lock_guard<std::mutex>  guard(m_mutex);
        m_out << log_msg << std::endl;
        return true;
    }
    catch (const std::exception& exp){
        std::cout<< exp.what();
        return false;
    }
}

bool Loger::isInit()
{
    return m_isInit;
}

bool Loger::createLogFile(const std::string &logFilePath)
{
    std::ofstream file(logFilePath, std::ios_base::out | std::ios_base::trunc);
    if(file.is_open()){
        file.close();
        return true;
    }
    else{
        return false;
    }

    return false;
}

bool Loger::logFileIsValid(const std::string &logFilePath)
{
    std::ifstream file;
    file.open(logFilePath);
    if(!file){
        return false;
    }
    else{
        file.close();
        return true;
    }

    return false;
}

std::string Loger::get_type(const LOG_TYPE &type)
{
    std::string ret_type;
    switch (type) {
    case (LOG_TYPE::DEB):
        ret_type = "<DEBUG> ";
        break;
    case (LOG_TYPE::WAR):
        ret_type = "<WARNING> ";
        break;
    case (LOG_TYPE::CRIT):
        ret_type = "<!CRITICAL!> ";
        break;
    case (LOG_TYPE::FAT):
        ret_type = "<!!!FATAL!!!> ";
        break;
    default:
        ret_type = "<DEBUG> ";
        break;
    }
    return ret_type;
}

Loger::~Loger()
{
    if(m_out.is_open()) m_out.close();
}

Loger::Loger()
{}
