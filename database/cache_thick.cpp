#include "cache_thick.h"
#include "../config/config.h"



#include <exception>



namespace database
{
    CacheThick::CacheThick(ignite::Ignite &client) : _client(client),_cache(_client.GetCache<long, std::string>("authors"))
    {

    }

    CacheThick CacheThick::get()
    {
        static ignite::IgniteConfiguration cfg;    
        cfg.springCfgPath = "config/config.xml";
        static  ignite::Ignite client  = ignite::Ignition::Start(cfg);  
        static CacheThick instance(client);
  
        return instance;
    }

    void CacheThick::put(long id, const std::string& val){
        _cache.Put(id,val);
        
    } 

    void CacheThick::remove(long id){
        _cache.Remove(id);
    }

    size_t CacheThick::size(){
        return 0;//cache.GetSize(ignite::thin::cache::CachePeekMode::ALL);
    }

    void CacheThick::remove_all(){
        _cache.RemoveAll();;
    }

    bool CacheThick::get(long id, std::string& val){
        try{
            val = _cache.Get(id);
            return true;
        }catch(...){
            throw std::logic_error("key not found in cache");
        }
    }

    CacheThick::~CacheThick(){
        ignite::Ignition::StopAll(false);
    }
}