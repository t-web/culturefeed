<?php
/**
 * @file
 * Defines page callback to render the search results.
 */

use \Guzzle\Http\Exception;

/**
 * Page callback to search.
 *
 * @param String $name
 *   The name of the searchable type.
 * @param String $class_name
 *   The name of class to be used to load the correct search page.
 * @param Boolean $ajax
 *   The type of request.
 */
function culturefeed_search_ui_search_page($name, $class_name = NULL, $request_type = 'nojs') {

  // The first search page callback is a dummy callback to redirect to the
  // real search page.
  if ($name == "submitted") {
    return "";
  }
  $ajax = $request_type == 'ajax';

  try {

    $conf = culturefeed_get_searchable_type($name);
    $page = culturefeed_get_search_page($conf);

    if ($ajax) {
      $page->setFullPage(FALSE);
    }
    $page->setPagerType(variable_get('culturefeed_search_ui_pager_type', CULTUREFEED_SEARCH_UI_PAGER_NORMAL));
    $page->setDefaultTitle($conf['page_title']);
    $build = $page->loadPage();

    drupal_set_title($page->getPageTitle());

    $description = $page->getPageDescription();
    if (!empty($description)) {
      $element = array(
        '#tag' => 'meta',
        '#attributes' => array(
          'name' => 'description',
          'content' => $description,
        ),
      );
      drupal_add_html_head($element, 'meta_description');
    }

    $active_trail = $page->getActiveTrail();
    if ($active_trail) {
      menu_set_active_trail($active_trail);

      // Last item of the breadcrumb should not be clickable.
      $breadcrumb = drupal_get_breadcrumb();
      $last_item = array_pop($breadcrumb);
      $breadcrumb[] = strip_tags($last_item);
      drupal_set_breadcrumb($breadcrumb);

    }

  }
  catch (Exception\ClientErrorResponseException $e) {
    watchdog_exception('culturefeed_search_ui', $e);
    $build = t('There was an error while loading the search results.');
  }
  catch (Exception\ServerErrorResponseException $e) {
    watchdog_exception('culturefeed_search_ui', $e);
    $build = t('There was an error while loading the search results.');
  }
  catch (Exception\CurlException $e) {
    watchdog_exception('culturefeed_search_ui', $e);
    $build = t('There was an error while loading the search results.');
  }
  catch (InvalidSearchPageException $e) {
    $build = $e->getMessage();
  }
  catch (CultureFeed_Cdb_ParseException $e) {
    watchdog_exception('culturefeed_search_ui', $e);
    $build = t('There was an error while loading the search results.');
  }

  if ($ajax) {
    $commands = array(
      ajax_command_invoke('.more-link:first', 'remove'),
      ajax_command_append('#culturefeed-search-results-more-wrapper', render($build)),
    );

    ajax_deliver(array('#type' => 'ajax', '#commands' => $commands));
    exit;
  }
  else {
    return $build;
  }

}

/**
 * Page callback for the city suggestions autocomplete.
 *
 * (using jquery ui autocomplete format).
 */
function culturefeed_search_ui_city_suggestion_autocomplete_page($search_string, $include_regions = TRUE) {

  $matches = array();

  if ($search_string) {

    $parents = (isset($_GET['parents']) && !empty($_GET['parents'])) ? $_GET['parents'] : array();
    // Get the list of suggestions from service.
    $suggestions = culturefeed_search_get_city_suggestions($search_string, $include_regions, $parents);
    foreach ($suggestions as $key => $suggestion) {
      $matches[] = (object) array('value' => $key, 'label' => check_plain($suggestion));
    }

  }

  drupal_json_output($matches);

}
