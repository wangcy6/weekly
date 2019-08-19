

/**
 * Copyright 2015 Evernote Corporation. All rights reserved.
 */
define(['require','react','classnames','focus-NotesView-RemindersList-Reminder','SimpleDropArea','focus-NotesView-AutomationTags'],function (require) {
  

  var React = require('react');
  var classnames = require('classnames');

  var Reminder = require('focus-NotesView-RemindersList-Reminder');
  var SimpleDropArea = require('SimpleDropArea');

  var AUTOMATION_TAGS = require('focus-NotesView-AutomationTags');
  var BASE_NAME = 'focus-NotesView-NotebookReminders';

  function prefixedClass(suffix) {
    return BASE_NAME + '-' + suffix;
  }

  function getDate(date) {
    if (!date) {
      return null;
    }
    return new Date(date);
  }

  /**
   * Represents a set of reminders for a particular notebook.
   */
  var NotebookReminders = React.createClass({
    displayName: 'NotebookReminders',

    propTypes: {
      collapsed: React.PropTypes.bool,
      isCustomSortOrder: React.PropTypes.bool,
      markAsDone: React.PropTypes.func.isRequired,
      markAsUndone: React.PropTypes.func.isRequired,
      reminders: React.PropTypes.arrayOf(React.PropTypes.shape({
        formattedReminderTime: React.PropTypes.string,
        guid: React.PropTypes.string.isRequired,
        notebookGuid: React.PropTypes.string.isRequired,
        notebookName: React.PropTypes.string.isRequired,
        reminderDoneTime: React.PropTypes.object, // Date
        reminderOrder: React.PropTypes.number,
        reminderTime: React.PropTypes.object, // Date
        title: React.PropTypes.string.isRequired
      })).isRequired,
      reorderReminders: React.PropTypes.func.isRequired,
      selectNote: React.PropTypes.func.isRequired,
      setCollapsedReminder: React.PropTypes.func.isRequired,
      showReminderSetDialog: React.PropTypes.func.isRequired,
      singleNotebookView: React.PropTypes.bool.isRequired
    },

    onHeaderClick: function onHeaderClick() {
      var notebookGuid = this.props.reminders[0].notebookGuid;
      this.props.setCollapsedReminder(notebookGuid, !this.props.collapsed);
    },

    /**
     * Generates a DropArea.
     * @param {String} notebookGuid
     * @param {String} larger - guid of larger note
     * @param {String} smaller - guid of smaller note
     * @param {Number} key
     */
    dropArea: function dropArea(notebookGuid, larger, smaller, key) {
      var dropItem = {
        type: 'reminder-drop-area',
        notebookGuid: notebookGuid,
        larger: larger,
        smaller: smaller
      };
      var hoverProps = {
        className: classnames(prefixedClass('DropArea'), prefixedClass('DropAreaHovered'))
      };
      return React.createElement(
        'div',
        {
          key: 'dropArea-' + key,
          className: prefixedClass('DropAreaContainer')
        },
        React.createElement(
          SimpleDropArea,
          {
            className: prefixedClass('DropArea'),
            dropItem: dropItem,
            hoverProps: hoverProps
          },
          React.createElement('div', { className: prefixedClass('DropAreaLine') })
        )
      );
    },

    sortByCustomOrder: function sortByCustomOrder(a, b) {
      if (a.reminderOrder > b.reminderOrder) {
        return -1;
      }
      if (a.reminderOrder < b.reminderOrder) {
        return 1;
      }
      return 0;
    },

    sortByDueDate: function sortByDueDate(a, b) {
      if (a.reminderTime && !b.reminderTime || a.reminderTime < b.reminderTime) {
        return -1;
      }
      if (b.reminderTime && !a.reminderTime || a.reminderTime > b.reminderTime) {
        return 1;
      }
      return 0;
    },

    render: function render() {
      var classMap = {};
      classMap[prefixedClass('expanded')] = !this.props.collapsed;
      var classes = classnames(BASE_NAME, classMap);

      var reminders;
      if (!this.props.collapsed || this.props.singleNotebookView) {
        reminders = [];
        var sortFn = this.props.isCustomSortOrder ? this.sortByCustomOrder : this.sortByDueDate;
        var sortedReminders = this.props.reminders.sort(sortFn);
        if (this.props.isCustomSortOrder && sortedReminders.length >= 1) {
          reminders.push(this.dropArea(sortedReminders[0].notebookGuid, null, sortedReminders[0].guid, -1));
        }
        for (var i = 0; i < sortedReminders.length; i++) {
          var reminder = sortedReminders[i];
          reminders.push(React.createElement(Reminder, {
            formattedReminderTime: reminder.formattedReminderTime,
            guid: reminder.guid,
            isCustomSortOrder: this.props.isCustomSortOrder,
            key: i,
            markAsDone: this.props.markAsDone,
            markAsUndone: this.props.markAsUndone,
            notebookGuid: reminder.notebookGuid,
            notebookName: reminder.notebookName,
            reminderDoneTime: getDate(reminder.reminderDoneTime),
            reminderOrder: reminder.reminderOrder,
            reminderTime: getDate(reminder.reminderTime),
            reorderReminders: this.props.reorderReminders,
            selectNote: this.props.selectNote,
            showReminderSetDialog: this.props.showReminderSetDialog,
            title: reminder.title
          }));
          if (this.props.isCustomSortOrder) {
            var smaller = i !== sortedReminders.length - 1 ? sortedReminders[i + 1].guid : null;
            reminders.push(this.dropArea(reminder.notebookGuid, reminder.guid, smaller, i));
          }
        }
      }

      var notebookHeader;
      var notebookHeaderClassMap = {};
      notebookHeaderClassMap[AUTOMATION_TAGS.REMINDER_NOTEBOOK_EXPANDED] = !this.props.collapsed;
      notebookHeaderClassMap[AUTOMATION_TAGS.REMINDER_NOTEBOOK_COLLAPSED] = this.props.collapsed;
      if (!this.props.singleNotebookView) {
        notebookHeader = React.createElement(
          'div',
          {
            className: classnames(prefixedClass('notebookTitle'), AUTOMATION_TAGS.REMINDER_NOTEBOOK_TITLE, notebookHeaderClassMap),
            onClick: this.onHeaderClick
          },
          this.props.reminders[0].notebookName,
          React.createElement('div', { className: prefixedClass('notebookTitleDownCaret') })
        );
      }

      return React.createElement(
        'div',
        { className: classes },
        notebookHeader,
        React.createElement(
          'div',
          { className: 'reminders' },
          reminders
        )
      );
    }
  });

  return NotebookReminders;
});