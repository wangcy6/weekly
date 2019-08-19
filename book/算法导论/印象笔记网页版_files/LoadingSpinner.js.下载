

/**
 * Copyright 2015-2016 Evernote Corporation. All rights reserved.
 */
define(['require','resolve!i18n','react','css!focus/drawer/LoadingSpinner'],function (require) {
  

  var i18n = require('resolve!i18n');
  var React = require('react');
  require('css!focus/drawer/LoadingSpinner');

  function prefixedClass(suffix) {
    return 'focus-drawer-LoadingSpinner-' + suffix;
  }

  /**
   * An image that animates to indicate a loading state with the text "loading" below it.
   */
  var LoadingSpinner = React.createClass({
    displayName: 'LoadingSpinner',

    render: function render() {
      return React.createElement(
        'div',
        { className: prefixedClass('container') },
        React.createElement('div', { className: prefixedClass('spinner') }),
        React.createElement(
          'div',
          { className: prefixedClass('label') },
          i18n.L('Focus.drawer.loadingSpinner')
        )
      );
    }
  });

  return LoadingSpinner;
});