
#include "../include/User.h"
#include <iostream>
#include "../include/Watchable.h"
#include "../include/Session.h"
#include <cmath>
#include <map>
#include <iterator>
    User::User (const std::string &_name) :name(_name){
        averageLen=0;
        std::map<int,std::string> tempUserMap{};
        tagsMap = tempUserMap;
}
    void User::printHistory () {
        for (int i = 0; i < history.size(); i = i + 1) {
            history[i]->toString();
        }
    }
    void User::addToHistory(Watchable* w){
        history.push_back(w);
        averageLen=((averageLen*(history.size()-1))+w->getLen())/history.size();
        std::vector<std::string> tags=w->getTags();
        std::map<int, std::string>::iterator it;
        it=tagsMap.begin();
        bool isE=false;
        if(isGenere) {
            for (int i = 0; i < tags.size(); i = i + 1) {
               while(it!=tagsMap.end()){
                   if ((*it).second==tags[i]){
                       int x=(*it).first+1;
                       tagsMap.erase(it);
                       tagsMap.insert(std::make_pair(x,tags[i]));
                   isE=true;
                   }
                    ++it;
                }
               if(!isE)
                tagsMap.insert(std::make_pair((*it).first+1,tags[i]));
                isE=false;
            }
        }
    }
    int User::getAverage() { return averageLen;}
    std::string User::getName() const {
        return name;
    }
    std::vector<Watchable*> User::get_history() const {
        return history;
    }
//Length
    LengthRecommenderUser::LengthRecommenderUser( const std::string &name) : User(name) {}

    Watchable* LengthRecommenderUser::getRecommendation(Session& s){
        Watchable* curr;
        Watchable* output;
        curr = history[history.size() - 1];
        if(curr->isEpisode()) {
            Episode currE = reinterpret_cast<Episode &&>(curr);
            if (!currE.isLastEp()) {
                return s.getFromContent(currE.getId() + 1);
            }
        }
        int min=INT8_MAX;
        std::vector<Watchable*> cont = s.geContent();
        for (int i=0 ; i< cont.size();i=i+1){
            if (!cont[i]->isWatched() & std::abs(cont[i]->getLen()-s.getActiveUser()->getAverage())<min) {
                min = abs(cont[i]->getLen() - s.getActiveUser()->getAverage());
                output=cont[i];
            }
        }
        return output;
    }
//RE-RUN
    RerunRecommenderUser::RerunRecommenderUser( const std::string &name) : User(name) {
        lastRec=-1;
    }

    Watchable* RerunRecommenderUser::getRecommendation(Session& s){
        Watchable* curr;
        Watchable* output;
        curr = history[history.size() - 1];
        if(curr->isEpisode()) {
            Episode currE = reinterpret_cast<Episode &&>(curr);
            if (!currE.isLastEp()) {
                return s.getFromContent(currE.getId() + 1);
            }
        }
        std::vector<Watchable *> hist;
        hist = history;
        lastRec=+1;
        return hist[(lastRec)%(hist.size())];
    }
    int User::tagsLen() {
        return tagsMap.size();
    }
    std::string User::getMaxTag(int index) {
        std::map<int, std::string>::iterator it;
        int j=0;
        while (j<=tagsMap.size()-index){
            ++it;
            ++j;
        }
        return (*it).second;
    }


//Genre
    GenreRecommenderUser::GenreRecommenderUser( const std::string &name) :User (name){
        isGenere=true;
    }
    Watchable* GenreRecommenderUser::getRecommendation(Session& s) {
        Watchable *curr;
        Watchable *output;
        curr = history[history.size() - 1];
        if (curr->isEpisode()) {
            Episode currE = reinterpret_cast<Episode &&>(curr);
            if (!currE.isLastEp()) {
                return s.getFromContent(currE.getId() + 1);
            }
        }
        bool found = false;
        for (int i = 1; !found & i <= tagsLen(); i = i + 1) {
            std::string popularT = getMaxTag(i);
            output = s.nextWatchableByTag(popularT);
            if (output != nullptr)
                return output;
        }
        return nullptr;
    }
