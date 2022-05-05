#ifndef CACHE_THICK_H
#define CACHE_THICK_H

#include <string>
#include <memory>
#include <ignite/ignite.h>
#include <ignite/ignition.h>

namespace database
{
    class CacheThick
    {
        private:
            ignite::Ignite &_client;
            ignite::cache::Cache<long, std::string> _cache;
            CacheThick(ignite::Ignite &client);

        public:
            static CacheThick get();
            void put(long id, const std::string& val);
            bool get(long id, std::string& val);
            size_t size();
            void remove(long id);
            void remove_all();
            ~CacheThick();
    };
}

#endif