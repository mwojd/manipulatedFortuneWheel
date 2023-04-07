#include "includes.h"

void clear_scr()
{
#ifdef _WIN32
    std::system("cls");
#else

    std::system("clear");
#endif
}
void mySleep(int sleepMs)
{
#ifdef __linux__
    usleep(sleepMs * 1000);
#endif
#ifdef _WIN32
    Sleep(sleepMs);
#endif
}
