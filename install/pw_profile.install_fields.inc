<?php
/**
 * @file
 * Fields configuration.
 */

/**
 * Create fields.
 */
function pw_profile_create_fields() {
  // Body.
  pw_profile_create_field(array(
    'field_name' => 'body',
    'type' => 'text_long',
  ));

  // Link.
  pw_profile_create_field(array(
    'field_name' => 'link',
    'type' => 'link_field',
  ));

  // Slideshow image.
  pw_profile_create_field(array(
    'field_name' => 'slideshow_image',
    'type' => 'image',
  ));
}

/**
 * Attach fields to content types.
 */
function pw_profile_attach_fields() {
  $t = get_t();

  // Page: Body.
  pw_profile_attach_field(array(
    'field_name' => 'body',
    'bundle' => 'page',
    'label' => $t('Body'),
    'required' => TRUE,
    'settings' => array(
      'text_processing' => 1,
      'text_format_access_formats' => array(
        'full_editor' => 'full_editor',
      ),
    ),
    'widget' => array(
      'type' => 'text_textarea',
      'settings' => array(
        'rows' => '20',
      ),
      'weight' => 0,
    ),
    'display' => array(
      'default' => array(
        'type' => 'text_default',
      ),
    ),
  ));

  // Slideshow image: Slideshow image.
  pw_profile_attach_field(array(
    'field_name' => 'slideshow_image',
    'bundle' => 'slideshow_image',
    'label' => $t('Slideshow Image'),
    'required' => TRUE,
    'settings' => array(
      'filefield_paths_enabled' => TRUE,
      'filefield_paths' => array(
        'file_path' => array(
          'value' => 'slideshow',
        ),
        'file_name' => array(
          'options' => array(
            'slashes' => TRUE,
            'pathauto' => TRUE,
            'transliterate' => TRUE,
          ),
        ),
      ),
      'max_resolution' => '2000x2000',
      'alt_field' => TRUE,
      'alt_field_update_on_edit' => TRUE,
      'alt_field_hide' => TRUE,
      'alt_field_default' => '[node:title]',
    ),
    'widget' => array(
      'type' => 'image_image',
      'settings' => array(
        'progress_indicator' => 'bar',
        'manualcrop_enable' => TRUE,
        'manualcrop_maximize_default_crop_area' => TRUE,
        'manualcrop_styles_list' => array(
          'slideshow' => 'slideshow',
        ),
      ),
      'weight' => 0,
    ),
    'display' => array(
      'default' => array(
        'type' => 'image',
        'settings' => array(
          'image_style' => 'flexslider_full',
        ),
      ),
    ),
  ));

  // Slideshow image: Link.
  pw_profile_attach_field(array(
    'field_name' => 'link',
    'bundle' => 'slideshow_image',
    'label' => $t('Link'),
    'required' => FALSE,
    'settings' => array(
      'title' => 'none',
      'enable_tokens' => FALSE,
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
}

/**
 * Configure extra fields.
 */
function pw_profile_extra_fields() {
  foreach (array_keys(field_info_bundles('node')) as $bundle) {
    // Submitted by.
    pw_profile_configure_extra_field('submitted_by', $bundle, array());
  }
}


/*** ---------------------------------------------------------------------- ***/


/**
 * Create a new field.
 *
 * @param $field
 *   An associative array containing:
 *   - field_name: The machine-readable name of the field.
 *   - type: The field type, such as 'text' or 'image'.
 *   - settings: An array of field type-specific settings.
 *   - cardinality: (optional) The number of values this field can hold.
 *     Defaults to 1.
 *   - entity_types: (optional) An array of entity types that this field can be
 *     added to. Defaults to all entities.
 */
function pw_profile_create_field($field) {
  // Add field defaults for optional values.
  $field += array(
    'cardinality' => 1,
    'entity_types' => array(),
  );

  // Create field.
  field_create_field($field);
}

/**
 * Attach a field instance to a content type.
 *
 * @param $instance
 *   An associative array containing:
 *   - field_name: The name of the field.
 *   - bundle: The name of the entity bundle to attach the field to.
 *   - label: The human-readable name of the field.
 *   - settings: An array of field instance-specific settings.
 *   - widget: An associative array containing:
 *     - type: The widget type, such as 'text_textfield'.
 *     - settings: An array of widget type-specific settings.
 *     - weight: The position of the widget relative to other elements on the
 *       edit form.
 *   - display: An array where the key is the view mode, such as 'default' or
 *     'teaser', and the value is an associative array containing:
 *     - type: (optional) The type of display formatter, such as 'text_default'
 *       or 'text_trimmed'. Defaults to hidden.
 *     - settings: (optional) An array of field formatter-specific settings.
 *     - label: (optional) The position of the label. Defaults to hidden.
 *     - weight: (optional) The position of the field relative to other fields
 *       in the entity. Defaults to 0.
 *   - required: (optional) Whether this field needs a value or not. Defaults to
 *     false.
 *   - description: (optional) Help text displayed below the field. Defaults to
 *     no description.
 *   - default_value: (optional) Default value(s) of the field. Defaults to no
 *     value.
 *   - entity_type: (optional) The name of the entity type to attach the field
 *     to. Defaults to node.
 */
function pw_profile_attach_field($instance) {
  // Add field defaults for optional values.
  $instance += array(
    'required' => FALSE,
    'description' => '',
    'default_value' => array(),
    'entity_type' => 'node',
  );

  foreach (element_children($instance['display']) as $type) {
    $instance['display'][$type] += array(
      'type' => 'hidden',
      'label' => 'hidden',
      'weight' => 0,
    );
  }

  // Attach field instance.
  field_create_instance($instance);
}

/**
 * Configure an extra field of a node type.
 *
 * @param $field
 *   The machine-name of the extra field to configure.
 * @param $node_type
 *   The machine-name of the node type to configure the field for.
 * @param $view_modes
 *   An associative array of view modes where the field should be visible. The
 *   keys are view mode names and the values are arrays of settings.
 * @param $entity_type
 *   The machine-name of the entity type the field belongs to. Defaults to node.
 */
function pw_profile_configure_extra_field($field, $node_type, $view_modes, $entity_type = 'node') {
  $settings = field_bundle_settings($entity_type, $node_type);

  $all_view_modes = element_children($settings['view_modes']);
  array_unshift($all_view_modes, 'default');

  foreach ($all_view_modes as $view_mode) {
    if (!empty($view_modes[$view_mode])) {
      $settings['extra_fields']['display'][$field][$view_mode] = $view_modes[$view_mode];
      $settings['extra_fields']['display'][$field][$view_mode]['visible'] = TRUE;
    }
    else {
      $settings['extra_fields']['display'][$field][$view_mode]['weight'] = 0;
      $settings['extra_fields']['display'][$field][$view_mode]['visible'] = FALSE;
    }
  }

  field_bundle_settings($entity_type, $node_type, $settings);
}

