#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <memory.h>

#include "../external/xlUnitTest/include/unittest.h"
#include "../include/string.h"

using namespace std;
using namespace stdex;

// str_length
XL_NAMED_TEST_CASE(str_length)
{
    XL_TEST_ASSERT(str_length("") == 0);
    XL_TEST_ASSERT(str_length("\0") == 0);
    XL_TEST_ASSERT(str_length("\0\0") == 0);
    XL_TEST_ASSERT(str_length("a") == 1);
    XL_TEST_ASSERT(str_length("ab") == 2);
    XL_TEST_ASSERT(str_length("a\0b") == 1);
}

// str_split
XL_NAMED_TEST_CASE(str_split)
{
    // char *str, str_len, char *delimiter, delimiter_len
    // char *str, str_len, char delimiter
    // char *str, char *delimiter
    // char *str, char delimiter
    // std::string str, char *delimiter
    // std::string str, char delimiter
    // std::string str, std::string delimiter

    vector<shadow_string> r;

    // char *str, str_len, char *delimiter, size_t delimiter_len

    r = str_split("a|b", 0, "||", 0);
    XL_TEST_ASSERT(r.size() == 0);
    r = str_split("a|b", 0, "||", 1);
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT((string)r[0] == "");
    r = str_split("a|b", 0, "||", 2);
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT((string)r[0] == "");

    r = str_split("a|b", 1, "||", 0);
    XL_TEST_ASSERT(r.size() == 0);
    r = str_split("a|b", 1, "||", 1);
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT((string)r[0] == "a");
    r = str_split("a|b", 1, "||", 2);
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT((string)r[0] == "a");

    r = str_split("a|b", 2, "||", 0);
    XL_TEST_ASSERT(r.size() == 0);
    r = str_split("a|b", 2, "||", 1);
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT((string)r[0] == "a");
    XL_TEST_ASSERT((string)r[1] == "");
    r = str_split("a|b", 2, "||", 2);
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT((string)r[0] == "a|");

    r = str_split("a|b", 3, "||", 0);
    XL_TEST_ASSERT(r.size() == 0);
    r = str_split("a|b", 3, "||", 1);
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT((string)r[0] == "a");
    XL_TEST_ASSERT((string)r[1] == "b");
    r = str_split("a|b", 3, "||", 2);
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT((string)r[0] == "a|b");

    r = str_split("a|b", 3, "||", 1, 1);
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT((string)r[0] == "a|b");
    r = str_split("a|b|c", 5, "||", 1, 2);
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT((string)r[0] == "a");
    XL_TEST_ASSERT((string)r[1] == "b|c");

    // char *str, str_len, char delimiter

    r = str_split("a|b", 0, '|');
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT((string)r[0] == "");
    r = str_split("a|b", 1, '|');
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT((string)r[0] == "a");
    r = str_split("a|b", 2, '|');
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT((string)r[0] == "a");
    XL_TEST_ASSERT((string)r[1] == "");
    r = str_split("a|b", 3, '|');
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT((string)r[0] == "a");
    XL_TEST_ASSERT((string)r[1] == "b");
    r = str_split("a|b", 3, '|', 1);
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT((string)r[0] == "a|b");
    r = str_split("a|b|c", 5, '|', 2);
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT((string)r[0] == "a");
    XL_TEST_ASSERT((string)r[1] == "b|c");

    // char *str, char *delimiter

    r = str_split("", "");
    XL_TEST_ASSERT(r.size() == 0);
    r = str_split("", "|");
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT((string)r[0] == "");
    r = str_split("", "||");
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT((string)r[0] == "");

    r = str_split("a", "");
    XL_TEST_ASSERT(r.size() == 0);
    r = str_split("a", "|");
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT((string)r[0] == "a");
    r = str_split("a", "||");
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT((string)r[0] == "a");

    r = str_split("a|", "");
    XL_TEST_ASSERT(r.size() == 0);
    r = str_split("a|", "|");
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT((string)r[0] == "a");
    XL_TEST_ASSERT((string)r[1] == "");
    r = str_split("a|", "||");
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT((string)r[0] == "a|");

    r = str_split("a|b", "");
    XL_TEST_ASSERT(r.size() == 0);
    r = str_split("a|b", "|");
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT((string)r[0] == "a");
    XL_TEST_ASSERT((string)r[1] == "b");
    r = str_split("a|b", "||");
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT((string)r[0] == "a|b");

    r = str_split("a|b", "|", 1);
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT((string)r[0] == "a|b");
    r = str_split("a|b|c", "|", 2);
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT((string)r[0] == "a");
    XL_TEST_ASSERT((string)r[1] == "b|c");

    // char *str, char delimiter
    r = str_split("", '|');
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT((string)r[0] == "");
    r = str_split("a", '|');
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT((string)r[0] == "a");
    r = str_split("a|", '|');
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT((string)r[0] == "a");
    XL_TEST_ASSERT((string)r[1] == "");
    r = str_split("a|b", '|');
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT((string)r[0] == "a");
    XL_TEST_ASSERT((string)r[1] == "b");
    r = str_split("a|b", '|', 1);
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT((string)r[0] == "a|b");
    r = str_split("a|b|c", '|', 2);
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT((string)r[0] == "a");
    XL_TEST_ASSERT((string)r[1] == "b|c");

    // std::string str, char *delimiter

    std::string str;
    str = "";
    r = str_split(str, "");
    XL_TEST_ASSERT(r.size() == 0);
    r = str_split(str, "|");
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT((string)r[0] == "");
    r = str_split(str, "||");
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT((string)r[0] == "");

    str = "a";
    r = str_split(str, "");
    XL_TEST_ASSERT(r.size() == 0);
    r = str_split(str, "|");
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT((string)r[0] == "a");
    r = str_split(str, "||");
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT((string)r[0] == "a");

    str = "a|";
    r = str_split(str, "");
    XL_TEST_ASSERT(r.size() == 0);
    r = str_split(str, "|");
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT((string)r[0] == "a");
    XL_TEST_ASSERT((string)r[1] == "");
    r = str_split(str, "||");
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT((string)r[0] == "a|");

    str = "a|b";
    r = str_split(str, "");
    XL_TEST_ASSERT(r.size() == 0);
    r = str_split(str, "|");
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT((string)r[0] == "a");
    XL_TEST_ASSERT((string)r[1] == "b");
    r = str_split(str, "||");
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT((string)r[0] == "a|b");

    str = "a|b";
    r = str_split(str, "|", 1);
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT((string)r[0] == "a|b");
    str = "a|b|c";
    r = str_split(str, "|", 2);
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT((string)r[0] == "a");
    XL_TEST_ASSERT((string)r[1] == "b|c");

    // std::string str, char delimiter

    str = "";
    r = str_split(str, '|');
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT((string)r[0] == "");
    str = "a";
    r = str_split(str, '|');
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT((string)r[0] == "a");
    str = "a|";
    r = str_split(str, '|');
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT((string)r[0] == "a");
    XL_TEST_ASSERT((string)r[1] == "");
    str = "a|b";
    r = str_split(str, '|');
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT((string)r[0] == "a");
    XL_TEST_ASSERT((string)r[1] == "b");
    r = str_split(str, '|', 1);
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT((string)r[0] == "a|b");
    str = "a|b|c";
    r = str_split(str, '|', 2);
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT((string)r[0] == "a");
    XL_TEST_ASSERT((string)r[1] == "b|c");

    // std::string str, std::string delimiter

    str = "";
    r = str_split(str, string(""));
    XL_TEST_ASSERT(r.size() == 0);
    r = str_split(str, string("|"));
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT((string)r[0] == "");
    r = str_split(str, string("||"));
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT((string)r[0] == "");

    str = "a";
    r = str_split(str, string(""));
    XL_TEST_ASSERT(r.size() == 0);
    r = str_split(str, string("|"));
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT((string)r[0] == "a");
    r = str_split(str, string("||"));
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT((string)r[0] == "a");

    str = "a|";
    r = str_split(str, string(""));
    XL_TEST_ASSERT(r.size() == 0);
    r = str_split(str, string("|"));
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT((string)r[0] == "a");
    XL_TEST_ASSERT((string)r[1] == "");
    r = str_split(str, string("||"));
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT((string)r[0] == "a|");

    str = "a|b";
    r = str_split(str, string(""));
    XL_TEST_ASSERT(r.size() == 0);
    r = str_split(str, string("|"));
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT((string)r[0] == "a");
    XL_TEST_ASSERT((string)r[1] == "b");
    r = str_split(str, string("||"));
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT((string)r[0] == "a|b");

    str = "a|b";
    r = str_split(str, string("|"), 1);
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT((string)r[0] == "a|b");
    str = "a|b|c";
    r = str_split(str, string("|"), 2);
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT((string)r[0] == "a");
    XL_TEST_ASSERT((string)r[1] == "b|c"); 
}

