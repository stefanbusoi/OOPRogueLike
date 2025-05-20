#pragma once
#include <functional>
#include <set>

template<class T, class... ARGS>
class Event {
  std::set<std::function<void(ARGS &&... args)>> EventFunctions;
  public:

  void subscribe(const std::function<void(ARGS &&... args)>& func) {
      EventFunctions.insert(func);
  }
  void unsubscribe(const std::function<void(ARGS &&... args)>& func) {
    EventFunctions.erase(func);
  }
  Event& operator +=(const std::function<void(ARGS &&... args)>& func) {
    EventFunctions.insert(func);
    return *this;
  }
  Event& operator -=(const std::function<void(ARGS &&... args)>& func) {
    EventFunctions.erase(func);
    return *this;
  }
  void CallFunction(ARGS &&... args){
    for (auto func : EventFunctions) {
      func(std::forward<ARGS>(args)...);
    }
  }
};


