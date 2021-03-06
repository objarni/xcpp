#include "phone_number.h"
#include <algorithm>
#include <cctype>
#include <iterator>
#include <sstream>

using namespace std;

namespace
{

const int area_code_length = 3;
const int exchange_length = 3;
const int extension_length = 4;
const int valid_number_length = area_code_length + exchange_length + extension_length;
const string cleaned_invalid_number(valid_number_length, '0');

string clean_number(const string& text)
{
    string result;
    copy_if(text.begin(), text.end(), back_inserter(result),
        [](char c) { return isdigit(c) != 0; });
    if (result.length() == valid_number_length + 1) {
        if (result[0] == '1') {
            result.erase(result.begin());
        } else {
            result = cleaned_invalid_number;
        }
    } else if (result.length() < valid_number_length) {
        result = cleaned_invalid_number;
    }
    return result;
}

}

phone_number::phone_number(const string& text)
    : digits_(clean_number(text))
{
}

string phone_number::area_code() const
{
    return digits_.substr(0, area_code_length);
}

string phone_number::exchange() const
{
    return digits_.substr(area_code_length, exchange_length);
}

string phone_number::extension() const
{
    return digits_.substr(area_code_length + exchange_length);
}

string phone_number::number() const
{
    return digits_;
}

phone_number::operator std::string() const
{
    ostringstream buff;
    buff << '(' << area_code() << ") " << exchange() << '-' << extension();
    return buff.str();
}

