#include <iostream>

class ProcessLog {
public:
    enum LogType {
        Process, Success, Fail, Error
    };
    static void log(const std::string& str) noexcept {
        #ifdef ENABLE_LOG
        std::cout << str << std::endl;
        #endif
    }
    static void logs(const std::string& str) noexcept {
        #ifdef ENABLE_LOG
        std::cout << str;
        #endif
    }
    static void log(LogType type, const std::string& str) noexcept {
        #ifdef ENABLE_LOG
        switch(type) {
            case Process:
                std::cout << "[Process] " << str << std::endl;
            break;
            case Success:
                std::cout << "[Success] " << str << std::endl;
            break;
            case Fail:
                std::cout << "[Fail] " << str << std::endl;
            break;
            case Error:
                std::cerr << "[Error] " << str << std::endl;
            break;
        }
        #endif
    }
};