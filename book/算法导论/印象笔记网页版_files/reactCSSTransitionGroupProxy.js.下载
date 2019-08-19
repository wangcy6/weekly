define(['require','react'],function(require) {
  /*
   * Workaround for https://github.com/facebook/react/issues/7874 - since we currently use
   * react-with-addons to satisfy react's AMD module, we cannot simply import
   * react-addons-css-transition-group in web-frontend code that's exported as an AMD
   * module. By doing so, webpack bundles react (from npm in web-frontend), which results
   * in two react versions being used by the same module. Instead, web-frontend makes
   * react-addons-css-transition-group an external dependency for the AMD modules that is
   * satisfied by this module, which simply references react-with-addons.
   */
  var React = require('react');
  return React.addons.CSSTransitionGroup;
});
