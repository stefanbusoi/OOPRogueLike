#pragma once


#include <exception>
#include <iostream>
#include <string>


/**
 * Exception thrown when is an Game logic error(missing components on types of objects witch are necesary...)
 */
class GameLogicException:public std::exception {
private:
  std::string m_message;
public:

  explicit GameLogicException(const std::string& message);
  const char *what() const noexcept;
};
