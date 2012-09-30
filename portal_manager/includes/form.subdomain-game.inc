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
  $all_games = $query->orderBy('name', 'ASC')->execute()->fetchallAssoc('gid');

  $currentgames = db_select('microgame_subdomain_games', 'm')
          ->fields('m')
          ->condition('sdid', $sdid)
          ->orderBy('weight', 'ASC')
          ->execute()
          ->fetchallAssoc('gid');

    

    $gamelist = $currentgames;
    
    foreach ($currentgames as $gid => $game) {
      $gamelist[$gid] = $all_games[$gid];
      $gamelist[$gid]->weight = $game->weight;
      unset ($all_games[$gid]);
    }
    
    $item = new stdClass();
    $item->name = "TEST";
    $item->description = "TEST";
    $item->gid = 0;
    $gamelist[0] = $item;
    
    $gamelist += $all_games;
    
    
    $form['example_items']['#tree'] = TRUE;
    
    foreach ($gamelist as $item) {      
      $item->depth = 0;
      $item->pid = 0;
      if (!isset($item->weight)) {
        $item->weight = 10;
      }
    // Create a form entry for this item.
    //
    // Each entry will be an array using the the unique id for that item as
    // the array key, and an array of table row data as the value.
    $form['example_items'][$item->gid] = array(

      // We'll use a form element of type '#markup' to display the item name.
      'name' => array(
        '#markup' => $item->name,
      ),

      // We'll use a form element of type '#textfield' to display the item
      // description, to demonstrate that form elements can be included in the
      // table. We limit the input to 255 characters, which is the limit we
      // set on the database field.
      'description' => array(
        '#type' => 'textfield',
        '#default_value' => $item->description,
        '#size' => 20,
        '#maxlength' => 255,
      ),

      // For parent/child relationships, we also need to add form items to
      // store the current item's unique id and parent item's unique id.
      //
      // We would normally use a hidden element for this, but for this example
      // we'll use a disabled textfield element called 'id' so that we can
      // display the current item's id in the table.
      //
      // Because tabledrag modifies the #value of this element, we use
      // '#default_value' instead of '#value' when defining a hidden element.
      // Also, because tabledrag modifies '#value', we cannot use a markup
      // element, which does not support the '#value' property. (Markup
      // elements use the '#markup' property instead.)
      'id' => array(
       '#type' => 'hidden',
        //'#default_value' => $item->id,
       // '#type' => 'textfield',
        '#size' => 3,
        '#default_value' => $item->gid,
        '#disabled' => TRUE,
      ),

      // The same information holds true for the parent id field as for the
      // item id field, described above.
      'pid' => array(
        //'#type' => 'hidden',
        //'#default_value' => $item->pid,
        '#type' => 'hidden',
        '#size' => 3,
        '#default_value' => $item->pid,
      ),

      // The 'weight' field will be manipulated as we move the items around in
      // the table using the tabledrag activity.  We use the 'weight' element
      // defined in Drupal's Form API.
      'weight' => array(
        '#type' => 'weight',
        '#title' => t('Weight'),
        '#default_value' => $item->weight,
        '#delta' => 10,
        '#title-display' => 'invisible',
      ),

      // We'll use a hidden form element to pass the current 'depth' of each
      // item within our parent/child tree structure to the theme function.
      // This will be used to calculate the initial amount of indentation to
      // add before displaying any child item rows.
      'depth' => array(
        '#type' => 'hidden',
        '#value' => $item->depth,
      ),
    );
  }
  
  
  
//  $header = array();
//  $options = array();
//  $default_value = array();
//
//  $IsCheckbox = true;
//
//  $header = array(
//      'title' => t('Game')
//  );
//  $versiontext = t('version');
//  $defaults = array();
//  foreach ($result as $gid => $val) {
//    $options[$gid]['title'] = "{$val->name} ({$versiontext} {$val->active_version})";
//    $options[$gid]['#attributes'] = array('class' => array('red-row'));
//    if (array_key_exists($gid, $currentgames)) {
//      $defaults[$gid] = $gid;
//    }
//  }
//
//  if ($IsCheckbox) {
//    /* Checkbox only */
//    $default_value[0] = true;
//    $default_value[1] = false;
//  } else {
//    /* Radiobox only */
//    $default_value = '0';
//  }
//
//  $form['sdid'] = array('#type' => 'value', '#value' => $sdid);
//  $form['name'] = array('#type' => 'value', '#value' => $name);
//
//  $form['game_ids'] = array(
//      '#type' => 'tableselect',
//      '#title' => 'Games',
//      '#header' => $header,
//      '#options' => $options,
//      '#multiple' => $IsCheckbox,
//      '#default_value' => $defaults
//  );
//
//  $form['submit'] = array(
//      '#type' => 'submit',
//      '#value' => t('Submit'),
//  );

  // The 'actions' wrapper used here isn't strictly necessary for tabledrag,
  // but is included as a Form API recommended practice.
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array( '#type' => 'submit', '#value' => t('Save Changes'));
  return $form;
}



/**
 * Theme callback for the tabledrag_example_parent_form form
 *
 * The theme callback will format the $form data structure into a table and
 * add our tabledrag functionality.  (Note that drupal_add_tabledrag should be
 * called from the theme layer, and not from a form declaration.  This helps
 * keep template files clean and readable, and prevents tabledrag.js from
 * being added twice accidently.
 */
