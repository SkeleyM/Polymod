#include <string>
#include <iostream>

static std::string ANSI_WHITE{ "\x1B[37m" };
static std::string ANSI_RED{ "\x1B[31m" };
static std::string ANSI_GREEN{ "\x1B[32m" };

void set_ansi_colour(std::string ansii) {
	std::cout << ansii;
}

void test_log(std::string name, bool status, int line) {
	if (status) {
		std::cout << "Test " << name;
		set_ansi_colour(ANSI_GREEN);
		std::cout << " passed" << std::endl;
		set_ansi_colour(ANSI_WHITE);
	}
	else {
		std::cout << "Test " << name;
		set_ansi_colour(ANSI_RED);
		std::cout << " Failed";
		set_ansi_colour(ANSI_WHITE);
		std::cout << "; line: " << line << std::endl;
	}
}


#define ASSERT_TRUE(status) test_log(__FUNCTION__, status, __LINE__);
#define ASSERT_FALSE(status) test_log(__FUNCTION__, !status, __LINE__);

