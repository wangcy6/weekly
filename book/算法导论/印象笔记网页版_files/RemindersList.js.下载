

/**
 * Copyright 2015-2016 Evernote Corporation. All rights reserved.
 */
define(['require','lodash','react','react-dom','classnames','resolve!i18n','Dropdown','focus-NotesView-RemindersList-NotebookReminders','focus-NotesView-RemindersList-QuickReminderCreator','focus-NotesView-Menu-Selector','focus-NotesView-Menu-Toggle','focus-NotesView-AutomationTags','css!focus/NotesView/RemindersList/RemindersList'],function (require) {
  

  var _ = require('lodash');
  var React = require('react');
  var ReactDOM = require('react-dom');
  var classnames = require('classnames');
  var i18n = require('resolve!i18n');

  var Dropdown = require('Dropdown');
  var NotebookReminders = require('focus-NotesView-RemindersList-NotebookReminders');
  var QuickReminderCreator = require('focus-NotesView-RemindersList-QuickReminderCreator');
  var Selector = require('focus-NotesView-Menu-Selector');
  var Toggle = require('focus-NotesView-Menu-Toggle');

  var AUTOMATION_TAGS = require('focus-NotesView-AutomationTags');
  var REMINDERS_LIST_KEY = 'TOP_LEVEL';

  require('css!focus/NotesView/RemindersList/RemindersList');

  var BASE_NAME = 'focus-NotesView-RemindersList';

  function prefixedClass(suffix) {
    return BASE_NAME + '-' + suffix;
  }

  /**
   * Shows and allows the user to manage Reminders associated with notes currently
   * displayed in the NotesList.
   */
  var RemindersList = React.createClass({
    displayName: 'RemindersList',

    propTypes: {
      expanded: React.PropTypes.bool,
      reminderViewOptions: React.PropTypes.shape({
        isShowRecentlyCompleted: React.PropTypes.bool.isRequired,
        isShowUpcoming: React.PropTypes.bool.isRequired,
        sortOptions: React.PropTypes.arrayOf(React.PropTypes.shape({
          isSelected: React.PropTypes.bool.isRequired,
          label: React.PropTypes.string.isRequired,
          value: React.PropTypes.any.isRequired
        })).isRequired
      }).isRequired,
      reminders: React.PropTypes.arrayOf(React.PropTypes.shape({
        guid: React.PropTypes.string.isRequired,
        notebookGuid: React.PropTypes.string.isRequired,
        notebookName: React.PropTypes.string.isRequired,
        reminderDoneTime: React.PropTypes.object, // Date
        reminderOrder: React.PropTypes.number,
        reminderTime: React.PropTypes.object, // Date
        title: React.PropTypes.string.isRequired
      })).isRequired,
      remindersListCollapsedState: React.PropTypes.object,
      remindersPresenter: React.PropTypes.shape({
        createReminder: React.PropTypes.func.isRequired,
        markAsDone: React.PropTypes.func.isRequired,
        markAsUndone: React.PropTypes.func.isRequired,
        reorderReminders: React.PropTypes.func.isRequired,
        selectNote: React.PropTypes.func.isRequired,
        setCollapsedReminder: React.PropTypes.func.isRequired,
        setRemindersListHeight: React.PropTypes.func.isRequired,
        setSortOrder: React.PropTypes.func.isRequired,
        showReminderSetDialog: React.PropTypes.func.isRequired,
        toggleShowRecentlyCompleted: React.PropTypes.func.isRequired,
        toggleShowUpcoming: React.PropTypes.func.isRequired
      }).isRequired,
      selectedNotebookGuid: React.PropTypes.string
    },

    componentDidMount: function componentDidMount() {
      this.setHeight();
    },

    shouldComponentUpdate: function shouldComponentUpdate(nextProps) {
      return this.props.reminders !== nextProps.reminders || this.props.selectedNotebookGuid !== nextProps.selectedNotebookGuid || this.props.expanded !== nextProps.expanded || this.props.remindersListCollapsedState !== nextProps.remindersListCollapsedState;
    },

    componentDidUpdate: function componentDidUpdate() {
      this.setHeight();
    },

    onHeaderClick: function onHeaderClick() {
      this.props.remindersPresenter.setCollapsedReminder(REMINDERS_LIST_KEY, !this.props.expanded);
    },

    onOptionSelected: function onOptionSelected(option) {
      this.props.remindersPresenter.setSortOrder(option);
      this.refs.dropdown.hideMenu();
    },

    onShowRecentlyCompletedToggle: function onShowRecentlyCompletedToggle() {
      this.props.remindersPresenter.toggleShowRecentlyCompleted();
    },

    onShowUpcomingToggled: function onShowUpcomingToggled() {
      this.props.remindersPresenter.toggleShowUpcoming();
    },

    groupRemindersByNotebook: function groupRemindersByNotebook() {
      var notebookReminders = {};
      this.props.reminders.forEach(function (reminder) {
        if (!notebookReminders[reminder.notebookGuid]) {
          notebookReminders[reminder.notebookGuid] = [];
        }
        notebookReminders[reminder.notebookGuid].push(reminder);
      });
      return _.values(notebookReminders).sort(function (a, b) {
        return a[0].notebookName > b[0].notebookName;
      });
    },

    setHeight: function setHeight() {
      var node = ReactDOM.findDOMNode(this);
      if (node) {
        var currentHeight = node.offsetHeight;
        if (currentHeight !== this.remindersListHeight) {
          this.remindersListHeight = currentHeight;
          this.props.remindersPresenter.setRemindersListHeight(currentHeight);
        }
      }
    },

    remindersListHeight: 0,

    render: function render() {
      if (!this.props.reminders || !this.props.reminders.length) {
        return null;
      }
      var classMap = {};
      classMap[prefixedClass('expanded')] = this.props.expanded;
      classMap[AUTOMATION_TAGS.REMINDER_LIST_EXPANDED] = this.props.expanded;
      classMap[AUTOMATION_TAGS.REMINDER_LIST_COLLAPSED] = !this.props.expanded;
      var classes = classnames(BASE_NAME, classMap);

      var notebookReminders = this.groupRemindersByNotebook().map(function (nbReminders, i) {
        var notebookGuid = nbReminders[0].notebookGuid;
        var isCollapsed = !!this.props.remindersListCollapsedState[notebookGuid];
        return React.createElement(NotebookReminders, {
          key: i,
          reminders: nbReminders,
          collapsed: isCollapsed,
          singleNotebookView: !!this.props.selectedNotebookGuid,
          markAsDone: this.props.remindersPresenter.markAsDone,
          markAsUndone: this.props.remindersPresenter.markAsUndone,
          selectNote: this.props.remindersPresenter.selectNote,
          showReminderSetDialog: this.props.remindersPresenter.showReminderSetDialog,
          reorderReminders: this.props.remindersPresenter.reorderReminders,
          setCollapsedReminder: this.props.remindersPresenter.setCollapsedReminder,
          isCustomSortOrder: this.props.reminderViewOptions.sortOptions[1].isSelected
        });
      }, this);

      var rightBadge;
      var badgeClasses = prefixedClass('rightBadge');
      if (!this.props.expanded) {
        badgeClasses = classnames(badgeClasses, prefixedClass('numReminders'), AUTOMATION_TAGS.REMINDER_COUNT);
        rightBadge = React.createElement(
          'div',
          { className: badgeClasses },
          this.props.reminders.length
        );
      } else {
        var optionsButton = React.createElement('div', {
          className: prefixedClass('reminderOptions')
        });
        rightBadge = React.createElement(
          'div',
          { className: badgeClasses },
          React.createElement(
            Dropdown,
            {
              buttonContent: optionsButton,
              isMenuPositionFixed: true,
              ref: 'dropdown'
            },
            React.createElement(
              'legend',
              null,
              i18n.L('Focus.remindersList.options.sortBy.label')
            ),
            React.createElement(Selector, {
              onOptionSelected: this.onOptionSelected,
              options: this.props.reminderViewOptions.sortOptions
            }),
            React.createElement(
              'legend',
              null,
              i18n.L('Focus.remindersList.options.viewOptions.label')
            ),
            React.createElement(Toggle, {
              label: i18n.L('Focus.remindersList.options.viewOptions.showUpcoming'),
              onToggle: this.onShowUpcomingToggled,
              value: this.props.reminderViewOptions.isShowUpcoming
            }),
            React.createElement(Toggle, {
              label: i18n.L('Focus.remindersList.options.viewOptions.showRecentlyCompleted'),
              onToggle: this.onShowRecentlyCompletedToggle,
              value: this.props.reminderViewOptions.isShowRecentlyCompleted
            })
          )
        );
      }

      var quickReminderCreator;
      if (this.props.selectedNotebookGuid) {
        quickReminderCreator = React.createElement(QuickReminderCreator, {
          createReminder: this.props.remindersPresenter.createReminder,
          notebookName: this.props.reminders[0].notebookName,
          notebookGuid: this.props.selectedNotebookGuid
        });
      }

      return React.createElement(
        'div',
        { className: classes },
        React.createElement(
          'div',
          {
            className: prefixedClass('remindersHeader'),
            onClick: this.onHeaderClick
          },
          React.createElement(
            'div',
            {
              className: classnames(prefixedClass('remindersTitle'), AUTOMATION_TAGS.REMINDER_SECTION_TITLE)
            },
            i18n.L('Focus.remindersList.reminders')
          ),
          rightBadge
        ),
        React.createElement(
          'div',
          { className: prefixedClass('notebookReminders') },
          quickReminderCreator,
          notebookReminders
        )
      );
    }
  });

  return RemindersList;
});