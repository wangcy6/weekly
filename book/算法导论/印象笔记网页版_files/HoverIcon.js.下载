

/**
 * Copyright 2015 Evernote Corporation. All rights reserved.
 */
define(['require','react','classnames','focus-tooltip-Direction','focus-tooltip-WithTooltip'],function (require) {
  

  var React = require('react');
  var classnames = require('classnames');

  var Direction = require('focus-tooltip-Direction');
  var WithTooltip = require('focus-tooltip-WithTooltip');

  function prefixedClass(suffix) {
    return 'focus-NotesView-Note-' + suffix;
  }

  /**
   * Icon shown in the overlay that appears over a note on user hover.
   */
  var HoverIcon = React.createClass({
    displayName: 'HoverIcon',

    propTypes: {
      className: React.PropTypes.string,
      clickHandler: React.PropTypes.func.isRequired,
      tooltip: React.PropTypes.string.isRequired
    },

    render: function render() {
      var classes = classnames(prefixedClass('hoverIcon'), this.props.className);
      return React.createElement(
        WithTooltip,
        {
          className: prefixedClass('iconContainer'),
          arrowDirection: Direction.UP,
          label: this.props.tooltip
        },
        React.createElement('div', {
          className: classes,
          onClick: this.props.clickHandler
        })
      );
    }
  });

  return HoverIcon;
});