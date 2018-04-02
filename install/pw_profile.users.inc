<?php
/**
 * @file
 * Users, roles & permissions configuration.
 */

/**
 * Setup admin role.
 */
function pw_profile_setup_admin_role() {
  $t = get_t();

  // Create admin role.
  $admin_role = new stdClass();
  $admin_role->name = 'administrator';
  $admin_role->label = $t('Administrator');
  user_role_save($admin_role);
  config_set('system.core', 'user_admin_role', '0');

  // Add user 1 to admin role.
  db_insert('users_roles')
    ->fields(array(
      'uid' => 1,
      'role' => $admin_role->name,
    ))
    ->execute();
}

/**
 * Configure permissions.
 */
function pw_profile_configure_permissions() {
  // Start with a clean slate.
  db_delete('role_permission')->execute();

  // Anonymous.
  $anonymous = array(
    'access site-wide contact form',
    'use text format basic_editor',
    'access content',
  );
  pw_profile_grant_permissions('anonymous user', $anonymous);

  // Authenticated.
  $authenticated = array_merge($anonymous, array());
  pw_profile_grant_permissions('authenticated user', $authenticated);

  // Administrator.
  $administrator = array_merge($authenticated, array(
    'access administration menu',
    'access the block administration page',
    'view all blocks',
    'skip CAPTCHA',
    'administer contact forms',
    'access contextual links',
    'use text format full_editor',
    'administer locationmap',
    'use manualcrop',
    'administer main-menu menu items',
    'administer nodes',
    'access content overview',
    'view own unpublished content',
    'create page content',
    'edit own page content',
    'edit any page content',
    'delete own page content',
    'delete any page content',
    'create slideshow_image content',
    'edit own slideshow_image content',
    'edit any slideshow_image content',
    'delete own slideshow_image content',
    'delete any slideshow_image content',
    'access administration pages',
    'view the administration theme',
    'change own username',
  ));
  pw_profile_grant_permissions('administrator', $administrator);
}


/*** ---------------------------------------------------------------------- ***/


/**
 * Grant permissions to a user role.
 *
 * @param $role
 *   The name of the user role to assign permissions to.
 * @param $permissions
 *   An array of machine-readable permissions to assign to the user role.
 */
function pw_profile_grant_permissions($role, $permissions) {
  // Load role.
  $user_role = user_role_load_by_name($role);

  // Grant permissions.
  user_role_grant_permissions($user_role->rid, $permissions);
}

