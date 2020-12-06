#include <string>

namespace Babel
{
    /**
     * @brief Contains the Babel's Rfc.
     */
    namespace Rfc
    {
        /**
         * @brief Contains every command id.
         */
        enum Code
        {
            UNKNOWN = 0,
            SC_OK = 101,
            SC_ERROR,
            SC_DELETE,
            SC_USER,
            SC_CALL,
            SC_CALL_ANSWER,
            SC_CALL_END,
            SC_CONTACT,
            SC_MSG,
            SC_PING,
            CS_OK = 201,
            CS_ERROR,
            CS_LOGIN,
            CS_LOGOUT,
            CS_DELETE,
            CS_CALL,
            CS_CALL_ANSWER,
            CS_CALL_END,
            CS_CONTACT,
            CS_MSG,
            CS_PING
        };
        /**
         * @brief Contains every user states.
         */
        enum State
        {
            Connected,
            Disconnected,
            Occupied // In a call
        };
    };
};
