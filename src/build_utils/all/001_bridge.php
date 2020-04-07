<?php

shchdir($makeDir."/src/bridge");

if (!file_exists($makeDir."/src/bridge/Makefile")) {
    mmlog("phpize...");
    sh("phpize");
    sh("./configure");
}

mmlog("make");
sh("make");
