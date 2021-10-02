#include "./../headers/TerminalIOProxy.h"

TerminalIOproxy* TerminalIOproxy::m_pterminalIOProxy = NULL;

TerminalIOproxy& TerminalIOproxy::getRef()
{
    if(!m_pterminalIOProxy)
    {
        throw std::runtime_error("m_pterminalIOProxy not set!");
    }
    return *m_pterminalIOProxy;
}

TerminalIOproxy::TerminalIOproxy()
{
    m_pterminalIOProxy = this;
}

TerminalIOproxy::~TerminalIOproxy()
{
    m_pterminalIOProxy= NULL;
}

void TerminalIOproxy::registerInputCallback(std::function<char(void)> const & rInputCallbackFn)
{
    m_inputCallback = rInputCallbackFn;
}

char TerminalIOproxy::getInput()
{
    if(!m_inputCallback)
    {
        log(reportableObject::ERROR, "inputHandlerNotSet!");
        throw std::runtime_error("inputHandlerNotSet!");
    }

    return m_inputCallback();
}

void TerminalIOproxy::registerOutputCallback(std::function<void(std::string const &, bool)> const & rOutputCallbackFn) 
{
    m_outputCallback = rOutputCallbackFn;
}

void TerminalIOproxy::pushOutput(std::string const& rStr, bool bForceUpdate)
{
    if(!m_outputCallback)
    {
        log(reportableObject::ERROR, "outputHandlerNotSet!");
        throw std::runtime_error("outputHandlerNotSet!");
    }

    m_outputCallback(rStr, bForceUpdate);
}