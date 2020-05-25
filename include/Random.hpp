#pragma once

#include <boost/filesystem.hpp>
#include <random>
#include <iostream>
#include <thread>
#include <boost/program_options.hpp>
#include <boost/log/trivial.hpp>
#include <boost/program_options/parsers.hpp>
#include "PicoSHA2/picosha2.hpp"


int programArguments(int argc, char **argv);

std::string createRandomString(size_t length);

void copyDirectory(const boost::filesystem::path &src, const boost::filesystem::path &dst);

void removeDirectoryIfExists(const boost::filesystem::path &path);
