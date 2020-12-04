//
// Created by magami@wincs.cs.bgu.ac.il on 25/11/2019.
//

#ifndef REALSPLFLIX_ACTION_H
#define REALSPLFLIX_ACTION_H
#include <string>
#include <iostream>

class Session;

enum ActionStatus{
    PENDING, COMPLETED, ERROR
};
class BaseAction{
public:
    BaseAction();
    BaseAction(std::string name,std::string SecName, std::string pref);
    ActionStatus getStatus() const;
    virtual void act(Session&)=0;
    virtual std::string toString() const=0;
    std::string getPref();
    std::string getName();
    std::string getSecName();
protected:
    void complete();
    void error(const std::string& _errorMsg);
    std::string getErrorMsg() const;
private:
    std::string errorMsg;
    ActionStatus status;
    std::string name;
    std::string SecName;
    std::string pref;

};

class CreateUser  : public BaseAction {
public:
    virtual void act(Session&);
    virtual std::string toString() const;
};

class ChangeActiveUser : public BaseAction {
public:
    virtual void act(Session& sess);
    virtual std::string toString() const;
};

class DeleteUser : public BaseAction {
public:
    virtual void act(Session & sess);
    virtual std::string toString() const;
};


class DuplicateUser : public BaseAction {
public:
    virtual void act(Session & sess);
    virtual std::string toString() const;
};

class PrintContentList : public BaseAction {
public:
    virtual void act (Session& sess);
    virtual std::string toString() const;
};

class PrintWatchHistory : public BaseAction {
public:
    virtual void act (Session& sess);
    virtual std::string toString() const;
};


class Watch : public BaseAction {
public:
    Watch(int id);
    virtual void act(Session& sess);
    virtual std::string toString() const;
private:
    int id;
};


class PrintActionsLog : public BaseAction {
public:
    virtual void act(Session& sess);
    virtual std::string toString() const;
};

class Exit : public BaseAction {
public:
    virtual void act(Session& sess);
    virtual std::string toString() const;
};
#endif //REALSPLFLIX_ACTION_H
