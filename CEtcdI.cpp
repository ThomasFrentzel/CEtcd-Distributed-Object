#include "CEtcdI.h"
#include <map>
#include <iostream>
#include <stdexcept>

extern CORBA::ORB_var orb;

CEtcd_i::CEtcd_i() {}

CEtcd_i::~CEtcd_i() {}

std::map<std::string, std::string> serverDb;

std::string CEtcd_i::id ()
{
    return string("customId");
}

::CORBA::Boolean CEtcd_i::put(const std::string& key, const std::string& val)
{
    auto result = serverDb.insert({key, val});

    if (result.second)
    {
        return true;
    }
    else
    {
        serverDb[key] = val;
        return false;
    }
}

std::string CEtcd_i::get(const std::string& key)
{
    auto value = serverDb.find(key);

    if (value == serverDb.end())
    {
        throw InvalidKey();
    }
    else
    {
        return value->second;
    }
}

void CEtcd_i::del(const std::string& key)
{
    auto value = serverDb.find(key);

    if (value == serverDb.end())
    {
        throw InvalidKey();
    }
    else
    {
        serverDb.erase(value);
    }
}