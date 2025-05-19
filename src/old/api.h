#ifndef API_H
#define API_H

#ifdef _WIN32
#include "apiWin.h"
#endif

#ifdef __linux__
#include "apiLinuxX11.h"
#endif

#endif
