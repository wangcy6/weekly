/* global Evernote */

/**
 * (c) 2011 Evernote Corp
 *
 * i18N support for Javascript via JSON.
 *
 * <h3>Configuration Options:</h3>
 *
 *  e.g.
 *    Evernote.i18n = {
 *      "baseUrl": "override source location of i18n files - default /js/i18n/i18n",
 *      "fatalError": function(msg) { ...some other fatal error handler - default log to console if it exists... }
 *    }
 *
 *  <h3>Library Usage:</h3>
 *
 *  The translation strings may be accessed in 2 ways.
 *
 *    1. (PREFERRED) Access through require module. The require module returns a deferred object
 *       to which callbacks can be attached for success, failure  and/or progress. The callbacks
 *       may recieve a handle to the i18n library, allowing them to translate any needed strings.
 *
 *      require(["i18n", ...], function(i18n, ...) {
 *          ...
 *          i18n.done(function(i18n) {
 *            i18n.L("key", [ Array | Object ]);
 *          });
 *      });
 *
 *    2. (DEPRICATED) Access through global Evernote object. Note that any uses must be passed
 *       to the i18n.onReady function() which will schedule them for execution when the tranlation
 *       file has been loaded.
 *
 *       ...
 *       Evernote.i18n.onReady(function() {
 *         Evernote.i18n.L("key", [ Array | Object ]);
 *       });
 *
 *  You must use string Object notation when using the object style because JavaScript does not support
 *  numbers to be used as object element names.
 *
 *  e.g.
 *  Array style substitution done in order using tokens from 0 - 9.
 *
 *    Evernote.i18n.L("my.key.1", [ "sub1", "sub2" ]);
 *
 *  Object style substitution done using tokens.
 *
 *    Evernote.i18n.L("my.key.1", { "0": "value1", "1": "value2" });
 *
 *  If no parameters are required you can simply use
 *
 *    Evernote.i18n.L("my.key.1");
 */

define([
  'jquery',
  'webI18nResources',
  'plurr',
  'common',
  'json2',
  'domReady!'
], function(
  $,
  WebI18nResources,
  Plurr
) {
  

  // Some legacy code relies on i18n being attached to global Evernote object.
  if (!Evernote) {
    window.Evernote = {};
  }
  if (!Evernote.i18n) {
    Evernote.i18n = {};
  }
  var i18n = Evernote.i18n;

  i18n.isFunction = function(fn) {
    return typeof fn !== 'undefined' && typeof fn === 'function';
  };

  Evernote.i18n.onReady = function(fn) {
    i18n.defer.done(fn);
  };

  Evernote.i18n.runReady = function() {
    i18n.defer.resolve(i18n);
  };

  /**
   * attach our load function to window on load using an anon function
   */
  (function() {
    i18n.defer = $.Deferred();
    if (!i18n.messages || $.isEmptyObject(i18n.messages)) {
      // Messages may be prepopulated via ContentI18NManifest.
      i18n.messages = window.__EVERNOTE_I18N__;
    }
    i18n.runReady();
  }());

  /**
   * Array version of l10n method.
   * @param msg with tokens
   * @param args to substitute
   * @returns string
   */
  i18n.LArray = function(msg, args) {
    function replaceFunction(whole, index) {
      return (args[index] ? args[index] : '');
    }

    for (var i = 0, iMax = args.length; i < iMax; ++i) {
      msg = msg.replace(/\{\{ ([0-9]+) \}\}/g, replaceFunction);
    }
    return msg;
  };

  /**
   * Object version of l10n method.
   * @param msg with tokens
   * @param args to substitute
   * @returns string
   */
  i18n.LObject = function(msg, args) {
    for (var k in args) {
      if (args.hasOwnProperty(k)) {
        msg = msg.replace(new RegExp('\{\{ ' + k + ' \}\}', 'g'), args[k]);
      }
    }
    return msg;
  };

  /**
   * Based on a i18n key, create a localized message with substituted parameters.
   *
   * @param key to use
   * @param args to substitute
   * @returns string or null
   */
  i18n.L = function(key, args) {
    var self = this;
    if (self.messages === {}) {
      return null;
    }
    var msg = '';
    try {
      msg = self.messages[key];
    } catch (err) {
      if (self.fatalError) {
        self.fatalError(err + ' on while looking up key ' + key);
      } else {
        console.log(err + ' on while looking up key ' + key);
      }
    }
    if (!msg) {
      return null;
    }
    if (Object.prototype.toString.call(args) === '[object Array]') {
      return self.LArray(msg, args);
    }
    return self.LObject(msg, args);
  };

  /**
   * Creates a Plurr instance with the current locale.
   */
  i18n._getPlurr = function() {
    var self = this;
    if (!self._plurr) {
      var metaLocale = WebI18nResources.getLocale();
      var plurrLocale;
      if (!metaLocale) {
        plurrLocale = 'en';
      } else if (metaLocale.startsWith('zh_')) {
        plurrLocale = 'zh';
      } else if (metaLocale === 'in') {
        plurrLocale = 'id';
      } else if (metaLocale === 'pt_BR') {
        plurrLocale = 'pt-br';
      } else {
        plurrLocale = metaLocale;
      }

      self._plurr = new Plurr({
        locale: plurrLocale
      });
    }
    return self._plurr;
  };

  /**
   * Use plurr to localize the i18n key with the provided plurr parameters.
   *
   * @param {string} key  the key of the i18n entry - required
   * @param {object} plurrParams  parameters to pass to Plurr.format - optional
   * @return a translated string, or an empty string if no translation is found
   */
  i18n.plurr = function(key, plurrParams) {
    var self = this;
    var msg = self.messages[key];
    if (!msg) {
      // Not translated yet.
      console.error('Untranslated string', key);
      return '';
    }

    /* Our makeJsI18n.pl script replaces all instances of "{N}" with "{{ N }}" during
     * compilation. Undo this work here at runtime for plurr only. */
    msg = self.messages[key].replace(/\{\{ /g, '{').replace(/ \}\}/g, '}');

    try {
      return self._getPlurr().format(msg, plurrParams || {});
    } catch (e) {
      console.error('Required plurr replacement variable probably not found for', key,
          '\n', e);
      return '';
    }
  };

  return i18n.defer.promise();
});
