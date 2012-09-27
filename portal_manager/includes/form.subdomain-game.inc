<?php

/**
 * @file
 * Contains the form for editing and creating a subdomain.
 */
function subdomain_game_edit_form($form, &$form_state, $subdomain = '') {
  menu_tree_set_path('microgame_portal', 'portal/admin');

  $arg = arg();
  $name = $arg[count($arg) - 2];
  $sdid = subdomain()->name_exists($name);

  $query = db_select('microgame_games', 'm');
  $query->leftJoin('users', 'u', 'm.created_by_uid = u.uid');
  $query->leftJoin('users', 'v', 'm.updated_by_uid = v.uid');
  $query->leftJoin('microgame_game_versions', 'gv', 'm.gid = gv.gid');
  $query->fields('m');
  $query->addField('u', 'name', 'created_by_name');
  $query->addField('v', 'name', 'updated_by_name');
  $query->addExpression('COUNT (gv.version_id)', 'version_count');
  $query->groupBy('m.gid');
  $result = $query->execute()->fetchallAssoc('gid');

  $currentgames = db_select('microgame_subdomain_games', 'm')->fields('m')->condition('sdid', $sdid)->execute()->fetchallAssoc('gid');

  $header = array();
  $options = array();
  $default_value = array();

  $IsCheckbox = true;

  $header = array(
      'title' => t('Game')
  );
  $versiontext = t('version');
  $defaults = array();
  foreach ($result as $gid => $val) {
    $options[$gid]['title'] = "{$val->name} ({$versiontext} {$val->active_version})";
    $options[$gid]['#attributes'] = array('class' => array('red-row'));
    if (array_key_exists($gid, $currentgames)) {
      $defaults[$gid] = $gid;
    }
  }

  if ($IsCheckbox) {
    /* Checkbox only */
    $default_value[0] = true;
    $default_value[1] = false;
  } else {
    /* Radiobox only */
    $default_value = '0';
  }

  $form['sdid'] = array('#type' => 'value', '#value' => $sdid);
  $form['name'] = array('#type' => 'value', '#value' => $name);

  $form['game_ids'] = array(
      '#type' => 'tableselect',
      '#title' => 'Games',
      '#header' => $header,
      '#options' => $options,
      '#multiple' => $IsCheckbox,
      '#default_value' => $defaults
  );

  $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Submit'),
  );

  return $form;
}

function subdomain_game_edit_form_submit($form, &$form_state) {
  global $user;

  $sdid = $form_state['values']['sdid'];

  if ($sdid != 0) {
    db_delete('microgame_subdomain_games')->condition('sdid', $sdid)->execute();
    foreach ($form_state['values']['game_ids'] as $gid => $val) {
      if ($val != 0) {
        db_insert('microgame_subdomain_games')
                ->fields(array(
                    'sdid' => $sdid,
                    'gid' => $gid,
                    'enabled' => 1, // for now hardcoded
                ))
                ->execute();
      }
    }
  }

  drupal_set_message(t('Game selection for subdomain "@name" has been updated', array('@name' => $form_state['values']['name'])));
  drupal_goto('portal/admin/subdomains');
}