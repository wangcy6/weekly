

/**
 * Copyright 2015-2016 Evernote Corporation. All rights reserved.
 */
define(['require','react','classnames','elementPosition','resolve!i18n','EvernoteDragUtil','focus-tooltip-Direction','focus-tooltip-WithTooltip','focus-NotesView-AutomationTags','css!focus/NotesView/RemindersList/Reminder'],function (require) {
  

  var React = require('react');
  var classnames = require('classnames');
  var elementPosition = require('elementPosition');
  var i18n = require('resolve!i18n');
  var EvernoteDragUtil = require('EvernoteDragUtil');

  var Direction = require('focus-tooltip-Direction');
  var WithTooltip = require('focus-tooltip-WithTooltip');

  var AUTOMATION_TAGS = require('focus-NotesView-AutomationTags');
  var EDIT_HEIGHT = 40;
  var EDIT_RIGHT_PADDING = 12;

  var BASE_NAME = 'focus-NotesView-RemindersList-Reminder';

  require('css!focus/NotesView/RemindersList/Reminder');

  function prefixedClass(suffix) {
    return BASE_NAME + '-' + suffix;
  }

  /**
   * Represents a set of reminders for a particular notebook.
   */
  var Reminder = React.createClass({
    displayName: 'Reminder',

    propTypes: {
      dragging: React.PropTypes.bool,
      formattedReminderTime: React.PropTypes.string,
      guid: React.PropTypes.string.isRequired,
      markAsDone: React.PropTypes.func.isRequired,
      markAsUndone: React.PropTypes.func.isRequired,
      notebookGuid: React.PropTypes.string.isRequired,
      notebookName: React.PropTypes.string.isRequired,
      reminderDoneTime: React.PropTypes.instanceOf(Date),
      reminderOrder: React.PropTypes.number,
      reminderTime: React.PropTypes.instanceOf(Date),
      selectNote: React.PropTypes.func.isRequired,
      setReminderOrder: React.PropTypes.func.isRequired,
      showReminderSetDialog: React.PropTypes.func.isRequired,
      title: React.PropTypes.string.isRequired
    },

    onClick: function onClick() {
      if (this.props.guid) {
        this.props.selectNote(this.props.guid);
      }
    },

    onEditClick: function onEditClick(e) {
      e.stopPropagation();
      var pos = elementPosition(e.target);
      var topCord = pos.top + EDIT_HEIGHT;
      var leftCord = pos.left + (e.target.offsetWidth - EDIT_RIGHT_PADDING) / 2;
      this.props.showReminderSetDialog(this.props.guid, leftCord, topCord, 0);
    },

    onCheckboxClick: function onCheckboxClick(e) {
      e.stopPropagation();
      if (!this.props.reminderDoneTime) {
        this.props.markAsDone(this.props.guid);
      } else {
        this.props.markAsUndone(this.props.guid);
      }
    },

    render: function render() {
      var checkbox;
      if (!this.props.reminderDoneTime) {
        // Not yet complete
        checkbox = React.createElement(
          WithTooltip,
          {
            className: prefixedClass('checkboxTooltip'),
            arrowDirection: Direction.UP,
            label: i18n.L('Focus.remindersList.reminder.markdone')
          },
          React.createElement('div', {
            className: classnames(prefixedClass('checkbox-undone'), AUTOMATION_TAGS.REMINDER_DONE),
            onClick: this.onCheckboxClick
          })
        );
      } else {
        checkbox = React.createElement(
          WithTooltip,
          {
            className: prefixedClass('checkboxTooltip'),
            arrowDirection: Direction.UP,
            label: i18n.L('Focus.remindersList.reminder.done')
          },
          React.createElement('div', {
            className: classnames(prefixedClass('checkbox-done'), AUTOMATION_TAGS.REMINDER_DONE),
            onClick: this.onCheckboxClick
          })
        );
      }

      var reminderOptions = React.createElement(
        'div',
        {
          className: classnames(prefixedClass('reminderOptions'), AUTOMATION_TAGS.REMINDER_OPTIONS)
        },
        React.createElement(
          'div',
          {
            className: classnames(prefixedClass('edit'), AUTOMATION_TAGS.REMINDER_EDIT),
            onClick: this.onEditClick
          },
          i18n.L('Focus.remindersList.reminder.edit')
        ),
        checkbox
      );

      var reminderDate;
      if (this.props.reminderTime) {
        reminderDate = React.createElement(
          'div',
          { className: prefixedClass('reminderDate') },
          this.props.formattedReminderTime
        );
      }

      var classMap = {};
      classMap[prefixedClass('hasDate')] = this.props.reminderTime;
      classMap[prefixedClass('done')] = this.props.reminderDoneTime;
      classMap[prefixedClass('dragging')] = this.props.dragging;
      var classes = classnames(BASE_NAME, AUTOMATION_TAGS.REMINDER, classMap);
      return React.createElement(
        'div',
        {
          className: classes,
          onClick: this.onClick
        },
        React.createElement(
          'div',
          { className: prefixedClass('title') },
          this.props.title
        ),
        reminderDate,
        reminderOptions
      );
    }
  });

  var ReminderDraggable = EvernoteDragUtil.createDragClass({
    reactClass: Reminder,

    getDragItem: function getDragItem(props) {
      return {
        guid: props.guid
      };
    },

    dropItemFilter: function dropItemFilter(dropItem, props) {
      return dropItem.type === 'reminder-drop-area' && dropItem.notebookGuid === props.notebookGuid && dropItem.larger !== props.guid && dropItem.smaller !== props.guid;
    },

    addProps: function addProps(dragItemState) {
      return {
        dragging: dragItemState === EvernoteDragUtil.DRAG_STATE.DRAGGING
      };
    },

    getDropDescriptor: function getDropDescriptor(dragItem, dropItem) {
      return {
        dragItem: dragItem,
        dropItem: dropItem
      };
    },

    isDraggable: function isDraggable(props) {
      return props.isCustomSortOrder;
    },

    onDrop: function onDrop(dropDescriptor, props) {
      var dropItem = dropDescriptor.dropItem;
      if (dropItem) {
        props.reorderReminders(dropDescriptor.dragItem.guid, dropItem.larger, dropItem.smaller);
      }
    }

  });

  return ReminderDraggable;
});