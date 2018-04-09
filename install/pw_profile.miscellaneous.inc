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

  // Since system.core is often used, access it now and then save it later.
  $system = config('system.core');

  // Contact form.
  $config = config('contact.categories');
  $categories = $config->get('categories');
  foreach ($categories as $key => $value) {
    if ($value['cid'] == 1) {
      $categories[$key]['category'] = $t('Website enquiry');
      $categories[$key]['recipients'] = 'info@packweb.eu';
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
  $system->set('file_transliterate_lowercase', 1);

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
  $system->set('image_jpeg_quality', '90');

  // Date and time formats.
  $config = config('system.date');
  $formats = $config->get('formats');
  $formats['long']['pattern'] = 'l, jS F Y - g:ia';
  $formats['medium']['pattern'] = 'D, d/m/Y - g:ia';
  $formats['short']['pattern'] = 'd/m/Y - g:ia';
  $config->set('formats', $formats);
  $config->save();

  // Cron.
  $system->set('cron_safe_threshold', '0');

  // URL aliases.
  $config = config('path.settings');
  $config->set('node_pattern', '[node:title]');
  $config->set('node_page_pattern', '[node:menu-link:parents:join-path]/[node:title]');
  $config->set('node_slideshow_image_pattern', 'slideshow/[node:title]');
  $config->set('transliterate', true);
  $config->set('reduce_ascii', true);
  $config->save();

  // URL redirects.
  config_set('redirect.settings', 'purge_inactive', '31536000');

  // URL settings.
  $system->set('canonical_secure', true);

  // Account settings.
  config_set('contact.settings', 'contact_default_status', false);
  $system->set('user_pictures', false);

  // Captcha.
  $config = config('captcha.settings');
  $config->set('default_challenge', 'recaptcha/reCAPTCHA');
  $forms = $config->get('captcha_points');
  $forms['user_register_form']['module'] = 'recaptcha';
  $forms['user_register_form']['captcha_type'] = 'reCAPTCHA';
  $forms['contact_site_form'] = array(
    'form_id' => 'contact_site_form',
    'module' => 'recaptcha',
    'captcha_type' => 'reCAPTCHA',
  );
  $config->set('captcha_points', $forms);
  $config->save();

  // External links.
  $config = config('extlink.settings');
  $config->set('class', false);
  $config->set('mailto_class', false);
  $config->set('subdomains', false);
  $config->set('target', '_blank');
  $config->save();

  // Simplify.
  $config = config('simplify.global');
  $config->set('nodes', array(
    'author',
    'format',
    'revision',
    'path',
    'redirect',
  ));
  $config->set('users', array(
    'format',
    'status',
    'contact',
    'redirect',
  ));
  $config->set('blocks', array(
    'format',
  ));
  $config->save();

  // On The Web settings.
  config_set('on_the_web.settings', 'type', 'font');

  // Save system.core.
  $system->save();
}

