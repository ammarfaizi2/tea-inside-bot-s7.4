<?php
$json = '{
  "message": {
    "chat": {
      "id": -1001226735471,
      "title": "Private Cloud",
      "type": "supergroup",
      "username": null
    },
    "date": 1586278376,
    "entities": [
      {
        "length": 6,
        "offset": 0,
        "type": "bot_command"
      }
    ],
    "from": {
      "first_name": "Ammar",
      "id": 243692601,
      "is_bot": false,
      "language_code": "en",
      "last_name": "Faizi",
      "username": "ammarfaizi2"
    },
    "message_id": 103,
    "reply_to_message": null,
    "text": "dqc"
  },
  "update_id": 345747644
}';
$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
socket_connect($socket, "127.0.0.1", 10001);
socket_send($socket, sprintf("%07d", $len = strlen($json)), 7, 0);
socket_send($socket, $json, $len, 0);
socket_close($socket);
