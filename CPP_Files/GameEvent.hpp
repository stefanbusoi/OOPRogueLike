#pragma once
#include <functional>
#include <set>

template<class... ARGS>
class GameEvent {

  std::unordered_map<size_t,std::function<void(ARGS &&... args)>> EventFunctions;
  size_t HandlerId=0;
public:

  size_t subscribe(const std::function<void(ARGS &&... args)>& func) {
    EventFunctions[++HandlerId]=func;
    return HandlerId;
  }
  void unsubscribe(size_t handler_ID) {
    EventFunctions.erase(handler_ID);
  }
  void CallFunction(ARGS &&... args){
    for (auto [index,func] : EventFunctions) {
      func(std::forward<ARGS>(args)...);
    }
  }
};


