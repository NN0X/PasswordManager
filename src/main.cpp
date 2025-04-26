#include <iostream>
#include <thread>

#include "config.h"
#include "api.h"
#include "loader.h"
#include "timer.h"
#include "cli.h"

void exitOnTimeout(Timer &generalTimer, bool &exitFlag)
{
        if (timeLimit == NULL)
                return;
        while (generalTimer.elapsed < timeLimit)
        {
                generalTimer.update();
                msleep(10);
        }
        setClipboard("");
        clear();
        exitFlag = true;
}

int main()
{
        Timer generalTimer;
        generalTimer.start();

        bool exitFlag = false;
        std::thread timeoutThread(exitOnTimeout, std::ref(generalTimer), std::ref(exitFlag));

        AccountsData data;
        if (encrypted)
        {
                std::cerr << "Error: Encrypted mode is not supported yet.\n";
                return 1;
        }
        else
                data = loadNotEncrypted(dataPath + passwordsPath);

        clear();

        bool finished = false;
        int choice;
        std::thread inputThread(inputLoop, data, std::ref(finished), std::ref(choice));
        while (!finished)
        {
                if (exitFlag)
                {
                        clear();
                        std::cout << "Time limit reached.\n";
                        exit(1);
                }
                msleep(10);
        }
        inputThread.join();
        finished = false;

        double skipTime;
        std::thread loginThread(loginLoop, std::cref(data.names[choice]), std::cref(data.logins[choice]), std::ref(generalTimer), std::ref(skipTime), std::ref(finished));
        while (!finished)
        {
                if (exitFlag)
                {
                        clear();
                        std::cout << "Time limit reached.\n";
                        exit(1);
                }
                msleep(10);
        }
        loginThread.join();
        finished = false;

        std::thread passwordThread(passwordLoop, std::cref(data.names[choice]), std::cref(data.passwords[choice]), std::ref(generalTimer), skipTime, std::ref(finished));
        while (!finished)
        {
                if (exitFlag)
                {
                        clear();
                        std::cout << "Time limit reached.\n";
                        exit(1);
                }
                msleep(10);
        }
        passwordThread.join();

        setClipboard("");
        clear();

        exit(0);

        return 0;
}
