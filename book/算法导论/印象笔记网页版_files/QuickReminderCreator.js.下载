

/**
 * Copyright 2015-2016 Evernote Corporation. All rights reserved.
 */
define(['require','keyCode','react','classnames','resolve!i18n','css!focus/NotesView/RemindersList/QuickReminderCreator','focus-NotesView-AutomationTags'],function (require) {
  

  var KeyCode = require('keyCode');
  var React = require('react');
  var classnames = require('classnames');
  var i18n = require('resolve!i18n');
  require('css!focus/NotesView/RemindersList/QuickReminderCreator');

  var AUTOMATION_TAGS = require('focus-NotesView-AutomationTags');
  var BASE_NAME = 'focus-NotesView-RemindersList-QuickReminderCreator';

  function prefixedClass(suffix) {
    return BASE_NAME + '-' + suffix;
  }

  /**
   * Component for quickly creating a Reminder
   */
  var QuickReminderCreator = React.createClass({
    displayName: 'QuickReminderCreator',

    propTypes: {
      createReminder: React.PropTypes.func.isRequired,
      notebookGuid: React.PropTypes.string.isRequired,
      notebookName: React.PropTypes.string.isRequired
    },

    getInitialState: function getInitialState() {
      return { value: this.getDefaultText() };
    },

    componentWillReceiveProps: function componentWillReceiveProps(nextProps) {
      if (nextProps.notebookName !== this.props.notebookName) {
        this.setState({ value: this.getDefaultText(nextProps.notebookName) });
      }
    },

    getDefaultText: function getDefaultText(notebookName) {
      notebookName = notebookName || this.props.notebookName;
      return i18n.L('Focus.remindersList.reminder.addReminder', [notebookName]);
    },

    onBlur: function onBlur() {
      this.setState({
        editing: false,
        value: this.getDefaultText()
      });
    },

    onFocus: function onFocus() {
      this.setState({
        editing: true,
        value: undefined
      });
    },

    onKeyup: function onKeyup(e) {
      if (e.keyCode === KeyCode.ESCAPE) {
        var reminderInput = this.refs.quickNoteTitle;
        if (reminderInput) {
          reminderInput.blur();
        }
      }
    },

    onSubmit: function onSubmit(e) {
      e.preventDefault();
      var reminderInput = this.refs.quickNoteTitle;
      var reminderTitle = reminderInput.value;
      reminderInput.blur();
      if (reminderTitle !== '') {
        this.props.createReminder(reminderTitle, this.props.notebookGuid);
      }
    },

    render: function render() {
      var classMap = {};
      classMap[prefixedClass('editing')] = this.state.editing;
      var classes = classnames(prefixedClass('form'), AUTOMATION_TAGS.REMINDER_ADD_NEW, classMap);
      return React.createElement(
        'form',
        {
          className: classes,
          onSubmit: this.onSubmit
        },
        React.createElement('div', { className: prefixedClass('plusIcon') }),
        React.createElement('input', {
          ref: 'quickNoteTitle',
          readOnly: !this.state.editing,
          value: this.state.value,
          className: BASE_NAME,
          onBlur: this.onBlur,
          onFocus: this.onFocus,
          onKeyUp: this.onKeyup
        })
      );
    }
  });

  return QuickReminderCreator;
});