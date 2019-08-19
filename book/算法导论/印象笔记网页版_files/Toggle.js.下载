

/**
 * Copyright 2015 Evernote Corporation. All rights reserved.
 */
define(['require','react','classnames','css!focus/NotesView/Menu/Toggle'],function (require) {
  

  var React = require('react');
  var classnames = require('classnames');

  require('css!focus/NotesView/Menu/Toggle');

  var BASE_NAME = 'Toggle';

  function prefixedClass(suffix) {
    return BASE_NAME + '-' + suffix;
  }

  var Toggle = React.createClass({
    displayName: 'Toggle',

    propTypes: {
      label: React.PropTypes.string.isRequired,
      onToggle: React.PropTypes.func.isRequired,
      value: React.PropTypes.bool.isRequired
    },

    onClick: function onClick(e) {
      e.stopPropagation();
      this.props.onToggle(!this.props.value);
    },

    render: function render() {
      var classMap = {};
      classMap[prefixedClass('true')] = this.props.value;
      classMap[prefixedClass('false')] = !this.props.value;

      return React.createElement(
        'div',
        {
          onClick: this.onClick,
          className: classnames(BASE_NAME, classMap)
        },
        this.props.label
      );
    }
  });

  return Toggle;
});