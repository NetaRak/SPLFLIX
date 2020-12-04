

    #include "../include/Session.h"
    #include "../include/User.h"
    #include "../include/Watchable.h"
    #include <iostream>
    #include "../include/json.hpp"
    #include <unordered_map>
    #include <fstream>


    using json = nlohmann::json;

    Session::Session(const std::string &configFilePath) {
        std::vector<Watchable *> tempVec = {};
        content = tempVec;
        std::vector<BaseAction *> tempVecBase = {};
        actionsLog = tempVecBase;
        LengthRecommenderUser defaultUser("default");
        activeUser = &(defaultUser);
        std::unordered_map<std::string, User *> tempUserMap{};
        userMap = tempUserMap;

        std::ifstream i("file.json");
        json j;
        i >> j;
        json movies = j["movies"];
        int id = 0;
        for (int i = 0; i < movies.size(); i++) {
            json movie = movies[i];
            std::string name = movie["name"];
            Watchable *temp = new Movie(id, movie["name"], movie["length    "], movie["tags"]);
            content.push_back(temp);
            id++;
        }
        json tvShows = j["tv_series"];
        for (int l = 0; l < tvShows.size(); l++) {
            json series = tvShows[l];
            for (int k = 0; k < series["seasons"].size(); k++) {
                for (int n = 1; n < series["seasons"][k]; n++) {
                    int seasonsLen = series["seasons"][k];
                    bool isLast = (n == (seasonsLen - 1));
                    Watchable *tempEpisode = new Episode(id, series["name"], series["episode_length"], (k + 1), isLast, n,
                                                         series["tags"]);
                    content.push_back(tempEpisode);
                    id++;
                }
            }
        }
    }
    void Session::start() {
        printf("SPLFLIX is now on!");
    }
    void Session::addUserToMap(User *user){
        User* userPtr = user;
        std::string name = user->getName();
        userMap.insert(std::make_pair(name,userPtr));
    }

    bool Session::SearchInMap(std::string s){
        std::unordered_map<std::string, User*>::iterator it;
        bool answer;
        it = userMap.find(s);
        if (it != userMap.end()) {
            answer= true;
        }
        else
        {
            answer = false;
        }
        return answer;

    }
        Watchable* Session::nextWatchableByTag(std::string s){
            Watchable* curr;
            for (int i = 0; i < content.size() ;i=i+1) {
                curr = content[i];
                if (!curr->wasSeen) {
                    for (int j = 0; j < curr->getTags().size(); j = j + 1) {
                        if((curr->getTags()[i])==s)
                            return curr;
                    }

                }
            }
            return nullptr;
    }


    void Session::addActionToActionLog(BaseAction *action){
        actionsLog.push_back(action);
    }

    void Session::setActiveUser(std::string _name){
        std::unordered_map<std::string, User*>::iterator it;
        it = userMap.find(_name);
        User *user= (*it).second;
        activeUser= user;
    }

    void Session::removeUser(std::string name){
        std::unordered_map<std::string, User*>::iterator it;
        it = userMap.find(name);
        userMap.erase(it);
    }

    void Session::printCont (){
        for(int i=0 ; i<content.size() ; i=i+1){
            content[i]->toString();
        }
    }
    User* Session::getUser(std::string name){
        std::unordered_map<std::string, User*>::iterator it;
        it = userMap.find(name);
        User *user= (*it).second;
        return user;
    }

    User* Session::getActiveUser(){
        return activeUser;
    }

    Watchable* Session::getFromContent (int id){
        Watchable* toWatch;
        int i=0;
        bool found=false;
        while (i<content.size() & !false){
            if (content[i]->getId())
                found=true;
            i=i+1;
        }
        if (found) {
            toWatch = content[i - 1];
            return toWatch;
        }
        return nullptr;
    }

    void Session::printActionsLog() {

        for (int i = 0; i < actionsLog.size(); i = i + 1) {
            printf("%s", actionsLog[i]->toString().c_str());
        }
    }

    std::vector<Watchable*> Session::geContent(){
        return content;
    }
