

/**
 * Copyright 2015 Evernote Corporation. All rights reserved.
 */
define(['require','react','classnames','elementPosition','resolve!i18n','focus-NotesView-NotesList-HoverIcon','focus-NotesView-AutomationTags'],function (require) {
  

  var React = require('react');
  var classnames = require('classnames');
  var elementPosition = require('elementPosition');
  var i18n = require('resolve!i18n');

  var HoverIcon = require('focus-NotesView-NotesList-HoverIcon');

  var AUTOMATION_TAGS = require('focus-NotesView-AutomationTags');

  var REMINDER_ICON_HEIGHT = 8 + 24; // top margin + icon height
  var REMINDER_ICON_WIDTH = 24;

  function prefixedClass(suffix) {
    return 'focus-NotesView-Note-' + suffix;
  }

  /**
   * Component that manages which icons should appear over a Note on user hover.
   */
  var HoverOptions = React.createClass({
    displayName: 'HoverOptions',

    propTypes: {
      addShortcut: React.PropTypes.func.isRequired,
      allowsDelete: React.PropTypes.bool.isRequired,
      allowsExpunge: React.PropTypes.bool.isRequired,
      allowsReminder: React.PropTypes.bool.isRequired,
      allowsRestore: React.PropTypes.bool.isRequired,
      allowsShare: React.PropTypes.bool.isRequired,
      allowsShortcut: React.PropTypes.bool.isRequired,
      expunge: React.PropTypes.func.isRequired,
      guid: React.PropTypes.string.isRequired,
      hasReminder: React.PropTypes.bool.isRequired,
      hasShortcut: React.PropTypes.bool.isRequired,
      inTrash: React.PropTypes.bool.isRequired,
      remove: React.PropTypes.func.isRequired,
      removeShortcut: React.PropTypes.func.isRequired,
      restore: React.PropTypes.func.isRequired,
      sendByWorkChat: React.PropTypes.func.isRequired,
      showReminderSetDialog: React.PropTypes.func.isRequired
    },

    onShareClick: function onShareClick(e) {
      e.stopPropagation();
      this.props.sendByWorkChat(this.props.guid);
    },

    onReminderClick: function onReminderClick(e) {
      e.stopPropagation();
      var pos = elementPosition(e.target);
      var topCord = pos.top + REMINDER_ICON_HEIGHT;
      var leftCord = pos.left + REMINDER_ICON_WIDTH / 2;
      this.props.showReminderSetDialog(this.props.guid, leftCord, topCord, 0);
      this.setState({ hover: true });
    },

    onShortcutClick: function onShortcutClick(e) {
      e.stopPropagation();
      if (!this.props.hasShortcut) {
        this.props.addShortcut(this.props.guid);
      } else {
        this.props.removeShortcut(this.props.guid);
      }
    },

    onDeleteClick: function onDeleteClick(e) {
      e.stopPropagation();
      this.props.remove(this.props.guid);
    },

    onEraseClick: function onEraseClick(e) {
      e.stopPropagation();
      this.props.expunge(this.props.guid);
    },

    onRestoreClick: function onRestoreClick(e) {
      e.stopPropagation();
      this.props.restore(this.props.guid);
    },

    render: function render() {
      var tooltipText;
      var classes;
      if (this.props.inTrash) {
        // Trash Options
        var expungeButton;
        var restoreButton;
        if (this.props.allowsExpunge) {
          expungeButton = React.createElement(
            'button',
            {
              className: prefixedClass('hoverButton'),
              onClick: this.onEraseClick
            },
            i18n.L('Focus.notesView.trash.erase')
          );
        }
        if (this.props.allowsRestore) {
          restoreButton = React.createElement(
            'button',
            {
              className: prefixedClass('hoverButton'),
              onClick: this.onRestoreClick
            },
            i18n.L('Focus.notesView.trash.restore')
          );
        }
        return React.createElement(
          'div',
          null,
          expungeButton,
          restoreButton
        );
      }
      // Normal Hover Options
      var shareIcon;
      if (this.props.allowsShare) {
        classes = classnames(prefixedClass('workChat'), AUTOMATION_TAGS.NOTE_SHARE_BUTTON);
        shareIcon = React.createElement(HoverIcon, {
          clickHandler: this.onShareClick,
          tooltip: i18n.L('Focus.notesView.tooltip.shareNote'),
          className: classes
        });
      }

      var reminderIcon;
      if (this.props.allowsReminder) {
        classes = classnames(prefixedClass('reminder'), AUTOMATION_TAGS.NOTE_REMINDER_BUTTON, { active: this.props.hasReminder });
        tooltipText = this.props.hasReminder ? i18n.L('Focus.notesView.tooltip.editReminder') : i18n.L('Focus.notesView.tooltip.setReminder');
        reminderIcon = React.createElement(HoverIcon, {
          clickHandler: this.onReminderClick,
          tooltip: tooltipText,
          className: classes
        });
      }

      var shortcutIcon;
      if (this.props.allowsShortcut) {
        classes = classnames(prefixedClass('shortcut'), AUTOMATION_TAGS.NOTE_SHORTCUT_BUTTON, { active: this.props.hasShortcut });
        tooltipText = this.props.hasShortcut ? i18n.L('Focus.notesView.tooltip.removeShortcut') : i18n.L('Focus.notesView.tooltip.addShortcut');
        shortcutIcon = React.createElement(HoverIcon, {
          clickHandler: this.onShortcutClick,
          tooltip: tooltipText,
          className: classes
        });
      }

      var deleteIcon;
      if (this.props.allowsDelete) {
        classes = classnames(prefixedClass('delete'), AUTOMATION_TAGS.NOTE_DELETE_BUTTON);
        deleteIcon = React.createElement(HoverIcon, {
          clickHandler: this.onDeleteClick,
          tooltip: i18n.L('Focus.notesView.tooltip.deleteNote'),
          className: classes
        });
      }

      return React.createElement(
        'div',
        { className: prefixedClass('normalNoteOptions') },
        shareIcon,
        reminderIcon,
        shortcutIcon,
        deleteIcon
      );
    }
  });

  return HoverOptions;
});