// str_split_copy
XL_NAMED_TEST_CASE(str_split_copy)
{
    // char *str, str_len, char *delimiter, delimiter_len
    // char *str, str_len, char delimiter
    // char *str, char *delimiter
    // char *str, char delimiter
    // std::string str, char *delimiter
    // std::string str, char delimiter
    // std::string str, std::string delimiter

    vector<string> r;

    // char *str, str_len, char *delimiter, size_t delimiter_len

    r = str_split_copy("a|b", 0, "||", 0);
    XL_TEST_ASSERT(r.size() == 0);
    r = str_split_copy("a|b", 0, "||", 1);
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT(r[0] == "");
    r = str_split_copy("a|b", 0, "||", 2);
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT(r[0] == "");

    r = str_split_copy("a|b", 1, "||", 0);
    XL_TEST_ASSERT(r.size() == 0);
    r = str_split_copy("a|b", 1, "||", 1);
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT(r[0] == "a");
    r = str_split_copy("a|b", 1, "||", 2);
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT(r[0] == "a");

    r = str_split_copy("a|b", 2, "||", 0);
    XL_TEST_ASSERT(r.size() == 0);
    r = str_split_copy("a|b", 2, "||", 1);
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT(r[0] == "a");
    XL_TEST_ASSERT(r[1] == "");
    r = str_split_copy("a|b", 2, "||", 2);
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT(r[0] == "a|");

    r = str_split_copy("a|b", 3, "||", 0);
    XL_TEST_ASSERT(r.size() == 0);
    r = str_split_copy("a|b", 3, "||", 1);
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT(r[0] == "a");
    XL_TEST_ASSERT(r[1] == "b");
    r = str_split_copy("a|b", 3, "||", 2);
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT(r[0] == "a|b");

    r = str_split_copy("a|b", 3, "||", 1, 1);
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT(r[0] == "a|b");
    r = str_split_copy("a|b|c", 5, "||", 1, 2);
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT(r[0] == "a");
    XL_TEST_ASSERT(r[1] == "b|c");

    // char *str, str_len, char delimiter

    r = str_split_copy("a|b", 0, '|');
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT(r[0] == "");
    r = str_split_copy("a|b", 1, '|');
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT(r[0] == "a");
    r = str_split_copy("a|b", 2, '|');
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT(r[0] == "a");
    XL_TEST_ASSERT(r[1] == "");
    r = str_split_copy("a|b", 3, '|');
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT(r[0] == "a");
    XL_TEST_ASSERT(r[1] == "b");
    r = str_split_copy("a|b", 3, '|', 1);
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT(r[0] == "a|b");
    r = str_split_copy("a|b|c", 5, '|', 2);
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT(r[0] == "a");
    XL_TEST_ASSERT(r[1] == "b|c");

    // char *str, char *delimiter

    r = str_split_copy("", "");
    XL_TEST_ASSERT(r.size() == 0);
    r = str_split_copy("", "|");
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT(r[0] == "");
    r = str_split_copy("", "||");
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT(r[0] == "");

    r = str_split_copy("a", "");
    XL_TEST_ASSERT(r.size() == 0);
    r = str_split_copy("a", "|");
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT(r[0] == "a");
    r = str_split_copy("a", "||");
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT(r[0] == "a");

    r = str_split_copy("a|", "");
    XL_TEST_ASSERT(r.size() == 0);
    r = str_split_copy("a|", "|");
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT(r[0] == "a");
    XL_TEST_ASSERT(r[1] == "");
    r = str_split_copy("a|", "||");
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT(r[0] == "a|");

    r = str_split_copy("a|b", "");
    XL_TEST_ASSERT(r.size() == 0);
    r = str_split_copy("a|b", "|");
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT(r[0] == "a");
    XL_TEST_ASSERT(r[1] == "b");
    r = str_split_copy("a|b", "||");
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT(r[0] == "a|b");

    r = str_split_copy("a|b", "|", 1);
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT(r[0] == "a|b");
    r = str_split_copy("a|b|c", "|", 2);
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT(r[0] == "a");
    XL_TEST_ASSERT(r[1] == "b|c");

    // char *str, char delimiter
    r = str_split_copy("", '|');
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT(r[0] == "");
    r = str_split_copy("a", '|');
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT(r[0] == "a");
    r = str_split_copy("a|", '|');
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT(r[0] == "a");
    XL_TEST_ASSERT(r[1] == "");
    r = str_split_copy("a|b", '|');
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT(r[0] == "a");
    XL_TEST_ASSERT(r[1] == "b");
    r = str_split_copy("a|b", '|', 1);
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT(r[0] == "a|b");
    r = str_split_copy("a|b|c", '|', 2);
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT(r[0] == "a");
    XL_TEST_ASSERT(r[1] == "b|c");

    // std::string str, char *delimiter

    r = str_split_copy(string(""), "");
    XL_TEST_ASSERT(r.size() == 0);
    r = str_split_copy(string(""), "|");
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT(r[0] == "");
    r = str_split_copy(string(""), "||");
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT(r[0] == "");

    r = str_split_copy(string("a"), "");
    XL_TEST_ASSERT(r.size() == 0);
    r = str_split_copy(string("a"), "|");
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT(r[0] == "a");
    r = str_split_copy(string("a"), "||");
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT(r[0] == "a");

    r = str_split_copy(string("a|"), "");
    XL_TEST_ASSERT(r.size() == 0);
    r = str_split_copy(string("a|"), "|");
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT(r[0] == "a");
    XL_TEST_ASSERT(r[1] == "");
    r = str_split_copy(string("a|"), "||");
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT(r[0] == "a|");

    r = str_split_copy(string("a|b"), "");
    XL_TEST_ASSERT(r.size() == 0);
    r = str_split_copy(string("a|b"), "|");
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT(r[0] == "a");
    XL_TEST_ASSERT(r[1] == "b");
    r = str_split_copy(string("a|b"), "||");
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT(r[0] == "a|b");

    r = str_split_copy(string("a|b"), "|", 1);
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT(r[0] == "a|b");
    r = str_split_copy(string("a|b|c"), "|", 2);
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT(r[0] == "a");
    XL_TEST_ASSERT(r[1] == "b|c");

    // std::string str, char delimiter

    r = str_split_copy(string(""), '|');
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT(r[0] == "");
    r = str_split_copy(string("a"), '|');
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT(r[0] == "a");
    r = str_split_copy(string("a|"), '|');
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT(r[0] == "a");
    XL_TEST_ASSERT(r[1] == "");
    r = str_split_copy(string("a|b"), '|');
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT(r[0] == "a");
    XL_TEST_ASSERT(r[1] == "b");
    r = str_split_copy(string("a|b"), '|', 1);
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT(r[0] == "a|b");
    r = str_split_copy(string("a|b|c"), '|', 2);
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT(r[0] == "a");
    XL_TEST_ASSERT(r[1] == "b|c");

    // std::string str, std::string delimiter

    r = str_split_copy(string(""), string(""));
    XL_TEST_ASSERT(r.size() == 0);
    r = str_split_copy(string(""), string("|"));
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT(r[0] == "");
    r = str_split_copy(string(""), string("||"));
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT(r[0] == "");

    r = str_split_copy(string("a"), string(""));
    XL_TEST_ASSERT(r.size() == 0);
    r = str_split_copy(string("a"), string("|"));
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT(r[0] == "a");
    r = str_split_copy(string("a"), string("||"));
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT(r[0] == "a");

    r = str_split_copy(string("a|"), string(""));
    XL_TEST_ASSERT(r.size() == 0);
    r = str_split_copy(string("a|"), string("|"));
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT(r[0] == "a");
    XL_TEST_ASSERT(r[1] == "");
    r = str_split_copy(string("a|"), string("||"));
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT(r[0] == "a|");

    r = str_split_copy(string("a|b"), string(""));
    XL_TEST_ASSERT(r.size() == 0);
    r = str_split_copy(string("a|b"), string("|"));
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT(r[0] == "a");
    XL_TEST_ASSERT(r[1] == "b");
    r = str_split_copy(string("a|b"), string("||"));
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT(r[0] == "a|b");

    r = str_split_copy(string("a|b"), string("|"), 1);
    XL_TEST_ASSERT(r.size() == 1);
    XL_TEST_ASSERT(r[0] == "a|b");
    r = str_split_copy(string("a|b|c"), string("|"), 2);
    XL_TEST_ASSERT(r.size() == 2);
    XL_TEST_ASSERT(r[0] == "a");
    XL_TEST_ASSERT(r[1] == "b|c");
}

