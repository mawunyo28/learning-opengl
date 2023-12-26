#include <string>
#include <iostream>
#include <chrono>

class Timer
{
public:
    std::string process_name;
    std::chrono::time_point<std::chrono::_V2::system_clock> start, end;
    std::chrono::duration<double> duration;
    Timer(std::string process_name) : process_name(process_name)
    {
        start = std::chrono::high_resolution_clock::now();
    }

    ~Timer()
    {
        end = std::chrono::high_resolution_clock::now();

        duration = end - start;

        if (duration.count() > 1)
            std::cout << "Process " << process_name << " took " << duration.count() << "s to complete" << std::endl;
        else
            std::cout << "Process " << process_name << " took " << duration.count() * 1000 << "ms to complete" << std::endl;
            
    }
};
