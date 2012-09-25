<?php

/**
 * @file
 * Content for page with portal admin functions
 */
function portal_admin_page() {
  
  $output = array(
      'first_para' => array(
          '#type' => 'markup',
          '#markup' => '<p>Portal admin functions</p>',
      ),
      'second_para' => array(
          '#items' => array(l('Create a subdomain', 'portal/subdomain/create'), l('Create a subdomain', 'portal/subdomain/edit/'.subdomain()->name())),
          '#theme' => 'item_list',
      ),
  );
  return $output;

}

?>
