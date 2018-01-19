<?php
/**
 * @file
 * Content types configuration.
 */

/**
 * Add new content types.
 */
function pw_profile_add_content_types() {
  $t = get_t();

  // Page.
  pw_profile_add_content_type(array(
    'type' => 'page',
    'name' => $t('Page'),
    'description' => $t("A simple page with a menu link, such as an 'About us' page."),
  ));

  // Slideshow image.
  pw_profile_add_content_type(array(
    'type' => 'slideshow_image',
    'name' => $t('Slideshow Image'),
    'description' => $t("An image to display in the slideshow with an optional link to another page/URL."),
    'help' => $t("The Title is displayed in the admin interface to identify this slideshow image, and is also shown to people who can't see images in their browser."),
  ));
}

/**
 * Configure content type settings.
 */
function pw_profile_configure_content_types() {
  // Page.
  $page = array(
    'auto_menutitle' => TRUE,
    'menus_available' => array('main-menu'),
    'menu_parent' => 'main-menu:0',
    'simplify_fields' => array(),
  );
  pw_profile_configure_content_type('page', $page);
  pw_profile_configure_view_modes('page', array());

  // Slideshow image.
  $slideshow_image = array(
    'simplify_fields' => array('menu'),
  );
  pw_profile_configure_content_type('slideshow_image', $slideshow_image);
  pw_profile_configure_view_modes('slideshow_image', array());
}


/*** ---------------------------------------------------------------------- ***/


/**
 * Add a new content type.
 *
 * @param $content_type
 *   An associative array containing:
 *   - type: The machine-readable name of the content type.
 *   - name: The human-readable name of the content type.
 *   - description: A description of the content type.
 */
function pw_profile_add_content_type($content_type) {
  // Add content type defaults.
  $content_type += array(
    'base' => 'node_content',
    'help' => '',
  );

  // Save content type.
  node_type_save((object) $content_type);
}

/**
 * Configure general settings for a content type.
 *
 * @param $node_type
 *   The machine-readable name of the node type to configure settings for.
 * @param $settings
 *   An associative array containing:
 *   - preview: (optional) Whether node previews should be disabled, optional or
 *     required. Defaults to disabled.
 *   - publishing_options: (optional) An array of publishing options for a node.
 *     Defaults to published.
 *   - display_submitted: (optional) Whether or not a node's author and date
 *     should be displayed. Defaults to not displayed.
 *   - submitted_byline: (optional) The 'submitted by' text to display for all
 *     non-teaser view modes. Defaults to 'Posted on [node:created:long]'.
 *   - submitted_byline_teaser: (optional) The 'submitted by' text to display
 *     for all teaser view modes. Defaults to 'Posted on [node:created:medium]'.
 *   - auto_menutitle: (optional) Whether a menu item should be created
 *     automatically. Defaults to no.
 *   - menus_available: (optional) An array of menu names that are available for
 *     creating the menu item under. Defaults to no menus.
 *   - menu_parent: (optional) The existing menu item a node's menu item will be
 *     created under. Defaults to no parent.
 *   - simplify_fields: (optional) An array of fields that should be hidden for
 *     a node. Defaults to menu.
 */
function pw_profile_configure_content_type($node_type, $settings = array()) {
  $t = get_t();
  module_load_include('inc', 'pw_profile', 'pw_profile.install_miscellaneous');

  // Add default settings for optional values.
  $settings += array(
    'preview' => 0,
    'publishing_options' => array('status'),
    'display_submitted' => FALSE,
    'submitted_byline' => $t('Posted on [node:created:long]'),
    'submitted_byline_teaser' => $t('Posted on [node:created:medium]'),
    'auto_menutitle' => FALSE,
    'menus_available' => array(),
    'menu_parent' => '',
    'simplify_fields' => array('menu'),
  );

  // Save settings.
  variable_set('node_preview_' . $node_type, $settings['preview']);
  variable_set('node_options_' . $node_type, $settings['publishing_options']);
  variable_set('node_submitted_' . $node_type, $settings['display_submitted']);
  pw_profile_configure_submitted_byline($node_type, $settings['submitted_byline'], $settings['submitted_byline_teaser']);
  variable_set('auto_menutitle_' . $node_type, $settings['auto_menutitle']);
  variable_set('menu_options_' . $node_type, $settings['menus_available']);
  variable_set('menu_parent_' . $node_type, $settings['menu_parent']);
  pw_profile_configure_simplify('nodes_' . $node_type, $settings['simplify_fields']);
}

/**
 * Configure submitted byline for a content type.
 *
 * @param $node_type
 *   The machine-readable name of the node type to configure the byline for.
 * @param $byline
 *   The text to use as the byline for all non-teaser view modes.
 * @param $byline_teaser
 *   The text to use as the byline for all teaser view modes.
 */
function pw_profile_configure_submitted_byline($node_type, $byline, $byline_teaser) {
  $bylines = array();

  // Get view modes.
  $entity_info = entity_get_info('node');
  $view_modes = array_keys($entity_info['view modes']);

  // Add view modes to bylines array.
  foreach ($view_modes as $view_mode) {
    if ($view_mode == 'teaser') {
      $bylines[$view_mode] = $byline_teaser;
    }
    else {
      $bylines[$view_mode] = $byline;
    }
  }

  // Set variable.
  variable_set('submitted_by_' . $node_type, $bylines);
}

/**
 * Configure view modes for an entity bundle.
 *
 * @param $bundle
 *   The bundle to configure the view modes for, such as 'page' or 'article'.
 * @param $view_modes
 *   An array of view modes that should be enabled.
 * @param $entity
 *   The entity type this bundle belong to. Defaults to node.
 */
function pw_profile_configure_view_modes($bundle, $view_modes, $entity = 'node') {
  // Get all view modes.
  $entity_info = entity_get_info($entity);
  $entity_view_modes = array_keys($entity_info['view modes']);

  // Get current settings.
  $settings = field_bundle_settings($entity, $bundle);

  // Configure view modes.
  foreach ($entity_view_modes as $entity_view_mode) {
    $settings['view_modes'][$entity_view_mode]['custom_settings'] = in_array($entity_view_mode, $view_modes);
  }

  // Save settings.
  field_bundle_settings($entity, $bundle, $settings);
}