// str_combine
XL_NAMED_TEST_CASE(str_combine)
{
    // shadow_string list, char *delimiter, delimiter_len
    // shadow_string list, char *delimiter
    // shadow_string list, char delimiter
    // shadow_string list, std::string delimiter
    // std::string list, char *delimiter, delimiter_len
    // std::string list, char *delimiter
    // std::string list, char delimiter
    // std::string list, std::string delimiter

    const char *p = "ab";
    vector<shadow_string> l0;
    vector<shadow_string> l1;
    l1.push_back(shadow_string(p, 1));
    vector<shadow_string> l2;
    l2.push_back(shadow_string(p++, 1));
    l2.push_back(shadow_string(p++, 1));

    // shadow_string list, char *delimiter, delimiter_len
    XL_TEST_ASSERT(str_combine(l0, "|||", 1) == "");
    XL_TEST_ASSERT(str_combine(l0, "|||", 2) == "");
    XL_TEST_ASSERT(str_combine(l0, "|||", 3) == "");
    XL_TEST_ASSERT(str_combine(l1, "|||", 1) == "a");
    XL_TEST_ASSERT(str_combine(l1, "|||", 2) == "a");
    XL_TEST_ASSERT(str_combine(l1, "|||", 3) == "a");
    XL_TEST_ASSERT(str_combine(l2, "|||", 1) == "a|b");
    XL_TEST_ASSERT(str_combine(l2, "|||", 2) == "a||b");
    XL_TEST_ASSERT(str_combine(l2, "|||", 3) == "a|||b");
    // shadow_string list, char *delimiter
    XL_TEST_ASSERT(str_combine(l0, "|") == "");
    XL_TEST_ASSERT(str_combine(l1, "|") == "a");
    XL_TEST_ASSERT(str_combine(l2, "|") == "a|b");
    // shadow_string list, char delimiter
    XL_TEST_ASSERT(str_combine(l0, '|') == "");
    XL_TEST_ASSERT(str_combine(l1, '|') == "a");
    XL_TEST_ASSERT(str_combine(l2, '|') == "a|b");
    // shadow_string list, std::string delimiter
    XL_TEST_ASSERT(str_combine(l0, string("|")) == "");
    XL_TEST_ASSERT(str_combine(l1, string("|")) == "a");
    XL_TEST_ASSERT(str_combine(l2, string("|")) == "a|b");

    vector<string> m0;
    vector<string> m1;
    m1.push_back("a");
    vector<string> m2;
    m2.push_back("a");
    m2.push_back("b");

    // std::string list, char *delimiter, delimiter_len
    XL_TEST_ASSERT(str_combine(m0, "|||", 1) == "");
    XL_TEST_ASSERT(str_combine(m0, "|||", 2) == "");
    XL_TEST_ASSERT(str_combine(m0, "|||", 3) == "");
    XL_TEST_ASSERT(str_combine(m1, "|||", 1) == "a");
    XL_TEST_ASSERT(str_combine(m1, "|||", 2) == "a");
    XL_TEST_ASSERT(str_combine(m1, "|||", 3) == "a");
    XL_TEST_ASSERT(str_combine(m2, "|||", 1) == "a|b");
    XL_TEST_ASSERT(str_combine(m2, "|||", 2) == "a||b");
    XL_TEST_ASSERT(str_combine(m2, "|||", 3) == "a|||b");
    // std::string list, char *delimiter
    XL_TEST_ASSERT(str_combine(m0, "|") == "");
    XL_TEST_ASSERT(str_combine(m1, "|") == "a");
    XL_TEST_ASSERT(str_combine(m2, "|") == "a|b");
    // std::string list, char delimiter
    XL_TEST_ASSERT(str_combine(m0, '|') == "");
    XL_TEST_ASSERT(str_combine(m1, '|') == "a");
    XL_TEST_ASSERT(str_combine(m2, '|') == "a|b");
    // std::string list, std::string delimiter
    XL_TEST_ASSERT(str_combine(m0, string("|")) == "");
    XL_TEST_ASSERT(str_combine(m1, string("|")) == "a");
    XL_TEST_ASSERT(str_combine(m2, string("|")) == "a|b");
}

