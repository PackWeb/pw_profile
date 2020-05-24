#!/usr/bin/env php
<?php
/**
 * @file
 * PHP script to setup a Backdrop installation with the necessary modules,
 * themes, etc. ready to run the PackWeb install profile.
 *
 * Requires Backdrop Console (`b`) to be installed on the server:
 * https://github.com/backdrop-contrib/b
 */

$root = __DIR__ . '/../../..';

// Get the list of projects.
require_once __DIR__ . '/../includes/projects.inc';

// Get list of contrib modules.
$modules['dl'] = array_keys($projects['modules']['contrib']);
foreach ($projects['modules']['contrib'] as $module => $data) {
  if (isset($data['#git'])) {
    // Remove from download list.
    $key = array_search($module, $modules['dl']);
    unset($modules['dl'][$key]);

    // Add to git list.
    $modules['git'][$module] = $data['#git'];
  }
}

// Download modules.
foreach ($modules['dl'] as $module) {
  if (!file_exists($root . '/modules/' . $module)) {
    echo "Downloading $module\n";
    exec('b dl -y ' . $module);
  }
}
foreach ($modules['git'] as $module => $repo) {
  if (!file_exists($root . '/modules/' . $module)) {
    echo "Cloning $module\n";
    exec('git clone ' . $repo);
  }
}

echo "\nSetup complete!\n";
