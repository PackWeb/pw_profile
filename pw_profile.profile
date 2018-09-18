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

/**
 * Implements hook_tokens_alter().
 */
function pw_profile_tokens_alter(array &$replacements, array $context) {
  if ($context['type'] == 'node' && !empty($context['data']['node'])) {
    $node = $context['data']['node'];

    // Replace 'node:summary' token with 'field_body' value.
    if (isset($context['tokens']['summary']) && isset($node->field_body)) {
      $body = field_get_items('node', $node, 'field_body');

      if (!empty($body[0]['safe_summary'])) {
        $replacements[$context['tokens']['summary']] = $body[0]['safe_summary'];
      }
      elseif (!empty($body[0]['safe_value'])) {
        $replacements[$context['tokens']['summary']] = text_summary($body[0]['safe_value'], 'full_editor');
      }
    }

    // Replace 'node:body' token with 'field_body' value.
    if (isset($context['tokens']['body']) && isset($node->field_body)) {
      $body = field_get_items('node', $node, 'field_body');

      if (!empty($body[0]['safe_value'])) {
        $replacements[$context['tokens']['body']] = $body[0]['safe_value'];
      }
    }
  }
}

