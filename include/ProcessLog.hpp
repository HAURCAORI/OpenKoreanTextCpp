#include <iostream>

class ProcessLog {
private:
    static bool active = true;
public:
    enum LogType {
        Process, Success, Fail, Error
    };
    static void log(const std::string& str) noexcept {
        if(!active){ return; }
        std::cout << str << std::endl;
    }
    static void logs(const std::string& str) noexcept {
        if(!active){ return; }
        std::cout << str;
    }
    static void log(LogType type, const std::string& str) noexcept {
        if(!active){ return; }
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
    }
};