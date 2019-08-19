

var _extends = Object.assign || function (target) { for (var i = 1; i < arguments.length; i++) { var source = arguments[i]; for (var key in source) { if (Object.prototype.hasOwnProperty.call(source, key)) { target[key] = source[key]; } } } return target; };

/**
 * Copyright 2015 Evernote Corporation. All rights reserved.
 */
define(['require','react','focus-NotesView-Menu-SelectorOption','css!focus/NotesView/Menu/Selector'],function (require) {
  

  var React = require('react');

  var SelectorOption = require('focus-NotesView-Menu-SelectorOption');

  require('css!focus/NotesView/Menu/Selector');

  var BASE_NAME = 'Selector';

  var Selector = React.createClass({
    displayName: 'Selector',

    propTypes: {
      onOptionSelected: React.PropTypes.func.isRequired,
      options: React.PropTypes.arrayOf(React.PropTypes.shape({
        isSelected: React.PropTypes.bool,
        label: React.PropTypes.string.isRequired,
        value: React.PropTypes.any.isRequired
      }))
    },

    onOptionSelected: function onOptionSelected(value) {
      this.props.onOptionSelected(value);
    },

    render: function render() {
      var selectorOptions = this.props.options.map(function (option, i) {
        return React.createElement(SelectorOption, _extends({
          key: i
        }, option, {
          onOptionSelected: this.onOptionSelected
        }));
      }, this);
      return React.createElement(
        'div',
        { className: BASE_NAME },
        selectorOptions
      );
    }
  });

  return Selector;
});