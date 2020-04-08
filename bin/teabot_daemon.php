<?php

error_reporting(E_ALL);
set_time_limit(0);
ob_implicit_flush();

// declare(ticks=1);
// $sig = function () {
//     global $sock;
//     echo "Got SIGINT!\n";
//     (isset($sock) && $sock) and socket_close($sock);
//     posix_kill(getmypid(), SIGKILL);
//     exit;
// };
// pcntl_signal(SIGINT, $sig);
// pcntl_signal(SIGTERM, $sig);
// pcntl_signal(SIGHUP, $sig);
// pcntl_signal(SIGCHLD, $sig);

require __DIR__."/../config.php";

$address = "0.0.0.0";
$port = 10001;

$daemon = new TeaBot\Daemon(BOT_TOKEN);

if (($sock = socket_create(AF_INET, SOCK_STREAM, SOL_TCP)) === false) {
    echo "socket_create() failed: reason: ".socket_strerror(socket_last_error())."\n";
    exit(1);
}

if (socket_bind($sock, $address, $port) === false) {
    echo "socket_bind() failed: reason: ".socket_strerror(socket_last_error($sock))."\n";
    exit(1);
}

if (socket_listen($sock, 5) === false) {
    echo "socket_listen() failed: reason: ".socket_strerror(socket_last_error($sock))."\n";
    exit(1);
}

echo "Listening on {$address}:{$port}...\n";

do {
    if (($msgsock = socket_accept($sock)) === false) {
        echo "socket_accept() failed: reason: " . socket_strerror(socket_last_error($sock))."\n";
        break;
    }

    $buf = socket_read($msgsock, 7, PHP_NORMAL_READ);
    var_dump($buf);
    if (false === ($buf = socket_read($msgsock, (int)$buf, PHP_BINARY_READ))) {
        echo "socket_read() failed: reason: " . socket_strerror(socket_last_error($msgsock))."\n";
        break;
    }

    $daemon->passPayload($buf);
    socket_close($msgsock);
} while (true);

socket_close($sock);
