<?php

require __DIR__."/src/build_utils/helpers.php";

$makeDir = __DIR__;

$scan = scandir(__DIR__."/src/build_utils/all");
unset($scan[0], $scan[1]);
foreach ($scan as $k => $v) {
    require __DIR__."/src/build_utils/all/".$v;
}
