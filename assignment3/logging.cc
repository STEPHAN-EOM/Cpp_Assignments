#include <iostream>
#include "logging.h"

std::string sourceline(const std::source_location location){

std::ostringstream oss;
oss << "file: " << location.file_name() << "(" << location.line() << ":" << location.column() << ")";
return oss.str();
}
