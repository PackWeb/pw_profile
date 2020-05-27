<?php
/**
 * @file
 * Text format configuration.
 */

/**
 * Add text formats.
 */
function pw_profile_setup_text_formats() {
  $t = get_t();

  // Full editor.
  filter_format_save((object) array(
    'format' => 'full_editor',
    'name' => $t('Full editor'),
    'weight' => -10,
    'editor' => 'ckeditor',
    'editor_settings' => array(
      'image_upload' => array(
        'status' => 1,
        'directory' => 'images',
        'max_dimensions' => array(
          'width' => '1200',
          'height' => '1200',
        ),
      ),
      'toolbar' => array(
        array(
          array(
            'name' => $t('Formatting'),
            'items' => array('Format', 'Bold', 'Italic', 'Underline', 'Strike', '-', 'Blockquote', 'Superscript', 'Subscript', 'HorizontalRule'),
          ),
          array(
            'name' => $t('Lists'),
            'items' => array('BulletedList', 'NumberedList'),
          ),
          array(
            'name' => $t('Alignment'),
            'items' => array('JustifyLeft', 'JustifyCenter', 'JustifyRight', 'JustifyBlock'),
          ),
          array(
            'name' => $t('Linking'),
            'items' => array('BackdropLink', 'BackdropUnlink'),
          ),
          array(
            'name' => $t('Media'),
            'items' => array('BackdropImage', 'Table'),
          ),
          array(
            'name' => $t('Tools'),
            'items' => array('RemoveFormat', 'Source'),
          ),
        ),
      ),
    ),
    'filters' => array(
      'filter_url' => array(
        'status' => 1,
        'weight' => 0,
      ),
      'filter_autop' => array(
        'status' => 1,
        'weight' => 1,
      ),
      'filter_image_caption' => array(
        'status' => 1,
        'weight' => 2,
      ),
      'filter_image_align' => array(
        'status' => 1,
        'weight' => 3,
      ),
      'filter_htmlcorrector' => array(
        'status' => 1,
        'weight' => 4,
      ),
      'pathologic' => array(
        'status' => 1,
        'weight' => 5,
        'settings' => array(
          'settings_source' => 'global',
        ),
      ),
      'invisimail_encode_js_entities' => array(
        'status' => 1,
        'weight' => 6,
        'settings' => array(
          'link' => TRUE,
        ),
      ),
      // This is needed otherwise certain CKEditor buttons get disabled.
      // @see https://github.com/backdrop/backdrop-issues/issues/2966
      'filter_html' => array(
        'status' => 0,
        'settings' => array(
          'allowed_html' => '<p> <br> <strong> <b> <em> <i> <span> <u> <del> <blockquote> <sup> <sub> <hr> <ul> <ol> <li> <a> <img> <table> <thead> <tbody> <tfoot> <tr> <th> <td>',
        ),
      ),
    ),
  ));

  // Basic editor.
  filter_format_save((object) array(
    'format' => 'basic_editor',
    'name' => $t('Basic editor'),
    'editor' => 'ckeditor',
    'editor_settings' => array(
      'image_upload' => array(
        'status' => 1,
        'directory' => 'images',
        'max_dimensions' => array(
          'width' => '1200',
          'height' => '1200',
        ),
      ),
      'toolbar' => array(
        array(
          array(
            'name' => $t('Formatting'),
            'items' => array('Bold', 'Italic', 'Underline', 'Strike'),
          ),
          array(
            'name' => $t('Linking'),
            'items' => array('BackdropLink', 'BackdropUnlink'),
          ),
          array(
            'name' => $t('Tools'),
            'items' => array('RemoveFormat', 'Source'),
          ),
        ),
      ),
    ),
    'filters' => array(
      'filter_html' => array(
        'status' => 1,
        'weight' => 0,
        'settings' => array(
          'allowed_html' => '<p> <br> <strong> <b> <em> <i> <span> <u> <del> <a>',
        ),
      ),
      'filter_url' => array(
        'status' => 1,
        'weight' => 1,
      ),
      'filter_autop' => array(
        'status' => 1,
        'weight' => 2,
      ),
      'filter_htmlcorrector' => array(
        'status' => 1,
        'weight' => 3,
      ),
      'pathologic' => array(
        'status' => 1,
        'weight' => 4,
        'settings' => array(
          'settings_source' => 'global',
        ),
      ),
      'invisimail_encode_js_entities' => array(
        'status' => 1,
        'weight' => 5,
        'settings' => array(
          'link' => TRUE,
        ),
      ),
    ),
  ));

  // No editor.
  filter_format_save((object) array(
    'format' => 'plain_text',
    'name' => $t('No editor'),
    'filters' => array(
      'filter_html_escape' => array(
        'status' => 1,
        'weight' => 0,
      ),
      'filter_url' => array(
        'status' => 1,
        'weight' => 1,
      ),
      'filter_autop' => array(
        'status' => 1,
        'weight' => 2,
      ),
      'pathologic' => array(
        'status' => 1,
        'weight' => 3,
        'settings' => array(
          'settings_source' => 'global',
        ),
      ),
      'invisimail_encode_js_entities' => array(
        'status' => 1,
        'weight' => 4,
        'settings' => array(
          'link' => TRUE,
        ),
      ),
    ),
  ));
}
