

/**
 * Copyright 2015-2016 Evernote Corporation. All rights reserved.
 *
 * A simple EvernoteDragUtil drop area container div with a constant dropItem.
 * Since all props are passed to the div, you can add a container css class and style
 * the div. The hoverProps will be conditionally added to the div only when it is hovered
 * over by an element can be dropped on this dropItem, so you can add a conditional
 * contianer css class if the drag item can be dropped on this element.
 */
define(['require','react','EvernoteDragUtil','lodash'],function (require) {
  

  var React = require('react');
  var EvernoteDragUtil = require('EvernoteDragUtil');
  var _ = require('lodash');

  // Same as React.DOM.div except it can be used with JSX, which EvernoteDragUtil needs
  var jsxDiv = React.createClass({
    displayName: 'jsxDiv',

    render: function render() {
      return React.createElement('div', this.props);
    }
  });

  var SimpleDropArea = EvernoteDragUtil.createDropAreaClass({
    reactClass: jsxDiv,

    propTypes: {
      // The constant dropItem object for the component instance
      dropItem: React.PropTypes.object,

      // Extra props (style, className) to pass to the div when hovered over
      hoverProps: React.PropTypes.object
    },

    getDropItem: function getDropItem(props) {
      return props.dropItem;
    },

    addProps: function addProps(dropItem, dropDescriptor, props) {
      if (dropDescriptor && _.isEqual(dropItem, dropDescriptor.dropItem)) {
        return props.hoverProps;
      } else {
        return {};
      }
    }
  });

  return SimpleDropArea;
});