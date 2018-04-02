<?php
/**
 * @file
 * Block configuration.
 */

/**
 * Configure layouts.
 */
function pw_profile_setup_layouts() {
  module_load_include('inc', 'layout', 'layout.admin');
  $t = get_t();

  // Change the template of the Default layout.
  $layout = layout_load('default', TRUE);
  $template = 'pw_layout';
  $region_mapping = layout_get_legacy_region_mapping($layout->layout_template, $template);
  $layout->setLayoutTemplate($template, $region_mapping);

  // Add blocks to Default layout.
  _pw_profile_configure_block($layout, 'system', 'header', 'header_top', array(
    'menu' => '',
  ));
  _pw_profile_configure_block($layout, 'on_the_web', 'social_links', 'header_top');
  _pw_profile_configure_block($layout, 'system', 'main-menu', 'header_bottom', array(
    'style' => 'dropdown',
    'depth' => '0',
  ));
  _pw_profile_configure_block($layout, 'system', 'breadcrumb', 'above', array(
    'current' => TRUE,
  ));
  _pw_profile_configure_block($layout, 'copyright_notice', 'copyright_notice', 'footer_bottom', array(
    'title' => '',
    'body' => array(
      'value' => $t('Copyright &copy; [site:name], [current-date:custom:Y]. All rights reserved. | <a href="/user/login">Admin</a>'),
      'format' => 'basic_editor',
    ),
  ));
  _pw_profile_configure_block($layout, 'pw_module', 'packweb', 'footer_bottom');

  // Save layout.
  $layout->save();
}

/**
 * Enable & configure blocks.
 */
function pw_profile_enable_blocks() {
  // Default theme.
  // Help.
  pw_profile_enable_block(array(
    'module' => 'system',
    'delta' => 'help',
    'region' => 'help',
  ));
  // Content.
  pw_profile_enable_block(array(
    'module' => 'system',
    'delta' => 'main',
    'region' => 'content',
  ));

  // Admin theme.
  $admin_theme = variable_get('admin_theme', 'adminimal');
  // Content.
  pw_profile_enable_block(array(
    'module' => 'system',
    'delta' => 'main',
    'region' => 'content',
    'theme' => $admin_theme,
  ));
  // Help.
  pw_profile_enable_block(array(
    'module' => 'system',
    'delta' => 'help',
    'region' => 'help',
    'theme' => $admin_theme,
  ));
}

/**
 * Configure block settings.
 */
function pw_profile_configure_blocks() {
  $t = get_t();

  // Set block titles for all enabled themes.
  pw_profile_configure_block_titles();

  // Contact details.
  pw_profile_configure_block_access('pw_module', 'contact', array(
    'config_title' => array('3' => '3'),
    'config_body' => array('3' => '3'),
  ));

  // Copyright.
  variable_set('copyright_block_text', array(
    'value' => $t('Copyright &copy; [site:name], [current-date:custom:Y] | <a href="/user/login">Admin</a>'),
    'format' => 'plain_text',
  ));

  // Location map.
  variable_set('locationmap_block_type', 'interactive');
  variable_set('locationmap_block_mapwidth', '1200');
  variable_set('locationmap_block_mapheight', '300');

  // Social media links.
  variable_set('social_media_links_icon_style', 'socicon:32_square');
  pw_profile_configure_block_access('social_media_links', 'social-media-links', array(
    'config' => array('3' => '3'),
    'config_title' => array('3' => '3'),
  ));

  // Superfish.
  variable_set('superfish_name_1', $t('Main Menu'));
  variable_set('superfish_shadow_1', FALSE);
  variable_set('superfish_delay_1', '500');
  variable_set('superfish_touch_1', 3);
  variable_set('superfish_touchdh_1', TRUE);
  variable_set('superfish_smallbp_1', '701');
  variable_set('superfish_smallamt_1', $t('Menu'));
  variable_set('superfish_maxwidth_1', '25');
}


/*** ---------------------------------------------------------------------- ***/


/**
 * Configure block.
 *
 * @param $layout
 *   The layout to add the block to.
 * @param $module
 *   The module that owns the block.
 * @param $delta
 *   The specific block within the module.
 * @param $region
 *   The region to add the block to.
 * @param $settings
 *   Optional. An array of block settings to configure.
 */
