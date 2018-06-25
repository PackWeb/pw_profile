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
  $form['admin_account']['account']['mail']['#default_value'] = 'info@packweb.eu';
}

/**
 * Implements hook_install_tasks().
 */
function pw_profile_install_tasks(&$install_state) {
  // Add custom task to run at end of installation.
  return array(
    'pw_profile_final_setup' => array(),
  );
}

/**
 * Miscellaneous configuration that needs to run after everything else.
 */
function pw_profile_final_setup(&$install_state) {
  // Set User 1's timezone.
  $user = user_load(1);
  $user->timezone = 'Europe/Tallinn';
  $user->save();
}

/**
 * Implements hook_form_FORM_ID_alter() for node_type_form.
 */
function pw_profile_form_node_type_form_alter(&$form, &$form_state, $form_id) {
  // Disable creation of the default Body field.
  $form['body']['#value'] = FALSE;
}

