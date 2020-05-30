// Copyright 2020 <mmeshcher>

#include <gtest/gtest.h>
#include <DataBase.hpp>
#include <Globals.hpp>
#include <logs.hpp>
#include <Random.hpp>
#include <iostream>

class TestKVStorage : public ::testing::Test
{
protected:
	void SetUp()
	{
		int argc_test = 6;
		const char* argv_test[] = {"", "--log-level=error", "--thread=2", "--output=./ted", "./der", "--write-only"};

	    programArguments(argc_test, const_cast<char **>(argv_test));
        	
    	removeDirectoryIfExists(Globals::output);
    	copyDirectory(Globals::input, Globals::output);

    	m_db = new DataBase { Globals::output };
	}
	void TearDown()
	{
		delete m_db;
	}
	DataBase *m_db;
};

TEST_F(TestKVStorage, test1)
{
	auto descriptors = m_db->getFamilyDescriptorList();
	ASSERT_GE(descriptors.size(), 0);

	auto handlers = m_db->open(descriptors);
	ASSERT_GE(handlers.size(), 0);
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
