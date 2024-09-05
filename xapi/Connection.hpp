#pragma once

/**
 * @file Connection.hpp
 * @brief Defines the Connection class for managing connection.
 *
 * This file contains the definition of the Connection class, which is used for
 * establishing and managing connections, making requests, and handling responses.
 */

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/url.hpp>
#include <chrono>
#include <json/json.h>
#include <string>
#include <unordered_set>

namespace xapi
{
namespace internals
{

/**
 * @class Connection
 * @brief Manages connection and communication with a server using secure WebSocket.
 *
 * The Connection class encapsulates the functionality for establishing an SSL connection,
 * sending requests, and receiving responses.
 */
class Connection
{
  public:
    Connection() = delete;

    Connection(const Connection &) = delete;
    Connection &operator=(const Connection &) = delete;

    Connection(Connection &&other) = default;
    // Move assignment operator is not supported because of boost::beast::websocket::stream
    Connection &operator=(Connection &&other) = delete;

    /**
     * @brief Constructs a new Connection object.
     * @param ioContext The IO context for asynchronous operations.
     */
    explicit Connection(boost::asio::io_context &ioContext);

    virtual ~Connection() = default;

    /**
     * @brief Asynchronously establishes secure WebSocket connection to the server.
     * @param url The URL to connect to.
     * @return An awaitable void.
     * @throw xapi::exception::ConnectionClosed if the connection fails.
     */
    boost::asio::awaitable<void> connect(const boost::url &url);

    /**
     * @brief Asynchronously disconnects from the server.
     * @return An awaitable void.
     */
    boost::asio::awaitable<void> disconnect();

    /**
     * @brief Validates the account type.
     * @param accountType The account type to validate.
     * @throw xapi::exception::ConnectionClosed if the account type is not known.
     */
    void validateAccountType(const std::string &accountType) const;

    /**
     * @brief Makes an asynchronous request to the server.
     * @param command The command to send as a JSON value.
     * @return An awaitable void.
     * @throw xapi::exception::ConnectionClosed if the request fails.
     */
    boost::asio::awaitable<void> makeRequest(const Json::Value &command);

    /**
     * @brief Waits for a response from the server.
     * @return An awaitable Json::Value with response from the server.
     * @throw xapi::exception::ConnectionClosed if the response fails.
     */
    boost::asio::awaitable<Json::Value> waitResponse();

  private:
    /**
     * @brief Establishes an SSL connection asynchronously.
     * @param results The resolved endpoints to attempt to connect to.
     * @param host The host name.
     * @return An awaitable void.
     * @throw xapi::exception::ConnectionClosed if the SSL connection fails.
     */
    boost::asio::awaitable<void> establishSSLConnection(boost::asio::ip::tcp::resolver::results_type results,
                                                        const char *host);

    // The IO context for asynchronous operations.
    boost::asio::io_context &m_ioContext;

    // SSL context, stores certificates.
    boost::asio::ssl::context m_sslContext;

    // The WebSocket stream.
    boost::beast::websocket::stream<boost::asio::ssl::stream<boost::beast::tcp_stream>> m_websocket;

    // Time of the last request.
    std::chrono::time_point<std::chrono::system_clock> m_lastRequestTime;

    // Flag indicating if the connection is established.
    bool m_connectionEstablished;

    // Timeout for requests.
    const std::chrono::milliseconds m_requestTimeout;

    // Default port for WebSocket connections.
    const std::string m_websocketDefaultPort;

    // Set of known account types.
    const std::unordered_set<std::string> m_knownAccountTypes;
};

} // namespace internals
} // namespace xapi
