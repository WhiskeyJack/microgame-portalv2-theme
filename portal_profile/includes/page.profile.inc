<?php

/**
 * @file
 * Content for profile page
 */
function portal_profile_page() {
  
  $output = array(
      'first_para' => array(
          '#type' => 'markup',
          '#markup' => '<p>Portal Profile Page</p>',
      ),
  );
  return $output;

}

?>
