#pragma once

#include <functional>
#include <string>
#include <unordered_map>

class Request;
class Response;

using handler_t = std::function<void(const Request& req, Response& res)>;


enum class RoutingMethods : int {
    kAll = 0,
    kPost = 1,
    kGet = 2,
    kPut = 3,
    kHead = 4,
    kCheckout = 5,
    kCopy = 6,
    kDelete = 7,
    kLock = 8,
    kMerge = 9,
    kMkactivity = 10,
    kMkcol = 11,
    kMove = 12,
    kMSearch = 13,
    kNotify = 14,
    kOptions = 15,
    kPatch = 16,
    kPurge = 17,
    kReport = 18,
    kSearch = 19,
    kSubscribe = 20,
    kTrace = 21,
    kUnlock = 22,
    kUnsubscribe = 23,
};

class Router;
class Router {
    Router& All(const std::string& uri, handler_t handler) {
        routers_.push_back(std::make_shared<Router>(uri, RoutingMethods::kAll, handler));
        return *this;
    }
    
    Router& Post(const std::string& uri, Router& router);
    Router& Get(const std::string& uri, Router& router);
    Router& Put(const std::string& uri, Router& router);
    Router& Head(const std::string& uri, Router& router);
    Router& Checkout(const std::string& uri, Router& router);
    Router& Copy(const std::string& uri, Router& router);
    Router& Delete(const std::string& uri, Router& router);
    Router& Lock(const std::string& uri, Router& router);
    Router& Merge(const std::string& uri, Router& router);
    Router& Mkactivity(const std::string& uri, Router& router);
    Router& Mkcol(const std::string& uri, Router& router);
    Router& Move(const std::string& uri, Router& router);
    Router& MSearch(const std::string& uri, Router& router);
    Router& Notify(const std::string& uri, Router& router);
    Router& Options(const std::string& uri, Router& router);
    Router& Patch(const std::string& uri, Router& router);
    Router& Purge(const std::string& uri, Router& router);
    Router& Report(const std::string& uri, Router& router);
    Router& Search(const std::string& uri, Router& router);
    Router& Subscribe(const std::string& uri, Router& router);
    Router& Trace(const std::string& uri, Router& router);
    Router& Unlock(const std::string& uri, Router& router);
    Router& Unsubscribe(const std::string& uri, Router& router);

    Router& Param() { return *this; }

    inline Router& Route(const std::string& uri)
    {
        uri_ = uri;
        return *this;
    }

    Router& Use(handler_t handler)
    {
        handler_ = handler;
        return *this;
    }
    
    Router& Use(const std::string& uri, handler_t handler)
    {
        routers_.push_back(std::make_shared<Router>(uri, RoutingMethods::kAll, handler));
        return *this;
    }

    // 构造函数定义 
    Router(const std::string& uri, RoutingMethods method, handler_t handler) 
    : uri_(uri), method_(method), handler_(handler)
    {
    }

private:
    std::string uri_;
    RoutingMethods method_;
    handler_t handler_;

    std::vector<std::shared_ptr<Router>> routers_;
};