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
require_once __DIR__ . '/../includes/projects.inc';

foreach ($projects as $project_type => $project_type_data) {
  $download = array();
  $git = array();
  $patches = array();
  $list = ($project_type == 'modules') ? $projects[$project_type]['contrib'] : $projects[$project_type];

  foreach ($list as $project => $data) {
    // Get projects to download.
    $download[] = $project;

    // Get git projects to clone.
    if (isset($data['#git'])) {
      $key = array_search($project, $download);
      unset($download[$key]);
      $git[$project] = $data['#git'];
    }

    // Get projects to patch.
    if (isset($data['#patches'])) {
      $patches[$project] = $data['#patches'];
    }
  }

  // Download projects.
  foreach ($download as $project) {
    if (!file_exists($root . '/' . $project_type . '/' . $project)) {
      echo "Downloading $project\n";
      exec('b dl -y ' . $project);
    }
  }

  // Clone git projects.
  foreach ($git as $project => $repo) {
    if (!file_exists($root . '/' . $project_type . '/' . $project)) {
      echo "Cloning $project\n";
      exec('git clone ' . $repo);
    }
  }

  // Patch projects.
  foreach ($patches as $project => $patch_list) {
    $project_path = $root . '/' . $project_type . '/' . $project;

    if (file_exists($project_path)) {
      echo "Patching $project\n";

      foreach ($patch_list as $patch) {
        $filename = basename($patch);

        // Download the patch file.
        if (!file_exists($project_path . '/' . $filename)) {
          exec('cd ' . $project_path . ' && wget -q ' . $patch);
        }

        // Apply the patch.
        if (file_exists($project_path . '/.git')) {
          exec('cd ' . $project_path . ' && git apply ' . $filename);
        }
        else {
          exec('cd ' . $project_path . ' && patch -p1 < ' . $filename);
        }
      }
    }
  }
}

echo "\nSetup complete!\n";
