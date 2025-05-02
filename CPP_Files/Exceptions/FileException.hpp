#pragma once

#include <exception>
#include <string>


class FileException:public std::exception {
private:
  std::string m_message;
public:
  explicit FileException(const std::string& message):m_message(message ){
#ifndef NDEBUG
   // __debugbreak();
#endif
  }

  const char *what() ;
};

