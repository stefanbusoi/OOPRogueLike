#pragma once


#include <exception>
#include <iostream>
#include <string>


class GameLogicException:public std::exception {
private:
  std::string m_message;
public:

  explicit GameLogicException(const std::string& message);
  const char *what() const noexcept;
};
