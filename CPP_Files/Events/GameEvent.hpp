#pragma once
#include <functional>
#include <set>

/**
 *
 * @tparam ARGS The parammates of the event
 */
template<class... ARGS>
class GameEvent {

  std::unordered_map<size_t,std::function<void(ARGS &&... args)>> EventFunctions;
  size_t HandlerId=0;
public:
  /**
   *
   * @param func calls the function when the event happen
   * @return an id witch is used for unsubscribe
   */
  size_t subscribe(const std::function<void(ARGS &&... args)>& func);

  /**
   *
   * @param handler_ID the id of the function, returned from subscribe(const std::function<...>)
   */
 [[maybe_unused]] void unsubscribe(size_t handler_ID);

  /**
   * calls all subscribed functions
   * @param args paramaters of the function
   */
  void callFunction(ARGS &&... args);
};


//template functions can t be placed in cpp files

template<class ... ARGS>
size_t GameEvent<ARGS...>::subscribe(const std::function<void(ARGS &&...args)> &func) {
  EventFunctions[++HandlerId]=func;
  return HandlerId;
}

template<class ... ARGS>
 void GameEvent<ARGS...>::unsubscribe(size_t handler_ID) {
  EventFunctions.erase(handler_ID);
}

template<class ... ARGS>
void GameEvent<ARGS...>::callFunction(ARGS &&...args) {
  for (const auto& [index,func] : EventFunctions) {
    func(std::forward<ARGS>(args)...);
  }
}


