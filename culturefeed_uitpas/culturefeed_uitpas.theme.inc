<?php

/**
 * @file
 * Theme implementations for Culturefeed uitpas.
 */

/**
 * Implements hook_theme().
 */
function culturefeed_uitpas_theme() {

  return array(
    'culturefeed_uitpas_advantages_promotions' => array(
      'variables' => array(
        'advantages' => array(),
        'advantages_total' => 0,
        'advantages_pager_element' => 0,
        'promotions' => array(),
        'promotions_total' => 0,
        'promotions_pager_element' => 0,
      ),
      'template' => 'culturefeed-uitpas-advantages-promotions',
    ),
    'culturefeed_uitpas_my_uitpas_summary' => array(
      'variables' => array(
        'uitpas_user' => NULL,
        'passholder' => NULL,
        'advantages' => array(),
        'promotions' => array(),
        'upcoming_promotions' => array(),
      ),
      'template' => 'culturefeed-uitpas-my-uitpas-summary',
      'file' => 'theme.inc',
      'path' => drupal_get_path('module', 'culturefeed_uitpas') . '/theme',
    ),
    'culturefeed_uitpas_promotions_highlight' => array(
      'variables' => array('promotions' => array()),
      'template' => 'culturefeed-uitpas-promotions-highlight',
      'file' => 'theme.inc',
      'path' => drupal_get_path('module', 'culturefeed_uitpas') . '/theme',
    ),
    'culturefeed_uitpas_recent_actions' => array(
      'variables' => array('actions' => array()),
      'template' => 'culturefeed-uitpas-recent-actions',
      'file' => 'theme.inc',
      'path' => drupal_get_path('module', 'culturefeed_uitpas') . '/theme',
    ),
  );

}