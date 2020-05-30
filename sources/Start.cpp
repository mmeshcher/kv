// Copyright 2020 <mmeshcher>

#include <boost/asio.hpp>

#include "Random.hpp"
#include "DataBase.hpp"
#include "logs.hpp"
#include "Globals.hpp"


int main(int argc, char *argv[])
{
    if (auto returnCode = programArguments(argc, argv); returnCode != 0) {
        return returnCode;
    }

    init();

    if (Globals::writeOnly) {
        BOOST_LOG_TRIVIAL(info) << "Creating random db...";

        DataBase actions{Globals::input};
        actions.create();
        actions.randomFill();

        return 0;
    }

    removeDirectoryIfExists(Globals::output);
    copyDirectory(Globals::input, Globals::output);

    DataBase actions{Globals::output};

    boost::asio::thread_pool pool(Globals::threadAmount);

    auto descriptors = actions.getFamilyDescriptorList();
    auto handlers = actions.open(descriptors);

    std::list<boost::unordered_map<std::string, std::string>> cachedRows;
    for (auto &family : handlers) {
        cachedRows.push_back(actions.getRows(family.get()));
        auto &rows = cachedRows.back();
        auto beginIterator = rows.cbegin();
        if (beginIterator != rows.cend()) {
            boost::asio::post(
                pool, [&actions, &family, beginIterator, &rows]() {
                actions.hashRows(family.get(), beginIterator, rows.cend());
            });
        }
    }
    pool.join();
}
