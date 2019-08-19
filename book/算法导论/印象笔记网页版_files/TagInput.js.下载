

/**
 * Copyright 2015-2016 Evernote Corporation. All rights reserved.
 */
define(['require','classnames','keyCode','Limits','react','css!focus/drawer/TagsDrawer/TagInput'],function (require) {
  

  var classNames = require('classnames');
  var KeyCode = require('keyCode');
  var Limits = require('Limits');
  var React = require('react');
  require('css!focus/drawer/TagsDrawer/TagInput');

  function prefixedClass(suffix) {
    return 'focus-drawer-TagsDrawer-TagInput-' + suffix;
  }

  /**
   * A wide input field styled like a tag with a "confirm" button.
   */
  var TagInput = React.createClass({
    displayName: 'TagInput',

    propTypes: {
      cancelEdit: React.PropTypes.func.isRequired,
      editMode: React.PropTypes.bool.isRequired,
      rename: React.PropTypes.func.isRequired,
      tag: React.PropTypes.shape({
        children: React.PropTypes.array,
        key: React.PropTypes.string,
        name: React.PropTypes.string
      }).isRequired
    },

    getInitialState: function getInitialState() {
      return {
        inputValue: this.props.tag.name,
        preventCancelOnBlur: false
      };
    },

    componentWillReceiveProps: function componentWillReceiveProps(nextProps) {
      var self = this;
      if (!this.props.editMode && nextProps.editMode) {
        this.setState({ inputValue: nextProps.tag.name });
        this.focusTimeoutId = setTimeout(function () {
          var nameLen = self.props.tag.name.length;
          self.refs.input.focus();
          self.refs.input.setSelectionRange(nameLen, nameLen);
        }, 550); // half-a-second (transition duration) with a bit of a grace period
      }
    },

    componentWillUnmount: function componentWillUnmount() {
      clearTimeout(this.focusTimeoutId);
      this.focusTimeoutId = null;
    },

    focusTimeoutId: null,

    onMouseDownConfirm: function onMouseDownConfirm() {
      var self = this;
      this.setState({ preventCancelOnBlur: true });
      if (this.props.tag.name !== this.state.inputValue) {
        this.props.rename(this.props.tag.key, this.state.inputValue);
        // refocus input in case of rename error
        this.focusTimeoutId = setTimeout(function () {
          self.refs.input.focus();
        }, 1);
      } else {
        this.props.cancelEdit();
      }
    },

    onBlurInput: function onBlurInput() {
      if (this.state.preventCancelOnBlur) {
        this.setState({ preventCancelOnBlur: false });
      } else {
        this.props.cancelEdit();
      }
    },

    onChangeInput: function onChangeInput(event) {
      if (event.target.value.length <= Limits.EDAM_TAG_NAME_LEN_MAX) {
        this.setState({ inputValue: event.target.value });
      }
    },

    onKeyUpInput: function onKeyUpInput(event) {
      if (event.keyCode === KeyCode.ESCAPE) {
        this.props.cancelEdit();
      } else if (event.keyCode === KeyCode.ENTER) {
        this.props.rename(this.props.tag.key, this.state.inputValue);
      }
    },

    render: function render() {
      var confirmClassMap = {};
      var inputClassMap = {};
      var positionerClassMap = {};
      var confirmClasses;
      var inputClasses;
      var positionerClasses;

      positionerClassMap[prefixedClass('edit-mode')] = this.props.editMode;
      positionerClasses = classNames(prefixedClass('input-positioner'), positionerClassMap);

      inputClassMap[prefixedClass('edit-mode')] = this.props.editMode;
      inputClasses = classNames(prefixedClass('input-container'), inputClassMap);

      confirmClassMap[prefixedClass('hidden')] = !this.props.editMode;
      confirmClasses = classNames(prefixedClass('icon'), prefixedClass('confirm-icon'), confirmClassMap);

      return React.createElement(
        'div',
        { className: positionerClasses },
        React.createElement(
          'div',
          { className: inputClasses },
          React.createElement('input', {
            ref: 'input',
            type: 'text',
            value: this.state.inputValue,
            onBlur: this.onBlurInput,
            onChange: this.onChangeInput,
            onKeyUp: this.onKeyUpInput,
            className: prefixedClass('input')
          })
        ),
        React.createElement('div', { onMouseDown: this.onMouseDownConfirm, className: confirmClasses })
      );
    }
  });

  return TagInput;
});