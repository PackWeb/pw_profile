<?php
/**
 * @file
 * Miscellaneous configuration.
 */

/**
 * Configure miscellaneous settings.
 */
function pw_profile_configure_miscellaneous() {
  $t = get_t();
  ctools_include('export');

  // Views.
  variable_set('views_ui_show_advanced_help_warning', FALSE);
  variable_set('views_ui_show_advanced_column', TRUE);

  // Administration menu.
  variable_set('admin_menu_components', array(
    'admin_menu.icon' => TRUE,
    'admin_menu.menu' => TRUE,
    'admin_menu.search' => FALSE,
    'admin_menu.users' => FALSE,
    'admin_menu.account' => TRUE,
  ));

  // Locationmap.
  variable_set('locationmap_address', 'Coffs Harbour, NSW, Australia');
  variable_set('locationmap_zoom', '17');
  variable_set('locationmap_width', '900');
  variable_set('locationmap_height', '300');
  variable_set('locationmap_scroll', FALSE);

  // Error logging.
  variable_set('error_level', '0');

  // jQuery update.
  variable_set('jquery_update_jquery_version', '1.7');

  // FlexSlider.
  $optionset = flexslider_optionset_create(array(
    'name' => 'packweb',
    'title' => $t('PackWeb'),
    'options' => array(
      'animation' => 'slide',
      'animationSpeed' => 500,
      'smoothHeight' => TRUE,
      'slideshowSpeed' => 10000,
      'controlNav' => FALSE,
      'keyboard' => FALSE,
      'pauseOnHover' => TRUE,
    ),
  ));
  flexslider_optionset_save($optionset, TRUE);

  // Image styles.
  // Medium.
  $medium = image_style_load('medium');
  $medium['label'] = $t('Medium');
  $medium = image_style_save($medium);
  $medium_effect = array(
    'isid' => $medium['isid'],
    'name' => 'image_scale',
    'data' => array(
      'width' => '250',
      'height' => '250',
      'upscale' => TRUE,
    ),
  );
  image_effect_save($medium_effect);
  // Large.
  $large = image_style_load('large');
  $large['label'] = $t('Large');
  $large = image_style_save($large);
  $large_effect = array(
    'isid' => $large['isid'],
    'name' => 'image_scale',
    'data' => array(
      'width' => '600',
      'height' => '600',
      'upscale' => FALSE,
    ),
  );
  image_effect_save($large_effect);
  // Slideshow.
  $slideshow = array(
    'name' => 'slideshow',
    'label' => $t('Slideshow'),
  );
  $slideshow = image_style_save($slideshow);
  $slideshow_effect = array(
    'isid' => $slideshow['isid'],
    'name' => 'manualcrop_crop_and_scale',
    'data' => array(
      'width' => '1200',
      'height' => '300',
      'upscale' => TRUE,
      'respectminimum' => TRUE,
      'onlyscaleifcrop' => FALSE,
    ),
  );
  image_effect_save($slideshow_effect);

  // Image toolkit.
  variable_set('image_jpeg_quality', '90');

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

