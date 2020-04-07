<?php

$st = new TeaBot\Daemon("test abc");
$st->passPayload('{
    "update_id": 345747644,
    "message": {
        "message_id": 103,
        "from": {
            "id": 243692601,
            "is_bot": false,
            "first_name": "Ammar",
            "last_name": "Faizi",
            "username": "ammarfaizi2",
            "language_code": "en"
        },
        "chat": {
            "id": -1001226735471,
            "title": "Private Cloud",
            "type": "supergroup",
            "username": null
        },
        "date": 1586278376,
        "text": "/debug",
        "entities": [
            {
                "offset": 0,
                "length": 6,
                "type": "bot_command"
            }
        ],
        "reply_to_message": null
    }
}');