// str_replace_inplace
XL_NAMED_TEST_CASE(str_replace_inplace)
{
    // char *str, str_len, char *find, find_len, char *replace, replace_len
    // char *str, str_len, char *find, char *replace
    // char *str, str_len, char find, char replace
    // std::string &str, char *find, find_len, char *replace, replace_len
    // std::string &str, char *find, char *replace
    // std::string &str, char find, char replace
    // std::string &str, std::string find, std::string replace

    char sz[] = "ab";
    // char *str, str_len, char *find, find_len, char *replace, replace_len
    strcpy(sz, "ab");
    XL_TEST_ASSERT(str_replace_inplace(sz, 2, "ab", 1, "xy", 1) == sz);
    XL_TEST_ASSERT(string(sz) == "xb");
    strcpy(sz, "ab");
    XL_TEST_ASSERT(str_replace_inplace(sz, 2, "ab", 2, "xy", 1) == sz);
    XL_TEST_ASSERT(string(sz) == "x");
    strcpy(sz, "ab");
    XL_TEST_ASSERT(str_replace_inplace(sz, 2, "ab", 2, "xy", 2) == sz);
    XL_TEST_ASSERT(string(sz) == "xy");
    strcpy(sz, "aa");
    XL_TEST_ASSERT(str_replace_inplace(sz, 2, "a", 1, "x", 1) == sz);
    XL_TEST_ASSERT(string(sz) == "xx");
    strcpy(sz, "aa");
    XL_TEST_ASSERT(str_replace_inplace(sz, 2, "a", 1, "x", 1, 1) == sz);
    XL_TEST_ASSERT(string(sz) == "xa");
    // char *str, str_len, char *find, char *replace
    strcpy(sz, "ab");
    XL_TEST_ASSERT(str_replace_inplace(sz, 2, "a", "x") == sz);
    XL_TEST_ASSERT(string(sz) == "xb");
    strcpy(sz, "ab");
    XL_TEST_ASSERT(str_replace_inplace(sz, 2, "ab", "x") == sz);
    XL_TEST_ASSERT(string(sz) == "x");
    strcpy(sz, "ab");
    XL_TEST_ASSERT(str_replace_inplace(sz, 2, "ab", "xy") == sz);
    XL_TEST_ASSERT(string(sz) == "xy");
    strcpy(sz, "aa");
    XL_TEST_ASSERT(str_replace_inplace(sz, 2, "a", "x") == sz);
    XL_TEST_ASSERT(string(sz) == "xx");
    strcpy(sz, "aa");
    XL_TEST_ASSERT(str_replace_inplace(sz, 2, "a", "x", 1) == sz);
    XL_TEST_ASSERT(string(sz) == "xa");
    // char *str, str_len, char find, char replace
    strcpy(sz, "ab");
    XL_TEST_ASSERT(str_replace_inplace(sz, 2, 'a', 'x') == sz);
    XL_TEST_ASSERT(string(sz) == "xb");
    strcpy(sz, "aa");
    XL_TEST_ASSERT(str_replace_inplace(sz, 2, 'a', 'x') == sz);
    XL_TEST_ASSERT(string(sz) == "xx");
    strcpy(sz, "aa");
    XL_TEST_ASSERT(str_replace_inplace(sz, 2, 'a', 'x', 1) == sz);
    XL_TEST_ASSERT(string(sz) == "xa");

    string str;
    // std::string &str, char *find, find_len, char *replace, replace_len
    str = "ab";
    XL_TEST_ASSERT(str_replace_inplace(str, "ab", 1, "xy", 1) == str);
    XL_TEST_ASSERT(str == "xb");
    str = "ab";
    XL_TEST_ASSERT(str_replace_inplace(str, "ab", 2, "xy", 1) == str);
    XL_TEST_ASSERT(str == "x");
    str = "ab";
    XL_TEST_ASSERT(str_replace_inplace(str, "ab", 2, "xy", 2) == str);
    XL_TEST_ASSERT(str == "xy");
    str = "aa";
    XL_TEST_ASSERT(str_replace_inplace(str, "a", 1, "x", 1) == str);
    XL_TEST_ASSERT(str == "xx");
    str = "aa";
    XL_TEST_ASSERT(str_replace_inplace(str, "a", 1, "x", 1, 1) == str);
    XL_TEST_ASSERT(str == "xa");
    // std::string &str, char *find, char *replace
    str = "ab";
    XL_TEST_ASSERT(str_replace_inplace(str, "a", "x") == str);
    XL_TEST_ASSERT(str == "xb");
    str = "ab";
    XL_TEST_ASSERT(str_replace_inplace(str, "ab", "x") == str);
    XL_TEST_ASSERT(str == "x");
    str = "ab";
    XL_TEST_ASSERT(str_replace_inplace(str, "ab", "xy") == str);
    XL_TEST_ASSERT(str == "xy");
    str = "aa";
    XL_TEST_ASSERT(str_replace_inplace(str, "a", "x") == str);
    XL_TEST_ASSERT(str == "xx");
    str = "aa";
    XL_TEST_ASSERT(str_replace_inplace(str, "a", "x", 1) == str);
    XL_TEST_ASSERT(str == "xa");
    // std::string &str, char find, char replace
    str = "ab";
    XL_TEST_ASSERT(str_replace_inplace(str, 'a', 'x') == str);
    XL_TEST_ASSERT(str == "xb");
    str = "aa";
    XL_TEST_ASSERT(str_replace_inplace(str, 'a', 'x') == str);
    XL_TEST_ASSERT(str == "xx");
    str = "aa";
    XL_TEST_ASSERT(str_replace_inplace(str, 'a', 'x', 1) == str);
    XL_TEST_ASSERT(str == "xa");
    // std::string &str, std::string find, std::string replace
    str = "ab";
    XL_TEST_ASSERT(str_replace_inplace(str, string("a"), string("x")) == str);
    XL_TEST_ASSERT(str == "xb");
    str = "ab";
    XL_TEST_ASSERT(str_replace_inplace(str, string("ab"), string("x")) == str);
    XL_TEST_ASSERT(str == "x");
    str = "ab";
    XL_TEST_ASSERT(str_replace_inplace(str, string("ab"), string("xy")) == str);
    XL_TEST_ASSERT(str == "xy");
    str = "aa";
    XL_TEST_ASSERT(str_replace_inplace(str, string("a"), string("x")) == str);
    XL_TEST_ASSERT(str == "xx");
    str = "aa";
    XL_TEST_ASSERT(str_replace_inplace(str, string("a"), string("x"), 1) == str);
    XL_TEST_ASSERT(str == "xa");
}

