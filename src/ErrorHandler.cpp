#include "ErrorHandler.h"

ErrorHandler::ErrorHandler()
    : errorCode_(ErrorCode::SUCCESS), errorMessage_("") {

  errorMessages_[ErrorCode::CONNECTION_FAILED] = "Failed to connect to server.";
  errorMessages_[ErrorCode::TIMEOUT] = "Request timed out.";
  errorMessages_[ErrorCode::DATA_PARSE_ERROR] = "Failed to parse data.";
  errorMessages_[ErrorCode::INVALID_RESPONSE] = "Invalid response received.";
  errorMessages_[ErrorCode::UNKNOWN_ERROR] = "An unknown error occurred.";
}

ErrorHandler::ErrorCode ErrorHandler::getErrorCode() const {

  return errorCode_;
}

std::string ErrorHandler::getErrorMessage() const { return errorMessage_; }

void ErrorHandler::logError(ErrorCode code, const std::string &message) {

  errorCode_ = code;
  errorMessage_ = message.empty() ? errorMessages_[code] : message;

  if (errorCode_ != ErrorCode::SUCCESS) {

    std::cerr << "Error " << static_cast<int>(errorCode_) << ": "
              << errorMessage_ << std::endl;
  }
}

void ErrorHandler::logError(const std::string &message) {

  std::cerr << message << std::endl;
}