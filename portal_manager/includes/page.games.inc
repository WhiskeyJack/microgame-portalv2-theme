<?php

function portal_games_page() {


  menu_tree_set_path('microgame_portal', 'portal/admin');

  // get all themes
  $all_themes = list_themes();
  $theme_list = array();
  foreach ($all_themes as $theme_name => $theme) {
    $theme_list[$theme_name] = $theme->info['name'];
  }

  $header = array(
      array('data' => t('ID'), 'field' => 'gid', 'sort' => 'desc'),
      array('data' => t('Name'), 'field' => 'name'),
      array('data' => t('Active version'), 'field' => 'active_version'),
      array('data' => t('Version count'), 'field' => 'version_count'),
      array('data' => t('Created by'), 'field' => 'created_by_name'),
      array('data' => t('Updated by'), 'field' => 'updated_by_name'),
      array('data' => t('Created on'), 'field' => 'created_on'),
      array('data' => t('Updated on'), 'field' => 'updated_on'),
  );

  $query = db_select('microgame_games', 'm');
  $query->leftJoin('users', 'u', 'm.created_by_uid = u.uid');
  $query->leftJoin('users', 'v', 'm.updated_by_uid = v.uid');
  $query->leftJoin('microgame_game_versions', 'gv', 'm.gid = gv.gid');
  $query->fields('m');
  $query->addField('u', 'name', 'created_by_name');
  $query->addField('v', 'name', 'updated_by_name');
  $query->addExpression('COUNT (gv.version_id)', 'version_count');
  $query->groupBy('m.gid');
  $result = $query->extend('PagerDefault')->limit(10)->extend('TableSort')->orderByHeader($header)->execute()->fetchallAssoc('gid');

  $rows = array();
  foreach ($result as $row) {
    $fields = array();
    foreach ($header as $col) {
      if ($col['field'] == 'created_on' || $col['field'] == 'updated_on') {
        $fields[$col['field']] = format_date($row->$col['field'], 'short');
      } else {
        $fields[$col['field']] = $row->$col['field'];
      }
    }
    $fields['edit'] = l(t('edit'), 'portal/admin/games/edit/' . $row->gid);
    $rows[] = $fields;
  }

  /*
    $table['header'] = $header;
    $table['attributes'] = array('class' => array('mg_table', 'subdomain_table'));
    $table['caption'] = '';
    $table['colgroups'] = array();
    $table['sticky'] = "";
    $table['empty'] = t('No subdomains have been configured');
    $table['rows'] = $rows;
    return theme_table($table);
   */

  $link = l(t('Create a game'), 'portal/admin/games/upload');

  $output = array(
      'first_para' => array(
          '#type' => 'markup',
          '#markup' => "<p>{$link}</p>",
      ),
      'second_para' => array(
          '#theme' => 'table',
          '#header' => $header,
          '#attributes' => array('class' => array('mg_table', 'gamelist_table')),
          '#empty' => t('No games have been configured'),
          '#rows' => $rows,
      ),
  );
  return $output;
}