// str_replace
XL_NAMED_TEST_CASE(str_replace)
{
    // char *str, str_len, char *find, find_len, char *replace, replace_len
    // char *str, str_len, char *find, char *replace
    // char *str, str_len, char find, char replace
    // std::string str, char *find, find_len, char *replace, replace_len
    // std::string str, char *find, char *replace
    // std::string str, char find, char replace
    // std::string str, std::string find, std::string replace

    char sz[] = "ab";
    // char *str, str_len, char *find, find_len, char *replace, replace_len
    strcpy(sz, "ab");
    XL_TEST_ASSERT(str_replace(sz, 2, "ab", 1, "xy", 1) == "xb");
    XL_TEST_ASSERT(string(sz) == "ab");
    XL_TEST_ASSERT(str_replace(sz, 2, "ab", 2, "xy", 1) == "x");
    XL_TEST_ASSERT(string(sz) == "ab");
    XL_TEST_ASSERT(str_replace(sz, 2, "ab", 2, "xy", 2) == "xy");
    XL_TEST_ASSERT(string(sz) == "ab");
    strcpy(sz, "aa");
    XL_TEST_ASSERT(str_replace(sz, 2, "a", 1, "x", 1) == "xx");
    XL_TEST_ASSERT(string(sz) == "aa");
    XL_TEST_ASSERT(str_replace(sz, 2, "a", 1, "x", 1, 1) == "xa");
    XL_TEST_ASSERT(string(sz) == "aa");
    // char *str, str_len, char *find, char *replace
    strcpy(sz, "ab");
    XL_TEST_ASSERT(str_replace(sz, 2, "a", "x") == "xb");
    XL_TEST_ASSERT(string(sz) == "ab");
    XL_TEST_ASSERT(str_replace(sz, 2, "ab", "x") == "x");
    XL_TEST_ASSERT(string(sz) == "ab");
    XL_TEST_ASSERT(str_replace(sz, 2, "ab", "xy") == "xy");
    XL_TEST_ASSERT(string(sz) == "ab");
    strcpy(sz, "aa");
    XL_TEST_ASSERT(str_replace(sz, 2, "a", "x") == "xx");
    XL_TEST_ASSERT(string(sz) == "aa");
    XL_TEST_ASSERT(str_replace(sz, 2, "a", "x", 1) == "xa");
    XL_TEST_ASSERT(string(sz) == "aa");
    // char *str, str_len, char find, char replace
    strcpy(sz, "ab");
    XL_TEST_ASSERT(str_replace(sz, 2, 'a', 'x') == "xb");
    XL_TEST_ASSERT(string(sz) == "ab");
    strcpy(sz, "aa");
    XL_TEST_ASSERT(str_replace(sz, 2, 'a', 'x') == "xx");
    XL_TEST_ASSERT(string(sz) == "aa");
    XL_TEST_ASSERT(str_replace(sz, 2, 'a', 'x', 1) == "xa");
    XL_TEST_ASSERT(string(sz) == "aa");

    string str;
    // std::string str, char *find, find_len, char *replace, replace_len
    str = "ab";
    XL_TEST_ASSERT(str_replace(str, "ab", 1, "xy", 1) == "xb");
    XL_TEST_ASSERT(str == "ab");
    XL_TEST_ASSERT(str_replace(str, "ab", 2, "xy", 1) == "x");
    XL_TEST_ASSERT(str == "ab");
    XL_TEST_ASSERT(str_replace(str, "ab", 2, "xy", 2) == "xy");
    XL_TEST_ASSERT(str == "ab");
    str = "aa";
    XL_TEST_ASSERT(str_replace(str, "a", 1, "x", 1) == "xx");
    XL_TEST_ASSERT(str == "aa");
    XL_TEST_ASSERT(str_replace(str, "a", 1, "x", 1, 1) == "xa");
    XL_TEST_ASSERT(str == "aa");
    // std::string str, char *find, char *replace
    str = "ab";
    XL_TEST_ASSERT(str_replace(str, "a", "x") == "xb");
    XL_TEST_ASSERT(str == "ab");
    XL_TEST_ASSERT(str_replace(str, "ab", "x") == "x");
    XL_TEST_ASSERT(str == "ab");
    XL_TEST_ASSERT(str_replace(str, "ab", "xy") == "xy");
    XL_TEST_ASSERT(str == "ab");
    str = "aa";
    XL_TEST_ASSERT(str_replace(str, "a", "x") == "xx");
    XL_TEST_ASSERT(str == "aa");
    XL_TEST_ASSERT(str_replace(str, "a", "x", 1) == "xa");
    XL_TEST_ASSERT(str == "aa");
    // std::string str, char find, char replace
    str = "ab";
    XL_TEST_ASSERT(str_replace(str, 'a', 'x') == "xb");
    XL_TEST_ASSERT(str == "ab");
    str = "aa";
    XL_TEST_ASSERT(str_replace(str, 'a', 'x') == "xx");
    XL_TEST_ASSERT(str == "aa");
    XL_TEST_ASSERT(str_replace(str, 'a', 'x', 1) == "xa");
    XL_TEST_ASSERT(str == "aa");
    // std::string str, std::string find, std::string replace
    str = "ab";
    XL_TEST_ASSERT(str_replace(str, string("a"), string("x")) == "xb");
    XL_TEST_ASSERT(str == "ab");
    XL_TEST_ASSERT(str_replace(str, string("ab"), string("x")) == "x");
    XL_TEST_ASSERT(str == "ab");
    XL_TEST_ASSERT(str_replace(str, string("ab"), string("xy")) == "xy");
    XL_TEST_ASSERT(str == "ab");
    str = "aa";
    XL_TEST_ASSERT(str_replace(str, string("a"), string("x")) == "xx");
    XL_TEST_ASSERT(str == "aa");
    XL_TEST_ASSERT(str_replace(str, string("a"), string("x"), 1) == "xa");
    XL_TEST_ASSERT(str == "aa");
}
