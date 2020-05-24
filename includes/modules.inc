<?php
/**
 * @file
 * Install modules.
 */

/**
 * Install modules.
 */
function pw_profile_install_modules($projects) {
  // Get core modules.
  $modules = $projects['modules']['core'];

  // Get contrib modules.
  $modules = array_merge($modules, array_keys($projects['modules']['contrib']));
  foreach ($projects['modules']['contrib'] as $module => $data) {
    foreach (_pw_profile_get_children($data) as $child) {
      $modules[] = $child;
    }
  }

  // Enable modules.
  module_enable(array_unique($modules));
}
