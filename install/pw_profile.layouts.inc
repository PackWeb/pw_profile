<?php
/**
 * @file
 * Layout configuration.
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

  // Setup conditions.
  $condition_front = layout_create_access('front');
  $condition_front->is_new = TRUE;

  // Add blocks to Default layout.
  _pw_profile_configure_block($layout, 'system', 'header', 'header_top', array(
    'block_settings' => array(
      'menu' => '',
    ),
  ));
  _pw_profile_configure_block($layout, 'on_the_web', 'social_links', 'header_top', array(
    'block_settings' => array(
      'services' => array(
        'display' => 'auto',
      ),
    ),
  ));
  _pw_profile_configure_block($layout, 'system', 'main-menu', 'header_bottom', array(
    'title_display' => 'none',
    'block_settings' => array(
      'style' => 'dropdown',
      'depth' => '0',
    ),
  ));
  _pw_profile_configure_block($layout, 'views', 'slideshow-block', 'above', array(), array($condition_front));
  _pw_profile_configure_block($layout, 'system', 'breadcrumb', 'above', array(
    'block_settings' => array(
      'current' => TRUE,
    ),
  ));
  _pw_profile_configure_block($layout, 'copyright_notice', 'copyright_notice', 'footer_bottom', array(
    'block_settings' => array(
      'title' => '',
      'body' => array(
        'value' => $t('Copyright &copy; [site:name], [current-date:custom:Y]. All rights reserved. | <a href="/user/login">Admin</a>'),
        'format' => 'basic_editor',
      ),
    ),
  ));
  _pw_profile_configure_block($layout, 'pw_module', 'packweb', 'footer_bottom');

  // Save layout.
  $layout->save();
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
 *   Optional. An array of settings to configure.
 * @param $conditions
 *   Optional. An array of LayoutAccess objects.
 */
function _pw_profile_configure_block(&$layout, $module, $delta, $region, $settings = array(), $conditions = array()) {
  // Add block to layout.
  $block = $layout->addBlock($module, $delta, $region);

  // Update settings.
  $layout->content[$block->uuid]->settings = array_merge($layout->content[$block->uuid]->settings, $settings);

  // Add conditions.
  if (!empty($conditions)) {
    $layout->content[$block->uuid]->conditions = $conditions;
  }
}
