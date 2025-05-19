#ifndef CONFIG_H
#define CONFIG_H

// PATHS
const std::string dataPath = "data/";
const std::string passwordsPath = "passwords";

// FLAGS
const bool encrypted = false;
const bool skipAfterInput = true;
const bool hidePassword = true;

// TIME
const int timeLimit = 30;
const int timeLogin = 10;
const int timePassword = 5;
const double skipTimeout = 0.1;

#endif
