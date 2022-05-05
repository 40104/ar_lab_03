#include "cache.h"
#include "../config/config.h"


#include <ignite/thin/ignite_client.h>
#include <ignite/thin/ignite_client_configuration.h>
#include <ignite/thin/cache/cache_peek_mode.h>
#include <exception>

static ignite::thin::IgniteClient _client;
static ignite::thin::cache::CacheClient<long, std::string> _cache;

namespace database
{
    Cache::Cache()
    {
        ignite::thin::IgniteClientConfiguration cfg;
        cfg.SetEndPoints(Config::get().get_cache_servers());
        cfg.SetPartitionAwareness(true);
        try
        {
            _client = ignite::thin::IgniteClient::Start(cfg);
            _cache = _client.GetOrCreateCache<long, std::string>("authors");
        }
        catch (ignite::IgniteError* err)
        {
            std::cout << "error:" << err->what() << std::endl;
            throw;
        }
    }

    Cache Cache::get()
    {
        static Cache instance;
        return instance;
    }

    void Cache::put(long id, const std::string& val){
        _cache.Put(id,val);
    } 

    void Cache::remove(long id){
        _cache.Remove(id);
    }

    size_t Cache::size(){
        return _cache.GetSize(ignite::thin::cache::CachePeekMode::ALL);
    }

    void Cache::remove_all(){
        _cache.RemoveAll();;
    }

    bool Cache::get(long id, std::string& val){
        try{
            val = _cache.Get(id);
            return true;
        }catch(...){
            throw std::logic_error("key not found in cache");
        }
    }
}