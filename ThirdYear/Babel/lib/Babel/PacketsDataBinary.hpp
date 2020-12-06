#pragma once

#include "PacketsData.hpp"
#include "Exception.hpp"

namespace Babel
{
    namespace Common
    {
        const size_t maxStringSize = 100;
        const size_t maxArguments = 3;
        /**
         * @brief Contains every needed data for de/serialization.
         */
        struct PacketsDataBinarySerialized
        {
            int size;
            int commandId;
            int intArraySize;
            int argumentsSize[maxArguments];
            char arguments[maxArguments][maxStringSize];
        };
        /**
         * @brief Contains command and parameters of the babel commands.
         * This class is meant to be used for binary communication between the server and the clients.
         */
        class PacketsDataBinary {
        public:
            /**
             * @brief Constructor.
             * @param Babel::Rfc::Code CommandType, command code.
             * @param const std::vector<std::string> & args, contains arguments.
             */
            PacketsDataBinary(Babel::Rfc::Code CommandType = Babel::Rfc::Code::UNKNOWN,
                const std::vector<std::string> & args
                = std::vector<std::string>()) : _commandType(CommandType), _arguments(args) {}
            ~PacketsDataBinary() {}
            /**
             * @brief Returns arguments.
             * @return const std::vector<std::string> &
             */
            const std::vector<std::string>& getArguments() const { return _arguments; }
            /**
             * @brief Sets the arguments.
             * @param const std::vector<std::string> &
             */
            void setArguments(const std::vector<std::string>& ArgumentstoSet) { _arguments = ArgumentstoSet; }
            /**
             * @brief Returns the command code.
             * @return Babel::Rfc::Code
             */
            Babel::Rfc::Code getCommandType() const { return _commandType; }
            /**
             * @brief getNumberOfArguments
             * @return
             */
            size_t getNumberOfArguments() const { return _arguments.size(); }
            /**
             * @brief Sets command code.
             * @param Babel::Rfc::Code CommandType
             */
            void setCommandType(Babel::Rfc::Code CommandType) { _commandType = CommandType; }
            /**
             * @brief Returns the data size in bytes.
             * @return size_t
             */
            size_t getBytesSize() const { return _bytesSize; }
            /**
             * @brief Sets the data size in bytes.
             * @param size_t
             */
            void setBytesSize(size_t size) { _bytesSize = size; }

            /**
             * @brief Returns a serialized version of PacketsDataBinary, it's meant to be sent by a socket.
             * @return PacketsDataBinarySerialized
             */
            const PacketsDataBinarySerialized serializeData()
            {
                PacketsDataBinarySerialized structure;

                structure.size = 0;
                structure.size += sizeof(int);

                structure.commandId = (int)_commandType;
                structure.size += sizeof(int);

                structure.intArraySize = (int)_arguments.size();
                structure.size += sizeof(int);

                structure.size += sizeof(int) * maxArguments;

                structure.size += (sizeof(char) * maxStringSize) * 3;

                for (int i = 0; i < structure.intArraySize; ++i)
                {
                    structure.argumentsSize[i] = (int)_arguments[i].size();
                    if (structure.argumentsSize[i] > 100)
                        structure.argumentsSize[i] = 100;
                    for (int j = 0; j < structure.argumentsSize[i] && j < maxStringSize; ++j)
                    {
                        structure.arguments[i][j] = _arguments[i][j];
                    }
                    structure.arguments[i][structure.argumentsSize[i]] = 0;
                }
                _bytesSize = structure.size;
                return structure;
            }

            static const size_t PacketsDataBinarySerializedMinimumSize = sizeof(int) + sizeof(int) + sizeof(int) + sizeof(int) * maxArguments + sizeof(char) * maxArguments * maxStringSize;
            /**
             * @brief Returns a deserialized version of 'data'.
             * @param void * data
             * @param size_t readData (bytes of read data)
             * @return PacketsDataBinary
             */
            static PacketsDataBinary deserializeData(void * data, size_t readData)
            {
                if (readData < PacketsDataBinarySerializedMinimumSize)
                    throw EXCEPTION("Packet not complete.");

                PacketsDataBinarySerialized * dataSerialized = new PacketsDataBinarySerialized;

                memcpy(dataSerialized, data, readData);

                if (dataSerialized->size < readData)
                    throw EXCEPTION("Packet not complete.");

                PacketsDataBinary packet;
                packet.setBytesSize(readData);

                packet.setCommandType((Babel::Rfc::Code)dataSerialized->commandId);

                std::vector<std::string> strings;
                for (int i = 0; i < dataSerialized->intArraySize; ++i)
                {
                    strings.push_back(dataSerialized->arguments[i]);
                }

                packet.setArguments(strings);
                packet.setBytesSize(dataSerialized->size);
                

                return packet;
            }
        private:
            Babel::Rfc::Code _commandType;
            std::vector<std::string> _arguments;
            size_t _bytesSize;
        };
    }
}
