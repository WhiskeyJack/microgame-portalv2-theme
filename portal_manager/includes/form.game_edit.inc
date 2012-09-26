<?php

/**
 * @file
 * Contains the form for editing and uploading a game.
 */
function game_edit_form($form, &$form_state, $gid = 0) {
  menu_tree_set_path('microgame_portal', 'portal/admin');

  $defaults = array('name' => '', 'description' => '', 'gid' => 0);
  if ($gid != 0) {
    $defaults = array('name' => '', 'description' => '', 'gid' => 0);
    $form['lastedit'] = array(
        '#type' => 'item',
        //'#title' => t('Last edited on'),
        '#markup' => t('This subdomain was last edited on @date', array('@date' => format_date($defaults['updated_on'])))
    );
    if (!$defaults) {
      drupal_set_message(t('The specified subdomain has not been configured, you can configure it now'), 'error');
      $defaults = array('name' => $subdomain, 'theme_name' => $theme_key, 'group_name' => '', 'sdid' => 0);
    }
  }

  $form['gid'] = array('#type' => 'value', '#value' => $defaults['gid']);

  $form['game_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Game name'),
      '#description' => t('The name of this game'),
      '#size' => 30,
      '#maxlength' => 50,
      '#required' => TRUE,
      '#default_value' => $defaults['name'],
      '#element_validate' => array('mg_is_valid_game_name'),
  );

  $form['game_description'] = array(
      '#type' => 'textarea',
      '#title' => t('Game description'),
      '#description' => t('Short description of the game'),
      '#cols' => 30,
      '#rows' => 4,
      '#resizable' => FALSE,
      '#required' => TRUE,
      '#default_value' => $defaults['description'],
  );

  $form['fid'] = array(
      '#title' => t('Game file'),
      '#type' => 'file',
      '#size' => 22,
      '#description' => t('File must have a .unity3d extension'),
  );

  $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Submit'),
  );
  
  return $form;
}


function game_edit_form_validate($form, &$form_state) {
  // This is not needed, I use this to use the same validate function
  // for several fields.
  //$key = $form['#key'];


  $file = file_save_upload('fid', array(
    'file_validate_extensions' => array('unity3d'),
  ));
  
  if ($file) {
    $a=1;
    // Get the image info to get the correct extension for the uploaded file.
    if (file_move($file, 'games/'. $file->filename, FILE_EXISTS_RENAME)) {
      // Mark the file for permanent storage.
      file_set_status($file, FILE_STATUS_PERMANENT);
      // Update the files table.
      drupal_write_record('files', $file, 'fid');
      $form_state['values']['fid'] = $file->filepath;
    }
    else {
      form_set_error('fid', t('Failed to write the uploaded file to the site’s files folder.'));
    }
  }
  
}

function mg_is_valid_game_name($element, &$form_state) {
  return TRUE;
  /*
    if (!preg_match('/^[a-z\d\-]+$/i', $element['#value'])) {
    form_error($element, t('Invalid name specified, only alphanumeric characters and the dash are allowed'));
    }
    else if ($form_state['values']['sdid'] == 0 && subdomain()->name_exists($element['#value'])) {
    form_error($element, t('The specified name already exists'));
    }
    else if ($form_state['values']['sdid'] != 0 && subdomain()->name_exists($element['#value'])  && subdomain()->name_exists($element['#value']) != $form_state['values']['sdid'] ) {
    form_error($element, t('The specified name is already in use'));
    }

   */
}