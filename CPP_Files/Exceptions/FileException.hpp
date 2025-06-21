#pragma once

#include <exception>
#include <string>


/**
 * exception throw when is a problem with files,(Missing files, reading priviliges missing ...)
 */
class FileException:public std::exception {
  std::string m_message;
public:

  explicit FileException(const std::string& message);
  const char *what() const noexcept;
};

