#pragma once

#include "Connection.hpp"
#include "Enums.hpp"

namespace xapi
{

class Socket final : protected internals::Connection
{
  public:
    Socket() = delete;

    Socket(const Socket &) = delete;
    Socket &operator=(const Socket &) = delete;

    Socket(Socket &&other) = default;
    Socket &operator=(Socket &&other) = delete;

    explicit Socket(boost::asio::io_context &ioContext);
    ~Socket() override = default;

    bool safeMode;

    boost::asio::awaitable<void> initSession(const std::string &host, const std::string &type);

    boost::asio::awaitable<void> closeSession();

    boost::asio::awaitable<std::string> login(const std::string &accountId, const std::string &password);

    boost::asio::awaitable<Json::Value> logout();

    boost::asio::awaitable<Json::Value> getAllSymbols();

    boost::asio::awaitable<Json::Value> getCalendar();

    boost::asio::awaitable<Json::Value> getChartLastRequest(const std::string &symbol, const int start,
                                                            PeriodCode period);

    boost::asio::awaitable<Json::Value> getChartRangeRequest(const std::string &symbol, int start, int end,
                                                             PeriodCode period, int ticks);

    boost::asio::awaitable<Json::Value> getCommissionDef(const std::string &symbol, float volme);

    boost::asio::awaitable<Json::Value> getCurrentUserData();

    boost::asio::awaitable<Json::Value> getIbsHistory(int start, int end);

    boost::asio::awaitable<Json::Value> getMarginLevel();

    boost::asio::awaitable<Json::Value> getMarginTrade(const std::string &symbol, float volume);

    boost::asio::awaitable<Json::Value> getNews(int start, int end);

    boost::asio::awaitable<Json::Value> getProfitCalculation(const std::string &symbol, int cmd, float openPrice,
                                                             float closePrice, float volume);

    boost::asio::awaitable<Json::Value> getServerTime();

    boost::asio::awaitable<Json::Value> getStepRules();

    boost::asio::awaitable<Json::Value> getSymbol(const std::string &symbol);

    boost::asio::awaitable<Json::Value> getTickPrices(const std::vector<std::string> &symbols, int timestamp,
                                                      int level);

    boost::asio::awaitable<Json::Value> getTradeRecords(const std::vector<int> &orders);

    boost::asio::awaitable<Json::Value> getTrades(bool openedOnly);

    boost::asio::awaitable<Json::Value> getTradesHistory(int start, int end);

    boost::asio::awaitable<Json::Value> getTradingHours(const std::vector<std::string> &symbols);

    boost::asio::awaitable<Json::Value> getVersion();

    boost::asio::awaitable<Json::Value> ping();

    boost::asio::awaitable<Json::Value> tradeTransaction(const std::string &symbol, TradeCmd cmd, TradeType type,
                                                         float price, float volume, float sl, float tp, int order,
                                                         int expiration, int offset, const std::string &customComment);

    boost::asio::awaitable<Json::Value> tradeTransactionStatus(int order);

  private:
    boost::asio::awaitable<Json::Value> request(const Json::Value &command);
};

} // namespace xapi
