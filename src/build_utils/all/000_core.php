<?php

$cdir = $makeDir."/src/core";
shchdir($cdir);

$frag = file_get_contents($cdir."/Makefile.frag");
$frag = str_replace(
    ["~~BASEDIR~~"],
    [realpath($cdir)],
    $frag
);
file_put_contents($cdir."/Makefile", $frag);
sh("make");
