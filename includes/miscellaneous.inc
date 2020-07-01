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

  // Since system.core is used often, access it now and then save it later.
  $system = config('system.core');

  // Appearance.
  $default_theme = 'basis';
  $admin_theme = 'seven';
  theme_enable(array(
    $default_theme,
    $admin_theme,
  ));
  theme_disable(array('stark'));
  $system->set('theme_default', $default_theme);
  $system->set('admin_theme', $admin_theme);
  $system->set('node_admin_theme', TRUE);

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

  // Menus.
  $links = array(
    array(
      'link_title' => $t('Home'),
      'link_path' => '<front>',
      'weight' => -50,
    ),
    array(
      'link_title' => $t('Contact'),
      'link_path' => 'contact',
      'weight' => 50,
    ),
  );
  foreach ($links as $link) {
    menu_link_save($link);
  }
  menu_cache_clear_all();

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

  // File system.
  $system->set('file_transliterate_lowercase', 1);

  // Image styles.
  image_style_save(array(
    'name' => 'slideshow_1500w',
    'label' => $t('Slideshow 1500w'),
    'effects' => array(
      array(
        'name' => 'manualcrop_reuse',
        'data' => array(
          'reuse_crop_style' => 'slideshow',
          'apply_all_effects' => FALSE,
        ),
        'weight' => 0,
      ),
      array(
        'name' => 'image_scale',
        'data' => array(
          'width' => '1500',
          'height' => '',
          'upscale' => FALSE,
        ),
        'weight' => 0,
      ),
    ),
  ));
  image_style_save(array(
    'name' => 'slideshow_1000w',
    'label' => $t('Slideshow 1000w'),
    'effects' => array(
      array(
        'name' => 'manualcrop_reuse',
        'data' => array(
          'reuse_crop_style' => 'slideshow',
          'apply_all_effects' => FALSE,
        ),
        'weight' => 0,
      ),
      array(
        'name' => 'image_scale',
        'data' => array(
          'width' => '1000',
          'height' => '',
          'upscale' => FALSE,
        ),
        'weight' => 0,
      ),
    ),
  ));
  image_style_save(array(
    'name' => 'slideshow_500w',
    'label' => $t('Slideshow 500w'),
    'effects' => array(
      array(
        'name' => 'manualcrop_reuse',
        'data' => array(
          'reuse_crop_style' => 'slideshow',
          'apply_all_effects' => FALSE,
        ),
        'weight' => 0,
      ),
      array(
        'name' => 'image_scale',
        'data' => array(
          'width' => '500',
          'height' => '',
          'upscale' => FALSE,
        ),
        'weight' => 0,
      ),
    ),
  ));
  image_style_save(array(
    'name' => 'slideshow',
    'label' => $t('Slideshow'),
    'effects' => array(
      array(
        'name' => 'manualcrop_crop_and_scale',
        'data' => array(
          'width' => '2000',
          'height' => '400',
          'upscale' => TRUE,
          'respectminimum' => TRUE,
          'onlyscaleifcrop' => FALSE,
          'style_name' => 'slideshow',
        ),
        'weight' => 0,
      ),
    ),
  ));

  // srcset image.
  $config = config('srcset_image.sets');
  $slideshow_set = array(
    'name' => $t('Slideshow'),
    'machine_name' => 'slideshow',
    'image_styles' => array(
      'slideshow',
      'slideshow_1500w',
      'slideshow_1000w',
      'slideshow_500w',
    ),
  );
  $config->set('slideshow', $slideshow_set);
  $config->save();

  // Image toolkit.
  $system->set('image_jpeg_quality', '90');

  // Metatag.
  $config = config('metatag.settings');
  $config->set('metatag_enable_node__post', FALSE);
  $config->set('metatag_enable_taxonomy_term', FALSE);
  $config->set('metatag_enable_user', FALSE);
  $config->save();
  $config = config('metatag.instance.global');
  $config->set('storage', 'overridden');
  $config->clear('config.generator');
  $config->set('config.content-language.value', 'en');
  $config->set('config.og:site_name.value', '[site:name]');
  $config->set('config.og:type.value', 'article');
  $config->set('config.og:url.value', '[current-page:url:absolute]');
  $config->set('config.og:title.value', '[current-page:title]');
  $config->save();
  $config = config('metatag.instance.global.frontpage');
  $config->set('storage', 'overridden');
  $config->clear('config.canonical');
  $config->clear('config.shortlink');
  $config->set('config.title.value', '[site:name] | [current-page:pager][site:slogan]');
  $config->set('config.description.value', '[site:slogan]');
  $config->set('config.og:type.value', 'website');
  $config->set('config.og:title.value', '[site:name]');
  $config->save();
  $config = config('metatag.instance.node');
  $config->set('storage', 'overridden');
  $config->clear('config.title');
  $config->clear('config.canonical');
  $config->set('config.description.value', '[node:summary]');
  $config->set('config.og:type.value', 'article');
  $config->set('config.og:title.value', '[node:title]');
  $config->save();
  config_set('metatag.instance.taxonomy_term', 'disabled', TRUE);
  config_set('metatag.instance.user', 'disabled', TRUE);

  // Date and time formats.
  $config = config('system.date');
  $formats = $config->get('formats');
  $formats['long']['pattern'] = 'l, jS F Y - g:ia';
  $formats['medium']['pattern'] = 'D, d/m/Y - g:ia';
  $formats['short']['pattern'] = 'd/m/Y - g:ia';
  $config->set('formats', $formats);
  $config->save();

  // XML sitemap.
  $config = config('xmlsitemap.settings');
  $config->set('engines', array(
    'bing' => 'bing',
    'google' => 'google',
  ));
  $config->set('engines_minimum_lifetime', '86400');
  $config->set('engines_submit_updated', TRUE);
  $config->set('minimum_lifetime', '86400');
  $config->set('settings_menu_link_main-menu', array(
    'status' => '1',
    'priority' => '0.5',
  ));
  $config->set('settings_node_page', array(
    'status' => '1',
    'priority' => '0.5',
  ));
  $config->save();

  // Global redirect.
  config_set('globalredirect.settings', 'globalredirect_settings.menu_check', TRUE);

  // Cron.
  $system->set('cron_safe_threshold', '0');

  // URL aliases.
  $config = config('path.settings');
  $config->set('node_pattern', '[node:title]');
  $config->set('node_page_pattern', '[node:menu-link:parents:join-path]/[node:title]');
  $config->set('node_slideshow_image_pattern', 'slideshow/[node:title]');
  $config->set('transliterate', TRUE);
  $config->set('reduce_ascii', TRUE);
  $config->save();

  // URL redirects.
  config_set('redirect.settings', 'purge_inactive', '31536000');

  // URL settings.
  $system->set('canonical_secure', TRUE);

  // Account settings.
  config_set('contact.settings', 'contact_default_status', FALSE);
  $system->set('user_pictures', FALSE);

  // External links.
  $config = config('extlink.settings');
  $config->set('class', FALSE);
  $config->set('mailto_class', FALSE);
  $config->set('subdomains', FALSE);
  $config->set('target', '_blank');
  $config->save();

  // Simplify.
  $config = config('simplify.global');
  $config->set('nodes', backdrop_map_assoc(array(
    'author',
    'format',
    'revision',
    'path',
    'redirect',
    'xmlsitemap',
  )));
  $config->set('users', backdrop_map_assoc(array(
    'format',
    'picture',
    'signature',
    'status',
    'contact',
    'redirect',
  )));
  $config->set('blocks', backdrop_map_assoc(array(
    'format',
  )));
  $config->save();

  // On The Web settings.
  config_set('on_the_web.settings', 'type', 'font');

  // Save system.core.
  $system->save();
}
