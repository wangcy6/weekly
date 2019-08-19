

/**
 * Copyright 2015 Evernote Corporation. All rights reserved.
 */
define(['require','react','classnames'],function (require) {
  

  var React = require('react');
  var classnames = require('classnames');

  var BASE_NAME = 'SelectorOption';

  function prefixedClass(suffix) {
    return BASE_NAME + '-' + suffix;
  }

  var SelectorOption = React.createClass({
    displayName: 'SelectorOption',

    propTypes: {
      isSelected: React.PropTypes.bool,
      label: React.PropTypes.string.isRequired,
      onOptionSelected: React.PropTypes.func.isRequired,
      value: React.PropTypes.any.isRequired
    },

    getDefaultProps: function getDefaultProps() {
      return {
        isSelected: false
      };
    },

    onClick: function onClick(e) {
      e.stopPropagation();
      if (!this.props.isSelected) {
        this.props.onOptionSelected(this.props.value);
      }
    },

    render: function render() {
      var classMap = {};
      classMap[prefixedClass('selected')] = this.props.isSelected;
      return React.createElement(
        'div',
        {
          className: classnames(BASE_NAME, classMap),
          onClick: this.onClick
        },
        this.props.label
      );
    }
  });

  return SelectorOption;
});