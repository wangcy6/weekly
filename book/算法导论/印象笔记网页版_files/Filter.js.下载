

/**
 * Copyright 2015-2016 Evernote Corporation. All rights reserved.
 */
define(['require','resolve!i18n','keyCode','react','css!focus/drawer/Filter'],function (require) {
  

  var i18n = require('resolve!i18n');
  var KeyCode = require('keyCode');
  var React = require('react');
  require('css!focus/drawer/Filter');

  function prefixedClass(suffix) {
    return 'focus-drawer-Filter-' + suffix;
  }

  /**
   * A search input text element with custom placeholder text, showing a magnifying
   * glass asset and placeholder text centered in the input element.
   */
  var Filter = React.createClass({
    displayName: 'Filter',

    propTypes: {
      filterValue: React.PropTypes.string.isRequired,
      handleEnter: React.PropTypes.func,
      setFilterValue: React.PropTypes.func.isRequired
    },

    getDefaultProps: function getDefaultProps() {
      return {
        handleEnter: function handleEnter() {}
      };
    },

    onChangeInput: function onChangeInput(event) {
      this.props.setFilterValue(event.target.value);
    },

    onClickClearButton: function onClickClearButton() {
      this.props.setFilterValue('');
    },

    onClickPlaceholder: function onClickPlaceholder() {
      this.refs.input.focus();
    },

    onKeyUpInput: function onKeyUpInput(event) {
      if (KeyCode.ENTER === event.keyCode) {
        if (this.props.handleEnter) {
          this.props.handleEnter();
        }
      }
    },

    render: function render() {
      return React.createElement(
        'div',
        { className: prefixedClass('container') },
        !this.props.filterValue && React.createElement(
          'div',
          {
            className: prefixedClass('placeholder'),
            onClick: this.onClickPlaceholder
          },
          React.createElement('div', { className: prefixedClass('search-icon') }),
          React.createElement(
            'div',
            { className: prefixedClass('placeholder-text') },
            i18n.L('Focus.drawer.inputPlaceholder.tag')
          )
        ),
        React.createElement('input', {
          ref: 'input',
          type: 'text',
          value: this.props.filterValue,
          className: prefixedClass('input'),
          onChange: this.onChangeInput,
          onKeyUp: this.onKeyUpInput
        }),
        this.props.filterValue && React.createElement('div', {
          className: prefixedClass('search-clear'),
          onClick: this.onClickClearButton
        })
      );
    }
  });

  return Filter;
});