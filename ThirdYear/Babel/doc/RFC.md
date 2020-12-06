# Babel's RFC

## Arguments

| Argument                  | Description                                |
| ------------------------- | ------------------------------------------ |
| CommandID                 | Command ID.                                |
| UserID                    | User ID.                                   |
| Username                  | Username.                                  |
| Password                  | Password.                                  |
| State                     | State (Connected / Diconnected / Calling). |
| IP                        | IP adress.                                 |
| Port                      | Port.                                      |
| Message                   | Message.                                   |
| AudioData                 | AudioData structure.                       |

## Server -> Client Requests

| Request name              | Arguments                 | Description                                                |
| ------------------------- | ------------------------- | ---------------------------------------------------------- |
| UNKNOWN                   | ()                        | Response if the command previously sent is not recognized. |
| SC_OK                     | (CommandID)               | Response if the command previously sent is okay.           |
| SC_ERROR                  | (CommandID, message)      | Response if the command previously sent has an error.      |
| SC_DELETE                 | (UserID)                  | User has been deleted.                                     |
| SC_USER                   | (UserID, Username, State) | Sends user informations.                                   |
| SC_CALL                   | (UserID, IP, Port)        | Asks for a call to the user.                               |
| SC_CALL_ANSWER            | (UserID, IP, Port)        | Anwsers the call from the user.                            |
| SC_CALL_END               | (UserID)                  | Ends the call with the user.                               |
| SC_CONTACT                | (UserID, Username, State) | Adds the user to the contacts list.                        |
| SC_MSG                    | (UserID, Message)         | Sends message to user.                                     |
| SC_PING                   | ()                        | Pings the client. (Response with CS_OK(SC_PING))           |

## Client -> Server Requests

| Request name              | Arguments            | Description                                                               |
| ------------------------- | -------------------- | ------------------------------------------------------------------------- |
| UNKNOWN                   | ()                   | Response if the command previously sent is not recognized.                |
| CS_OK                     | (CommandID)          | Response if the command previously sent is okay.                          |
| CS_ERROR                  | (CommandID, message) | Response if the command previously sent has an error.                     |
| CS_LOGIN                  | (Username, Password) | Sends login try with username.                                            |
| CS_LOGOUT                 | ()                   | Sends logout from the server.                                             |
| CS_CALL                   | (UserID, IP, Port)   | Asks for a call to the user.                                              |
| CS_CALL_ANSWER            | (UserID, IP, Port)   | Anwsers the call from the user.                                           |
| CS_CALL_END               | (UserID)             | Ends the call with the user.                                              |
| CS_CONTACT                | (Username)           | Adds the user to the contacts list.                                       |
| CS_MSG                    | (UserID, Message)    | Sends message to user.                                                    |
| CS_PING                   | ()                   | Pings the server. (Response with SC_OK(CS_PING))                          |