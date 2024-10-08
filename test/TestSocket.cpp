#include "xapi/Exceptions.hpp"
#include "xapi/Socket.hpp"
#include <gtest/gtest.h>
#include <string>

using namespace xapi;

class SocketTest : public testing::Test
{
  protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }

  public:
    boost::asio::io_context &getIoContext()
    {
        return m_context;
    }

    template <typename Awaitable> auto runAwaitable(Awaitable &&awaitable)
    {
        std::exception_ptr eptr;
        using result_type = typename Awaitable::value_type;
        result_type result;

        boost::asio::co_spawn(
            m_context,
            [&]() -> boost::asio::awaitable<void> {
                try
                {
                    result = co_await std::forward<Awaitable>(awaitable);
                }
                catch (...)
                {
                    eptr = std::current_exception();
                }
            },
            boost::asio::detached);

        m_context.run();

        if (eptr)
        {
            std::rethrow_exception(eptr);
        }

        return result;
    }

    template <typename Awaitable> auto runAwaitableVoid(Awaitable &&awaitable)
    {
        std::exception_ptr eptr;
        boost::asio::co_spawn(
            m_context,
            [&]() -> boost::asio::awaitable<void> {
                try
                {
                    co_await std::forward<Awaitable>(awaitable);
                }
                catch (...)
                {
                    eptr = std::current_exception();
                }
            },
            boost::asio::detached);

        m_context.run();

        if (eptr)
        {
            std::rethrow_exception(eptr);
        }
    }

  private:
    boost::asio::io_context m_context;
};

TEST_F(SocketTest, constructor)
{
    EXPECT_NO_THROW(internals::Socket socket = internals::Socket(getIoContext()));
}

TEST_F(SocketTest, getAllSymbols_exception)
{
    internals::Socket socket(getIoContext());
    boost::json::object result;
    EXPECT_THROW(result = runAwaitable(socket.getAllSymbols()), exception::ConnectionClosed);
    EXPECT_TRUE(result.empty());
}

TEST_F(SocketTest, getCalendar_exception)
{
    internals::Socket socket(getIoContext());
    boost::json::object result;
    EXPECT_THROW(result = runAwaitable(socket.getCalendar()), exception::ConnectionClosed);
    EXPECT_TRUE(result.empty());
}

TEST_F(SocketTest, getChartLastRequest_exception)
{
    internals::Socket socket(getIoContext());
    boost::json::object result;
    EXPECT_THROW(result = runAwaitable(socket.getChartLastRequest("EURUSD", 1625097600, PeriodCode::PERIOD_M1)),
                 exception::ConnectionClosed);
    EXPECT_TRUE(result.empty());
}

TEST_F(SocketTest, getChartRangeRequest_exception)
{
    internals::Socket socket(getIoContext());
    boost::json::object result;
    EXPECT_THROW(
        result = runAwaitable(socket.getChartRangeRequest("EURUSD", 1625097600, 1625184000, PeriodCode::PERIOD_M1, 10)),
        exception::ConnectionClosed);
    EXPECT_TRUE(result.empty());
}

TEST_F(SocketTest, getCommissionDef_exception)
{
    internals::Socket socket(getIoContext());
    boost::json::object result;
    EXPECT_THROW(result = runAwaitable(socket.getCommissionDef("EURUSD", 1.0f)), exception::ConnectionClosed);
    EXPECT_TRUE(result.empty());
}

TEST_F(SocketTest, getCurrentUserData_exception)
{
    internals::Socket socket(getIoContext());
    boost::json::object result;
    EXPECT_THROW(result = runAwaitable(socket.getCurrentUserData()), exception::ConnectionClosed);
    EXPECT_TRUE(result.empty());
}

TEST_F(SocketTest, getIbsHistory_exception)
{
    internals::Socket socket(getIoContext());
    boost::json::object result;
    EXPECT_THROW(result = runAwaitable(socket.getIbsHistory(1625097600, 1625184000)), exception::ConnectionClosed);
    EXPECT_TRUE(result.empty());
}

TEST_F(SocketTest, getMarginLevel_exception)
{
    internals::Socket socket(getIoContext());
    boost::json::object result;
    EXPECT_THROW(result = runAwaitable(socket.getMarginLevel()), exception::ConnectionClosed);
    EXPECT_TRUE(result.empty());
}

TEST_F(SocketTest, getMarginTrade_exception)
{
    internals::Socket socket(getIoContext());
    boost::json::object result;
    EXPECT_THROW(result = runAwaitable(socket.getMarginTrade("EURUSD", 1.0f)), exception::ConnectionClosed);
    EXPECT_TRUE(result.empty());
}

TEST_F(SocketTest, getNews_exception)
{
    internals::Socket socket(getIoContext());
    boost::json::object result;
    EXPECT_THROW(result = runAwaitable(socket.getNews(1625097600, 1625184000)), exception::ConnectionClosed);
    EXPECT_TRUE(result.empty());
}

