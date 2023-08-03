#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#include "record.h"
#include "records.h"
#include "redis.h"

const char *records_key = "movepoint.ru:records";

std::string Records::content(const char *key)
{
    if (key == NULL)
        key = records_key;

    //TODO: optimize&cleanup
	auto redis = get_redis();
    std::vector<std::string> rs;
	redis.lrange(key, 0, -1, std::back_inserter(rs));

    std::vector<Record> records;
    for (const auto &r : rs) {
        std::istringstream s(r);
        Record rec;
        s >> rec;
        records.push_back(rec);
    }

    std::stringstream s;
    std::copy(std::begin(records),
              std::end(records),
              std::ostream_iterator<Record>(s));
    return s.str();
}

void Records::add(const std::string &meta, const std::string &url)
{
	auto redis = get_redis();
	redis.rpush(records_key, meta + "\n" + url);
}