function theme_subdomain_game_edit_form($variables) {
  $form = $variables['form'];

  // Initialize the variable which will store our table rows
  $rows = array();

  // Iterate over each element in our $form['example_items'] array
  foreach (element_children($form['example_items']) as $id) {

    // Before we add our 'weight' column to the row, we need to give the
    // element a custom class so that it can be identified in the
    // drupal_add_tabledrag call.
    //
    // This could also have been done during the form declaration by adding
    //     '#attributes' => array('class' => 'example-item-weight'),
    // directly to the 'weight' element in tabledrag_example_simple_form().
    $form['example_items'][$id]['weight']['#attributes']['class'] = array('example-item-weight');

    // In the parent/child example, we must also set this same custom class on
    // our id and parent_id columns (which could also have been done within
    // the form declaration, as above).
    $form['example_items'][$id]['id']['#attributes']['class'] = array('example-item-id');
    $form['example_items'][$id]['pid']['#attributes']['class'] = array('example-item-pid');

    // To support the tabledrag behaviour, we need to assign each row of the
    // table a class attribute of 'draggable'. This will add the 'draggable'
    // class to the <tr> element for that row when the final table is
    // rendered.
    if ($id != 0) {
      $class = array('draggable');
      $class[] = 'tabledrag-leaf';
    } else {
      $class = array();
    }
    // We can add the 'tabledrag-root' class to a row in order to indicate
    // that the row may not be nested under a parent row.  In our sample data
    // for this example, the description for the item with id '8' flags it as
    // a 'root' item which should not be nested.
   // if ($id == '8') {
   //   $class[] = 'tabledrag-root';
    //}

    // We can add the 'tabledrag-leaf' class to a row in order to indicate
    // that the row may not contain child rows.  In our sample data for this
    // example, the description for the item with id '9' flags it as a 'leaf'
    // item which can not contain child items.
    //if ($id == '9') {
      
//    /}

    // If this is a child element, we need to add some indentation to the row,
    // so that it appears nested under its parent.  Our $depth parameter was
    // calculated while building the tree in tabledrag_example_parent_get_data
    $indent = theme('indentation', array('size' => $form['example_items'][$id]['depth']['#value']));
    unset ($form['example_items'][$id]['depth']);

    // We are now ready to add each element of our $form data to the $rows
    // array, so that they end up as individual table cells when rendered
    // in the final table.  We run each element through the drupal_render()
    // function to generate the final html markup for that element.
    $rows[] = array(
      'data' => array(
        // Add our 'name' column, being sure to include our indentation.
        $indent . drupal_render($form['example_items'][$id]['name']),
        // Add our 'description' column
        drupal_render($form['example_items'][$id]['description']),
        // Add our 'weight' column
        drupal_render($form['example_items'][$id]['weight']),
        // Add our hidden 'id' column
        drupal_render($form['example_items'][$id]['id']),
        // Add our hidden 'parent id' column
        drupal_render($form['example_items'][$id]['pid']),
      ),
      // To support the tabledrag behaviour, we need to assign each row of the
      // table a class attribute of 'draggable'. This will add the 'draggable'
      // class to the <tr> element for that row when the final table is
      // rendered.
      'class' => $class,
    );
  }

  // We now define the table header values.  Ensure that the 'header' count
  // matches the final column count for your table.
  //
  // Normally, we would hide the headers on our hidden columns, but we are
  // leaving them visible in this example.
 $header = array(t('Name'), t('Description'), t('Weight'));
//  $header = array(t('Name'), t('Description'), t('Weight'), t('ID'), t('PID'));

  // We also need to pass the drupal_add_tabledrag() function an id which will
  // be used to identify the <table> element containing our tabledrag form.
  // Because an element's 'id' should be unique on a page, make sure the value
  // you select is NOT the same as the form ID used in your form declaration.
  $table_id = 'example-items-table';

  // We can render our tabledrag table for output.
  $output = theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => $table_id)));

  // And then render any remaining form elements (such as our submit button)
  $output .= drupal_render_children($form);

  // We now call the drupal_add_tabledrag() function in order to add the
  // tabledrag.js goodness onto our page.
  //
  // For our parent/child tree table, we need to pass it:
  //   - the $table_id of our <table> element (example-items-table),
  //   - the $action to be performed on our form items ('match'),
  //   - a string describing where $action should be applied ('parent'),
  //   - the $group value (pid column) class name ('example-item-pid'),
  //   - the $subgroup value (pid column) class name ('example-item-pid'),
  //   - the $source value (id column) class name ('example-item-id'),
  //   - an optional $hidden flag identifying if the columns should be hidden,
  //   - an optional $limit parameter to control the max parenting depth
  drupal_add_tabledrag($table_id, 'match', 'parent', 'example-item-pid', 'example-item-pid', 'example-item-id',  FALSE);

  // Because we also want to sort in addition to providing parenting, we call
  // the drupal_add_tabledrag function again, instructing it to update the
  // weight field as items at the same level are re-ordered.
  drupal_add_tabledrag($table_id, 'order', 'sibling', 'example-item-weight', NULL, NULL, FALSE);

  return $output;
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