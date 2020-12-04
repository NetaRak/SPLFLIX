//
// Created by magami@wincs.cs.bgu.ac.il on 25/11/2019.
//

#ifndef REALSPLFLIX_SESSION_H
#define REALSPLFLIX_SESSION_H

#include <vector>
#include <unordered_map>
#include <string>
#include "Action.h"

class User;
class Watchable;

class Session{
public:
    Session(const std::string &configFilePath);
    ~Session();
    void start();
    void addUserToMap(User *user);
    bool SearchInMap(std::string s);
    void addActionToActionLog (BaseAction *action);
    void setActiveUser(std::string name);
    void removeUser (std::string name);
    void printCont ();
    User* getUser(std::string name);
    User* getActiveUser();
    Watchable* getFromContent (int id);
    void printActionsLog();
    std::vector<Watchable*> geContent();
    Watchable* nextWatchableByTag(std::string);
private:
    std::vector<Watchable*> content;
    std::vector<BaseAction*> actionsLog;
    std::unordered_map<std::string,User*> userMap;
    User* activeUser;

};
#endif //REALSPLFLIX_SESSION_H
