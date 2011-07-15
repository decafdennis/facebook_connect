// Developed by Dennis Stevense for Digital Deployment

Drupal.behaviors.facebookConnect = function() {
  var appID = Drupal.settings.facebookConnect.appID;

  // Initialize if we have a like button and/or a login box
  if ($('.facebook-connect-login-box, .facebook-connect-like-button').length > 0) {
    new Drupal.facebookConnect(appID);
  }
}

Drupal.facebookConnect = function(anAppID) {
  var self = this;
  var appID = anAppID;
  
  // Unhide the login boxes but hide the elements for the different states
  $('.facebook-connect-login-box > div').hide();
  $('.facebook-connect-login-box').show();
  
  // Asynchronously load the Facebook Javascript SDK
  $.getScript(document.location.protocol + '//connect.facebook.net/en_US/all.js', function() {
    // Add the element that the SDK needs for some reason
    $('body').prepend('<div id="fb-root"></div>');
    
    // Initialize the SDK
    FB.init({ appId: appID, status: true, cookie: true, xfbml: true });
    
    // Determine the user's login status, if we have any login boxes
    if ($('.facebook-connect-login-box').length > 0) {
      FB.getLoginStatus(function(response) {
        self.handleResponse(response);

        // Subscribe to changes to the user's login status
        FB.Event.subscribe('auth.sessionChange', self.handleResponse);
      });
    }
  });
}

Drupal.facebookConnect.prototype.handleResponse = function(response) {
  if (response.session) {
    $('.facebook-connect-login-box .no-session').hide();
    
    var query = FB.Data.query('SELECT name, url, pic_square FROM profile WHERE id = {0}', response.session.uid);
    
    query.wait(function(rows) {
      if (rows.length > 0) {
        var profile = rows[0];
        
        var sessionElement = $('.facebook-connect-login-box .session');

        var pictureElement = $('.picture', sessionElement);
        pictureElement.attr('src', profile.pic_square);
        pictureElement.attr('alt', profile.name);

        var nameElement = $('.prompt .name-link', sessionElement);
        nameElement.attr('href', profile.url);
        nameElement.text(profile.name);

        sessionElement.show();
      }
    });
  }
  else {
    $('.facebook-connect-login-box .session').hide();
    $('.facebook-connect-login-box .no-session').show();
  }
}
