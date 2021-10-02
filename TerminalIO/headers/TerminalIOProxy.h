#pragma once

#include <functional>
#include "../../headers/reportableObject.h"

class TerminalIOproxy : public reportableObject
{
    public:
        TerminalIOproxy();
        ~TerminalIOproxy();

        void registerInputCallback(std::function<char(void)> const&);
        void registerOutputCallback(std::function<void(std::string const &, bool)> const&);

        char getInput();
        void pushOutput(std::string const& str, bool bForceUpdate = true);

        static TerminalIOproxy& getRef();
    private:
        static TerminalIOproxy* m_pterminalIOProxy;
        std::function<char(void)> m_inputCallback;
        std::function<void(std::string const &, bool)> m_outputCallback;
};