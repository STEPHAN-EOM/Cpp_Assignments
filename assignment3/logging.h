/**
 * @file logging.h
 * @brief Header file for logging functions.
 * 		See https://en.cppreference.com/w/cpp/utility/source_location
 * @author Chanho Eom
 * @date 23-Mar-2023
 */
#ifndef LOGGING_H_QYJGNTWO
#define LOGGING_H_QYJGNTWO

#include <iostream>
#include <string>
#include <sstream>
#include <source_location>

std::string sourceline(const std::source_location location = std::source_location::current());

#endif /* end of include guard: LOGGING_H_QYJGNTWO */
