<?php
// Developed by Dennis Stevense for Digital Deployment
?>
<div class="facebook-connect-login-box">

  <div class="no-session">
    <fb:login-button show-faces="false"><?php print t('Connect'); ?></fb:login-button>
  </div>

  <div class="session">
    <img class="picture" src="" alt="" />
    <span class="prompt"><?php print t('Welcome, !name!', array('!name' => '<a class="name-link" href=""></a>')); ?></span>
  </div>

</div>
