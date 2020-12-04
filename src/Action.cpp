//
// Created by naama on 21/11/2019.
//
//neta
#include "../include/Action.h"
#include "../include/Session.h"
#include <iostream>
#include "../include/User.h"
#include "../include/Watchable.h"
#include <string>

class Session;
class Watchable;

BaseAction::BaseAction() {
    status = PENDING;
    errorMsg = "";
    name = "default";
    SecName="";
    pref = "len";
};
BaseAction::BaseAction(std::string _name,std::string _SecName, std::string _pref) {
    status = PENDING;
    errorMsg = "";
    name = _name;
    SecName= _SecName;
    pref = _pref;
};

std::string BaseAction::getPref() {
    return pref;
}
std::string BaseAction::getName() {
    return name;
}
std::string BaseAction::getSecName() {
    return SecName;
}
//void act(Session &sess){
//
//};
//std::string toString(){
//
//};

void BaseAction::complete(){
    status=COMPLETED;
}
void BaseAction::error(const std::string& _errorMsg){
    status=ERROR;
    errorMsg=_errorMsg;
    printf("%s",getErrorMsg().c_str());
}
std::string BaseAction::getErrorMsg() const{
    return errorMsg;
}

//CREATE USER
void CreateUser::act(Session &sess) {
    if (sess.SearchInMap(getName())){
        error("User name is already in use");
        sess.addActionToActionLog(this);
    }
    else if (this->getPref() == "len") {
        LengthRecommenderUser newUser = LengthRecommenderUser(getName());
        sess.addUserToMap(&newUser);
        complete();
        sess.addActionToActionLog(this);
    }
    else if (this->getPref()=="rer"){
        RerunRecommenderUser newUser = RerunRecommenderUser(getName());
        sess.addUserToMap(&newUser);
        complete();
        sess.addActionToActionLog(this);
    }
    else if (this->getPref()=="gem"){
        GenreRecommenderUser newUser = GenreRecommenderUser(getName());
        sess.addUserToMap(&newUser);
        complete();
        sess.addActionToActionLog(this);
    }
    else {
        error("Recommended algorithm cant not be found");
        sess.addActionToActionLog(this);
    }
}
std::string CreateUser::toString() const{
    ActionStatus stat = getStatus();
    std::string ans;
    if (stat==ERROR){
        ans = "ERROR";
        return ("CreateUser: %s : %s", ans, getErrorMsg());
    }
    if (stat==COMPLETED)
        ans = "COMPLETED";
    if (stat==PENDING)
        ans = "PENDING";
    return ("Create user : %s", ans);

}
//CHANGE ACTIVE USER
void ChangeActiveUser::act(Session &sess) {
    std::string s = getName();
    bool isEx = sess.SearchInMap(s);
    if (isEx) {
        sess.setActiveUser(s);
        complete();
        sess.addActionToActionLog(this);
    } else {
        error("User dose not exist");
        sess.addActionToActionLog(this);
    }
}
std::string ChangeActiveUser::toString() const{
    ActionStatus stat = getStatus();
    std::string ans;
    if (stat==ERROR){
        ans = "ERROR";
        return ("ChangeActiveUser: %s : %s", ans, getErrorMsg());
    }
    if (stat==COMPLETED)
        ans = "COMPLETED";
    if (stat==PENDING)
        ans = "PENDING";
    return ("Change active user : %s", ans);
}

//DELETE USER
void DeleteUser::act(Session &sess) {
    std::string s = getName();
    bool isEx = sess.SearchInMap(s);
    if (isEx) {
        sess.removeUser(s);
        complete();
        sess.addActionToActionLog(this);
    } else {
        error("User dose not exist");
        sess.addActionToActionLog(this);
    }
}

std::string DeleteUser::toString() const{
    ActionStatus stat = getStatus();
    std::string ans;
    if (stat==ERROR){
        ans = "ERROR";
        return ("DeleteUser: %s : %s", ans, getErrorMsg());
    }
    if (stat==COMPLETED)
        ans = "COMPLETED";
    if (stat==PENDING)
        ans = "PENDING";
    return ("Delete user : %s", ans);
}

