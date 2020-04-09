<?php
$json = file_get_contents("php://input");
$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
socket_connect($socket, "127.0.0.1", 10002);
socket_send($socket, sprintf("%07d", $len = strlen($json)), 7, 0);
socket_send($socket, $json, $len, 0);
socket_close($socket);
