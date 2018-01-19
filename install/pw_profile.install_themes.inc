<?php
/**
 * @file
 * Theme configuration.
 */

/**
 * Enable default themes.
 */
function pw_profile_enable_default_themes() {
  // Enable themes.
  theme_enable(array(
    'adminimal',
  ));

  // Set admin theme.
  variable_set('admin_theme', 'adminimal');
  variable_set('node_admin_theme', TRUE);
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

