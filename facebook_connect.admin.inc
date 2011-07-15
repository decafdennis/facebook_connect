<?php
// Developed by Dennis Stevense for Digital Deployment

function facebook_connect_admin_settings() {
  $form = array();
  
  $form[FACEBOOK_CONNECT_APP_ID] = array(
    '#type' => 'textfield',
    '#title' => t('App ID/API key'),
    '#description' => t('Your site\'s Facebook App ID, which can be found on the <a href="https://developers.facebook.com/apps">Facebook developers site</a>.'),
    '#default_value' => variable_get(FACEBOOK_CONNECT_APP_ID, NULL),
  );
  
  return system_settings_form($form);
}
