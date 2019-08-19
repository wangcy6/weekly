

/**
 * Copyright 2015 Evernote Corporation. All rights reserved.
 */
define(['require','react','classnames','css!focus/drawer/HelpIllustration'],function (require) {
  

  var React = require('react');
  var classnames = require('classnames');
  require('css!focus/drawer/HelpIllustration');

  function prefixedClass(suffix) {
    if (!suffix) {
      return null;
    }
    return 'focus-drawer-HelpIllustration-' + suffix;
  }

  /**
   * An illustration and text to help the user understand the drawer. Generally shown as
   * an "empty state" when a user has a low number of elements in the drawer.
   */
  var HelpIllustration = React.createClass({
    displayName: 'HelpIllustration',

    propTypes: {
      baseClass: React.PropTypes.string,
      body: React.PropTypes.string,
      // use children to pass formatted header
      children: React.PropTypes.oneOfType([React.PropTypes.arrayOf(React.PropTypes.node), React.PropTypes.node]),
      imageClass: React.PropTypes.string.isRequired,
      top: React.PropTypes.number
    },

    render: function render() {
      var styles = {};
      if (this.props.top !== undefined) {
        styles.top = this.props.top;
      }
      var body;
      if (this.props.body) {
        body = React.createElement(
          'div',
          { className: prefixedClass('body') },
          this.props.body
        );
      }
      return React.createElement(
        'div',
        {
          className: classnames(prefixedClass('container'), prefixedClass(this.props.baseClass)),
          style: styles
        },
        React.createElement('div', { className: this.props.imageClass + ' ' + prefixedClass('image') }),
        React.createElement(
          'div',
          { className: prefixedClass('header') },
          this.props.children
        ),
        body
      );
    }
  });

  return HelpIllustration;
});