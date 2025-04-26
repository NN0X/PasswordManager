#include <iostream>
#include <vector>

#include "loader.h"
#include "search.h"
#include "timer.h"
#include "api.h"
#include "config.h"

void inputLoop(const AccountsData& data, bool &finished, int &choice)
{
        std::vector<std::string> names = data.names;
        std::vector<std::string> logins = data.logins;
        std::vector<std::string> passwords = data.passwords;

        std::vector<int> foundIndices = genIndices(names);
        choice = -1;
        while (true)
        {
                std::string searchWord;
                std::cout << "Search: ";
                std::getline(std::cin, searchWord);
                foundIndices = search(searchWord, names); 
                if (foundIndices.size() == 1)
                {
                        choice = foundIndices[0];
                        break;
                }
                else if (foundIndices.size() == 0)
                {
                        std::cout << "No results found for: " << searchWord << "\n";
                        foundIndices = genIndices(names);
                }
                else
                {
                        while (true)
                        {
                                for (int i : foundIndices)
                                {
                                        std::cout << i + 1 << ". " << names[i] << "\n";
                                }
                                std::cin >> choice;
                                choice--;
                                if (choice < 0 || choice >= names.size())
                                {
                                        clear();
                                        std::cout << "Error: Invalid choice.\n";
                                }
                                else
                                        break;
                        }
                        break;
                }
        }
        clear();

        finished = true;
}

void loginLoop(const std::string &name, const std::string &login, Timer &generalTimer, double &skipTime, bool &finished)
{
        clear();
        std::string output;
        output += name + "\n";
        output += login + "\n";
        std::cout << output;
        setClipboard(login);

        Timer timer;
        timer.start();
        skipTime = 0;
        while (timer.elapsed < timeLogin)
        {
                timer.update();
                std::cout << "Time left: " << int(timeLogin - timer.elapsed + 0.5) << "s\n"; 
                msleep(10);
                clearln(3);
                if (getKeyPressed() == CTRL_V && skipAfterInput)
                {
                        generalTimer.update();
                        skipTime = generalTimer.elapsed;
                        break;
                }
        }
        clear();

        finished = true;
}

void passwordLoop(const std::string &name, const std::string &password, Timer &generalTimer, double skipTime, bool &finished)
{
        clear();
        std::string output = "";
        output += name + "\n";
        if (!hidePassword)
                output += password + "\n";
        else
                output += std::string(password.size(), '*') + "\n";
        std::cout << output;
        setClipboard(password);

        Timer timer;
        timer.start();
        while (timer.elapsed < timePassword)
        {
                timer.update();
                std::cout << "Time left: " << int(timePassword - timer.elapsed + 0.5) << "s\n";
                msleep(10);
                clearln(3);
                generalTimer.update();
                if (getKeyPressed() == CTRL_V && generalTimer.elapsed - skipTime > skipTimeout && skipAfterInput)
                        break;
        }
        clear();

        finished = true;
}
