<?php
/**
 * @file
 * Theme configuration.
 */

/**
 * Enable default themes.
 */
function pw_profile_setup_themes() {
  $default_theme = 'basis';
  $admin_theme = 'seven';

  theme_enable(array(
    $default_theme,
    $admin_theme,
  ));
  theme_disable(array('stark'));

  $config = config('system.core');
  $config->set('theme_default', $default_theme);
  $config->set('admin_theme', $admin_theme);
  $config->set('node_admin_theme', TRUE);
  $config->save();
}

