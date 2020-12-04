#include "../include/Watchable.h"
#include "../include/Session.h"
#include "../include/User.h"
#include <iostream>
#include <string>

Watchable::Watchable(long _id, int _length, const std::vector<std::string>& _tags):id(_id),length(_length),tags(_tags){
    wasSeen= false;
}
int Watchable::getLen() {
    return length;
}
std::vector<std::string>& Watchable::getTags(){
    return tags;
}


Movie::Movie(long _id, const std::string& _name, int _length, const std::vector<std::string>& _tags): Watchable(_id, _length, _tags){
    name=(_name);
    MovieId=_id;
    MovieLen=_length;
    MovieTags=_tags;
    wasSeen=false;
    }
    int Watchable::getId (){
        return id;
    }

std::string Movie::toString() const {
        return name;
    }

        bool Movie::isEpisode() {
            return false;
    }
    bool Movie::isWatched() {
        return wasSeen;
}
    void Movie::changeToWached(){
       wasSeen=true;
    }


//    {
//    printf("%d,%s,%d minutes, [", MovieId,name.c_str(),MovieLen);
//    for (int i=0; i< MovieTags.size()-1;i++) {
//    printf("%s ,",  MovieTags.at(i).c_str());
//    }
//    printf("%s ]\n",MovieTags.at(MovieTags.size()-1).c_str());
//    }
//
//    Watchable* getNextWatchable(Session& sess) {
//
//
//    }

Episode::Episode(long _id, const std::string& _seriesName,int _length, int _season, bool _isLast, int _episode ,const std::vector<std::string>& _tags):Watchable(_id,_length,_tags){
    seriesName=(_seriesName);
    isLast=(_isLast);
    EpisodeId=_id;
    EpisodeLen=_length;
    EpisodeTags=_tags;
    wasSeen=false;


}
    bool Episode::isEpisode() {
        return true;
    }
    bool Episode::isLastEp(){
    return isLast;
}
bool Episode::isWatched() {
    return wasSeen;
}
void Episode::changeToWached(){
    wasSeen=true;
}
std::string Episode::toString() const {
    std::string s = seriesName+" S"+ std::to_string(season) +"E"+std::to_string(season);
    return s;
}


//    {
//    printf("%d,%s, S%d,E%d,%d minutes, [", EpisodeId,seriesName.c_str(),season,episode,EpisodeLen);
//    for (int i=0; i<EpisodeTags.size()-1;i++) {
//    printf("%s ,", EpisodeTags.at(i).c_str());
//    }
//    printf("%s ]\n",EpisodeTags.at(EpisodeTags.size()-1).c_str());
//    }
    Watchable* Episode::getNextWatchable(Session& s) const{
    User* temp=s.getActiveUser();
    return (temp->getRecommendation(s));
    }
