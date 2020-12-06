#pragma once

#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <boost/algorithm/string.hpp>

#include "NetworkRfc.hpp"

/**
 * @brief Contains all the Babel's code.
 */
namespace Babel {
    /**
     * @brief Contains the library put in common.
     */
    namespace Common {
        /**
         * @brief Deprecated class used for text communication protocol.
         */
        class PacketsData {
        public:
            PacketsData(Babel::Rfc::Code CommandType = Babel::Rfc::Code::UNKNOWN ,
                const std::vector<std::string>& args
                = std::vector<std::string>()) : _CommandType(CommandType), _Arguments(args) {}
            ~PacketsData() {}
            const std::vector<std::string>& getArguments() const { return _Arguments; }
            void setArguments(const std::vector<std::string>& ArgumentstoSet) { PacketsData::_Arguments = ArgumentstoSet; }
            Babel::Rfc::Code getCommandType() const { return _CommandType; }
            size_t getNumberOfArguments() const { return _Arguments.size(); }
            void setCommandType(Babel::Rfc::Code CommandType) { _CommandType = CommandType; }
            const std::string serializeData() const
            {
                std::string serialization;
                std::string ArgumentSerialization = serializeArguments();
                serialization += std::to_string(_CommandType) + ARG_SEPARATOR +
                    ArgumentSerialization;
                return serialization;
            }
            static PacketsData deserializeData(std::string serializedData)
            {
                Babel::Common::PacketsData PacketsData;
                std::vector<std::string> ArgumentsDeserialized;

                boost::split(ArgumentsDeserialized, serializedData, boost::is_any_of(ARG_SEPARATOR));
                if (ArgumentsDeserialized.empty())
                    return PacketsData;
                try {
                    PacketsData.setCommandType(
                        (Babel::Rfc::Code) std::stoi(ArgumentsDeserialized[0]));
                }
                catch (std::invalid_argument&) {
                    return PacketsData;
                }
                ArgumentsDeserialized.erase(ArgumentsDeserialized.begin());
                PacketsData.setArguments(ArgumentsDeserialized);
                return PacketsData;
            }

        public:
            static constexpr const char * ARG_SEPARATOR = "\x1f";
            static constexpr const char * PACKET_SEPARATOR = "\r\n";

        private:
            const std::string serializeArguments() const
            {
                std::ostringstream vts;
                if (!_Arguments.empty()) {
                    std::copy(_Arguments.begin(), _Arguments.end() - 1,
                        std::ostream_iterator<std::string>(vts,
                            ARG_SEPARATOR));
                    vts << _Arguments.back();
                }
                return vts.str();
            }
            Babel::Rfc::Code _CommandType;
            std::vector<std::string> _Arguments;
        };
    }
}
