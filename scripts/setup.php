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

// Get list of layouts.
$layouts['dl'] = array_keys($projects['layouts']);
foreach ($projects['layouts'] as $layout => $data) {
  if (isset($data['#git'])) {
    // Remove from download list.
    $key = array_search($layout, $layouts['dl']);
    unset($layouts['dl'][$key]);

    // Add to git list.
    $layouts['git'][$layout] = $data['#git'];
  }
}
// Download layouts.
foreach ($layouts['dl'] as $layout) {
  if (!file_exists($root . '/layouts/' . $layout)) {
    echo "Downloading $layout\n";
    exec('b dl -y ' . $layout);
  }
}
foreach ($layouts['git'] as $layout => $repo) {
  if (!file_exists($root . '/layouts/' . $layout)) {
    echo "Cloning $layout\n";
    exec('git clone ' . $repo);
  }
}

// Get list of themes.
$themes['dl'] = array_keys($projects['themes']);
foreach ($projects['themes'] as $theme => $data) {
  if (isset($data['#git'])) {
    // Remove from download list.
    $key = array_search($theme, $themes['dl']);
    unset($themes['dl'][$key]);

    // Add to git list.
    $themes['git'][$theme] = $data['#git'];
  }
}
// Download themes.
foreach ($themes['dl'] as $theme) {
  if (!file_exists($root . '/themes/' . $theme)) {
    echo "Downloading $theme\n";
    exec('b dl -y ' . $theme);
  }
}
foreach ($themes['git'] as $theme => $repo) {
  if (!file_exists($root . '/themes/' . $theme)) {
    echo "Cloning $theme\n";
    exec('git clone ' . $repo);
  }
}

echo "\nSetup complete!\n";
