# R-Type RFC

## UDP Binary Structure

| Argument                  | Description                                |
| ------------------------- | ------------------------------------------ |
| CommandID                 | Command ID.                                |
| RoomID                    | Room ID.                                   |
| Username                  | Username.                                  |
| Port                      | Port.                                      |
| Datas                     | Datas                                      |
| EntityID                  | Entity ID.                                 |
| InputCode                 | Input code.                                |

## TCP Binary Structure

| Argument                  | Description                                |
| ------------------------- | ------------------------------------------ |
| CommandID                 | Command ID.                                |
| UserID                    | User ID.                                   |

| Argument                  | Description                                |
| ------------------------- | ------------------------------------------ |
| CommandID                 | Command ID.                                |
| UserID                    | User ID.                                   |

## TCP Request Codes

| Request name              | Arguments                 | Description                                                     |
| ------------------------- | ------------------------- | --------------------------------------------------------------- |
| Unknown                   | ()                        | Response if the command previously sent is not recognized.      |
| Ok                        | (CommandID)               | Response if the command previously sent is okay.                |
| Error                     | (CommandID, message)      | Response if the command previously sent has an error.           |
| Login                     | (RoomID)                  | Connects user into a room, entitling a username to him.         |
| LoginAnswer               | (RoomID, port)            | Received by the client in order for him to connect to the room. |
| Logout                    | (RoomID)                  | Disconnects from the server.                                    |

## UDP Request Codes

| Request name              | Arguments                        | Description                                                               |
| ------------------------- | -------------------------------- | ------------------------------------------------------------------------- |
| Input                     | (KeyCode)                        | Sends an input.                                                           |
| InputXY                   | (KeyCode, KeyXValue, KeyYValue)  | Sends an input with x and y values.                                       |
| Create                    | (ObjectID, Object)               | Creates an object and assigns it ObjectID.                                |
| Update                    | (ObjectID, Object)               | Updates the object.                                                       |
| Delete                    | (ObjectID)                       | Deletes the object.                                                       |
| Logout                    | ()                               | Disconect from the room.                                                  |