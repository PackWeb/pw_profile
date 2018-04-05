<?php
/**
 * @file
 * Users & permissions configuration.
 */

/**
 * Configure users.
 */
function pw_profile_setup_users() {
  $t = get_t();

  // Create admin role.
  $role = (object) array(
    'name' => 'administrator',
    'label' => $t('Administrator'),
  );
  user_role_save($role);
  config_set('system.core', 'user_admin_role', '0');

  // Configure User 1.
  $user = user_load(1);
  $user->roles[] = $role->name;
  $user->data['contact'] = 0;
  $user->save();
}

/**
 * Configure permissions.
 */
function pw_profile_setup_permissions() {
  // Anonymous.
  $anonymous = config('user.role.anonymous');
  $permissions = array(
    'access site-wide contact form',
    'use text format basic_editor',
    'access content',
  );
  $anonymous->set('permissions', $permissions);
  $anonymous->save();

  // Authenticated.
  $authenticated = config('user.role.authenticated');
  $permissions = array_merge($permissions, array(
    'skip CAPTCHA',
    'change own username',
  ));
  $authenticated->set('permissions', $permissions);
  $authenticated->save();

  // Administrator.
  $administrator = config('user.role.administrator');
  $permissions = array_merge($permissions, array(
    'access administration bar',
    'administer contact forms',
    'access contextual links',
    'access file overview',
    'manage files',
    'delete files',
    'upload editor images',
    'use text format full_editor',
    'administer main-menu menu items',
    'administer nodes',
    'access content overview',
    'view own unpublished content',
    'view any unpublished content',
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
    'save draft',
    'access administration pages',
    'view the administration theme',
  ));
  $administrator->set('permissions', $permissions);
  $administrator->save();

  // Clear the user access cache.
  // @see user_role_save()
  backdrop_static_reset('user_roles');
  backdrop_static_reset('user_access');
}

