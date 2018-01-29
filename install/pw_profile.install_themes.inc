<?php
/**
 * @file
 * Theme configuration.
 */

/**
 * Enable default themes.
 */
function pw_profile_enable_default_themes() {
  $config = config('system.core');
  $default_theme = 'basis';
  $admin_theme = 'seven';

  theme_enable(array(
    $default_theme,
    $admin_theme,
  ));
  theme_disable(array('stark'));
  $config->set('theme_default', $default_theme);
  $config->set('admin_theme', $admin_theme);
  $config->set('node_admin_theme', TRUE);
  $config->save();
}

/**
 * Configure theme settings.
 */
function pw_profile_configure_themes() {
  $theme_settings = variable_get('theme_settings', array());
  $theme_settings['toggle_node_user_picture'] = FALSE;
  $theme_settings['toggle_comment_user_picture'] = FALSE;
  $theme_settings['toggle_comment_user_verification'] = FALSE;
  $theme_settings['toggle_main_menu'] = FALSE;
  $theme_settings['toggle_secondary_menu'] = FALSE;
  variable_set('theme_settings', $theme_settings);
}

