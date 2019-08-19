/**
 * Module for security-related functionality used on ActionBean pages.
 */
define(['require','jquery','cookies','actionBean'],function(require) {
  
  var $ = require('jquery');
  var cookies = require('cookies');
  var actionBean = require('actionBean');

  // The key for expiry in an encoded CSRF buster token
  var CSRF_EXPIRY_KEY = 'E';
  var CSRF_INPUT_SELECTOR = 'input[name=csrfBusterToken]';
  var CSRF_BUSTER_TOKEN_COOKIE = 'req_sec';

  // actionBean is undefined if PageTag is configured to skipJsIncludes
  actionBean = actionBean || {};

  var Security = {

    /**
     * Get a valid csrf buster token for the current user.
     *
     * @return a promise which resolves with a valid csrf buster token if procurable.
     */
    getCsrfBusterToken: function() {
      return this._refreshCsrfBusterTokenMaybe().then(
        this._getCsrfBusterTokenFromCookie.bind(this),
        function() {
          /* If the refresh fails, there's not much we can do. We proceed as normal
           * in the hopes that when the user attempts to use the csrf buster token
           * their request will encounter the same error (e.g. network outage, auth expired) */
          return $.Deferred().resolve('');
        });
    },

    /**
     * DEPRECATED. get the csrf buster we have in the cookie. do not attempt to refresh it.
     */
    getCsrfToken: function() {
      return this._getCsrfBusterTokenFromCookie();
    },

    /**
     * Either set the csrfBusterToken input field of the form to a valid csrf token or
     * add csrfBusterToken field to form.
     */
    setFormCsrfBusterToken: function(form) {
      return this.getCsrfBusterToken().then(function(token) {
        var hiddenInput = form.find(CSRF_INPUT_SELECTOR);
        if (hiddenInput.length > 0) {
          hiddenInput.val(token);
        } else {
          form.append($('<input>', {
            type: 'hidden',
            name: 'csrfBusterToken',
            value: token
          }));
        }
      });
    },

    /**
     * Attach submit handler to form to update csrf buster token. Incompatible with
     * any other handlers (jquery or native) on the form's submit event. Instead use
     * the callback parameter.
     *
     * @param form jquery element for a form with a csrfBusterToken hidden field.
     * @param callback (optional) a function to call after the csrfToken has been refreshed.
     *   If the callback returns false, the native submit event is not fired.
     * @return a promise which is resolved after the token is refreshed and the form is
     *   resubmitted. This is a testing hook.
     */
    ensureValidCsrfBusterTokenOnSubmit: function(form, callback) {
      var deferred = $.Deferred();
      form.submit(function() {
        /**
         * We're okay waiting here since if the csrf refresh request takes a long time
         * the submit request will probably take just as long - the user will see the same
         * laggy experience regardless so we might as well wait for a valid csrf.
         */
        this.setFormCsrfBusterToken(form).done(function() {
          if (typeof callback !== 'function' || callback() !== false) {
            // trigger native form submit. Does not trigger native submit handlers
            form[0].submit();
          }
          deferred.resolve();
        });
        return false;
      }.bind(this));
      return deferred.promise();
    },

    /**
     * Get the user's current csrf buster token.
     */
    _getCsrfBusterTokenFromCookie: function() {
      return cookies.get(CSRF_BUSTER_TOKEN_COOKIE, actionBean.slotSuffix);
    },

    /**
     * Refresh the user's csrf buster token if the current one is expired.
     * returns a promise which is resolved when the token is refreshed.
     */
    _refreshCsrfBusterTokenMaybe: function() {
      if (!this._isValidCsrfBusterToken(this._getCsrfBusterTokenFromCookie())) {
        return this._refreshCsrfBusterToken();
      }
      return $.Deferred().resolve().promise();
    },

    /**
     * Check if a csrf buster token is valid
     * @param token a string encoding of a csrf buster token
     */
    _isValidCsrfBusterToken: function(token) {
      if (!token) {
        return false;
      }
      var groups = new RegExp(':' + CSRF_EXPIRY_KEY + '=([a-zA-Z0-9]+)').exec(token);
      if (!groups) {
        return false;
      }
      var expiry = parseInt(groups[1], 16);
      return expiry > Date.now();
    },

    /**
     * Refresh the current user's csrf buster token.
     * @return a promise which resolves when the task is completed.
     */
    _refreshCsrfBusterToken: function() {
      return $.ajax(window.location.pathname + '?ping=');
    }
  };

  return Security;
});
