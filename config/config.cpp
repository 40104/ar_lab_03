#include "config.h"

Config::Config()
{
}

Config &Config::get()
{
    static Config _instance;
    return _instance;
}

const std::string &Config::get_cache_servers() const
{
    return _cache_servers;
}

std::string &Config::cache_servers()
{
    return _cache_servers;
}

const std::string &Config::get_port() const
{
    return _port;
}

const std::string &Config::get_host() const
{
    return _host;
}

const std::string &Config::get_username() const
{
    return _username;
}

const std::string &Config::get_password() const
{
    return _password;
}
const std::string &Config::get_database() const
{
    return _database;
}

std::string &Config::port()
{
    return _port;
}

std::string &Config::host()
{
    return _host;
}

std::string &Config::username()
{
    return _username;
}

std::string &Config::password()
{
    return _password;
}

std::string &Config::database()
{
    return _database;
}