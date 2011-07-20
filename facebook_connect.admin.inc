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
  
  $form[FACEBOOK_CONNECT_SITE_LIKE_PATH] = array(
    '#type' => 'textfield',
    '#title' => t('Site <em>Like</em> path'),
    '#description' => t('The path or URL that will be used for site-wide <em>Like</em> buttons. The default is to use the URL of your site\'s front page.'),
    '#default_value' => variable_get(FACEBOOK_CONNECT_SITE_LIKE_PATH, NULL),
  );
  
  $form[FACEBOOK_CONNECT_NODE_LIKE_BUTTONS] = array(
    '#type' => 'checkbox',
    '#title' => t('Show <em>Like</em> buttons on node teasers'),
    '#default_value' => variable_get(FACEBOOK_CONNECT_NODE_LIKE_BUTTONS, FALSE),
  );
  
  $form = system_settings_form($form);
  $form['#submit'][] = 'facebook_connect_admin_settings_submit';
  
  return $form;
}

function facebook_connect_admin_settings_submit() {
  // Fetch the blocks of this module
  $result = db_query("SELECT * FROM {blocks} WHERE module = '%s'", 'facebook_connect');
  
  // For each block, clear the block's cache
  while ($block = db_fetch_object($result)) {
    $cid = _block_get_cache_id($block);
    
    if (!empty($cid)) {
      cache_clear_all($cid, 'cache_block');
    }
  }
}
