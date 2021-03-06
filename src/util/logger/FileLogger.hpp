/*******************************************************************************
 * Project:  Nebula
 * @file     FileLogger.hpp
 * @brief 
 * @author   bwar
 * @date:    Mar 29, 2018
 * @note
 * Modify history:
 ******************************************************************************/
#ifndef SRC_UTIL_LOGGER_FILELOGGER_HPP_
#define SRC_UTIL_LOGGER_FILELOGGER_HPP_

#include <cstdio>
#include <string>
#include "Logger.hpp"

namespace neb
{

class FileLogger: public Logger
{
public:
    explicit FileLogger(
            const std::string& strLogFile,
            int iLogLev = Logger::INFO,
            unsigned int uiMaxFileSize = neb::gc_uiMaxLogFileSize,
            unsigned int uiMaxRollFileIndex = neb::gc_uiMaxRollLogFileIndex);
    virtual ~FileLogger()
    {
        fclose(m_fp);
    }

    static FileLogger* Instance(const std::string& strLogFile = "../log/default.log",
                    int iLogLev = Logger::INFO,
                    unsigned int uiMaxFileSize = neb::gc_uiMaxLogFileSize,
                    unsigned int uiMaxRollFileIndex = neb::gc_uiMaxRollLogFileIndex)
    {
        if (m_pInstance == nullptr)
        {
            m_pInstance = new FileLogger(strLogFile, iLogLev, uiMaxFileSize, uiMaxRollFileIndex);
        }
        return(m_pInstance);
    }

    void SetLogLevel(int iLev)
    {
        m_iLogLevel = iLev;
    }

    virtual int WriteLog(int iLev, const char* szFileName, unsigned int uiFileLine, const char* szFunction, const char* szLogStr = "info", ...);
    virtual int WriteLog(const std::string& strTraceId, int iLev, const char* szFileName, unsigned int uiFileLine, const char* szFunction, const char* szLogStr = "info", ...);

private:
    int OpenLogFile(const std::string strLogFile);
    void ReOpen();
    void RollOver();
    int Vappend(int iLev, const char* szFileName, unsigned int uiFileLine, const char* szFunction, const char* szLogStr, va_list ap);
    int Vappend(const std::string& strTraceId, int iLev, const char* szFileName, unsigned int uiFileLine, const char* szFunction, const char* szLogStr, va_list ap);

    static FileLogger* m_pInstance;

    FILE* m_fp;
    int m_iLogLevel;
    unsigned int m_uiMaxFileSize;       // 日志文件大小
    unsigned int m_uiMaxRollFileIndex;  // 滚动日志文件数量
    std::string m_strLogFileBase;       // 日志文件基本名（如 log/program_name.log）
};

} /* namespace neb */

#endif /* SRC_UTIL_LOGGER_FILELOGGER_HPP_ */