//DUPLICATE USER
void DuplicateUser::act(Session &sess) {
    std::string s = getName();
    bool isEx = sess.SearchInMap(s);
    if ((isEx) ){
        User* oldUser = sess.getUser(s);
        if (sess.SearchInMap(getSecName())){
            error("New name is already in use");
            sess.addActionToActionLog(this);
        }else {
            //User newUser(oldUser);
            complete();
            sess.addActionToActionLog(this);
        }
    } else {
        error("User dose not exist");
        sess.addActionToActionLog(this);
    }
}

std::string DuplicateUser::toString() const{
    ActionStatus stat = getStatus();
    std::string ans;
    if (stat==ERROR){
        ans = "ERROR";
        return ("DuplicateUser: %s : %s", ans, getErrorMsg());
    }
    if (stat==COMPLETED)
        ans = "COMPLETED";
    if (stat==PENDING)
        ans = "PENDING";
    return ("Duplicate user : %s", ans);
}

//PRINT CONTENT LIST
void PrintContentList::act(Session &sess) {
    sess.printCont();
    complete();
    sess.addActionToActionLog(this);
}

std::string PrintContentList::toString() const{
    ActionStatus stat = getStatus();
    std::string ans;
    if (stat==ERROR){
        ans = "ERROR";
        return ("PrintContentList: %s : %s", ans, getErrorMsg());
    }
    if (stat==COMPLETED)
        ans = "COMPLETED";
    if (stat==PENDING)
        ans = "PENDING";
    return ("Print content list : %s", ans);
}

//PRINT WATCH HISTORY
void PrintWatchHistory::act(Session &sess) {
    sess.getUser(getName())->printHistory();
    complete();
    sess.addActionToActionLog(this);
}

std::string PrintWatchHistory::toString() const{
    ActionStatus stat = getStatus();
    std::string ans;
    if (stat==ERROR){
        ans = "ERROR";
        return ("PrintWatchHistory: %s : %s", ans, getErrorMsg());
    }
    if (stat==COMPLETED)
        ans = "COMPLETED";
    if (stat==PENDING)
        ans = "PENDING";
    return ("Print watch history : %s", ans);
}

Watch::Watch (int _id) : BaseAction(){
    id =_id;
}

//WATCH
void Watch::act(Session &sess) {
    Watchable *toWatch = sess.getFromContent(id);
    if (toWatch==nullptr) {
        error("Content dose not exist");
        sess.addActionToActionLog(this);
    }else {
        printf("Watching %s ", toWatch->toString().c_str());
        sess.getActiveUser()->addToHistory(toWatch);
        complete();
        sess.addActionToActionLog(this);
        sess.getFromContent(id)->changeToWached();
        printf ("We recommend watching %s, continue watching? [y/n]",toWatch->getNextWatchable(sess)->toString().c_str());
    }
}

std::string Watch::toString() const{
    ActionStatus stat = getStatus();
    std::string ans;
    if (stat==ERROR) {
        ans = "ERROR";
        return ("Watch:"+ans+":"+getErrorMsg());
    }
    if (stat==COMPLETED)
        ans = "COMPLETED";
    if (stat==PENDING)
        ans = "PENDING";
    return ("Watch: %s", ans);
}

//PRINT ACTIONS LOG
void PrintActionsLog::act(Session &sess) {
    sess.printActionsLog();
}

std::string PrintActionsLog::toString() const{
    ActionStatus stat = getStatus();
    std::string ans;
    if (stat==ERROR)
        ans = "ERROR";
    if (stat==COMPLETED)
        ans = "COMPLETED";
    if (stat==PENDING)
        ans = "PENDING";
    return ("Print action log: %s", ans);
}

//EXIT - NEED TO WRITE
void Exit::act(Session &sess) {


}

std::string Exit::toString() const{
    ActionStatus stat = getStatus();
    std::string ans;
    if (stat==ERROR) {
        ans = "ERROR";
        return ("EXit: %s : %s", ans, getErrorMsg());
    }
    if (stat==COMPLETED)
        ans = "COMPLETED";
    if (stat==PENDING)
        ans = "PENDING";
    return ("EXit: %s", ans);
}
