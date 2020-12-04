//
// Created by magami@wincs.cs.bgu.ac.il on 25/11/2019.
//

#ifndef REALSPLFLIX_WATCHABLE_H
#define REALSPLFLIX_WATCHABLE_H
#include <string>
#include <vector>


class Session;

class Watchable{
public:
    Watchable(long id, int length, const std::vector<std::string>& tags);
    virtual ~Watchable();
    virtual std::string toString() const = 0;
    virtual Watchable* getNextWatchable(Session&) const = 0;
    int getId ();
    int getLen();
    virtual bool isEpisode ()=0;
    virtual bool isWatched ()=0;
    virtual void changeToWached()=0;
    std::vector<std::string>& getTags();
    bool wasSeen;

private:
    const long id;
    int length;
    std::vector<std::string> tags;
};

class Movie : public Watchable{
public:
    Movie(long id, const std::string& name, int length, const std::vector<std::string>& tags);
    virtual std::string toString() const;
    virtual Watchable* getNextWatchable(Session& sess) const;
    virtual bool isEpisode ();
    virtual bool isWatched ();
    virtual void changeToWached();


private:
    std::string name;
    long MovieId;
    int MovieLen;
    std::vector<std::string> MovieTags;
    bool wasSeen;

};


class Episode: public Watchable{
public:
    Episode(long id, const std::string& seriesName,int length, int season,bool isLast, int episode ,const std::vector<std::string>& tags);
    virtual std::string toString() const;
    virtual Watchable* getNextWatchable(Session&) const;
    virtual bool isEpisode ();
    bool isLastEp();
    virtual bool isWatched ();
    virtual void changeToWached();

private:
    std::string seriesName;
    int season;
    long EpisodeId;
    int EpisodeLen;
    int episode;
    long nextEpisodeId;
    bool isLast;
    bool wasSeen;
    std::vector<std::string> EpisodeTags;
};
#endif //REALSPLFLIX_WATCHABLE_H
