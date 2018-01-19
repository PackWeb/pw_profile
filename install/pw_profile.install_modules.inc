<?php
/**
 * @file
 * Install modules.
 */

/**
 * Install modules.
 */
function pw_profile_install_modules() {
  module_enable(array(
    // Core
    'admin_bar',
    'contextual',
    'dblog',
    'update',
    'date',
    'email',
    'field_ui',
    'image',
    'link',
    'list',
    'number',
    'options',
    'block',
    'contact',
    'menu',
    'path',
    'redirect',
    'ckeditor',
    'views_ui',
    // Contrib

    /*'auto_menutitle',
    'block_access',
    'captcha',
    'copyright_block',
    'ctools',
    'devel',
    'dialog',
    'disable_taxonomy_description',
    'editor',
    'editor_ckeditor',
    'emptyparagraphkiller',
    'entity',
    'extlink',
    'fancybox',
    'filefield_paths',
    'flexslider',
    'flexslider_views',
    'imagefield_tokens',
    'invisimail',
    'jquery_update',
    'libraries',
    'link',
    'locationmap',
    'logintoboggan',
    'manualcrop',
    'menu_admin_per_menu',
    'menu_trail_by_path',
    'module_filter',
    'multiupload_filefield_widget',
    'multiupload_imagefield_widget',
    'path_alias_xt',
    'pathauto',
    'pathologic',
    'pw_module',
    'recaptcha',
    'simple_pass_reset',
    'simplify',
    'social_media_links',
    'submitted_by',
    'superfish',
    'taxonomy_access_fix',
    'termcase',
    'text_format_access',
    'token',
    'transliteration',
    'update_advanced',
    'views',*/
  ));
}