function _pw_profile_configure_block(&$layout, $module, $delta, $region, $settings = array()) {
  // Add block to layout.
  $block = $layout->addBlock($module, $delta, $region);

  // Combine block settings.
  $settings += $layout->content[$block->uuid]->settings['block_settings'];

  // Update block with settings.
  $layout->content[$block->uuid]->settings['block_settings'] = $settings;
}

/**
 * Enable & configure a pre-defined block.
 *
 * @param $block
 *   An associative array containing:
 *   - module: The module the block originates from.
 *   - delta: The unique ID of the block within the module.
 *   - region: The region to add the block to.
 *   - theme: (optional) The theme to configure the block for. Defaults to the
 *     current theme.
 *   - weight: (optional) The position of the block relative to other blocks in
 *     the same region. Defaults to 0.
 *   - visibility: (optional) How the block will be displayed. Defaults to show
 *     on all pages except those listed.
 *   - pages: (optional) Specifies on which pages the block will be displayed.
 *     Depends on 'visibility' setting. Defaults to all pages.
 *   - title: (optional) Custom title for the block. Defaults to block default.
 *   - cache: (optional) The caching mode for the block. Defaults to global
 *     caching.
 * @param $roles
 *   An array of role IDs that are allowed to view the block. Leave empty to
 *   show the block to all users.
 */
function pw_profile_enable_block($block, $roles = array()) {
  // Get current theme.
  $theme = variable_get('theme_default', 'bartik');

  // Add block defaults for optional values.
  $block += array(
    'theme' => $theme,
    'weight' => 0,
    'visibility' => BLOCK_VISIBILITY_NOTLISTED,
    'pages' => '',
    'title' => '',
    'cache' => DRUPAL_CACHE_GLOBAL,
    'status' => 1,
  );

  // Add settings to database.
  db_merge('block')
    ->key(array(
      'module' => $block['module'],
      'delta' => $block['delta'],
      'theme' => $block['theme'],
    ))
    ->fields($block)
    ->execute();

  // Setup block roles.
  if ($roles) {
    foreach ($roles as $rid) {
      db_merge('block_role')
        ->key(array(
          'module' => $block['module'],
          'delta' => $block['delta'],
          'rid' => $rid,
        ))
        ->execute();
    }
  }
}

/**
 * Configure block access permissions for a block.
 *
 * @param $module
 *   The name of the module defining the block to set the permissions for.
 * @param $delta
 *   The unique ID of the block within the module to set the permissions for.
 * @param $permissions
 *   An array of permissions to set for the block, where the keys are permission
 *   names and the values are an array of role IDs.
 */
function pw_profile_configure_block_access($module, $delta, $permissions) {
  foreach ($permissions as $permission => $roles) {
    block_access_config_set_roles($permission, $roles, $module, $delta);
  }
}

/**
 * Set the title for a block.
 *
 * @param $theme
 *   The theme for which to set the block title. Defaults to all themes.
 */
function pw_profile_configure_block_titles($theme = NULL) {
  $blocks = pw_profile_get_block_titles();

  foreach ($blocks as $block) {
    $query = db_update('block');
    $query->fields(array('title' => $block['title']));
    $query->condition('module', $block['module']);
    $query->condition('delta', $block['delta']);
    if (!empty($theme)) {
      $query->condition('theme', $theme);
    }
    $query->execute();
  }
}

/**
 * Get a list of blocks and the titles to set for them each time a new theme is
 * enabled.
 */
function pw_profile_get_block_titles() {
  return array(
    array(
      'module' => 'copyright_block',
      'delta' => 'copyright_block',
      'title' => '<none>',
    ),
    array(
      'module' => 'locationmap',
      'delta' => 'image',
      'title' => '<none>',
    ),
    array(
      'module' => 'social_media_links',
      'delta' => 'social-media-links',
      'title' => '<none>',
    ),
    array(
      'module' => 'superfish',
      'delta' => '1',
      'title' => '<none>',
    ),
  );
}
