<?php
/**
 * @file
 * Text format configuration.
 */

/**
 * Add text formats.
 */
function pw_profile_add_text_formats() {
  $t = get_t();

  // Full editor.
  pw_profile_add_text_format(array(
    'format' => 'full_editor',
    'name' => $t('Full editor'),
    'weight' => -5,
    'editor' => 'ckeditor',
  ));

  // Basic editor.
  pw_profile_add_text_format(array(
    'format' => 'basic_editor',
    'name' => $t('Basic editor'),
    'weight' => 0,
    'editor' => 'ckeditor',
  ));

  // No editor.
  pw_profile_add_text_format(array(
    'format' => 'plain_text',
    'name' => $t('No editor'),
    'weight' => 5,
  ));
}

/**
 * Configure text formats.
 */
function pw_profile_configure_text_formats() {
  $t = get_t();

  // Full editor.
  $filters = array(
    'filter_autop' => array(
      'weight' => 0,
    ),
    'filter_htmlcorrector' => array(
      'weight' => 1,
    ),
    'emptyparagraphkiller' => array(
      'weight' => 2,
    ),
    'pathologic' => array(
      'weight' => 3,
      'settings' => array(
        'settings_source' => 'global',
      ),
    ),
    'invisimail_encode_js_entities' => array(
      'weight' => 4,
      'settings' => array(
        'link' => TRUE,
      ),
    ),
    'filter_url' => array(
      'weight' => 5,
    ),
  );
  $toolbar = array(
    array(
      'name' => $t('Formatting'),
      'items' => array('Format', 'Bold', 'Italic'),
    ),
    array(
      'name' => $t('Alignment'),
      'items' => array('JustifyLeft', 'JustifyCenter', 'JustifyRight'),
    ),
    array(
      'name' => $t('Lists'),
      'items' => array('BulletedList', 'NumberedList'),
    ),
    array(
      'name' => $t('Links'),
      'items' => array('DrupalLink', 'DrupalUnlink'),
    ),
    array(
      'name' => $t('Tools'),
      'items' => array('RemoveFormat', 'Source'),
    ),
  );
  pw_profile_configure_text_format('full_editor', $filters, $toolbar);

  // Basic editor.
  $filters = array(
    'filter_html' => array(
      'weight' => 0,
      'settings' => array(
        'allowed_html' => '<strong> <b> <em> <i> <a> <span>',
      ),
    ),
    'filter_autop' => array(
      'weight' => 1,
    ),
    'filter_htmlcorrector' => array(
      'weight' => 2,
    ),
    'emptyparagraphkiller' => array(
      'weight' => 3,
    ),
    'pathologic' => array(
      'weight' => 4,
      'settings' => array(
        'settings_source' => 'global',
      ),
    ),
    'invisimail_encode_js_entities' => array(
      'weight' => 5,
      'settings' => array(
        'link' => TRUE,
      ),
    ),
    'filter_url' => array(
      'weight' => 6,
    ),
  );
  $toolbar = array(
    array(
      'name' => $t('Formatting'),
      'items' => array('Bold', 'Italic'),
    ),
    array(
      'name' => $t('Links'),
      'items' => array('DrupalLink', 'DrupalUnlink'),
    ),
    array(
      'name' => $t('Tools'),
      'items' => array('RemoveFormat', 'Source'),
    ),
  );
  pw_profile_configure_text_format('basic_editor', $filters, $toolbar);

  // No editor.
  $filters = array(
    'filter_html_escape' => array(
      'weight' => 0,
    ),
    'filter_autop' => array(
      'weight' => 1,
    ),
    'pathologic' => array(
      'weight' => 2,
      'settings' => array(
        'settings_source' => 'global',
      ),
    ),
    'invisimail_encode_js_entities' => array(
      'weight' => 3,
      'settings' => array(
        'link' => TRUE,
      ),
    ),
    'filter_url' => array(
      'weight' => 4,
    ),
  );
  pw_profile_configure_text_format('plain_text', $filters);
}


/*** ---------------------------------------------------------------------- ***/


/**
 * Add a new, or update an existing, text format.
 *
 * @param $format
 *   An associative array containing:
 *   - format: The machine-readable name of the text format.
 *   - name: The human-readable name of the text format.
 *   - weight: (optional) The position of the text format relative to other text
 *     formats. Defaults to 0.
 *   - editor: (optional) The WYSIWYG editor to use for the text format.
 *     Defaults to none.
 */
function pw_profile_add_text_format($format) {
  // Add format defaults for optional values.
  $format += array(
    'weight' => 0,
    'editor' => '',
  );

  // Save text format.
  filter_format_save((object) $format);
}

/**
 * Configure a text format.
 *
 * @param $format_name
 *   The name of the text format to configure.
 * @param $filters
 *   An array where the keys are filter names, such as 'pathologic', and values
 *   are an associative array containing:
 *   - status: (optional) Whether the filter is enabled or not. Defaults to
 *     enabled.
 *   - weight: (optional) The position of the filter relative to other filters.
 *     Defaults to filter default.
 *   - settings: (optional) An array of filter-specific settings. Defaults to
 *     filter default.
 * @param $toolbar
 *   An array of toolbar groups, where each group is an associative array
 *   containing:
 *   - name: The human-readable name of the group.
 *   - items: An array of button names to display in this group.
 */
function pw_profile_configure_text_format($format_name, $filters, $toolbar = array()) {
  // Load the text format.
  $format = filter_format_load($format_name);

  // Add editor settings.
  $format->editor_settings = array('toolbar' => array($toolbar));

  // Add custom filter settings.
  foreach ($filters as $name => $properties) {
    // Add default settings.
    $properties += array(
      'status' => TRUE,
    );

    foreach ($properties as $key => $value) {
      if ($key == 'settings' && !empty($format->filters[$name][$key])) {
        $value += $format->filters[$name][$key];
      }
      $format->filters[$name][$key] = $value;
    }
  }

  // Save text format.
  filter_format_save($format);
}

