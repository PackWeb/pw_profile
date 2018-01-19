<?php
/**
 * @file
 * Configure Backdrop for a new PackWeb site.
 */

/**
 * Implements hook_form_FORM_ID_alter() for install_configure_form.
 */
function pw_profile_form_install_configure_form_alter(&$form, &$form_state, $form_id) {
  // Set default values for the admin account.
  $form['admin_account']['account']['name']['#default_value'] = 'PackWeb';
  $form['admin_account']['account']['mail']['#default_value'] = 'info@packweb.com.au';

  // Set default values for server settings.
  $form['server_settings']['date_default_timezone']['#default_value'] = 'Australia/Sydney';
  $form['server_settings']['date_default_timezone']['#attributes']['class'] = array();
}

