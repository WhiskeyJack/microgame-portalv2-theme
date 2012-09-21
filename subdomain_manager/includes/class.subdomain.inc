<?php
/**
 * @file
 * Contains Subdomain.
 */

class Subdomain {
  
  private $subdomain;

  function __construct() {
    $servername = explode('.', $_SERVER["SERVER_NAME"]);
    $firstdomain = $servername[0] == 'www' ? $servername[1] : $servername[0];
    $this->subdomain = $firstdomain == $servername[count($servername)-2] ? '' : $firstdomain;
  }
  
  function name() {
    return $this->subdomain;
  }
  
}