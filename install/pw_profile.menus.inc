<?php
/**
 * @file
 * Menu configuration.
 */

/**
 * Add menu items.
 */
function pw_profile_add_menu_items() {
  $t = get_t();

  // Main menu.
  // Home.
  pw_profile_add_menu_item(array(
    'link_title' => $t('Home'),
    'link_path' => '<front>',
    'weight' => -50,
  ));
  // Contact.
  pw_profile_add_menu_item(array(
    'link_title' => $t('Contact'),
    'link_path' => 'contact',
    'weight' => 50,
  ));

  menu_cache_clear_all();
}


/*** ---------------------------------------------------------------------- ***/


/**
 * Add a new menu item.
 *
 * @param $menu_item
 *   An associative array containing:
 *   - link_title: The human-readable title of the link.
 *   - link_path: The path the link points to.
 *   - menu_name: (optional) The menu the link is added to. Defaults to the main
 *     menu.
 *   - weight: (optional) The position of the link relative to other links in
 *     the same menu. Defaults to 0.
 *   - expanded: (optional) Whether the menu item is expanded or not. Defaults
 *     to not expanded.
 *   - plid: (optional) The mlid of the parent menu item. Defaults to 0.
 */
function pw_profile_add_menu_item($menu_item) {
  // Normalise the link path.
  $menu_item['link_path'] = drupal_get_normal_path($menu_item['link_path']);

  // Add menu item defaults for optional values.
  $menu_item += array(
    'menu_name' => 'main-menu',
    'weight' => 0,
    'expanded' => 0,
    'plid' => 0,
  );

  // Save menu item.
  menu_link_save($menu_item);
}