TEST_F(SocketTest, getProfitCalculation_exception)
{
    internals::Socket socket(getIoContext());
    boost::json::object result;
    EXPECT_THROW(result = runAwaitable(socket.getProfitCalculation("EURUSD", 0, 1.1000f, 1.1050f, 1.0f)),
                 exception::ConnectionClosed);
    EXPECT_TRUE(result.empty());
}

TEST_F(SocketTest, getServerTime_exception)
{
    internals::Socket socket(getIoContext());
    boost::json::object result;
    EXPECT_THROW(result = runAwaitable(socket.getServerTime()), exception::ConnectionClosed);
    EXPECT_TRUE(result.empty());
}

TEST_F(SocketTest, getStepRules_exception)
{
    internals::Socket socket(getIoContext());
    boost::json::object result;
    EXPECT_THROW(result = runAwaitable(socket.getStepRules()), exception::ConnectionClosed);
    EXPECT_TRUE(result.empty());
}

TEST_F(SocketTest, getSymbol_exception)
{
    internals::Socket socket(getIoContext());
    boost::json::object result;
    EXPECT_THROW(result = runAwaitable(socket.getSymbol("EURUSD")), exception::ConnectionClosed);
    EXPECT_TRUE(result.empty());
}

TEST_F(SocketTest, getTickPrices_exception)
{
    internals::Socket socket(getIoContext());
    boost::json::object result;
    EXPECT_THROW(result = runAwaitable(socket.getTickPrices({"EURUSD", "GBPUSD"}, 1625097600, 1)),
                 exception::ConnectionClosed);
    EXPECT_TRUE(result.empty());
}

TEST_F(SocketTest, getTradeRecords_exception)
{
    internals::Socket socket(getIoContext());
    boost::json::object result;
    EXPECT_THROW(result = runAwaitable(socket.getTradeRecords({123456, 789012})), exception::ConnectionClosed);
    EXPECT_TRUE(result.empty());
}

TEST_F(SocketTest, getTrades_exception)
{
    internals::Socket socket(getIoContext());
    boost::json::object result;
    EXPECT_THROW(result = runAwaitable(socket.getTrades(true)), exception::ConnectionClosed);
    EXPECT_TRUE(result.empty());
}

TEST_F(SocketTest, getTradesHistory_exception)
{
    internals::Socket socket(getIoContext());
    boost::json::object result;
    EXPECT_THROW(result = runAwaitable(socket.getTradesHistory(1625097600, 1625184000)), exception::ConnectionClosed);
    EXPECT_TRUE(result.empty());
}

TEST_F(SocketTest, getTradingHours_exception)
{
    internals::Socket socket(getIoContext());
    boost::json::object result;
    EXPECT_THROW(result = runAwaitable(socket.getTradingHours({"EURUSD", "GBPUSD"})), exception::ConnectionClosed);
    EXPECT_TRUE(result.empty());
}

TEST_F(SocketTest, getVersion_exception)
{
    internals::Socket socket(getIoContext());
    boost::json::object result;
    EXPECT_THROW(result = runAwaitable(socket.getVersion()), exception::ConnectionClosed);
    EXPECT_TRUE(result.empty());
}

TEST_F(SocketTest, ping_exception)
{
    internals::Socket socket(getIoContext());
    boost::json::object result;
    EXPECT_THROW(result = runAwaitable(socket.ping()), exception::ConnectionClosed);
    EXPECT_TRUE(result.empty());
}

TEST_F(SocketTest, tradeTransaction_safeMode_exception)
{
    internals::Socket socket(getIoContext());
    boost::json::object result;
    EXPECT_NO_THROW(result = runAwaitable(socket.tradeTransaction("EURUSD", TradeCmd::BUY, TradeType::OPEN, 1.1000f,
                                                                  1.0f, 0.0f, 0.0f, 123456, 0, 0, "Test comment")));

    boost::json::object expectedResult;
    expectedResult["status"] = false;
    expectedResult["errorCode"] = "N/A";
    expectedResult["errorDescr"] = "Trading is disabled when safe=True";

    EXPECT_EQ(result, expectedResult);
}

TEST_F(SocketTest, tradeTransaction_exception)
{
    internals::Socket socket(getIoContext());
    socket.setSafeMode(false);

    boost::json::object result;
    EXPECT_THROW(result = runAwaitable(socket.tradeTransaction("EURUSD", TradeCmd::BUY, TradeType::OPEN, 1.1000f, 1.0f,
                                                               0.0f, 0.0f, 123456, 0, 0, "Test comment")),
                 exception::ConnectionClosed);
    EXPECT_TRUE(result.empty());
}

TEST_F(SocketTest, tradeTransactionStatus_exception)
{
    internals::Socket socket(getIoContext());
    boost::json::object result;
    EXPECT_THROW(result = runAwaitable(socket.tradeTransactionStatus(123456)), exception::ConnectionClosed);
    EXPECT_TRUE(result.empty());
}
