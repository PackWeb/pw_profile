<?php
/**
 * @file
 * Content types configuration.
 */

/**
 * Setup content types.
 */
function pw_profile_setup_content_types() {
  module_load_include('inc', 'pw_profile', 'pw_profile.install_miscellaneous');
  $t = get_t();

  // Page.
  node_type_save((object) array(
    'type' => 'page',
    'name' => $t('Page'),
    'description' => $t("A simple page with a menu link, such as an 'About us' page."),
    'settings' => array(
      'sticky_enabled' => FALSE,
      'promote_enabled' => FALSE,
      'draft_enabled' => TRUE,
      'skip_required' => TRUE,
      'revision_enabled' => FALSE,
      'auto_menu_settings_default' => TRUE,
      'menu_options' => array('main-menu'),
      'auto_menu_settings_fields' => array(
        'provide',
        'title',
        'parent',
      ),
      'node_submitted' => FALSE,
      'node_user_picture' => FALSE,
    ),
    'is_new' => TRUE,
  ));
  _pw_profile_configure_view_modes('page', array());

  // Slideshow image.
  node_type_save((object) array(
    'type' => 'slideshow_image',
    'name' => $t('Slideshow Image'),
    'description' => $t("An image to display in the slideshow, with an optional link to another page/URL."),
    'help' => $t("The Title is only used to identify this image in the admin interface."),
    'settings' => array(
      'sticky_enabled' => FALSE,
      'promote_enabled' => FALSE,
      'draft_enabled' => TRUE,
      'skip_required' => TRUE,
      'revision_enabled' => FALSE,
      'node_submitted' => FALSE,
      'node_user_picture' => FALSE,
    ),
    'is_new' => TRUE,
  ));
  config_set('simplify.nodes', 'slideshow_image', array('menu'));
  _pw_profile_configure_view_modes('slideshow_image', array());
}

/**
 * Create fields.
 */
function pw_profile_setup_fields() {
  $t = get_t();

  // Body.
  field_create_field(array(
    'field_name' => 'field_body',
    'type' => 'text_with_summary',
  ));
  field_create_instance(array(
    'field_name' => 'field_body',
    'label' => $t('Body'),
    'entity_type' => 'node',
    'bundle' => 'page',
    'settings' => array(
      'text_processing' => 1,
      'display_summary' => FALSE,
    ),
    'widget' => array(
      'type' => 'text_textarea_with_summary',
      'weight' => 0,
      'settings' => array(
        'rows' => '20',
      ),
    ),
    'display' => array(
      'default' => array(
        'type' => 'text_default',
        'label' => 'hidden',
        'weight' => 0,
      ),
    ),
  ));

  // Link.
  field_create_field(array(
    'field_name' => 'field_link',
    'type' => 'link_field',
  ));
  field_create_instance(array(
    'field_name' => 'field_link',
    'label' => $t('Link'),
    'entity_type' => 'node',
    'bundle' => 'slideshow_image',
    'settings' => array(
      'title' => 'none',
    ),
    'widget' => array(
      'type' => 'link_field',
      'weight' => 1,
    ),
    'display' => array(
      'default' => array(
        'type' => 'link_url',
        'label' => 'inline',
        'weight' => 1,
      ),
    ),
  ));

  // Slideshow image.
  field_create_field(array(
    'field_name' => 'field_slideshow_image',
    'type' => 'image',
  ));
  field_create_instance(array(
    'field_name' => 'field_slideshow_image',
    'label' => $t('Slideshow Image'),
    'entity_type' => 'node',
    'bundle' => 'slideshow_image',
    'required' => TRUE,
    'settings' => array(
      'file_directory' => 'slideshows',
      'max_dimensions' => '2000x2000',
    ),
    'widget' => array(
      'type' => 'image_image',
      'weight' => 0,
      'settings' => array(
        'progress_indicator' => 'bar',
      ),
    ),
    'display' => array(
      'default' => array(
        'type' => 'image',
        'label' => 'hidden',
        'weight' => 0,
        'settings' => array(
          'image_style' => 'large',
        ),
      ),
    ),
  ));
}


/*** ---------------------------------------------------------------------- ***/


/**
 * Configure view modes for an entity bundle.
 *
 * @param $bundle
 *   The bundle to configure the view modes for, such as 'page'.
 * @param $view_modes
 *   An array of view modes that should be enabled.
 */
function _pw_profile_configure_view_modes($bundle, $view_modes) {
  // Get all view modes.
  $entity_info = entity_get_info('node');
  $entity_view_modes = array_keys($entity_info['view modes']);

  // Get current settings.
  $settings = field_bundle_settings('node', $bundle);

  // Configure view modes.
  foreach ($entity_view_modes as $entity_view_mode) {
    $settings['view_modes'][$entity_view_mode]['custom_settings'] = in_array($entity_view_mode, $view_modes);
  }
  field_bundle_settings('node', $bundle, $settings);
}

