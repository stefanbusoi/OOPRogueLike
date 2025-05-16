#pragma once

#include <exception>
#include <string>


class FileException:public std::exception {
private:
  std::string m_message;
public:

  explicit FileException(const std::string& message);
  const char *what() const noexcept;
};

