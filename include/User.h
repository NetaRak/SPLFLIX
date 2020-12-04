//
// Created by magami@wincs.cs.bgu.ac.il on 25/11/2019.
//

#ifndef REALSPLFLIX_USER_H
#define REALSPLFLIX_USER_H
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <map>
class Watchable;
class Session;

class User{
public:
    User(const std::string& name);
    virtual Watchable* getRecommendation(Session& s) = 0;
    void printHistory();
    std::string getName() const;
    std::vector<Watchable*> get_history() const;
    void addToHistory(Watchable*);
    int getAverage ();
    std::string getMaxTag(int);
    int tagsLen();
protected:
    std::vector<Watchable*> history;
private:
    std::string name;
    int averageLen;
    bool isGenere;
    std::map <int, std::string>tagsMap;


};


class LengthRecommenderUser : public User {
public:
    LengthRecommenderUser( const std::string &name);
    virtual Watchable* getRecommendation(Session& s);
private:

};

class RerunRecommenderUser : public User {
public:
    RerunRecommenderUser( const std::string& name);
    virtual Watchable* getRecommendation(Session& s);
private:
    int lastRec;
};

class GenreRecommenderUser : public User {
public:
    GenreRecommenderUser(const std::string& name);
    virtual Watchable* getRecommendation(Session& s);

private:
    bool isGenere;
};


#endif //REALSPLFLIX_USER_H
