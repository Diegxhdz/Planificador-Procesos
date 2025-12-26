#ifndef SRT_H
#define SRT_H

#include <vector>
#include "Process.h"

class SRT {
public:
    void schedule(Process p);
    void execute();
private:
    std::vector<Process> processQueue;
};

#endif
