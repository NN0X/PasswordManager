#ifndef CLI_H 
#define CLI_H

#include "loader.h"
#include "timer.h"

void inputLoop(const AccountsData& data, bool &finished, int &choice);
void loginLoop(const std::string &name, const std::string &login, Timer &generalTimer, double &skipTime, bool &finished);
void passwordLoop(const std::string &name, const std::string &password, Timer &generalTimer, double skipTime, bool &finished);

#endif
