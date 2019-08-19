

/**
 * Copyright 2015-2016 Evernote Corporation. All rights reserved.
 */
define(['require','classnames','focus-editor-SaveAnimation-IconState','react','css!focus/editor/SaveAnimation/Icon'],function (require) {
  

  var classNames = require('classnames');
  var IconState = require('focus-editor-SaveAnimation-IconState');
  var React = require('react');
  require('css!focus/editor/SaveAnimation/Icon');

  function prefixedClass(suffix) {
    return 'focus-editor-SaveAnimation-Icon-' + suffix;
  }

  /**
   * A specific icon state that should be animated with opacity in conjunction with other
   * icons of other states, overlayed on top of each other.
   */
  var Icon = React.createClass({
    displayName: 'Icon',

    propTypes: {
      iconState: React.PropTypes.oneOf([IconState.ERROR, IconState.IDLE, IconState.IN_PROGRESS, IconState.PENDING, IconState.SUCCESSFUL]).isRequired,
      visible: React.PropTypes.bool
    },

    getDefaultProps: function getDefaultProps() {
      return {
        visible: false
      };
    },

    getStateClassName: function getStateClassName() {
      switch (this.props.iconState) {
        case IconState.IN_PROGRESS:
          return prefixedClass('in-progress');
        case IconState.PENDING:
          return prefixedClass('gray');
        case IconState.SUCCESSFUL:
          return prefixedClass('green');
        default:
          return '';
      }
    },

    render: function render() {
      var classMap = {};
      var className;

      classMap[prefixedClass('visible')] = this.props.visible;
      className = classNames(prefixedClass('icon'), this.getStateClassName(), classMap);
      return React.createElement('div', { className: className });
    }
  });

  return Icon;
});