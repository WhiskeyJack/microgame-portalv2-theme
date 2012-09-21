<?php
/**
 * @file
 * Contains Subdomain.
 */

class Subdomain {

  private $subdomain;
  private $group;
  private $id;

  function __construct() {
    $servername = explode('.', $_SERVER["SERVER_NAME"]);
    $firstdomain = $servername[0] == 'www' ? $servername[1] : $servername[0];
    $this->subdomain = $firstdomain == $servername[count($servername)-2] ? '' : $firstdomain;
  }

  function name() {
    return $this->subdomain;
  }
  
  function get_details_in_array($id = NULL) {
    if (is_null($id)){
      $id = $this->id;
    }
    $sdid = is_numeric($id) ? $id : $this->get_subdomain_id_by_name($id);
    $array = db_select('microgame_subdomains', 'm')->fields('m')->condition('sdid', $sdid, '=')->execute()->fetchAssoc();
    return $array;
  }

  function get_subdomain_id_by_name($name) {
    $id = 1;
    return $id;
  }
  
}