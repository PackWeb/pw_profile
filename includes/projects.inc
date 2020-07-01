<?php
/**
 * @file
 * An array of projects (modules, themes, etc.) to be downloaded and installed
 * in a PackWeb Backdrop site.
 *
 * This list is kept in a separate file so it can be included wherever it's
 * needed to avoid duplication.
 */

$projects = array(
  'modules' => array(
    'core' => array(
      'admin_bar',
      'block',
      'ckeditor',
      'contact',
      'contextual',
      'dashboard',
      'date',
      'dblog',
      'email',
      'field_ui',
      'image',
      'link',
      'list', // Requires: Options.
      'menu',
      'number',
      'options',
      'path',
      'redirect',
      'update',
      'views_ui',
    ),
    'contrib' => array(
      'antibot' => array(),
      'auto_menu_settings' => array(),
      'copyright_notice' => array(),
      'devel' => array(),
      'extlink' => array(),
      'globalredirect' => array(),
      'html5_upload' => array(),
      'imagesloaded' => array(),
      'imgareaselect' => array(),
      'invisimail' => array(),
      'maintenance_page' => array(),
      'manualcrop' => array(),
      'menu_admin_per_menu' => array(),
      'menu_trail_by_path' => array(),
      'metatag' => array(
        'metatag_opengraph' => array(),
        '#patches' => array(
          'https://patch-diff.githubusercontent.com/raw/backdrop-contrib/metatag/pull/21.patch',
        ),
      ),
      'minify' => array(),
      'on_the_web' => array(),
      'pathologic' => array(),
      'pw_module' => array(
        '#git' => 'git@github.com:PackWeb/pw_module.git',
      ),
      'responsive_favicons' => array(),
      'save_draft' => array(),
      'simplify' => array(),
      'srcset_image' => array(),
      'views_slideshow' => array(),
      'views_slideshow_cycle2' => array(),
      'xmlsitemap' => array(
        'xmlsitemap_engines' => array(),
        'xmlsitemap_menu' => array(),
        'xmlsitemap_node' => array(),
      ),
    ),
  ),
  'layouts' => array(
    'pw_layout' => array(
      '#git' => 'git@github.com:PackWeb/pw_layout.git',
    ),
  ),
  'themes' => array(
    'pw_theme' => array(
      '#git' => 'git@github.com:PackWeb/pw_theme.git',
    ),
  ),
);


/*** ---------------------------------------------------------------------- ***/


/**
 * Get list of sub-projects.
 *
 * @param array $project
 *   The array value of an individual project from the $projects array.
 *
 * @return array
 *   An array of sub-projects.
 */
function _pw_profile_get_children($project) {
  $children = array();

  foreach ($project as $key => $value) {
    if ($key[0] !== '#') {
      $children[] = $key;
    }
  }

  return $children;
}
