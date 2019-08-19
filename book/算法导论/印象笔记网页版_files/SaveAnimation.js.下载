

/**
 * Copyright 2015-2016 Evernote Corporation. All rights reserved.
 */
define(['require','focus-editor-SaveAnimation-Icon','focus-editor-SaveAnimation-IconState','react','css!focus/editor/SaveAnimation/SaveAnimation'],function (require) {
  

  var Icon = require('focus-editor-SaveAnimation-Icon');
  var IconState = require('focus-editor-SaveAnimation-IconState');
  var React = require('react');
  require('css!focus/editor/SaveAnimation/SaveAnimation');

  function prefixedClass(suffix) {
    return 'focus-editor-SaveAnimation-SaveAnimation-' + suffix;
  }

  /**
   * A small icon that can show four states: idle, pending, in progress, and successful.
   * The idle state is empty. The pending state is a gray checkmark. The in progress state
   * is an animated green circle around the gray checkmark, and the successful state is a
   * green checkmark.
   */
  var SaveAnimation = React.createClass({
    displayName: 'SaveAnimation',

    propTypes: {
      iconState: React.PropTypes.oneOf([IconState.ERROR, IconState.IDLE, IconState.IN_PROGRESS, IconState.PENDING, IconState.SUCCESSFUL]).isRequired
    },

    renderIcons: function renderIcons(states) {
      return states.map(function (iconState, idx) {
        return React.createElement(Icon, {
          key: idx,
          iconState: iconState,
          visible: this.props.iconState === iconState
        });
      }, this);
    },

    render: function render() {
      return React.createElement(
        'div',
        { className: prefixedClass('container') },
        this.renderIcons([IconState.PENDING, IconState.IN_PROGRESS, IconState.SUCCESSFUL])
      );
    }
  });

  return SaveAnimation;
});