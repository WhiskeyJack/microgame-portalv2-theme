<?php
/**
 * @file
 * Contains the form for editing and creating a subdomain.
 */

function subdomain_create_form($form, &$form_state) {
  return subdomain_edit_form($form, $form_state, TRUE);
}

function subdomain_edit_form($form, &$form_state, $new = FALSE) {

  if ($new) {
    $defaults = array('sd_name' => '', 'sd_group' => '', 'sdid' => 0);
  }
  else {
    $arg = filter_xss(arg(2));
    $defaults = subdomain()->get_array($arg);
  }

  $form['subdomain_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Subdomain name'),
      '#description' => t('The name of the subdomain in the url. For example in "http://group1.microgame.nl" the subdomain name is "group1"'),
      '#size' => 30,
      '#maxlength' => 50,
      '#required' => TRUE,
      '#default' => $defaults['sdid']
  );

  return $form;
}
