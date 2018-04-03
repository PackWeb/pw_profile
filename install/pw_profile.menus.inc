<?php
/**
 * @file
 * Menu configuration.
 */

/**
 * Add menu links.
 */
function pw_profile_setup_menus() {
  $t = get_t();

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
}

