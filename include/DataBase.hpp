#pragma once

#include <string>
#include <random>
#include <utility>
#include <boost/filesystem.hpp>
#include <boost/log/trivial.hpp>
#include <boost/unordered_map.hpp>
#include <rocksdb/db.h>
#include <rocksdb/slice.h>
#include <rocksdb/options.h>
#include <PicoSHA2/picosha2.hpp>

#include "Random.hpp"

class DataBase
{
    std::string path_;
    std::unique_ptr<rocksdb::DB> db_;
public:

    std::list<std::unique_ptr<rocksdb::ColumnFamilyHandle>> randomFillFamilies();
    void randomFillRows(const std::list<std::unique_ptr<rocksdb::ColumnFamilyHandle>> &container);
    explicit DataBase(std::string path): path_(std::move(path)){}
    std::vector<rocksdb::ColumnFamilyDescriptor> getFamilyDescriptorList();
    std::list<std::unique_ptr<rocksdb::ColumnFamilyHandle>> open(const std::vector<rocksdb::ColumnFamilyDescriptor> &descriptors);
    boost::unordered_map<std::string, std::string> getRows(rocksdb::ColumnFamilyHandle *family);
    void hashRows(rocksdb::ColumnFamilyHandle *family,
                  const boost::unordered_map<std::string, std::string>::const_iterator &begin,
                  const boost::unordered_map<std::string, std::string>::const_iterator &end);
    void create();
    void randomFill();
};
