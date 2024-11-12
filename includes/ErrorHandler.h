#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <iostream>
#include <map>
#include <string>

class ErrorHandler {
public:
  enum class ErrorCode {
    SUCCESS = 0,
    CONNECTION_FAILED,
    TIMEOUT,
    DATA_PARSE_ERROR,
    INVALID_RESPONSE,
    UNKNOWN_ERROR
  };

  ErrorHandler();

  ErrorCode getErrorCode() const;
  std::string getErrorMessage() const;

  void logError(ErrorCode code, const std::string &message);
  void logError(const std::string &message);

private:
  ErrorCode errorCode_;
  std::string errorMessage_;
  std::map<ErrorCode, std::string> errorMessages_;
};

#endif // ERRORHANDLER_H