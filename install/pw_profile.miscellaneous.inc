<?php
/**
 * @file
 * Miscellaneous configuration.
 */

/**
 * Configure miscellaneous settings.
 */
function pw_profile_setup_miscellaneous() {
  $t = get_t();

  // Contact form.
  $config = config('contact.categories');
  $categories = $config->get('categories');
  foreach ($categories as $key => $value) {
    if ($value['cid'] == 1) {
      $categories[$key]['category'] = $t('Website enquiry');
      $categories[$key]['recipients'] = 'info@packweb.com.au';
    }
  }
  $config->set('categories', $categories);
  $config->save();

  // Administration bar.
  $config = config('admin_bar.settings');
  $components = $config->get('components');
  $config->set('position_fixed', 1);
  $config->set('components', array(
    'admin_bar.icon',
    'admin_bar.menu',
    'admin_bar.account',
  ));
  $config->save();

  // Pathologic.
  config_set('pathologic.settings', 'protocol_style', 'proto-rel');

  // File system.
  config_set('system.core', 'file_transliterate_lowercase', 1);

  // Image styles.
  image_style_save(array(
    'name' => 'slideshow',
    'label' => $t('Slideshow'),
    'effects' => array(
      array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '2000',
          'height' => '400',
        ),
      ),
    ),
  ));

  // Image toolkit.
  /*variable_set('image_jpeg_quality', '90');

  // Account settings.
  variable_set('contact_default_status', FALSE);
  variable_set('user_register', USER_REGISTER_ADMINISTRATORS_ONLY);
  variable_set('user_mail_register_admin_created_body', "[user:name],\n\nA site administrator at [site:name] has created an account for you. You may now log in by clicking this link or copying and pasting it to your browser:\n\n[user:one-time-login-url]/brief\n\nThis link can only be used once to log in and will lead you to a page where you can set your password.\n\nAfter setting your password, you will be able to log in at [site:login-url] in the future using:\n\nusername: [user:name]\npassword: Your password\n\n--  [site:name] team");
  variable_set('user_mail_register_no_approval_required_body', "[user:name],\n\nThank you for registering at [site:name]. You may now log in by clicking this link or copying and pasting it to your browser:\n\n[user:one-time-login-url]/brief\n\nThis link can only be used once to log in and will lead you to a page where you can set your password.\n\nAfter setting your password, you will be able to log in at [site:login-url] in the future using:\n\nusername: [user:name]\npassword: Your password\n\n--  [site:name] team");
  variable_set('user_mail_status_activated_body', "[user:name],\n\nYour account at [site:name] has been activated.\n\nYou may now log in by clicking this link or copying and pasting it into your browser:\n\n[user:one-time-login-url]/brief\n\nThis link can only be used once to log in and will lead you to a page where you can set your password.\n\nAfter setting your password, you will be able to log in at [site:login-url] in the future using:\n\nusername: [user:name]\npassword: Your password\n\n--  [site:name] team");
  variable_set('user_mail_password_reset_body', "[user:name],\n\nA request to reset the password for your account has been made at [site:name].\n\nYou may now log in by clicking this link or copying and pasting it to your browser:\n\n[user:one-time-login-url]/brief\n\nThis link can only be used once to log in and will lead you to a page where you can set your password. It expires after one day and nothing will happen if it's not used.\n\n--  [site:name] team");

  // Captcha.
  module_load_include('inc', 'captcha');
  variable_set('captcha_default_challenge', 'recaptcha/reCAPTCHA');
  captcha_set_form_id_setting('user_login', 'none');
  captcha_set_form_id_setting('user_login_block', 'none');

  // Regional settings.
  variable_set('configurable_timezones', FALSE);

  // Date & time.
  variable_set('date_format_long', 'l, j F Y - g:ia');
  variable_set('date_format_medium', 'D, d/m/Y - g:ia');
  variable_set('date_format_short', 'd/m/Y - g:ia');

  // Pathauto.
  variable_set('pathauto_node_pattern', '[node:title]');
  variable_set('pathauto_node_page_pattern', '[node:menu-link:parents:join-path]/[node:title]');
  variable_set('pathauto_node_slideshow_image_pattern', 'slideshow/[node:title]');
  variable_set('pathauto_transliterate', TRUE);
  variable_set('pathauto_reduce_ascii', TRUE);

  // Redirect.
  variable_set('redirect_purge_inactive', '31536000');

  // Site information.
  variable_set('site_403', 'toboggan/denied');

  // Logintoboggan.
  variable_set('logintoboggan_login_with_email', '1');
  variable_set('logintoboggan_confirm_email_at_registration', '1');
  variable_set('logintoboggan_minimum_password_length', '15');

  // Cron.
  variable_set('cron_safe_threshold', '0');

  // External links.
  variable_set('extlink_class', FALSE);
  variable_set('extlink_mailto_class', FALSE);
  variable_set('extlink_subdomains', FALSE);
  variable_set('extlink_target', '_blank');

  // Module filter.
  variable_set('module_filter_use_switch', FALSE);
  variable_set('module_filter_track_recent_modules', FALSE);

  // Simplify.
  pw_profile_configure_simplify('nodes_global', array(
    'author',
    'format',
    'revision',
    'path',
    'redirect',
  ));
  pw_profile_configure_simplify('users_global', array(
    'contact',
    'format',
    'redirect',
  ));
  pw_profile_configure_simplify('taxonomy_global', array(
    'format',
    'relations',
    'path',
    'redirect',
  ));
  pw_profile_configure_simplify('blocks_global', array(
    'format',
  ));

  // Superfish.
  variable_set('superfish_number', '1');

  // Update settings.
  variable_set('update_notify_emails', array('info@packweb.com.au'));
  variable_set('update_notification_threshold', 'security');
  */
}


/*** ---------------------------------------------------------------------- ***/


/**
 * Configure Simplify.
 *
 * @param $type
 *   The field type being configured (e.g., 'nodes_global', 'nodes_page').
 * @param $new_fields
 *   An array of fields to hide (e.g., 'format').
 */
function pw_profile_configure_simplify($type, $new_fields) {
  // Get current fields.
  $fields = variable_get('simplify_' . $type, array());

  // Add new fields.
  foreach ($new_fields as $field) {
    if (!in_array($field, $fields)) {
      $fields[] = $field;
    }
  }

  // Save fields.
  variable_set('simplify_' . $type, $fields);
}

